#pragma once
#include <Arduino.h>
#include "config.h"   // define DEBUG_SERIAL (0 or 1) and optionally DEBUG_BAUD

// Optional: default baud if you want a helper init
#ifndef DEBUG_BAUD
#define DEBUG_BAUD 115200
#endif

#if DEBUG_SERIAL

// --- Init helper (use in setup() if you want) ---
inline void DEBUG_BEGIN() { Serial.begin(DEBUG_BAUD); }

// --- Literals in PROGMEM ---
inline void DPRINT(const __FlashStringHelper* s)  { Serial.print(s); }
inline void DPRINTLN(const __FlashStringHelper* s){ Serial.println(s); }

// --- Generic variables/values (no format) ---
template<typename T> inline void DPRINT(const T& v)   { Serial.print(v); }
template<typename T> inline void DPRINTLN(const T& v) { Serial.println(v); }

// --- Values with format spec (HEX/DEC/BIN…) ---
template<typename T> inline void DPRINT(const T& v, int fmt)   { Serial.print(v, fmt); }
template<typename T> inline void DPRINTLN(const T& v, int fmt) { Serial.println(v, fmt); }

// --- Convenience for string LITERALS (auto F()) ---
#define DL(x)   DPRINT(F(x))
#define DLLN(x) DPRINTLN(F(x))

#else  // DEBUG_SERIAL == 0  → compile away

inline void DEBUG_BEGIN() {}

inline void DPRINT(const __FlashStringHelper*) {}
inline void DPRINTLN(const __FlashStringHelper*) {}

template<typename T> inline void DPRINT(const T&) {}
template<typename T> inline void DPRINTLN(const T&) {}

template<typename T> inline void DPRINT(const T&, int) {}
template<typename T> inline void DPRINTLN(const T&, int) {}

#define DL(x)   do{}while(0)
#define DLLN(x) do{}while(0)

#endif
