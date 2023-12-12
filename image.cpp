#include "pnglite.h"
#include "exception.h"
#include "image.h"

namespace {

struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite;

unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error: writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_pixels(new Color[width * height]) {
  // TODO: initialize pixel data
  for (int i = 0; i < m_width * m_height; i++) {
    m_pixels[i].set_color(0, 0, 0); // set the color to black by default
  }
}

Image::~Image() {
  // TODO: deallocate memory
  delete[] m_pixels;
}

// returns an array of pixels
const Color* Image::get_pixels() const {
  return m_pixels;
}

void Image::set_pixel(int row, int col, const Color& color) {
  if (row < m_height && row >= 0 && col < m_width && col >= 0) {
    int index = row * m_width + col;
    m_pixels[index] = color;
  }
  else {
    throw PlotException("Error: invalid row and col for setting the color of the pixel");
  }
}

// returns a single pixel based on the row and column provided
const Color& Image::get_pixel(int row, int col) const {
  if (row < m_height && row >= 0 && col < m_width && col >= 0) {
    return m_pixels[row * m_width + col];
  }
  else {
    throw PlotException("Error: invalid row and col for getting the color of the pixel");
  }
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error: opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(get_pixels());
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error: converting writing image data as PNG");
  }
}
