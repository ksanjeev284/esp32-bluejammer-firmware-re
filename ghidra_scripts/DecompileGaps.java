// Decompile remaining app gaps: OLED init, radio ctor, setup callees
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
import java.io.*;
import java.util.*;

public class DecompileGaps extends GhidraScript {
    private Address A(long a) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(a);
    }

    @Override
    public void run() throws Exception {
        String out = System.getenv("ESP32_OUT_DIR");
        if (out == null) out = "C:\\Users\\ksanj\\Downloads\\combochannel\\extracted\\ghidra";
        File dir = new File(out, "decomp");
        dir.mkdirs();
        PrintWriter pw = new PrintWriter(new FileWriter(new File(out, "GHIDRA_GAPS.md")));

        long[] seeds = {
            0x400d2714L, // setup
            0x400d2d68L, // called from setup before splash
            0x400d6150L,
            0x400d3e5cL,
            0x400d5ac4L, // Serial.begin
            0x400d6198L, // pinMode
            0x400d380cL, // loop display?
            0x400d2844L,
            0x400d337cL, // begin inner
            0x400d3144L,
            0x400d3034L, // writeRegister
            0x400d2fccL, // readRegister
            0x400d2f4cL, // ce write?
            0x400d31d8L,
            0x400d31fcL,
            0x400d3590L,
            0x400d32c4L,
            0x400949f4L, // xTaskCreate
            0x400d2bfcL, // loop
            0x400d6224L, // digitalRead
        };

        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Set<Long> all = new LinkedHashSet<>();
        for (long s : seeds) all.add(s);

        // callers of setup-ish and callees one level
        for (long s : new long[]{0x400d2714L, 0x400d2bfcL, 0x400d2d68L}) {
            Function f = fm.getFunctionAt(A(s));
            if (f == null) f = createFunction(A(s), null);
            if (f == null) continue;
            // find call instructions in body - use refs from function
            var it = f.getBody().getAddresses(true);
            while (it.hasNext()) {
                Address a = it.next();
                for (Reference r : rm.getReferencesFrom(a)) {
                    if (r.getReferenceType().isCall()) {
                        all.add(r.getToAddress().getOffset());
                    }
                }
            }
            // who calls this
            ReferenceIterator ri = rm.getReferencesTo(A(s));
            while (ri.hasNext()) {
                Reference r = ri.next();
                Function cf = fm.getFunctionContaining(r.getFromAddress());
                if (cf != null) all.add(cf.getEntryPoint().getOffset());
            }
        }

        // scan for functions that take immediate-like CE 16/22 - dump xrefs to data
        pw.println("# Gap fill decompilation");
        pw.println("Targets: " + all.size());

        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        int count = 0;
        for (long e : all) {
            if (e < 0x40080000L || e > 0x40170000L) continue;
            Function f = fm.getFunctionAt(A(e));
            if (f == null) f = createFunction(A(e), null);
            if (f == null) continue;
            DecompileResults res = ifc.decompileFunction(f, 60, new ConsoleTaskMonitor());
            String c = res != null && res.decompileCompleted() && res.getDecompiledFunction() != null
                    ? res.getDecompiledFunction().getC() : "<fail>";
            // keep if mentions interesting constants or small size
            boolean keep = c.contains("0x10") || c.contains("0x16") || c.contains("0x4")
                    || c.contains("0x5") || c.contains("0x1b") || c.contains("0x27")
                    || e == 0x400d2d68L || e == 0x400d2714L || e == 0x400d2bfcL
                    || e == 0x400d337cL || e == 0x400d3144L || e == 0x400d2f4cL
                    || e == 0x400d6198L || e == 0x400d5ac4L || e == 0x400d6150L
                    || e == 0x400d3e5cL || e == 0x400d380cL || e == 0x400d3034L
                    || c.length() < 800;
            if (!keep && count > 40) continue;

            String safe = f.getName().replaceAll("[^A-Za-z0-9_]", "_");
            File cf = new File(dir, String.format("%s_%s.c", f.getEntryPoint(), safe));
            try (PrintWriter cw = new PrintWriter(new FileWriter(cf))) {
                cw.println("// " + f.getEntryPoint() + " " + f.getName());
                cw.println(c);
            }
            pw.println("\n## `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
            pw.println("```c");
            String[] lines = c.split("\n");
            for (int i = 0; i < Math.min(80, lines.length); i++) pw.println(lines[i]);
            if (lines.length > 80) pw.println("// truncated");
            pw.println("```");
            count++;
            if (count > 60) break;
            println("OK " + f.getEntryPoint() + " " + f.getName());
        }
        ifc.dispose();
        pw.close();
        println("Wrote gaps, count=" + count);
    }
}
