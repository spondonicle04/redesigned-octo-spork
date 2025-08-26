// menu_debug.cpp
// Debug context

#include "menu_debug.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for DEBUG
static const Transition DEBUG_TRANSITIONS[] = {
  {"DEBUG", 0, "MAIN_MENU"},
};
static const unsigned DEBUG_TRANSITION_COUNT = sizeof(DEBUG_TRANSITIONS)/sizeof(DEBUG_TRANSITIONS[0]);

static const char* debugItems[] = {
  "System Info",
  "Test Beep",
  "Back"
};

DebugMenuContext::DebugMenuContext()
  : MenuObject("DEBUG", "MAIN_MENU", nullptr, 0, debugItems, 3) {}

void DebugMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  drawMenuPaged(u8, "Debug", items, itemCount, selectedIndex, 4);
}

void DebugMenuContext::handleInput(int input) {
  if (input == 1) {
    if (selectedIndex == 2) setContextByName("MAIN_MENU");
    // Add actual debug action stubs here later
  }
  else if (input == 2) {
    selectedIndex = (selectedIndex + 1) % itemCount;
  }
  else if (input == 3) {
    selectedIndex = (selectedIndex + itemCount - 1) % itemCount;
  }
  if (input == 0) {
    if (goBack()) return;             // BACK
 // if (goBack()) return;       // reliable, uses parentName
  // Optional: Serial.println("No parent to go back to");
}

}

DebugMenuContext debugMenuContext;

__attribute__((constructor))
void registerDebugMenuContext() {
  registerContext("DEBUG", &debugMenuContext);
}

void DebugMenuContext::update(void* /*gfx*/) {}
