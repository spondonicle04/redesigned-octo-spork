#pragma once
#include <U8g2lib.h>
#include <stddef.h>
#include <avr/pgmspace.h>

// Copy PROGMEM string into a small stack buffer and draw it.
inline void drawProgmemStr(U8G2* u8, int x, int y, const char* p) {
  char buf[22];                      // fit your longest menu label (tune as needed)
  strncpy_P(buf, p, sizeof(buf)-1);
  buf[sizeof(buf)-1] = '\0';
  u8->drawStr(x, y, buf);
}

// Read a char* from a PROGMEM table of pointers
inline const char* readPtrP(const char* const* tableP, uint8_t index) {
  return (const char*)pgm_read_ptr(&tableP[index]);
}

// Centered title with line flourishes on both sides.
// y = text baseline (12 works nicely for 64px-tall displays with 6x13 font)
// gapPx = space between the title and each line.
inline void drawTitleWithLines(U8G2* u8, const char* title, int y = 12, int gapPx = 6) {
  if (!u8 || !title) return;

  u8->setFont(u8g2_font_6x13_tf);

  const int W   = u8->getDisplayWidth();     // usually 128
  const int txt = u8->getUTF8Width(title);   // title width in pixels
  int x = (W - txt) / 2;                     // center the title
  if (x < 0) x = 0;

  // Draw the title
  u8->drawStr(x, y, title);

  // Draw horizontal lines (“flourishes”) on each side
  const int lineY     = y - 5;               // a little above the text
  const int leftEnd   = x - gapPx;           // end of left line
  const int rightBeg  = x + txt + gapPx;     // start of right line

  if (leftEnd > 0)  u8->drawHLine(0,        lineY, leftEnd);
  if (rightBeg < W) u8->drawHLine(rightBeg, lineY, W - rightBeg);
}

/* -------------------------
   RAM-backed items version
   ------------------------- */
inline void drawMenuPagedRam(U8G2* u8,
                             const char* title,
                             const char* const* items,
                             uint8_t count,
                             uint8_t selected,
                             uint8_t rows = 4)
{
  if (!u8) return;
  if (rows < 1) rows = 1;

  uint8_t maxStart = (count > rows) ? (count - rows) : 0;
  uint8_t start = 0;
  if (count > rows) {
    int center = (int)selected - (int)rows / 2;
    if (center < 0) center = 0;
    if ((uint8_t)center > maxStart) center = (int)maxStart;
    start = (uint8_t)center;
  }

  u8->firstPage();
  do {
    if (title) drawTitleWithLines(u8, title, /*y=*/12, /*gapPx=*/6);

    u8->setFont(u8g2_font_6x10_tf);
    const int startY = 26;
    const int lineH  = 12;

    for (uint8_t row = 0; row < rows && (start + row) < count; ++row) {
      uint8_t i = (uint8_t)(start + row);
      int y = startY + row * lineH;

      if (i == selected) {
        u8->drawBox(0, y - 10, 128, 12);
        u8->setDrawColor(0);
        u8->drawStr(4, y, items[i]);
        u8->setDrawColor(1);
      } else {
        u8->drawStr(4, y, items[i]);
      }
    }

    if (count > rows) {
      const int barX = 125, barTop = 16, barH = 48;
      u8->drawVLine(barX, barTop, barH);

      int knobH = (rows * barH) / (int)count;
      if (knobH < 6) knobH = 6;

      int maxStartPx = (int)(maxStart ? maxStart : 1);
      int knobY = barTop + (int)((start * (barH - knobH)) / (float)maxStartPx);
      u8->drawBox(barX - 1, knobY, 3, knobH);
    }
  } while (u8->nextPage());
}

/* --------------------------------
   PROGMEM-backed items version (✨)
   -------------------------------- */
inline void drawMenuPagedP(U8G2* u8,
                           const char* title,
                           const char* const* itemsP,  // pointer table in PROGMEM
                           uint8_t count,
                           uint8_t selected,
                           uint8_t rows = 4)
{
  if (!u8) return;
  if (rows < 1) rows = 1;

  uint8_t maxStart = (count > rows) ? (count - rows) : 0;
  uint8_t start = 0;
  if (count > rows) {
    int center = (int)selected - (int)rows / 2;
    if (center < 0) center = 0;
    if ((uint8_t)center > maxStart) center = (int)maxStart;
    start = (uint8_t)center;
  }

  u8->firstPage();
  do {
    if (title) drawTitleWithLines(u8, title, /*y=*/12, /*gapPx=*/6);

    u8->setFont(u8g2_font_6x10_tf);
    const int startY = 26;
    const int lineH  = 12;

    for (uint8_t row = 0; row < rows && (start + row) < count; ++row) {
      uint8_t i = (uint8_t)(start + row);
      int y = startY + row * lineH;

      const char* p = readPtrP(itemsP, i);   // fetch pointer from PROGMEM

      if (i == selected) {
        u8->drawBox(0, y - 10, 128, 12);
        u8->setDrawColor(0);
        drawProgmemStr(u8, 4, y, p);         // copy label from PROGMEM and draw
        u8->setDrawColor(1);
      } else {
        drawProgmemStr(u8, 4, y, p);
      }
    }

    if (count > rows) {
      const int barX = 125, barTop = 16, barH = 48;
      u8->drawVLine(barX, barTop, barH);

      int knobH = (rows * barH) / (int)count;
      if (knobH < 6) knobH = 6;

      int maxStartPx = (int)(maxStart ? maxStart : 1);
      int knobY = barTop + (int)((start * (barH - knobH)) / (float)maxStartPx);
      u8->drawBox(barX - 1, knobY, 3, knobH);
    }
  } while (u8->nextPage());
}

// Back-compat: keep old name pointing to the RAM version
inline void drawMenuPaged(U8G2* u8,
                          const char* title,
                          const char* const* items,
                          uint8_t count,
                          uint8_t selected,
                          uint8_t rows = 4)
{
  drawMenuPagedRam(u8, title, items, count, selected, rows);
}
