#include "func.h"

Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) 
  , color(new Color({255, 255, 255})) // set the color to white by default
{
}

Function::~Function() {
  // TODO: deallocate objects if necessary
  delete m_expr;
  delete color;
}

void Function::set_color(uint8_t r, uint8_t g, uint8_t b) {
  color->r = r;
  color->g = g;
  color->b = b;
  change++;
}