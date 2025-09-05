// main.cpp
// Startup sketch for modular context engine
#include <Arduino.h>
#include "config.h"
#include "context_registry.h"
#include "menu_boot.h"
#include "object_classes.h"
#include "context_state.h"
#include "contexts_init.h"
#include "debug.h"
#include "hal_buttons_simple.h"
#include "event_router.h"
#include <avr/wdt.h>
#include <avr/io.h>

// Optional display object
#include <U8g2lib.h>
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, LCD_CLK, LCD_MOSI, LCD_CS);

void setup() {
  //Serial.begin(115200);
  DEBUG_BEGIN();
  hal_buttons_setup();
  DL("Booting Context Engine...");
  
  // Init display
  u8g2.begin();

  // Init input manager (this sets up pins for all inputs declared in config)
  //initInputManager();

  // Register contexts (menus, live mode, etc.)
  registerAllContexts();

  // Start in LIVE mode (grid) instead of BOOT
  setContextByName("LIVE_MODE");

  DL("Setup complete.");
}


void loop() {
  hal_buttons_poll();  // produce events
  route_events();      // consume + deliver
  if (currentContext()) {
    if (auto* ctx = currentContext()) {
      ctx->update(&u8g2);
      ctx->draw(&u8g2);
    }
  }
}
