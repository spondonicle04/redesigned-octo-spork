// object_classes.h
// Sacred definition of all core object types used in the modular context engine.
// This file shall not be edited lightly. Break its laws at your own peril.

#ifndef OBJECT_CLASSES_H
#define OBJECT_CLASSES_H

#include <stdint.h>
#include <stddef.h>

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
  const char** subcontextNames;
  size_t subcontextCount;

  ContextObject(const char* name, const char* parent, const char** subs, size_t count)
    : BaseObject(name), parentName(parent), subcontextNames(subs), subcontextCount(count) {}

  virtual void draw(void* gfx) {}       // Accepts U8G2* or similar
  virtual void handleInput(int input) {}
  virtual void update(void* gfx) {}
  virtual void output(int signal) {}
};

//-----------------------------------
// 📜 Menu Object (a type of Context)
//-----------------------------------
class MenuObject : public ContextObject {
public:
  const char** items;
  size_t itemCount;
  size_t selectedIndex;

  MenuObject(const char* name, const char* parent, const char** subs, size_t subCount,
             const char** menuItems, size_t menuItemCount)
    : ContextObject(name, parent, subs, subCount),
      items(menuItems), itemCount(menuItemCount), selectedIndex(0) {}

  virtual void select() {} // override if item is chosen
};

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

  virtual void set(bool state) {}  // Turn on/off, send MIDI, etc.
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
  virtual void registerObject(BaseObject* obj) {}
};

#endif // OBJECT_CLASSES_H
