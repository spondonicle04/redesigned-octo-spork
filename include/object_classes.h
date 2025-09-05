// object_classes.h
// Sacred definition of all core object types used in the modular context engine.
// This file shall not be edited lightly. Break its laws at your own peril.

#ifndef OBJECT_CLASSES_H
#define OBJECT_CLASSES_H

#include "config.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>  // for UINTPTR_MAX in guarded asserts
#include <avr/pgmspace.h> // for PROGMEM reading
#include "input_codes.h"



// external navigation helpers – implemented elsewhere
extern bool goBack();
extern bool setContextByName(const char* name);

//-----------------------------------
// 🧱 Base Object
//-----------------------------------
class BaseObject {
public:
  const char* name;
  BaseObject(const char* n) : name(n) {}
  virtual ~BaseObject() {}
};


//-----------------------------------
// 🖥️ Context Object
//-----------------------------------
class ContextObject : public BaseObject {
public:
  const char* parentName;
  const char* const* subcontextNames;  // pointer to table of const char*
  uint8_t subcontextCount;

  ContextObject(const char* name, const char* parent, const char* const* subs, uint8_t count)
    : BaseObject(name), parentName(parent), subcontextNames(subs), subcontextCount(count) {}

  virtual void draw(void* /*gfx*/) {}       // Accepts U8G2* or similar
  virtual void handleInput(int /*input*/) {}
  virtual void update(void* /*gfx*/) {}
  virtual void output(int /*signal*/) {}
};
class MenuObject : public ContextObject {
public:
  const char* const* items;   // pointer to label table (RAM or PROGMEM)
  uint8_t itemCount;
  uint8_t selectedIndex;

  // NEW: if false, default handler ignores select (menu can be view-only)
  bool autoSelectEnabled;

  MenuObject(const char* name, const char* parent,
             const char* const* subs, uint8_t subCount,
             const char* const* menuItems, uint8_t menuItemCount,
             bool autoSelect = true)
    : ContextObject(name, parent, subs, subCount),
      items(menuItems), itemCount(menuItemCount), selectedIndex(0),
      autoSelectEnabled(autoSelect) {}

  // Hook: override in a specific menu if you want custom action on select.
  // Return true if you handled it (to suppress default behavior).
  virtual bool onSelect(uint8_t /*index*/) { return false; }

  // Generic navigation + select using subcontextNames (subs)
  virtual void handleInput(int input) override {
    if (input == KEY_SELECT) {
      if (onSelect(selectedIndex)) return;           // custom behavior took it
      if (!autoSelectEnabled) return;                // menu opted out
      if (subcontextNames && selectedIndex < subcontextCount) {
        const char* dest =
          (const char*)pgm_read_ptr(&subcontextNames[selectedIndex]); // PROGMEM-safe
        if (dest && dest[0]) setContextByName(dest);
      }
    } else if (input == KEY_DOWN) {
      if (itemCount) selectedIndex = (uint8_t)((selectedIndex + 1) % itemCount);
    } else if (input == KEY_UP) {
      if (itemCount) selectedIndex = (uint8_t)((selectedIndex + itemCount - 1) % itemCount);
    } else if (input == KEY_BACK) {
      (void)goBack();
    }
  }

  virtual void select() {} // legacy hook (kept for compatibility)
};

// //-----------------------------------
// // 📜 Menu Object (a type of Context)
// //-----------------------------------
// class MenuObject : public ContextObject {
// public:
//   const char* const* items;  // pointer to table of const char*
//   uint8_t itemCount;
//   uint8_t selectedIndex;

//   MenuObject(const char* name, const char* parent, const char* const* subs, uint8_t subCount,
//              const char* const* menuItems, uint8_t menuItemCount)
//     : ContextObject(name, parent, subs, subCount),
//       items(menuItems), itemCount(menuItemCount), selectedIndex(0) {}

//   virtual void select() {} // override if item is chosen
// };

// ===== Compile-time sanity checks (only on real AVR C++ builds, not IntelliSense) =====
#if defined(__cplusplus) && defined(__AVR__) && !defined(__INTELLISENSE__)

// On AVR, pointers are 16-bit; gate on uintptr_t to avoid host/editor models.
#if (UINTPTR_MAX == 0xFFFFu)
static_assert(sizeof(const char*) == 2, "AVR: expected 16-bit pointers");
#endif

// Sizes are conservative to avoid flapping if base layout shifts.
// (AVR: vptr ~2, each pointer 2, small fields 1.)
static_assert(sizeof(ContextObject) <= 24, "ContextObject grew unexpectedly");
static_assert(sizeof(MenuObject)    <= 28, "MenuObject grew unexpectedly");

#endif // guarded asserts

//-----------------------------------
// 🎛️ Input Object
//-----------------------------------
class InputObject : public BaseObject {
public:
  int pin;
  bool isEncoder;

  InputObject(const char* name, int pinNumber, bool encoder = false)
    : BaseObject(name), pin(pinNumber), isEncoder(encoder) {}
};

//-----------------------------------
// 💡 Output Object
//-----------------------------------
class OutputObject : public BaseObject {
public:
  int pin;

  OutputObject(const char* name, int pinNumber)
    : BaseObject(name), pin(pinNumber) {}

  virtual void set(bool /*state*/) {}  // Turn on/off, send MIDI, etc.
};

//-----------------------------------
// ⚙️ State Object
//-----------------------------------
class StateObject : public BaseObject {
public:
  int value;

  StateObject(const char* name, int initialValue = 0)
    : BaseObject(name), value(initialValue) {}
};

//-----------------------------------
// 🎬 Action Object
//-----------------------------------
class ActionObject : public BaseObject {
public:
  ActionObject(const char* name) : BaseObject(name) {}
  virtual void execute() {} // perform action
};

//-----------------------------------
// 📚 Registry Object
//-----------------------------------
class RegistryObject : public BaseObject {
public:
  RegistryObject() : BaseObject("Registry") {}
  virtual void registerObject(BaseObject* /*obj*/) {}
};

#endif // OBJECT_CLASSES_H
