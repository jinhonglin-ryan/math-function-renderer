#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cassert>

struct Color {
  uint8_t r = 255, g = 255, b = 255;

  /** member function to set rgb values
   *  @param red color value
   *  @param green color value
   *  @param blue color value
   */
  void set_color(uint8_t red, uint8_t green, uint8_t blue) {
    r = red;
    g = green;
    b = blue;
  }
};

#endif // COLOR_H
