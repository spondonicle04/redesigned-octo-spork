// menu_main.cpp
// Main menu context with selectable items

#include "menu_main.h"
#include "context_registry.h"
#include "context_state.h"
#include <U8g2lib.h>
#include <Arduino.h>
#include <avr/pgmspace.h>
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

// ---------- PROGMEM labels ----------
const char M_MAIN_0[] PROGMEM = "Pattern Menu";
const char M_MAIN_1[] PROGMEM = "Live Menu";
const char M_MAIN_2[] PROGMEM = "Settings";
const char M_MAIN_3[] PROGMEM = "Save Menu";
const char M_MAIN_4[] PROGMEM = "Debug Menu";

// Pointer table also lives in PROGMEM
const char* const MENU_MAIN_ITEMS[] PROGMEM = {
  M_MAIN_0, M_MAIN_1, M_MAIN_2, M_MAIN_3, M_MAIN_4
};
const uint8_t MENU_MAIN_COUNT = 5;

// --- MainMenuContext subclass ---
MainMenuContext::MainMenuContext()
  : MenuObject("MAIN_MENU", "BOOT",
               /*subs*/ nullptr, /*subCount*/ 0,
               /*menuItems*/ MENU_MAIN_ITEMS, /*menuItemCount*/ MENU_MAIN_COUNT) {}

// Small helpers local to this file for PROGMEM access

void MainMenuContext::draw(void* gfx) {
  U8G2* u8 = (U8G2*)gfx;
  if (!u8) return;

  const uint8_t rows = 4;

  // Compute start so selected item is roughly centered
  int count = (int)itemCount;
  int sel   = (int)selectedIndex;
  int start = 0;
  if (count > rows) {
    int center = sel - (rows / 2);
    if (center < 0) center = 0;
    int maxStart = count - rows;
    if (center > maxStart) center = maxStart;
    start = center;
  }

  u8->firstPage();
  do {
    // Title (centered, with side lines)
    drawTitleWithLines(u8, "Main Menu", /*y=*/12, /*gapPx=*/6);

    // List items
    u8->setFont(u8g2_font_6x10_tf);
    const int startY = 26;   // first row baseline
    const int lineH  = 12;   // row spacing

    for (int row = 0; row < rows && (start + row) < count; ++row) {
      int i = start + row;
      int y = startY + row * lineH;

      const char* p = readPtrP(items, (uint8_t)i);

      if (i == sel) {
        // Highlight bar
        u8->drawBox(0, y - 10, 128, 12);
        u8->setDrawColor(0);
        drawProgmemStr(u8, 4, y, p);
        u8->setDrawColor(1);
      } else {
        drawProgmemStr(u8, 4, y, p);
      }
    }

    // Simple scrollbar
    if (count > rows) {
      const int barX = 125;
      const int barTop = 16;
      const int barH = 48;

      u8->drawVLine(barX, barTop, barH);

      int knobH = (rows * barH) / count;
      if (knobH < 6) knobH = 6;

      int maxStart = (count - rows);
      if (maxStart <= 0) maxStart = 1;
      int knobY = barTop + (int)((start * (barH - knobH)) / (float)maxStart);
      u8->drawBox(barX - 1, knobY, 3, knobH);
    }
  } while (u8->nextPage());
}

void MainMenuContext::handleInput(int input) {
  // Map your existing input codes (1=enter, 2=down, 3=up, 0=back)
  if (input == 1) { // enter/select
    switch (selectedIndex) {
      case 0: setContextByName("PATTERN_MENU"); break;
      case 1: setContextByName("SETTINGS");     break;
      case 2: setContextByName("LIVE_MODE");    break;
      case 3: setContextByName("SAVE_MENU");    break;
      case 4: setContextByName("DEBUG");        break;
    }
  } else if (input == 2) { // down
    selectedIndex = (uint8_t)((selectedIndex + 1) % itemCount);
  } else if (input == 3) { // up
    selectedIndex = (uint8_t)((selectedIndex + itemCount - 1) % itemCount);
  } else if (input == 0) { // back
    if (goBack()) return;
    // Optional: fallback to root if you want:
    // setContextByName("MAIN_MENU");
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
