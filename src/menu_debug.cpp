// menu_debug.cpp
// Debug context

#include "menu_debug.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include <avr/pgmspace.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for DEBUG
static const Transition DEBUG_TRANSITIONS[] = {
  {"DEBUG", 0, "MAIN_MENU"},
};
static const unsigned DEBUG_TRANSITION_COUNT =
  sizeof(DEBUG_TRANSITIONS)/sizeof(DEBUG_TRANSITIONS[0]);

// ---------- PROGMEM labels ----------
const char D_ITEM_0[] PROGMEM = "System Info";
const char D_ITEM_1[] PROGMEM = "Test Beep";
const char D_ITEM_2[] PROGMEM = "Back";

// Pointer table also in PROGMEM
const char* const MENU_DEBUG_ITEMS[] PROGMEM = {
  D_ITEM_0, D_ITEM_1, D_ITEM_2
};
const uint8_t MENU_DEBUG_COUNT = 3;

DebugMenuContext::DebugMenuContext()
  : MenuObject("DEBUG", "MAIN_MENU",
               /*subs*/ nullptr, /*subCount*/ 0,
               /*menuItems*/ MENU_DEBUG_ITEMS, /*menuItemCount*/ MENU_DEBUG_COUNT) {}

void DebugMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  // PROGMEM-aware renderer
  drawMenuPagedP(u8, "Debug", items, itemCount, selectedIndex, 4);
}

void DebugMenuContext::handleInput(int input) {
  if (input == 1) {                       // select/enter
    if (selectedIndex == 2) {
      setContextByName("MAIN_MENU");      // Back
    } else if (selectedIndex == 0) {
      // TODO: show system info screen / print stats
      // e.g., setContextByName("SYS_INFO");
    } else if (selectedIndex == 1) {
      // TODO: beep test or diagnostic action
      // e.g., tone(BUZZER_PIN, 880, 100);
    }
  } else if (input == 2) {                // down
    selectedIndex = (uint8_t)((selectedIndex + 1) % itemCount);
  } else if (input == 3) {                // up
    selectedIndex = (uint8_t)((selectedIndex + itemCount - 1) % itemCount);
  } else if (input == 0) {                // back
    if (goBack()) return;
    // Optional fallback:
    // setContextByName("MAIN_MENU");
  }
}

void DebugMenuContext::update(void* /*gfx*/) {
  // No periodic work yet.
}

// --- Global instance + registration ---
DebugMenuContext debugMenuContext;

__attribute__((constructor))
void registerDebugMenuContext() {
  registerContext("DEBUG", &debugMenuContext);
}
