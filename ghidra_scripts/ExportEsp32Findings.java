// ExportEsp32Findings.java
// Post-analysis: dump functions, xrefs to key strings, decompile hotspots.
// @category ESP32

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ExportEsp32Findings extends GhidraScript {

    private Address addr(long a) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(a);
    }

    private void writeln(PrintWriter pw, String s) {
        pw.println(s);
        println(s);
    }

    private String decompile(DecompInterface ifc, Function f) {
        if (f == null) return "<null function>";
        DecompileResults res = ifc.decompileFunction(f, 60, new ConsoleTaskMonitor());
        if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
            return res.getDecompiledFunction().getC();
        }
        return "<decompile failed: " + (res != null ? res.getErrorMessage() : "null") + ">";
    }

    private Function functionContaining(long a) {
        return currentProgram.getFunctionManager().getFunctionContaining(addr(a));
    }

    private void dumpXrefs(PrintWriter pw, ReferenceManager rm, long target, String name) {
        writeln(pw, "\n### Xrefs to " + name + " @ " + String.format("0x%X", target));
        ReferenceIterator it = rm.getReferencesTo(addr(target));
        int n = 0;
        while (it.hasNext()) {
            Reference r = it.next();
            Address from = r.getFromAddress();
            Function f = currentProgram.getFunctionManager().getFunctionContaining(from);
            String fn = f != null ? f.getName() + " @ " + f.getEntryPoint() : "<no func>";
            writeln(pw, String.format("  from %s  (%s)  type=%s", from, fn, r.getReferenceType()));
            n++;
            if (n > 80) {
                writeln(pw, "  ... truncated");
                break;
            }
        }
        if (n == 0) writeln(pw, "  (none)");
    }

    @Override
    public void run() throws Exception {
        String outDir = System.getenv("ESP32_OUT_DIR");
        if (outDir == null || outDir.isEmpty()) {
            outDir = "C:\\Users\\ksanj\\Downloads\\combochannel\\extracted\\ghidra";
        }
        File dir = new File(outDir);
        dir.mkdirs();

        File report = new File(dir, "GHIDRA_FINDINGS.md");
        File funcsFile = new File(dir, "functions.txt");
        File decompDir = new File(dir, "decomp");
        decompDir.mkdirs();

        PrintWriter pw = new PrintWriter(new FileWriter(report));
        PrintWriter pf = new PrintWriter(new FileWriter(funcsFile));

        writeln(pw, "# Ghidra Headless Findings");
        writeln(pw, "");
        writeln(pw, "Program: `" + currentProgram.getName() + "`");
        writeln(pw, "Language: `" + currentProgram.getLanguageID() + "`");
        writeln(pw, "Image base: `" + currentProgram.getImageBase() + "`");
        writeln(pw, "");

        // Memory blocks
        writeln(pw, "## Memory blocks");
        for (ghidra.program.model.mem.MemoryBlock b : currentProgram.getMemory().getBlocks()) {
            writeln(pw, String.format("- **%s** %s – %s size=%d perms=%s%s%s",
                    b.getName(), b.getStart(), b.getEnd(), b.getSize(),
                    b.isRead() ? "R" : "-",
                    b.isWrite() ? "W" : "-",
                    b.isExecute() ? "X" : "-"));
        }

        // Function list
        FunctionManager fm = currentProgram.getFunctionManager();
        List<Function> funcs = new ArrayList<>();
        FunctionIterator fi = fm.getFunctions(true);
        while (fi.hasNext()) funcs.add(fi.next());
        funcs.sort(Comparator.comparingLong(f -> f.getEntryPoint().getOffset()));

        writeln(pw, "");
        writeln(pw, "## Functions (" + funcs.size() + ")");
        for (Function f : funcs) {
            String line = String.format("%s\t%s\tsize=%d", f.getEntryPoint(), f.getName(), f.getBody().getNumAddresses());
            pf.println(line);
        }
        pf.close();
        writeln(pw, "Full list: `functions.txt`");
        // sample first 50
        writeln(pw, "");
        writeln(pw, "### First 40 functions by address");
        for (int i = 0; i < Math.min(40, funcs.size()); i++) {
            Function f = funcs.get(i);
            writeln(pw, String.format("- `%s` %s", f.getEntryPoint(), f.getName()));
        }

        // Decompiler
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        long[] hotspots = new long[] {
                0x400D236CL, // radioTask
                0x40082F0CL, // entry
        };

        // Also find functions that xref key strings
        ReferenceManager rm = currentProgram.getReferenceManager();
        long[] keys = new long[] {
                0x3F4002C4L, 0x3F40044AL, 0x3F400608L, 0x3F400793L,
                0x3F401662L, 0x3F40167DL, 0x3F4016A3L, 0x3F4016B9L, 0x3F4016CDL,
                0x3F4016FAL, 0x3F401714L, 0x3F400E16L, 0x3F401658L,
                0x3F402080L, 0x3F401D60L, 0x3F401A40L, 0x3F401720L,
                0x400D010CL, 0x400D236CL
        };
        String[] keyNames = new String[] {
                "HSPI_SUCCESS", "HSPI_FAIL", "VSPI_SUCCESS", "VSPI_FAIL",
                "State1", "State2", "State3", "State4", "State0",
                "SSD1306_fail", "by_emensta", "Firmware_banner", "RadioTask_str",
                "bitmap1_data", "bitmap2_data", "bitmap3_data", "bitmap4_data",
                "table_state_strings", "radioTask"
        };

        writeln(pw, "");
        writeln(pw, "## Cross-references to application anchors");
        Set<Long> decompileEntries = new HashSet<>();
        decompileEntries.add(0x400D236CL);
        for (int i = 0; i < keys.length; i++) {
            dumpXrefs(pw, rm, keys[i], keyNames[i]);
            ReferenceIterator it = rm.getReferencesTo(addr(keys[i]));
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = fm.getFunctionContaining(r.getFromAddress());
                if (f != null) decompileEntries.add(f.getEntryPoint().getOffset());
            }
        }

        // Also createFunction at radioTask if missing
        if (fm.getFunctionAt(addr(0x400D236CL)) == null) {
            Function created = createFunction(addr(0x400D236CL), "radioTask");
            writeln(pw, "Created function radioTask: " + created);
            if (created != null) decompileEntries.add(0x400D236CL);
        } else {
            Function rt = fm.getFunctionAt(addr(0x400D236CL));
            rt.setName("radioTask", ghidra.program.model.symbol.SourceType.USER_DEFINED);
        }

        writeln(pw, "");
        writeln(pw, "## Decompilation of interesting functions");
        List<Long> entries = new ArrayList<>(decompileEntries);
        entries.sort(Long::compare);
        int limit = Math.min(entries.size(), 25);
        for (int i = 0; i < limit; i++) {
            long e = entries.get(i);
            Function f = fm.getFunctionAt(addr(e));
            if (f == null) f = fm.getFunctionContaining(addr(e));
            if (f == null) {
                // try create
                f = createFunction(addr(e), null);
            }
            if (f == null) {
                writeln(pw, "\n### Could not get function at " + String.format("0x%X", e));
                continue;
            }
            String name = f.getName();
            writeln(pw, "\n### `" + name + "` @ `" + f.getEntryPoint() + "`");
            String c = decompile(ifc, f);
            // write separate file
            String safe = name.replaceAll("[^A-Za-z0-9_]", "_");
            File cf = new File(decompDir, String.format("%s_%s.c", f.getEntryPoint(), safe));
            try (PrintWriter cw = new PrintWriter(new FileWriter(cf))) {
                cw.println("// " + f.getEntryPoint() + " " + name);
                cw.println(c);
            }
            // embed truncated in markdown
            String[] clines = c.split("\n");
            writeln(pw, "```c");
            for (int li = 0; li < Math.min(clines.length, 120); li++) {
                pw.println(clines[li]);
            }
            if (clines.length > 120) pw.println("// ... truncated, see decomp/" + cf.getName());
            writeln(pw, "```");
            writeln(pw, "Full: `decomp/" + cf.getName() + "`");
        }

        // Disassemble radioTask region raw if needed
        writeln(pw, "");
        writeln(pw, "## Disassembly snippet near radioTask (0x400D236C)");
        Address a = addr(0x400D236CL);
        InstructionIterator ii = currentProgram.getListing().getInstructions(a, true);
        int n = 0;
        writeln(pw, "```");
        while (ii.hasNext() && n < 40) {
            Instruction ins = ii.next();
            pw.println(ins.getAddress() + "  " + ins.toString());
            n++;
        }
        writeln(pw, "```");

        // Symbol dump for USER_DEFINED
        writeln(pw, "");
        writeln(pw, "## User labels");
        SymbolTable st = currentProgram.getSymbolTable();
        SymbolIterator si = st.getAllSymbols(true);
        while (si.hasNext()) {
            Symbol s = si.next();
            if (s.getSource() == ghidra.program.model.symbol.SourceType.USER_DEFINED) {
                writeln(pw, "- `" + s.getAddress() + "` " + s.getName());
            }
        }

        ifc.dispose();
        pw.close();
        println("Wrote " + report.getAbsolutePath());
        println("Functions: " + funcs.size());
    }
}
