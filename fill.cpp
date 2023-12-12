#include <algorithm>
#include <cassert>
#include "fill.h"

#include "bounds.h"

// TODO: implement constructors
// constructor for FillAbove and FillBelow
Fill::Fill(std::string f1, float opacity, uint8_t r, uint8_t g, uint8_t b, int type) 
    : f1_name(f1), m_opacity(opacity), color({r,g,b}), fill_type(type) {
}

// constructor for FillBetween
Fill::Fill(std::string f1, std::string f2, float opacity, uint8_t r, uint8_t g, uint8_t b, int type) 
    : f1_name(f1), f2_name(f2), m_opacity(opacity), color({r,g,b}), fill_type(type) {
}

// no need for a destructor since no dynamic allocation in Fill
Fill::~Fill() {}

// TODO: implement member functions
Function* Fill::get_f1 (std::vector<Function*> funcs, std::string f1_name) const {
    int exist = 0;
    // iterate through the vector of functions to match the name
    for (size_t i = 0; i < funcs.size(); i++) {
        if (funcs.at(i)->get_name() == f1_name) {
            return funcs.at(i);
        }
    }
    if (exist == 0) {
        throw PlotException("Error: fill directive referring to a nonexistent function name");
    }
    return nullptr;
}

Function* Fill::get_f2 (std::vector<Function*> funcs, std::string f2_name) const {
    int exist = 0;
    for (size_t i = 0; i < funcs.size(); i++) {
        if (funcs.at(i)->get_name() == f2_name) {
            exist++;
            return funcs.at(i);
        }
    }
    if (exist == 0) {
        throw PlotException("Error: fill directive referring to a nonexistent function name");
    }
    return nullptr;
}