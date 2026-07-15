// FindEverything.java
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
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeMap;

public class FindEverything extends GhidraScript {

    private Address A(long a) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(a);
    }

    private String decomp(DecompInterface ifc, Function f) {
        if (f == null) {
            return null;
        }
        DecompileResults r = ifc.decompileFunction(f, 90, new ConsoleTaskMonitor());
        if (r != null && r.decompileCompleted() && r.getDecompiledFunction() != null) {
            return r.getDecompiledFunction().getC();
        }
        return null;
    }

    private void save(File dir, Function f, String c) throws Exception {
        String safe = f.getName().replaceAll("[^A-Za-z0-9_]", "_");
        File cf = new File(dir, f.getEntryPoint().toString() + "_" + safe + ".c");
        PrintWriter pw = new PrintWriter(new FileWriter(cf));
        pw.println("// " + f.getEntryPoint() + " " + f.getName());
        pw.println(c);
        pw.close();
    }

    private void printC(PrintWriter report, String c, int maxLines) {
        report.println("```c");
        String[] lines = c.split("\n");
        int n = Math.min(maxLines, lines.length);
        for (int i = 0; i < n; i++) {
            report.println(lines[i]);
        }
        if (lines.length > maxLines) {
            report.println("// truncated");
        }
        report.println("```");
    }

    @Override
    public void run() throws Exception {
        String outDir = System.getenv("ESP32_OUT_DIR");
        if (outDir == null || outDir.length() == 0) {
            outDir = "C:\\Users\\ksanj\\Downloads\\combochannel\\extracted\\ghidra";
        }
        File out = new File(outDir);
        File decompDir = new File(out, "decomp_extra");
        decompDir.mkdirs();

        PrintWriter report = new PrintWriter(new FileWriter(new File(out, "REMAINING_FINDINGS.md")));
        PrintWriter pinsReport = new PrintWriter(new FileWriter(new File(out, "PIN_IMMEDIATES.txt")));

        FunctionManager fm = currentProgram.getFunctionManager();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        Memory mem = currentProgram.getMemory();
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);

        report.println("# Remaining Findings Pass");
        report.println();

        // 1) Immediate scan in app region
        report.println("## Immediate scan app region 0x400D2000-0x400D4000");
        long[] interestingPins = {0, 2, 4, 5, 12, 13, 14, 15, 16, 18, 19, 21, 22, 23, 27};
        TreeMap<Long, List<String>> pinHits = new TreeMap<Long, List<String>>();
        for (int i = 0; i < interestingPins.length; i++) {
            pinHits.put(Long.valueOf(interestingPins[i]), new ArrayList<String>());
        }

        Address start = A(0x400d2000L);
        Address end = A(0x400d4000L);
        InstructionIterator iit = listing.getInstructions(start, true);
        int insCount = 0;
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            if (ins.getAddress().compareTo(end) > 0) {
                break;
            }
            insCount++;
            for (int op = 0; op < ins.getNumOperands(); op++) {
                Object[] objs = ins.getOpObjects(op);
                for (int k = 0; k < objs.length; k++) {
                    if (objs[k] instanceof Scalar) {
                        long v = ((Scalar) objs[k]).getUnsignedValue();
                        if (pinHits.containsKey(Long.valueOf(v))) {
                            Function f = fm.getFunctionContaining(ins.getAddress());
                            String fn = f != null ? f.getName() : "?";
                            List<String> list = pinHits.get(Long.valueOf(v));
                            if (list.size() < 50) {
                                list.add(ins.getAddress() + "  " + ins.toString() + "  in " + fn);
                            }
                        }
                    }
                }
            }
        }
        pinsReport.println("scanned " + insCount);
        for (int i = 0; i < interestingPins.length; i++) {
            long p = interestingPins[i];
            List<String> list = pinHits.get(Long.valueOf(p));
            pinsReport.println();
            pinsReport.println("=== " + p + " hits=" + list.size() + " ===");
            for (int j = 0; j < list.size(); j++) {
                pinsReport.println(list.get(j));
            }
            report.println("- imm **" + p + "**: " + list.size() + " hits");
            // highlight CE candidates
            if (p == 16 || p == 22) {
                for (int j = 0; j < list.size(); j++) {
                    report.println("  - " + list.get(j));
                }
            }
        }

        // 2) Decompile entire app cluster
        report.println();
        report.println("## App cluster functions");
        List<Function> appFuncs = new ArrayList<Function>();
        FunctionIterator fi = fm.getFunctions(true);
        while (fi.hasNext()) {
            Function f = fi.next();
            long e = f.getEntryPoint().getOffset();
            if (e >= 0x400d2000L && e <= 0x400d4000L) {
                appFuncs.add(f);
            }
        }
        report.println("Count: " + appFuncs.size());
        for (int i = 0; i < appFuncs.size(); i++) {
            Function f = appFuncs.get(i);
            String c = decomp(ifc, f);
            if (c == null) {
                continue;
            }
            save(decompDir, f, c);
            boolean interesting = c.indexOf("0x10") >= 0 || c.indexOf("0x16") >= 0
                    || c.indexOf("0x1b") >= 0 || c.indexOf("0x3c") >= 0
                    || c.indexOf("0x4f") >= 0 || c.indexOf("0x7d") >= 0
                    || c.indexOf("0x27") >= 0 || c.length() < 600
                    || f.getName().indexOf("radio") >= 0 || f.getName().indexOf("State") >= 0
                    || f.getName().indexOf("nrf") >= 0 || f.getName().indexOf("spi") >= 0;
            if (interesting) {
                report.println();
                report.println("### `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
                printC(report, c, 70);
            }
            println("decompiled " + f.getEntryPoint());
        }

        // 3) pinMode callers
        report.println();
        report.println("## pinMode callers (FUN_400d6198)");
        ReferenceIterator pinModeRefs = rm.getReferencesTo(A(0x400d6198L));
        Set<Long> pinModeCallers = new LinkedHashSet<Long>();
        while (pinModeRefs.hasNext()) {
            Reference r = pinModeRefs.next();
            Function f = fm.getFunctionContaining(r.getFromAddress());
            if (f != null) {
                pinModeCallers.add(Long.valueOf(f.getEntryPoint().getOffset()));
            }
        }
        report.println("Caller count: " + pinModeCallers.size());
        for (Long eObj : pinModeCallers) {
            long e = eObj.longValue();
            Function f = fm.getFunctionAt(A(e));
            if (f == null) {
                continue;
            }
            String c = decomp(ifc, f);
            if (c == null) {
                continue;
            }
            save(decompDir, f, c);
            if (c.indexOf("0x10") >= 0 || c.indexOf("0x16") >= 0 || c.indexOf("0x1b") >= 0
                    || c.indexOf("0xf") >= 0 || (e >= 0x400d2000L && e <= 0x400d3800L)) {
                report.println();
                report.println("### pinMode caller `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
                printC(report, c, 90);
            }
        }

        // 4) Callers of setup/loop
        report.println();
        report.println("## Callers of setup / loop / radioTask");
        long[] targets = {0x400d2714L, 0x400d2bfcL, 0x400d236cL, 0x400d2d68L, 0x400d2f4cL};
        for (int t = 0; t < targets.length; t++) {
            long target = targets[t];
            report.println();
            report.println("### Target 0x" + Long.toHexString(target));
            ReferenceIterator ri = rm.getReferencesTo(A(target));
            int n = 0;
            while (ri.hasNext()) {
                Reference r = ri.next();
                Function f = fm.getFunctionContaining(r.getFromAddress());
                report.println("- from " + r.getFromAddress() + " type=" + r.getReferenceType()
                        + " in " + (f != null ? f.getName() + "@" + f.getEntryPoint() : "literal/data"));
                if (f != null && f.getEntryPoint().getOffset() != target) {
                    String c = decomp(ifc, f);
                    if (c != null) {
                        save(decompDir, f, c);
                        printC(report, c, 40);
                    }
                }
                n++;
                if (n > 15) {
                    break;
                }
            }
            if (n == 0) {
                report.println("- none");
            }
        }

        // 5) Pointer scan in memory for setup/loop
        report.println();
        report.println("## Absolute pointer locations for key functions");
        long[] keyFns = {0x400d2714L, 0x400d2bfcL, 0x400d236cL, 0x400d2d68L, 0x400d28d8L};
        MemoryBlock[] blocks = mem.getBlocks();
        for (int k = 0; k < keyFns.length; k++) {
            long fn = keyFns[k];
            byte b0 = (byte) (fn);
            byte b1 = (byte) (fn >> 8);
            byte b2 = (byte) (fn >> 16);
            byte b3 = (byte) (fn >> 24);
            for (int bi = 0; bi < blocks.length; bi++) {
                MemoryBlock block = blocks[bi];
                if (!block.isInitialized()) {
                    continue;
                }
                long bsize = block.getSize();
                if (bsize > 2000000) {
                    continue;
                }
                byte[] data = new byte[(int) bsize];
                try {
                    block.getBytes(block.getStart(), data);
                } catch (Exception ex) {
                    continue;
                }
                for (int i = 0; i + 3 < data.length; i += 4) {
                    if (data[i] == b0 && data[i + 1] == b1 && data[i + 2] == b2 && data[i + 3] == b3) {
                        long loc = block.getStart().getOffset() + i;
                        report.println(String.format("- fn 0x%X ptr at 0x%X (%s)", fn, loc, block.getName()));
                    }
                }
            }
        }

        // 6) Extra helpers
        report.println();
        report.println("## Extra helper decompilation");
        long[] more = {
            0x400d6d08L, 0x400d7038L, 0x400d2f38L, 0x400d2ff8L, 0x400d3078L,
            0x400d3060L, 0x400d30f0L, 0x400d3248L, 0x400d327cL, 0x400d3494L,
            0x400d3220L, 0x400d380cL, 0x400d2844L, 0x400d6224L, 0x400d670cL,
            0x400949f4L, 0x400d5ac4L, 0x400d493cL, 0x400d5220L, 0x400d63acL,
            0x400d63d0L, 0x400d48fcL, 0x400d36a4L
        };
        for (int i = 0; i < more.length; i++) {
            long e = more[i];
            Function f = fm.getFunctionAt(A(e));
            if (f == null) {
                f = createFunction(A(e), null);
            }
            if (f == null) {
                report.println("- could not create 0x" + Long.toHexString(e));
                continue;
            }
            String c = decomp(ifc, f);
            if (c == null) {
                continue;
            }
            save(decompDir, f, c);
            report.println();
            report.println("### `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
            printC(report, c, 55);
        }

        // 7) ctor heuristic
        report.println();
        report.println("## Possible constructors (assign +4 and +5)");
        fi = fm.getFunctions(true);
        int ctorHits = 0;
        while (fi.hasNext()) {
            Function f = fi.next();
            long e = f.getEntryPoint().getOffset();
            if (e < 0x400d2000L || e > 0x400e0000L) {
                continue;
            }
            String c = decomp(ifc, f);
            if (c == null) {
                continue;
            }
            boolean has4 = c.indexOf("+ 4)") >= 0 || c.indexOf("+4)") >= 0;
            boolean has5 = c.indexOf("+ 5)") >= 0 || c.indexOf("+5)") >= 0;
            if (has4 && has5 && c.length() < 2500) {
                report.println();
                report.println("### ctor-like `" + f.getName() + "` @ `" + f.getEntryPoint() + "`");
                printC(report, c, 80);
                save(decompDir, f, c);
                ctorHits++;
            }
        }
        report.println();
        report.println("Ctor-like count: " + ctorHits);

        // 8) Literal pool dump
        report.println();
        report.println("## Literal pool 0x400D0020-0x400D0280");
        for (long a = 0x400d0020L; a < 0x400d0280L; a += 4) {
            try {
                int val = mem.getInt(A(a));
                long u = val & 0xffffffffL;
                String note = "";
                if (u >= 0x3f400020L && u < 0x3f41d000L) {
                    byte[] buf = new byte[60];
                    int got = mem.getBytes(A(u), buf);
                    StringBuilder sb = new StringBuilder();
                    for (int i = 0; i < got && buf[i] != 0 && i < 50; i++) {
                        if (buf[i] >= 32 && buf[i] < 127) {
                            sb.append((char) buf[i]);
                        } else {
                            sb.append('.');
                            break;
                        }
                    }
                    note = "STR " + sb.toString();
                } else if (u >= 0x400d0000L && u < 0x40170000L) {
                    Function f = fm.getFunctionAt(A(u));
                    note = f != null ? "FN " + f.getName() : "CODE";
                } else if (u >= 0x3ffb0000L && u < 0x40000000L) {
                    note = "DRAM/BSS";
                } else if (u < 0x200000L) {
                    note = "IMM " + u;
                }
                report.println(String.format("- 0x%08X -> 0x%08X %s", a, u, note));
            } catch (Exception ex) {
                // skip
            }
        }

        ifc.dispose();
        report.println();
        report.println("## Done");
        report.close();
        pinsReport.close();
        println("FindEverything complete");
    }
}
