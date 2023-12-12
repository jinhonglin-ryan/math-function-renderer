#include <cmath>
#include "exception.h"
#include "expr.h"
#include <cmath>
#include <iterator>

// Expr (base class)

Expr::Expr() {
}

Expr::~Expr() {
  for (std::vector<Expr *>::iterator it = expr_nodes.begin(); it != expr_nodes.end(); ++it) {
    delete *it; // traverse through the child nodes and delete each of them
  }
}

void Expr::addChild (Expr & child) {
  expr_nodes.push_back(&child);
}

double X::eval(double x) const {
  return x;
}

double Pi::eval(double) const {
  return M_PI;
}

double Literal::eval(double) const {
  return literal;
}

double Sin::eval(double x) const {
  std::vector<Expr *> temp = get_expr_nodes();
  if (temp.size() != 1) { // sin function only takes one argument
    throw PlotException("Wrong number of arguments are passed to a function");
  }
  return sin(temp.front()->eval(x)); // sin function evaluated at the input value x by calling eval
}

double Cos::eval(double x) const {
  std::vector<Expr *> temp = get_expr_nodes();
  if (temp.size() != 1) { // cos function only takes one argument
    throw PlotException("Wrong number of arguments are passed to a function");
  }
  return cos(temp.front()->eval(x)); // cos function evaluated at the input value x by calling eval
}

double Plus::eval(double x) const {
  double sum = 0;
  std::vector<Expr *> temp = get_expr_nodes();
  for (std::vector<Expr *>::iterator it = temp.begin(); it != temp.end(); ++it) { // iterate over the child nodes
    sum += (*it)->eval(x); // evaluate each child node and add to the sum
  }
  return sum;
}

double Minus::eval(double x) const {
  double diff = 0;
  int i = 0;
  std::vector<Expr *> temp = get_expr_nodes();
  if (temp.size() != 2) { // minus function only takes two arguments
    throw PlotException("Wrong number of arguments are passed to a function");
  }
  for (std::vector<Expr *>::iterator it = temp.begin(); it != temp.end(); ++it) { // iterate over the child nodes
    if (i == 0) { // base case
      diff = (*it)->eval(x);
      i++; 
    } else { 
      diff -= (*it)->eval(x); // subtract the value of the child node
    }
  }
  return diff;
}

double Multiply::eval(double x) const {
  double product = 1.0;
  std::vector<Expr *> temp = get_expr_nodes();
  for (std::vector<Expr *>::iterator it = temp.begin(); it != temp.end(); ++it) { // iterate over the child nodes
    product *= (*it)->eval(x); // evaluate each child node and compute the product
  }
  return product;
}

double Divide::eval(double x) const {
  double divd = 1.0; int i = 0;
  std::vector<Expr *> temp = get_expr_nodes();
  if (temp.size() != 2) { // divide function only takes two arguments
    throw PlotException("Wrong number of arguments are passed to a function");
  }
  for (std::vector<Expr *>::iterator it = temp.begin(); it != temp.end(); ++it) {
    if (i == 0) { // base case
      divd = (*it)->eval(x);
      i++;
    } else {
      double d1 = (*it)->eval(x);
      if (d1 == 0) { // if d1 is 0, this is an attempt to divide by 0, throw an exception
        throw PlotException("Attempt to divide by 0");
      }
      divd /= d1;
    }
  }
  return divd;
}
