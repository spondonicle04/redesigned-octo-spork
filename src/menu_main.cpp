// menu_main.cpp
// Main menu context with selectable items

#include "menu_main.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include "ui_draw.h"
#include "events.h"
#include "transitions.h"

// Transition table for MAIN_MENU selections.
// We encode selectedIndex as code 100 + index.
static const Transition MAIN_MENU_TRANSITIONS[] = {
  {"MAIN_MENU", 100, "PATTERN_MENU"},
  {"MAIN_MENU", 101, "SETTINGS"},
  {"MAIN_MENU", 102, "LIVE_MODE"},
  {"MAIN_MENU", 103, "SAVE_MENU"},
  {"MAIN_MENU", 104, "DEBUG"},
};
static const unsigned int MAIN_MENU_TRANSITION_COUNT =
  sizeof(MAIN_MENU_TRANSITIONS)/sizeof(MAIN_MENU_TRANSITIONS[0]);


// Define menu item labels
static const char* mainMenuItems[] = {
  "Pattern Menu",
  "Settings",
  "Live Mode",
  "Save Menu",
  "Debug"
};

// --- MainMenuContext subclass ---
MainMenuContext::MainMenuContext()
  : MenuObject("MAIN_MENU", "BOOT", nullptr, 0, mainMenuItems, 5) {}

void MainMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  drawMenuPaged(u8, "Main Menu", items, itemCount, selectedIndex, 4);
}

void MainMenuContext::handleInput(int input) {
  Serial.print("MAIN input="); Serial.println(input);
  if (input == 1) { // Simulated enter
    // Hardcoded action for demo
    if (selectedIndex == 0) setContextByName("PATTERN_MENU");
    else if (selectedIndex == 1) setContextByName("SETTINGS");
    else if (selectedIndex == 2) setContextByName("LIVE_MODE");
    else if (selectedIndex == 3) setContextByName("SAVE_MENU");
    else if (selectedIndex == 4) setContextByName("DEBUG");
  }
  else if (input == 2) { // Simulate down
    selectedIndex = (selectedIndex + 1) % itemCount;
  }
  else if (input == 3) { // Simulate up
    selectedIndex = (selectedIndex + itemCount - 1) % itemCount;
  }
  if (input == 0) {
    if (goBack()) return;             // BACK
  if (goBack()) return;       // reliable, uses parentName
  // Optional: Serial.println("No parent to go back to");
}

}
void MainMenuContext::update(void* /*gfx*/) {
  // No time-based animation yet; keep it simple.
}

// --- Global instance + registration ---
MainMenuContext mainMenuContext;

__attribute__((constructor))
void registerMainMenuContext() {
  registerContext("MAIN_MENU", &mainMenuContext);
}
