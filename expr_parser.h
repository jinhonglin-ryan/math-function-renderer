#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include "expr.h"

#include <deque>

class ExprParser {
private:
  // value semantics are prohibited
  ExprParser(const ExprParser &);
  ExprParser &operator=(const ExprParser &);

public:
  ExprParser();
  ~ExprParser();

  /** checks if a strings is a number
   *  @param s1 a string
   *  @return true if is number, false is not
   */
  bool isNumber(std::string s1);

  /** parses an string into a deque
   *  @param in input string
   *  @return a pointer to an Expr
   */
  Expr *parse(std::istream &in);

  /** convert prefix expression into a tree
   *  @param tokens a deque of strings
   *  @return a pointer to an Expr
   */
  Expr* parseExpr(std::deque<std::string>& tokens);
};

#endif // FN_PARSER_H
