// menu_settings.cpp
// Settings menu context

#include "menu_settings.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include "ui_draw.h"
#include "events.h"
#include "transitions.h"

static const char* settingsItems[] = {
  "Audio Settings",
  "Display Options",
  "MIDI Config",
  "Back"
};


SettingsMenuContext::SettingsMenuContext()
  : MenuObject("SETTINGS", "MAIN_MENU", nullptr, 0, settingsItems, 4) {}

void SettingsMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  drawMenuPaged(u8, "Settings", items, itemCount, selectedIndex, 4);
}
void SettingsMenuContext::update(void* /*gfx*/) {
  // No periodic work yet.
}

void SettingsMenuContext::handleInput(int input) {
  if (input == 1) {
    if (selectedIndex == 3) setContextByName("MAIN_MENU");
    // Could add logic for launching submenus here
  }
  else if (input == 2) {
    selectedIndex = (selectedIndex + 1) % itemCount;
  }
  else if (input == 3) {
    selectedIndex = (selectedIndex + itemCount - 1) % itemCount;
  }
  if (input == 0) {
    if (goBack()) return;             // BACK
  if (goBack()) return;       // reliable, uses parentName
  // Optional: Serial.println("No parent to go back to");
}

}

SettingsMenuContext settingsMenuContext;

__attribute__((constructor))
void registerSettingsMenuContext() {
  registerContext("SETTINGS", &settingsMenuContext);
}
