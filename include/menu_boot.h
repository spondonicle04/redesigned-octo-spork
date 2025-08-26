// menu_boot.h
// Declaration for the BOOT context.

#ifndef MENU_BOOT_H
#define MENU_BOOT_H

#include "object_classes.h"

// Subclass of ContextObject with custom behavior
class BootContext : public ContextObject {
public:
  BootContext();
  void draw(void* gfx) override;
  void handleInput(int input) override;
};

extern BootContext bootContext;

#endif // MENU_BOOT_H
