#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}

// checks whether a given string is a valid numerical value
// returns true if the string is a number
bool ExprParser::isNumber(std::string s1) {
  bool is_num = false;
  int num_decimals = 0;
  for (size_t i = 0; i < s1.size(); i++) { // travere each char in the string and determine if they are all valid numbers
    if (!isdigit(s1.at(i))) {
      if (s1.at(i) == '.' && num_decimals == 0) {
        num_decimals++;
        is_num = true;
      }
      else if (s1.at(i) == '.' && num_decimals != 0) {
        is_num = false;
        throw PlotException("Error: invalid function"); // if not valid, throw an exception
      }
    }
    else {
      return true;
    }
  }
  return is_num; // return true if the string is a number
}


// Recommended strategy: read all of the tokens in the expression
// from the istream and put them in a sequence collection
// such as a vector or deque. The call a recursive helper function
// which parses the tokens and returns a pointer to an Expr object
// repersenting the parsed expression.

Expr* ExprParser::parse(std::istream& in) {
  // Read all tokens from input stream and put them in a deque
  std::deque<std::string> tokens;
  std::string line;
  getline(in, line);
  std::stringstream ss(line);

  std::string s;
  if (ss >> s) {
    tokens.push_back(s);
    while (ss >> s) {
      tokens.push_back(s);
    }
  }
  else {
    throw PlotException("Error: no valid function");
  }

  // Call recursive helper function to parse tokens
  return parseExpr(tokens);
}


Expr* ExprParser::parseExpr(std::deque<std::string>& tokens) {
  std::string n = tokens.front();
  tokens.pop_front();
  Expr * result;

  if (n == "x") {
    return new X();
  } else if (n == "pi") {
    return new Pi();
  } else if (isNumber(n)) {
    return new Literal(stof(n));
  }
  
  // If "(", expect a function name or operator to follow
  // return a corresponding object
  else if (n == "(") { 
    n = tokens.front();
    tokens.pop_front();

    if (n == "sin") {
      result = new Sin();
    } else if (n == "cos") {
      result = new Cos();
    } else if (n == "+") {
      result = new Plus();
    } else if (n == "-") {
      result = new Minus();
    } else if (n == "*") {
      result = new Multiply();
    } else if (n == "/") {
      result = new Divide();
    } else {
      throw PlotException("Error: invalid function name"); // throw an exception if the function name is not one of above
    }

    while (tokens.front() != ")") {
      Expr * arg = parseExpr(tokens);
      result->addChild(*arg); // add each parsed argument as a child of the expression object
    }

    tokens.pop_front(); // should be right paren
    return result;
  } else {
    throw PlotException("Error: unexpected token"); // throws an exception if the token is not one of above
  }
}