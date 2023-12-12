#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"
#include "color.h"

class Function {
private:
  // a function has a name and an expression computing its value (given x)
  std::string m_name;
  Expr *m_expr;
  Color *color;
  int change;

  // value semantics prohibited
  Function(const Function &);
  Function &operator=(const Function &);

public:
  /** constructor for a Function
   *  @param name name of function
   *  @param expr function expression
   */
  Function(const std::string &name, Expr *expr);

  /** The destructor releases allocated memory as needed to avoid leaks. */
  ~Function();

  // helper functions to get access to and modify the private fields

  /** function to retrieve name of function
   *  @return function name
   */
  std::string get_name() const { return m_name; }

  /** function to retrieve expression of function
   *  @return Expr object
   */
  Expr *get_expr() const       { return m_expr; }

  /** function to set the color of the function
   *  @param r color value
   *  @param g color value
   *  @param b color value
   */
  void set_color(uint8_t r, uint8_t g, uint8_t b);

  /** function to check if the color value of the function has been set already
   * @return the value of change, 0 not changed
   */
  int get_change() const { return change; }

  /** function to retrieve the color of the function
   * @return the Color object
   */
  Color* get_color() const { return color; }
};

#endif // FUNC_H
