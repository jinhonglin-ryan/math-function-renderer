#ifndef READER_H
#define READER_H

#include <iostream>
#include "plot.h"

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  Reader();
  ~Reader();

  /** read from input file to Plot
   *  @param in input file
   *  @param plot the Plot object
   */
  void read_input(std::istream &in, Plot &plot);
};

#endif // READER_H
