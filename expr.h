#ifndef EXPR_H
#define EXPR_H

#include <vector>

// Base expression class
class Expr {
private:
  std::vector<Expr *> expr_nodes;
  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);

public:
  Expr();
  virtual ~Expr();

  virtual double eval(double x) const = 0;

  /** add child node to node
   *  @param child takes an Expr node
   */
  void addChild (Expr & child);

  /** reutnr expr nodes
   *  @return a vector of Expr pointers
   */
  std::vector<Expr *> get_expr_nodes () const {return expr_nodes;}

};

class X : public Expr {
  public: 
    X(){}
    virtual ~X(){}
    double eval(double x) const override;

};

class Pi : public Expr {
  public: 
    Pi(){}
    virtual ~Pi(){}
    double eval(double x) const override;

};

class Literal : public Expr {
  public: 
    Literal(){}
    Literal(double x){literal = x;} 
    virtual ~Literal(){}
    double eval(double x) const override;
  private:
    double literal;

};


class Sin : public Expr {
  public: 
    Sin(){}
    virtual ~Sin(){}
    double eval(double x) const override;

};

class Cos : public Expr {
  public: 
    Cos(){}
    virtual ~Cos(){}
    double eval(double x) const override;

};

class Plus : public Expr {
  public: 
    Plus(){}
    virtual ~Plus(){}
    double eval(double x) const override;

};

class Minus : public Expr {
  public: 
    Minus(){}
    virtual ~Minus(){}
    double eval(double x) const override;

};

class Multiply : public Expr {
  public: 
    Multiply(){}
    virtual ~Multiply(){}
    double eval(double x) const override;

};

class Divide : public Expr {
  public: 
    Divide(){}
    virtual ~Divide(){}
    double eval(double x) const override;

};
#endif // EXPR_H
