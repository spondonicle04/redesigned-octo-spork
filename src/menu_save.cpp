// menu_save.cpp
// Save menu context

#include "menu_save.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for SAVE_MENU
static const Transition SAVE_MENU_TRANSITIONS[] = {
  {"SAVE_MENU", 0, "MAIN_MENU"},
};
static const unsigned SAVE_MENU_TRANSITION_COUNT = sizeof(SAVE_MENU_TRANSITIONS)/sizeof(SAVE_MENU_TRANSITIONS[0]);

static const char* saveMenuItems[] = {
  "Save Pattern",
  "Save All",
  "Back"
};

SaveMenuContext::SaveMenuContext()
  : MenuObject("SAVE_MENU", "MAIN_MENU", nullptr, 0, saveMenuItems, 3) {}

void SaveMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  drawMenuPaged(u8, "Save Menu", items, itemCount, selectedIndex, 4);
}

void SaveMenuContext::handleInput(int input) {
  if (input == 1) {
    if (selectedIndex == 2) setContextByName("MAIN_MENU");
    // else pretend to save for now
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

SaveMenuContext saveMenuContext;

__attribute__((constructor))
void registerSaveMenuContext() {
  registerContext("SAVE_MENU", &saveMenuContext);
}

void SaveMenuContext::update(void* /*gfx*/) {}
