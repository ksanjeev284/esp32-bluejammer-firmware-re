# Mine Pass Summary

- DROM C-strings extracted: **3051**
- Early app strings (<0x3F401800): **60**
- Serial art lines: **33**
- Literal pool entries: **312**

## Key corrections / details
- Boot `g_state=1` (BT), carrier ch **45**
- Idle labels `R1=` `R2=` `USB` `Connected`
- I2C 400k/100k, SPI 16MHz
- Full begin() + app RF sequences in `rf24_sequences.json`

## Files
- `dram1_data_named.txt` (3202 bytes)
- `drom_all_c_strings.json` (312453 bytes)
- `drom_early_strings.txt` (6462 bytes)
- `function_cheat_sheet.json` (1488 bytes)
- `irom_literal_pool_0x400d0020.txt` (12006 bytes)
- `OrigSerialArt.h` (13084773 bytes)
- `rf24_sequences.json` (1828 bytes)
- `serial_art_exact.json` (25501331 bytes)
