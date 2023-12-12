#include <cassert>
#include "plot.h"

// default constructor
Plot::Plot()
  : bounds(), image(nullptr), functions(), fills()
{}

// delete all the allocated memories
Plot::~Plot()
{
  delete image;
  for (std::vector<Function*>::iterator it = functions.begin(); it != functions.end(); ++it) {
    delete *it;
  }
  for (std::vector<Fill*>::iterator it = fills.begin(); it != fills.end(); ++it) {
    delete *it;
  }
  delete bounds;
}

void Plot::set_bounds(float xmin, float xmax, float ymin, float ymax) {
  bounds = new Bounds(xmin, xmax, ymin, ymax);
}

void Plot::set_image(int width, int height) {
  if (width < 0 || height < 0) {
    throw PlotException("Error: invalid image dimensions");
  }
  image = new Image(width, height);
}

void Plot::add_function(std::string &name, Expr *expr) {
  functions.push_back(new Function(name, expr));
}

void Plot::set_color(std::string f_name, int ri, int gi, int bi) {
  if (ri > 255 || ri < 0 || gi > 255 || gi < 0 || bi > 255 || bi < 0) {
    throw PlotException("Error: invalid pixel values");
  }

  int exist = 0;
  uint8_t r = (uint8_t)ri;
  uint8_t g = (uint8_t)gi;
  uint8_t b = (uint8_t)bi;
  std::vector<Function*> funcs = get_func();
  for (std::vector<Function*>::iterator it = funcs.begin(); it != funcs.end(); ++it) {
    if ((*it)->get_name() == f_name) {
      exist++;
      if ((*it)->get_change() == 0) {
        (*it)->set_color(r, g, b);
      }
      else {
        throw PlotException("Error: more than one Color directive for a function");
      }
    }
  }
  if (exist != 1) {
    throw PlotException("Error: function does not exist");
  }
}

void Plot::add_fill(std::string f1, float opacity, int ri, int gi, int bi, int type) {
  uint8_t r = (uint8_t)ri;
  uint8_t g = (uint8_t)gi;
  uint8_t b = (uint8_t)bi;
  fills.push_back(new Fill(f1, opacity, r, g, b, type));
}

void Plot::add_fill_2(std::string f1, std::string f2, float opacity, int ri, int gi, int bi, int type) {
  uint8_t r = (uint8_t)ri;
  uint8_t g = (uint8_t)gi;
  uint8_t b = (uint8_t)bi;
  fills.push_back(new Fill(f1, f2, opacity, r, g, b, type));
}

int Plot::get_width() const {
  int width = image->get_width();
  return width;
}

int Plot::get_height() const {
  int height = image->get_height();
  return height;
}