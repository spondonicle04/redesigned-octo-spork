// event_bus.h
#ifndef EVENT_BUS_H
#define EVENT_BUS_H
#include <stdint.h>


// Event types your HAL can emit
enum EventType : uint8_t {
EVT_NONE = 0,
EVT_KEY_DOWN,
EVT_KEY_UP,
EVT_POT_MOVE,
EVT_TICK_1MS,
EVT_TICK_24PPQN
};


// Event sources (which device produced the event)
// Extend as needed (matrices, pots, encoders, ext clock, etc.)
enum EventSource : uint8_t {
SRC_NONE = 0,
SRC_FN_KEYS = 1, // function button bank (includes BTN_LIVE, SELECT, UP/DOWN)
SRC_MATRIX_A = 2,
SRC_MATRIX_B = 3,
SRC_POTS = 4,
SRC_CLOCK = 5
};


struct Event {
EventType type;
EventSource src;
uint16_t a; // payload (row, pot idx, etc.)
uint16_t b; // payload (col, value, etc.)
};


// Push/pop (ring buffer). Use eb_pushFromISR in ISRs.
bool eb_push(const Event& e);
bool eb_pushFromISR(const Event& e);
bool eb_pop(Event& e);


#endif // EVENT_BUS_H