// DecompileMore.java - decompile additional helper functions
// @category ESP32

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;

public class DecompileMore extends GhidraScript {

    private Address addr(long a) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(a);
    }

    @Override
    public void run() throws Exception {
        String outDir = System.getenv("ESP32_OUT_DIR");
        if (outDir == null) outDir = "C:\\Users\\ksanj\\Downloads\\combochannel\\extracted\\ghidra";
        File decompDir = new File(outDir, "decomp");
        decompDir.mkdirs();
        File report = new File(outDir, "GHIDRA_MORE.md");
        PrintWriter pw = new PrintWriter(new FileWriter(report));

        long[] targets = {
            0x400d30d8L, // setChannel?
            0x400d5e80L, // random channel?
            0x400d2868L, // LED blink?
            0x400d3448L, // radio begin?
            0x400d35d0L, // SPI begin bus?
            0x400d35fcL, // SPI pins?
            0x400d32c4L,
            0x400d3180L,
            0x400d34b0L,
            0x400d32f4L,
            0x400d3328L,
            0x400d3460L,
            0x400d34d8L, // startConstCarrier?
            0x400d3590L,
            0x400d31d8L,
            0x400d31fcL,
            0x400d6214L, // pinMode LED
            0x400d36e4L,
            0x400d6724L, // delay?
            0x400d5d30L, // println
            0x400d5d1cL,
            0x400d3120L, // isChipConnected?
            0x400d51fcL, // display clear
            0x400d56b4L, // display display()
            0x400d4fd8L,
            0x400d5d08L,
        };

        // Also find callers of state handlers
        long[] stateFns = {0x400d28d8L, 0x400d2920L, 0x400d2968L, 0x400d29b0L, 0x400d2a24L, 0x400d236cL, 0x400d2dacL};
        ReferenceManager rm = currentProgram.getReferenceManager();
        FunctionManager fm = currentProgram.getFunctionManager();
        Set<Long> extra = new HashSet<>();

        pw.println("# Additional decompilation & call graph");
        pw.println();
        for (long t : stateFns) {
            pw.println("## Callers of " + String.format("0x%X", t));
            ReferenceIterator it = rm.getReferencesTo(addr(t));
            int n = 0;
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = fm.getFunctionContaining(r.getFromAddress());
                pw.println("- from " + r.getFromAddress() + " in " + (f != null ? f.getName() + " @ " + f.getEntryPoint() : "?") + " type=" + r.getReferenceType());
                if (f != null) extra.add(f.getEntryPoint().getOffset());
                n++;
                if (n > 30) break;
            }
            if (n == 0) pw.println("- (none found)");
            pw.println();
        }

        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        for (long t : targets) extra.add(t);

        for (long e : extra) {
            Function f = fm.getFunctionAt(addr(e));
            if (f == null) f = createFunction(addr(e), null);
            if (f == null) {
                pw.println("## FAIL create " + String.format("0x%X", e));
                continue;
            }
            // rename known
            String rename = null;
            if (e == 0x400d30d8L) rename = "nrf_setChannel";
            if (e == 0x400d5e80L) rename = "randomChannel";
            if (e == 0x400d2868L) rename = "statusLedBlink";
            if (e == 0x400d3448L) rename = "nrf_begin";
            if (e == 0x400d35d0L) rename = "spi_setBus";
            if (e == 0x400d35fcL) rename = "spi_setPins";
            if (e == 0x400d34d8L) rename = "nrf_startConstCarrier";
            if (e == 0x400d6214L) rename = "gpio_write_or_mode";
            if (e == 0x400d6724L) rename = "delay_ms";
            if (e == 0x400d5d30L) rename = "Serial_print";
            if (e == 0x400d5d1cL) rename = "Serial_println_empty";
            if (e == 0x400d3120L) rename = "nrf_isChipConnected";
            if (e == 0x400d28d8L) rename = "enterState_BT";
            if (e == 0x400d2920L) rename = "enterState_BLE";
            if (e == 0x400d2968L) rename = "enterState_WiFi";
            if (e == 0x400d29b0L) rename = "enterState_RC";
            if (e == 0x400d2a24L) rename = "enterState_Idle";
            if (e == 0x400d2dacL) rename = "drawModeBitmap";
            if (e == 0x400d236cL) rename = "radioTask";
            if (rename != null) {
                try { f.setName(rename, ghidra.program.model.symbol.SourceType.USER_DEFINED); } catch (Exception ex) {}
            }

            DecompileResults res = ifc.decompileFunction(f, 90, new ConsoleTaskMonitor());
            String c = "<fail>";
            if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                c = res.getDecompiledFunction().getC();
            } else if (res != null) {
                c = "<error: " + res.getErrorMessage() + ">";
            }
            String safe = f.getName().replaceAll("[^A-Za-z0-9_]", "_");
            File cf = new File(decompDir, String.format("%s_%s.c", f.getEntryPoint(), safe));
            try (PrintWriter cw = new PrintWriter(new FileWriter(cf))) {
                cw.println("// " + f.getEntryPoint() + " " + f.getName());
                cw.println(c);
            }
            pw.println("## `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
            pw.println("```c");
            String[] lines = c.split("\n");
            for (int i = 0; i < Math.min(lines.length, 100); i++) pw.println(lines[i]);
            if (lines.length > 100) pw.println("// truncated");
            pw.println("```");
            pw.println();
            println("Decompiled " + f.getName());
        }

        ifc.dispose();
        pw.close();
        println("Wrote " + report.getAbsolutePath());
    }
}
