#pragma once
#include "config_pins.h"
#include "config_features.h"
#include "board_profile_MEGA2560.h"

// // === config.h ===
// // Master pin and hardware definitions for the Super 707 Sequencer
// // Platform: Arduino Mega 2560 (targeted), fallback to Uno later
// // Change nothing before the big line!
// #pragma once

// // ================== DISPLAY ===================

// // ST7920 screen (using software SPI)
// #define LCD_CLK   13
// #define LCD_MOSI  11
// #define LCD_CS    10

// // NeoPixels
// //#define NEOPIXEL_PIN_1   00  // strip
// //#define NEOPIXEL_PIN_2   00  // circle

// // ================== CLOCK =====================

// // External hardware clock (555 timer or MIDI)
// // ISR-triggered — keep this pin INT-capable
// #define CLOCK_INPUT_PIN  2   // External clock input (INT4 on Mega)

// // ================== INPUTS ====================

// // --- Button Matrix 4x4 (step buttons) ---
// #define STEP_MATRIX_ROW_0  22
// #define STEP_MATRIX_ROW_1  23
// #define STEP_MATRIX_ROW_2  24
// #define STEP_MATRIX_ROW_3  25

// #define STEP_MATRIX_COL_0  26
// #define STEP_MATRIX_COL_1  27
// #define STEP_MATRIX_COL_2  28
// #define STEP_MATRIX_COL_3  29

// // --- Button Matrix 4x5 (UI matrix, future use) ---
// #define FUNC_MATRIX_ROW_0  30
// #define FUNC_MATRIX_ROW_1  31
// #define FUNC_MATRIX_ROW_2  32
// #define FUNC_MATRIX_ROW_3  33

// #define FUNC_MATRIX_COL_0  34
// #define FUNC_MATRIX_COL_1  35
// #define FUNC_MATRIX_COL_2  36
// #define FUNC_MATRIX_COL_3  37
// #define FUNC_MATRIX_COL_4  38

// // --- Standalone Buttons (8 total, assign as needed) ---
// //#define BTN_0  39
// //#define BTN_1  40
// //#define BTN_2  41
// #define BTN_LIVE  42
// #define BTN_DOWN    43
// #define BTN_UP      44
// #define BTN_SELECT  45
// #define BTN_BACK    46

// // --- Encoder (menu nav, etc) ---
// #define ENC_A   47   // CLK
// #define ENC_B   48   // DT
// #define ENC_BTN 49

// // --- Pots (10 channels) ---
// #define BK_LT   A0   
// #define POT_1   A1
// #define POT_2   A2
// #define POT_3   A3
// #define POT_4   A6
// #define POT_5   A7
// #define POT_6   A8
// #define POT_7   A9
// #define POT_8   A10
// #define POT_10   A11
// #define POT_11   A12

// // ================== OUTPUTS ===================

// // === Trigger/CV outputs (10 total) ===
// // These are relocated to avoid pin conflict with SPI and MUX
// #define TRIG_OUT_0  50
// // #define TRIG_OUT_1  51
// // #define TRIG_OUT_2  52
// // #define TRIG_OUT_3  53
// // #define TRIG_OUT_4  39
// // #define TRIG_OUT_5  40
// // #define TRIG_OUT_6  41
// // #define TRIG_OUT_7  A15
// // #define TRIG_OUT_8  14
// // #define TRIG_OUT_9  15

// // === AIP1640 (LED driver for grid LEDs) ===
// #define AIP1640_CLK  17
// #define AIP1640_DIO  18

// // ================== MULTIPLEXERS ===================
// // Two independent 4067 multiplexers: one for LED/channel outputs, one for button input

// // Column selector for LED driver mux (anodes)
// #define COL_SEL_0 4
// #define COL_SEL_1 5
// #define COL_SEL_2 6
// #define COL_SEL_3 7

// // Row selector for button reader mux (cathodes)
// #define ROW_SEL_0 8
// #define ROW_SEL_1 9
// #define ROW_SEL_2 10
// #define ROW_SEL_3 16

// // Enable pins for muxes
// #define EN_COL_MUX 19    // Enable line for LED matrix mux
// #define EN_ROW_MUX     // Enable line for button matrix mux

// // Signal lines
// #define MUX_SIG_WRITE 3   // Output to COL mux SIG (used for lighting LEDs)
// #define MUX_SIG_READ  A5  // Input from ROW mux SIG (used for reading buttons)

// // ================== MIDI ===================

// #define MIDI_IN_PIN   0   // Serial RX (via Serial1, Serial2, etc.)
// #define MIDI_OUT_PIN  1   // Serial TX

// // ================== AUDIO (optional/future) ===================

// #define AUDIO_OUT_PIN  A14   // Placeholder (dual-use with trigger if needed)
// #define AUDIO_IN_PIN   A15   // Placeholder (for beat detection, etc.)

// // ================== OTHER ===================

// #define NUM_POTS          10
// #define NUM_TRIGGER_OUTS  10
// #define NUM_STEP_BUTTONS  16
// #define NUM_UI_BUTTONS    20    // Matrix + standalones
// #define N_ROWS            4
// #define N_COLS            4
// #define DEBOUNCE_MS       10
// // //////////////////////////////////////////////////////////////////      -------Change nothing above this Line!!-------     /////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////                                                       ////////////////////////////////////////////////////////////
// #define CTX_HISTORY_ENABLED 1  // flip to 0 to strip history
