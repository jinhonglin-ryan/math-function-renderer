#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"

#include <string>

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in, Plot &plot) {
  std::string input_string;
  std::string line;

  while (getline(in, line)) {
    std::stringstream ss(line);
    std::string command;
    ss >> command;
    
    // Plot directive
    if (command == "Plot") {
      float xmin, ymin, xmax, ymax;
      int width, height;
      if (ss >> xmin >> ymin >> xmax >> ymax >> width >> height) {
        plot.set_bounds(xmin, xmax, ymin, ymax);
        plot.set_image(width, height);
      }
      else {
        throw PlotException("Error: invalid Plot command");
      }
    }

    // Function directive
    else if (command == "Function") {
      std::string f_name;
      if (ss >> f_name) {
        ExprParser parser;
        Expr *expression = parser.parse(ss);
        plot.add_function(f_name, expression);
      }
      else {
        throw PlotException("Error: invalid Function command");
      }
    }

    // Color directive
    else if (command == "Color") {
      std::string f_name;
      int ri, gi, bi;
      if (ss >> f_name >> ri >> gi >> bi) {
        plot.set_color(f_name, ri, gi, bi);
      }
      else {
        throw PlotException("Error: invalid Color command");
      }
    }

    // FillAbove directive
    else if (command == "FillAbove") {
      std::string f_name;
      std::string opacity_s;
      int ri, gi, bi;
      if (ss >> f_name >> opacity_s >> ri >> gi >> bi) {
        float opacity = stof(opacity_s);
        plot.add_fill(f_name, opacity, ri, gi, bi, 1);
      } 
      else {
        throw PlotException("Error: invalid FillAbove command");
      }
    }

    // FillBelow directive
    else if (command == "FillBelow") {
      std::string f_name;
      std::string opacity_s;
      int ri, gi, bi;
      if (ss >> f_name >> opacity_s >> ri >> gi >> bi) {
        float opacity = (float)stof(opacity_s);
        plot.add_fill(f_name, opacity, ri, gi, bi, 2);
      }
      else {
        throw PlotException("Error: invalid FillBelow command");
      }
    }

    // FillBetween directive
    else if (command == "FillBetween") {
      std::string f1_name, f2_name;
      std::string opacity_s;
      int ri, gi, bi;
      if (ss >> f1_name >> f2_name >> opacity_s >> ri >> gi >> bi) {
        float opacity = (float)stof(opacity_s);
        plot.add_fill_2(f1_name, f2_name, opacity, ri, gi, bi, 3);
      }
      else {
        throw PlotException("Error: invalid FillBetween command");
      }
    }
    else {
      throw PlotException("Error: Invalid command");
    }
  }
}
