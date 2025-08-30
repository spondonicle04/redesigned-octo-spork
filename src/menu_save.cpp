// menu_save.cpp
// Save menu context

#include "menu_save.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include <avr/pgmspace.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for SAVE_MENU
static const Transition SAVE_MENU_TRANSITIONS[] = {
  {"SAVE_MENU", 0, "MAIN_MENU"},
};
static const unsigned SAVE_MENU_TRANSITION_COUNT =
  sizeof(SAVE_MENU_TRANSITIONS)/sizeof(SAVE_MENU_TRANSITIONS[0]);

// ---------- PROGMEM labels ----------
const char SV_ITEM_0[] PROGMEM = "Save Pattern";
const char SV_ITEM_1[] PROGMEM = "Save All";
const char SV_ITEM_2[] PROGMEM = "Back";
const char TITLE_SAVE[] PROGMEM = "Save Menu";

// Pointer table also in PROGMEM
const char* const MENU_SAVE_ITEMS[] PROGMEM = {
  SV_ITEM_0,
  SV_ITEM_1,
  SV_ITEM_2
};
const uint8_t MENU_SAVE_COUNT = 3;

SaveMenuContext::SaveMenuContext()
  : MenuObject("SAVE_MENU", "MAIN_MENU",
               /*subs*/ nullptr, /*subCount*/ 0,
               /*menuItems*/ MENU_SAVE_ITEMS, /*menuItemCount*/ MENU_SAVE_COUNT) {}

void SaveMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
   char titleBuf[24];
  strncpy_P(titleBuf, TITLE_SAVE, sizeof(titleBuf)-1);
  titleBuf[sizeof(titleBuf)-1] = '\0';

  // PROGMEM-aware renderer
  drawMenuPagedP(u8, "Save Menu", items, itemCount, selectedIndex, 4);
}

void SaveMenuContext::handleInput(int input) {
  if (input == 1) {                       // select/enter
    if (selectedIndex == 2) {
      setContextByName("MAIN_MENU");      // Back
    } else {
      // TODO: implement actual save behavior
      // e.g., savePattern(selectedIndex == 0 ? current : ALL);
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

void SaveMenuContext::update(void* /*gfx*/) {
  // No periodic work yet.
}

// --- Global instance + registration ---
SaveMenuContext saveMenuContext;

__attribute__((constructor))
void registerSaveMenuContext() {
  registerContext("SAVE_MENU", &saveMenuContext);
}
