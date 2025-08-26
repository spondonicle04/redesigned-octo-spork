// hal_buttons_simple.cpp
#include <Arduino.h>
#include "hal_buttons_simple.h"  // provides FnKey enum + prototypes
#include "event_bus.h"           // eb_push(...)
#include "config.h"              // BTN_SELECT/BTN_DOWN/BTN_UP/BTN_LIVE/BTN_BACK

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// --------- Default pins if not overridden in config.h ----------
#ifndef BTN_SELECT
#define BTN_SELECT 3
#endif
#ifndef BTN_DOWN
#define BTN_DOWN 4
#endif
#ifndef BTN_UP
#define BTN_UP 5
#endif
#ifndef BTN_LIVE
#define BTN_LIVE 42
#endif
#ifndef BTN_BACK
#define BTN_BACK 46
#endif
// ---------------------------------------------------------------

// Helper to push function-key events onto the bus
static inline void pushFn(FnKey key, bool isDown) {
  Event e;
  e.src  = SRC_FN_KEYS;
  e.a    = key;         // which function key
  e.b    = 0;
  e.type = isDown ? EVT_KEY_DOWN : EVT_KEY_UP;
  eb_push(e);
}

// One struct per button we watch
struct Btn {
  uint8_t pin;
  uint8_t last;           // last stable level (HIGH/LOW)
  unsigned long tLast;    // last time we toggled (for debounce)
  FnKey key;              // semantic key
  const char* name;       // for serial debug
};

// Our button table
static Btn btns[] = {
  { BTN_SELECT, HIGH, 0, FN_SELECT, "SELECT" },
  { BTN_DOWN,   HIGH, 0, FN_DOWN,   "DOWN"   },
  { BTN_UP,     HIGH, 0, FN_UP,     "UP"     },
  { BTN_LIVE,   HIGH, 0, FN_LIVE,   "LIVE"   },
  { BTN_BACK,   HIGH, 0, FN_BACK,   "BACK"   },
};

void hal_buttons_setup() {
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_DOWN,   INPUT_PULLUP);
  pinMode(BTN_UP,     INPUT_PULLUP);
  pinMode(BTN_LIVE,   INPUT_PULLUP);
  pinMode(BTN_BACK,   INPUT_PULLUP);

  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);

  // Announce which pins we're watching
  Serial.print("BTN_SELECT="); Serial.println(BTN_SELECT);
  Serial.print("BTN_DOWN=");   Serial.println(BTN_DOWN);
  Serial.print("BTN_UP=");     Serial.println(BTN_UP);
  Serial.print("BTN_LIVE=");   Serial.println(BTN_LIVE);
  Serial.print("BTN_BACK=");   Serial.println(BTN_BACK);
}

void hal_buttons_poll() {
  const unsigned long now = millis();

  // Raw level dump every ~500 ms (helps when probing with a GND wire)
  static unsigned long lastDump = 0;
  if (now - lastDump > 500) {
    lastDump = now;
    Serial.print("RAW ");
    for (auto &b : btns) {
      Serial.print(b.name); Serial.print("=");
      Serial.print(digitalRead(b.pin) == LOW ? "L " : "H ");
    }
    Serial.println();
  }

  // Debounce + edge detection (25 ms)
  for (auto &b : btns) {
    uint8_t v = digitalRead(b.pin); // HIGH = released, LOW = pressed (INPUT_PULLUP)
    if (v != b.last && (now - b.tLast) >= 25) {
      b.tLast = now;
      b.last  = v;

      // Blink LED while any key is held
      // if (v == LOW) digitalWrite(LED_BUILTIN, HIGH);
      //else          digitalWrite(LED_BUILTIN, LOW);

      Serial.print("EDGE "); Serial.print(b.name);
      Serial.println(v == LOW ? " DOWN" : " UP");

      pushFn(b.key, v == LOW);
    }
  }
}
