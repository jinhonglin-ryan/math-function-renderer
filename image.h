#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height; // dimensions of the Image
  Color *m_pixels; // an array of pixel colors

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  /** constructor for an Image
   *  @param width of the image
   *  @param height of the image
   */
  Image(int width, int height);

  /** The destructor releases allocated memory as needed to avoid leaks. */
  ~Image();

  /** function to retrieve width of image
   *  @return width
   */
  int get_width() const { return m_width; }

  /** function to retrieve height of image
   *  @return height
   */
  int get_height() const { return m_height; }

  /** function to retrieve the array of pixels in the image
   *  @return pointer to an array of pixels
   */
  const Color* get_pixels() const;

  /** function to retrieve a pixel
   *  @param row
   *  @param col
   *  @return a reference to the Color object
   */
  const Color& get_pixel(int row, int col) const;

  /** function to retrieve a pixel
   *  @param row
   *  @param col
   *  @param color of the intended pixel
   *  @return a reference to the Color object
   */
  void set_pixel(int row, int col, const Color& color);

  void write_png(std::ostream &out);
};

#endif // IMAGE_H
