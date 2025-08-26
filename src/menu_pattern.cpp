// menu_pattern.cpp
#include "menu_pattern.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include "events.h"
#include "transitions.h"
#include "ui_draw.h"

// Back transitions for PATTERN_MENU
static const Transition PATTERN_MENU_TRANSITIONS[] = {
  {"PATTERN_MENU", 0, "MAIN_MENU"},
};
static const unsigned PATTERN_MENU_TRANSITION_COUNT = sizeof(PATTERN_MENU_TRANSITIONS)/sizeof(PATTERN_MENU_TRANSITIONS[0]);

static const char* patternItems[] = {
  "Pattern 1",
  "Pattern 2",
  "Pattern 3"
};

PatternMenuContext::PatternMenuContext()
  : MenuObject("PATTERN_MENU", "MAIN_MENU", nullptr, 0, patternItems, 3) {}

void PatternMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  drawMenuPaged(u8, "Pattern Menu", items, itemCount, selectedIndex, 4);
}

void PatternMenuContext::handleInput(int input) {
  if (input == 1) {
    // Simulate select or go back
    setContextByName("MAIN_MENU");
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

PatternMenuContext patternMenuContext;

__attribute__((constructor))
void registerPatternMenuContext() {
  registerContext("PATTERN_MENU", &patternMenuContext);
}

void PatternMenuContext::update(void* /*gfx*/) {}
