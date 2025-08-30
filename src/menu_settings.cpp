// menu_settings.cpp
// Settings menu context

#include "menu_settings.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include <avr/pgmspace.h>
#include "ui_draw.h"
#include "events.h"
#include "transitions.h"

// ---------- PROGMEM labels ----------
const char S_ITEM_0[] PROGMEM = "Audio Settings";
const char S_ITEM_1[] PROGMEM = "Display Options";
const char S_ITEM_2[] PROGMEM = "MIDI Config";
const char S_ITEM_3[] PROGMEM = "Back";
const char TITLE_SETTINGS[] PROGMEM = "Settings";

// Pointer table also in PROGMEM
const char* const MENU_SETTINGS_ITEMS[] PROGMEM = {
  S_ITEM_0, S_ITEM_1, S_ITEM_2, S_ITEM_3
};
const uint8_t MENU_SETTINGS_COUNT = 4;

SettingsMenuContext::SettingsMenuContext()
  : MenuObject("SETTINGS", "MAIN_MENU",
               /*subs*/ nullptr, /*subCount*/ 0,
               /*menuItems*/ MENU_SETTINGS_ITEMS, /*menuItemCount*/ MENU_SETTINGS_COUNT) {}

void SettingsMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  char titleBuf[24];
  strncpy_P(titleBuf, TITLE_SETTINGS, sizeof(titleBuf)-1);
  titleBuf[sizeof(titleBuf)-1] = '\0'; 
  // PROGMEM-aware renderer
  drawMenuPagedP(u8, "Settings", items, itemCount, selectedIndex, 4);
}

void SettingsMenuContext::update(void* /*gfx*/) {
  // No periodic work yet.
}

void SettingsMenuContext::handleInput(int input) {
  if (input == 1) {                       // select/enter
    if (selectedIndex == 3) {
      setContextByName("MAIN_MENU");      // "Back"
    } else {
      // TODO: jump to sub-menus (e.g., AUDIO_SETTINGS / DISPLAY_OPTIONS / MIDI_CONFIG)
      // setContextByName("AUDIO_SETTINGS");
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

// --- Global instance + registration ---
SettingsMenuContext settingsMenuContext;

__attribute__((constructor))
void registerSettingsMenuContext() {
  registerContext("SETTINGS", &settingsMenuContext);
}
