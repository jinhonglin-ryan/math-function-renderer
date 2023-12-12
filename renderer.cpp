#include <exception>
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();

  // call the helper functions
  render_fill();
  render_func();

  return img.release();
}

// TODO: implement private helper functions
void Renderer::render_fill() {
  std::vector<Fill*> fills = m_plot.get_fills();

  for (size_t i = 0; i < fills.size(); i++) {
    Fill *fill = fills.at(i);

    for (int row = 0; row < m_img->get_height(); row++) {
      for (int col = 0; col < m_img->get_width(); col++) {

        if (in_fill(row, col, *(m_plot.get_bounds()), *fill)) {
          const Color orig_color = m_img->get_pixel(row, col);
          Color new_color = blend_color(orig_color, fill->get_color(), fill->get_opacity());
          m_img->set_pixel(row, col, new_color);
        }
      }
    }
  }
}

bool Renderer::in_fill(int row, int col, Bounds bounds, Fill& fill) const {
  double xmin = bounds.get_xmin();
  double ymin = bounds.get_ymin();
  double xmax = bounds.get_xmax();
  double ymax = bounds.get_ymax();
  int width = m_img->get_width();
  int height = m_img->get_height();

  int fill_type = fill.get_fill_type();

  double x = xmin + ((double)col / width) * (xmax - xmin);
  double y = ymin + ((height - 1 - row) / (double)height) * (ymax - ymin);

  switch (fill_type) {
    case 1:
      return y > fill.get_f1(m_plot.get_func(), fill.get_f1_name())->get_expr()->eval(x);
    case 2:
      return y < fill.get_f1(m_plot.get_func(), fill.get_f1_name())->get_expr()->eval(x);
    case 3:
      if (fill.get_f2(m_plot.get_func(), fill.get_f2_name()) == NULL) { throw PlotException("Error: second function not specified"); }
      return (y > fill.get_f1(m_plot.get_func(), fill.get_f1_name())->get_expr()->eval(x) && 
              y < fill.get_f2(m_plot.get_func(), fill.get_f2_name())->get_expr()->eval(x)) ||
              (y < fill.get_f1(m_plot.get_func(), fill.get_f1_name())->get_expr()->eval(x) && 
              y > fill.get_f2(m_plot.get_func(), fill.get_f2_name())->get_expr()->eval(x));
    default:
      throw PlotException("Error: invalid fill_type value");
  }
}

Color Renderer::blend_color(const Color& orig_color, const Color& fill_color, float opacity) const {
  uint8_t r_new = floor((1-opacity) * orig_color.r + opacity * fill_color.r);
  uint8_t g_new = floor((1-opacity) * orig_color.g + opacity * fill_color.g);
  uint8_t b_new = floor((1-opacity) * orig_color.b + opacity * fill_color.b);

  return Color({r_new, g_new, b_new});
}

void Renderer::render_func() {
  std::vector<Function*> functions = m_plot.get_func();

  Bounds *bounds = m_plot.get_bounds();
  double xmin = bounds->get_xmin();
  double ymin = bounds->get_ymin();
  double xmax = bounds->get_xmax();
  double ymax = bounds->get_ymax();
  int width = m_plot.get_width();
  int height = m_plot.get_height();
  
  for (size_t i = 0; i < functions.size(); i++) {
    Function *func = functions.at(i);

    for (int col = 0; col < m_img->get_width(); col++) {
      double y = func->get_expr()->eval(xmin + (((double)col / width) * (xmax - xmin)));
      int row = height - 1 - floor((((double)(y - ymin) / (ymax - ymin)) * height));

      Color* color = func->get_color();
      m_img->set_pixel(row, col, *color);
      if (col - 1 >= 0) {
        m_img->set_pixel(row, col - 1,*color);
      }
      if (col + 1 < width) {
        m_img->set_pixel(row, col + 1, *color);
      }
      if (row + 1 < height) {
        m_img->set_pixel(row + 1, col, *color);
      }
      if (row - 1 >= 0) {
        m_img->set_pixel(row - 1, col, *color);
      }
    }
  }
}
