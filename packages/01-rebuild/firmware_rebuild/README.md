# Rebuild binaries (SPI 10 MHz dual-nRF)

Flash full image:

```bash
esptool.py --chip esp32 -p COMx write_flash 0x0 ComboChannelSelect.ino.merged.bin
```

Or split:

```bash
esptool.py --chip esp32 -p COMx write_flash \
  0x1000 ComboChannelSelect.ino.bootloader.bin \
  0x8000 ComboChannelSelect.ino.partitions.bin \
  0xe000 boot_app0.bin \
  0x10000 ComboChannelSelect.ino.bin
```

**SPI:** runtime **10 MHz** (original RE 16 MHz). See `docs/SPI_HSPI_COMPAT.md`.
