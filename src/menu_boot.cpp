// menu_boot.cpp
// Boot context: splash screen or welcome screen

#include "menu_boot.h"
#include "context_registry.h"
#include "object_classes.h"
#include "context_state.h"
#include "events.h"
#include "transitions.h"

static const Transition XXX_TRANSITIONS[] = {
  {"LIVE_MODE", 0, "MAIN_MENU"},       // example for Live
  {"PATTERN_MENU", 0, "MAIN_MENU"},    // example for Pattern
  {"SAVE_MENU", 0, "MAIN_MENU"},       // example for Save
  {"DEBUG", 0, "MAIN_MENU"},           // example for Debug
};
static const unsigned XXX_COUNT = sizeof(XXX_TRANSITIONS)/sizeof(XXX_TRANSITIONS[0]);

// --- BootContext class definition ---
BootContext::BootContext()
  : ContextObject("BOOT", nullptr, nullptr, 0) {}

void BootContext::draw(void* gfx) {
  // Example using U8G2* (cast from void*)
  // U8G2* u8g2 = static_cast<U8G2*>(gfx);
  // u8g2->clearBuffer();
  // u8g2->setFont(u8g2_font_ncenB08_tr);
  // u8g2->drawStr(0, 24, "Welcome to the Boot Menu");
  // u8g2->sendBuffer();
}

void BootContext::handleInput(int input) {
  if (input >= 0) {
    setContextByName("MAIN_MENU");

  }
}

// --- Global instance + registration ---
BootContext bootContext;

__attribute__((constructor))
void registerBootContext() {
  registerContext("BOOT", &bootContext);
}
