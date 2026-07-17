#pragma once
/*
 * Build configuration for hardware-faithful reconstruction.
 *
 * REBUILD_SAFE=0  → full dual-nRF24 path (matches original device behavior)
 * REBUILD_SAFE=1  → UI-only (Serial + OLED + button/LED), no RF TX APIs
 *
 * LEGAL: Operating RF jamming equipment is illegal in most countries.
 * Use REBUILD_SAFE=0 only in a lawful, shielded lab / with proper authorization.
 */

#ifndef REBUILD_SAFE
#define REBUILD_SAFE 0
#endif

// Original .data init: g_state = 1 (Bluetooth) — jams/hops after radio bring-up.
#ifndef INITIAL_STATE
#define INITIAL_STATE 1
#endif

// Initial startConstCarrier channel (DRAM1 0x3FFBDB70/74 = 45)
#ifndef INITIAL_CARRIER_CH
#define INITIAL_CARRIER_CH 45
#endif
