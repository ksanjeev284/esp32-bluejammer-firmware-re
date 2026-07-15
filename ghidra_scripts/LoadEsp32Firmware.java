// LoadEsp32Firmware.java
// Pre-analysis script: add ESP32 memory blocks and application labels.
// @category ESP32
// @menupath

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Program;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.database.mem.FileBytes;

import java.io.File;
import java.io.FileInputStream;
import java.nio.file.Files;

public class LoadEsp32Firmware extends GhidraScript {

    private Address addr(long a) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(a);
    }

    private void label(long a, String name) throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        Address ad = addr(a);
        // remove conflicting primary if needed
        st.createLabel(ad, name, SourceType.USER_DEFINED);
        println("Label " + name + " @ " + ad);
    }

    private void addBlock(String name, long base, File file, boolean r, boolean w, boolean x) throws Exception {
        Memory mem = currentProgram.getMemory();
        Address start = addr(base);
        // skip if exists
        if (mem.getBlock(start) != null && mem.getBlock(start).getStart().equals(start)) {
            println("Block already exists near " + name);
        }
        byte[] bytes = Files.readAllBytes(file.toPath());
        MemoryBlock existing = mem.getBlock(name);
        if (existing != null) {
            println("Block " + name + " already present, skip");
            return;
        }
        // If primary block already covers base (IROM import), skip creating IROM
        MemoryBlock at = mem.getBlock(start);
        if (at != null && at.contains(start) && name.equals("IROM")) {
            at.setName("IROM");
            at.setPermissions(r, w, x);
            println("Renamed primary block to IROM");
            return;
        }
        MemoryBlock block = mem.createInitializedBlock(name, start, bytes.length, (byte) 0, monitor, false);
        block.putBytes(start, bytes);
        block.setPermissions(r, w, x);
        block.setSourceName(file.getName());
        println("Created block " + name + " @ " + String.format("0x%X", base) + " size " + bytes.length);
    }

    @Override
    public void run() throws Exception {
        // Workspace-relative paths: pass -scriptPath and put segments next to scripts or use abs path via env
        String segDir = System.getenv("ESP32_SEG_DIR");
        if (segDir == null || segDir.isEmpty()) {
            // default relative to project or CWD
            segDir = "C:\\Users\\ksanj\\Downloads\\combochannel\\extracted\\segments";
        }
        println("Segment dir: " + segDir);

        File drom = new File(segDir, "seg0_DROM_0x3F400020.bin");
        File dram1 = new File(segDir, "seg1_DRAM1_0x3FFBDB60.bin");
        File irom = new File(segDir, "seg2_IROM_0x400D0020.bin");
        File dram2 = new File(segDir, "seg3_DRAM2_0x3FFC0BA0.bin");
        File iram = new File(segDir, "seg4_IRAM_0x40080000.bin");

        // Primary import should be IROM at 0x400D0020; ensure other segments exist
        if (drom.exists()) addBlock("DROM", 0x3F400020L, drom, true, false, false);
        if (dram1.exists()) addBlock("DRAM1", 0x3FFBDB60L, dram1, true, true, false);
        if (dram2.exists()) addBlock("DRAM2", 0x3FFC0BA0L, dram2, true, true, false);
        if (iram.exists()) addBlock("IRAM", 0x40080000L, iram, true, false, true);
        // IROM already imported as primary; rename/fix
        Memory mem = currentProgram.getMemory();
        for (MemoryBlock b : mem.getBlocks()) {
            if (b.getStart().getOffset() == 0x400D0020L) {
                b.setName("IROM");
                b.setPermissions(true, false, true);
                println("Configured primary as IROM");
            }
        }

        // Application labels
        label(0x40082F0CL, "ESP32_IMAGE_ENTRY");
        label(0x400D236CL, "radioTask");
        label(0x3F401658L, "str_RadioTask");
        label(0x3F401662L, "str_State1_Bluetooth");
        label(0x3F40167DL, "str_State2_BLE");
        label(0x3F4016A3L, "str_State3_WiFi");
        label(0x3F4016B9L, "str_State4_RC");
        label(0x3F4016CDL, "str_State0_Idle");
        label(0x3F4016FAL, "str_SSD1306_alloc_failed");
        label(0x3F401714L, "str_by_emensta");
        label(0x3F4002C4L, "str_HSPI_SUCCESS");
        label(0x3F40044AL, "str_HSPI_FAIL");
        label(0x3F400608L, "str_VSPI_SUCCESS");
        label(0x3F400793L, "str_VSPI_FAIL");
        label(0x3F400E16L, "str_Firmware_Banner");
        label(0x3F40154EL, "str_GitHub_URL");
        label(0x3F4014C9L, "str_Educational");
        label(0x3F4015D3L, "str_Disclaimer");
        label(0x3F40082DL, "str_bitmapboot");
        label(0x3F401675L, "str_bitmap1");
        label(0x3F40169BL, "str_bitmap2");
        label(0x3F4016B1L, "str_bitmap3");
        label(0x3F4016C5L, "str_bitmap4");
        label(0x3F402080L, "bitmap1_data");
        label(0x3F401D60L, "bitmap2_data");
        label(0x3F401A40L, "bitmap3_data");
        label(0x3F401720L, "bitmap4_data");
        label(0x3F4023A0L, "bitmap_boot_or_extra_data");
        label(0x400D010CL, "table_state_strings");
        label(0x400D01A4L, "table_bitmap_refs");
        label(0x400D00ECL, "ptr_RadioTask_name");
        label(0x400D00F0L, "ptr_radioTask_fn");
        label(0x3F403649L, "str_loopTask");
        label(0x3F4016F0L, "str_Connected");

        println("LoadEsp32Firmware complete");
    }
}
