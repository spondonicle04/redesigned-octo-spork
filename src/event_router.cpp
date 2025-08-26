// event_router.cpp — matches your Event bus + FnKey enums
#include "event_router.h"
#include "context_state.h"        // currentContext(), setContextByName(), goBack()
#include "input_codes.h"          // IN_SELECT/IN_UP/IN_DOWN/IN_BACK/...
#include "event_bus.h"            // Event, eb_pop(), EventType, EventSource
#include "hal_buttons_simple.h"   // FnKey (FN_SELECT, FN_DOWN, FN_UP, FN_LIVE, FN_BACK)
#include <Arduino.h>

// Helper: send a mapped InputCode to the active context
static void deliverToContext(InputCode code) {
  ContextObject* ctx = currentContext();   // <- call the getter
  if (ctx) ctx->handleInput((int)code);
}

// Handle a hardware function key (buttons)
static void handleFnKey(uint8_t fn) {
  switch (fn) {
    case FN_SELECT: deliverToContext(IN_SELECT); break;
    case FN_UP:     deliverToContext(IN_UP);     break;
    case FN_DOWN:   deliverToContext(IN_DOWN);   break;
    // If you wire these later, uncomment:
    // case FN_LEFT:   deliverToContext(IN_LEFT);   break;
    // case FN_RIGHT:  deliverToContext(IN_RIGHT);  break;

    case FN_BACK:
      if (!goBack()) setContextByName("MAIN_MENU");   // fallback root name
      break;

    case FN_LIVE:
      setContextByName("LIVE_MODE");                  // <-- exact name you register
      break;

    default:
      break;
  }
}

// Drain the event bus and route inputs
void route_events() {
  Event e;
  while (eb_pop(e)) {
    // We only care about function-key presses here (not releases)
    if (e.type == EVT_KEY_DOWN /*press*/ && e.src == SRC_FN_KEYS) {
      handleFnKey((uint8_t)e.a);   // e.a carries FnKey
      continue;
    }

    // Add other routing here later (pots, matrix, clock, etc.)
  }
}
