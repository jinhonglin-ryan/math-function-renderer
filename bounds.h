#ifndef BOUNDS_H
#define BOUNDS_H

#include "exception.h"

class Bounds {
private:
  float xmin;
  float ymin;
  float xmax;
  float ymax;

public:
  /** Constructor for Bounds, the bounds of the plot
 *  @param x_min minimum x value
 *  @param x_max maximum x value
 *  @param y_min minimum y value
 *  @param y_max maximum y value
 */
  Bounds(float x_min, float x_max, float y_min, float y_max);

  // Helper functions to get access to the the private fields
  float get_xmin();
  float get_xmax();
  float get_ymin();
  float get_ymax();
};

#endif // BOUNDS_H
