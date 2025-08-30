// menu_pattern.cpp
#include "menu_pattern.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include <avr/pgmspace.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for PATTERN_MENU
static const Transition PATTERN_MENU_TRANSITIONS[] = {
  {"PATTERN_MENU", 0, "MAIN_MENU"},
};
static const unsigned PATTERN_MENU_TRANSITION_COUNT =
  sizeof(PATTERN_MENU_TRANSITIONS)/sizeof(PATTERN_MENU_TRANSITIONS[0]);

// ---------- PROGMEM labels ----------
const char P_ITEM_0[] PROGMEM = "Pattern 1";
const char P_ITEM_1[] PROGMEM = "Pattern 2";
const char P_ITEM_2[] PROGMEM = "Pattern 3";
const char TITLE_PATTERN[] PROGMEM = "Pattern Menu";

// Pointer table also in PROGMEM
const char* const MENU_PATTERN_ITEMS[] PROGMEM = {
  P_ITEM_0, P_ITEM_1, P_ITEM_2
};
const uint8_t MENU_PATTERN_COUNT = 3;

// --- PatternMenuContext ---
PatternMenuContext::PatternMenuContext()
  : MenuObject("PATTERN_MENU", "MAIN_MENU",
               /*subs*/ nullptr, /*subCount*/ 0,
               /*menuItems*/ MENU_PATTERN_ITEMS, /*menuItemCount*/ MENU_PATTERN_COUNT) {}

void PatternMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  char titleBuf[24];
  strncpy_P(titleBuf, TITLE_PATTERN, sizeof(titleBuf)-1);
  titleBuf[sizeof(titleBuf)-1] = '\0';

  // PROGMEM-aware renderer
  drawMenuPagedP(u8, "Pattern Menu", items, itemCount, selectedIndex, 4);
}

void PatternMenuContext::handleInput(int input) {
  if (input == 1) {                 // select/enter -> back to main (for now)
    setContextByName("MAIN_MENU");
  } else if (input == 2) {          // down
    selectedIndex = (uint8_t)((selectedIndex + 1) % itemCount);
  } else if (input == 3) {          // up
    selectedIndex = (uint8_t)((selectedIndex + itemCount - 1) % itemCount);
  } else if (input == 0) {          // back
    if (goBack()) return;
    // Optional fallback:
    // setContextByName("MAIN_MENU");
  }
}

void PatternMenuContext::update(void* /*gfx*/) {
  // No time-based animation here yet.
}

// --- Global instance + registration ---
PatternMenuContext patternMenuContext;

__attribute__((constructor))
void registerPatternMenuContext() {
  registerContext("PATTERN_MENU", &patternMenuContext);
}
