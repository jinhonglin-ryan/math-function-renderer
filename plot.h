#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"

class Plot {
private:
  Bounds *bounds;
  Image *image;
  std::vector<Function*> functions;
  std::vector<Fill*> fills;

  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();
  ~Plot();

  /** function to set the bounds of a plot
   *  @param x_min minimum x value
   *  @param x_max maximum x value
   *  @param y_min minimum y value
   *  @param y_max maximum y value
   */
  void set_bounds(float xmin, float xmax, float ymin, float ymax);

  /** sets the bounds for an Image
   *  @param width of the image
   *  @param height of the image
   */
  void set_image(int width, int height);
  
  /** adds a Function to the vector of Functions
   *  @param name name of function
   *  @param expr function expression
   */
  void add_function(std::string &name, Expr *expr);

  /** member function to set color values for a function
   *  @param f_name function name
   *  @param ri integer color value
   *  @param gi integer color value
   *  @param bi integer color value
   */
  void set_color(std::string f_name, int ri, int gi, int bi);
  
  /** function for setting the FillAbove and FillBelow fills
   *  @param f1 function name
   *  @param opacity opacity
   *  @param ri integer color value
   *  @param gi integer color value
   *  @param bi integer color value
   *  @param type of fill, 1 for FillAbove, 2 for FillBelow, 3 for FillBetween
   */
  void add_fill(std::string f1, float opacity, int ri, int gi, int bi, int type);

   /** function for setting the FillBetween fills
   *  @param f1 first function
   *  @param f2 second function
   *  @param opacity opacity
   *  @param ri integer color value
   *  @param gi integer color value
   *  @param bi integer color value
   *  @param type of fill
   */
  void add_fill_2(std::string f1, std::string f2, float opacity, int ri, int gi, int bi, int type);

  /** function to retrieve the vector of Fills
   *  @return vector of Fills
   */
  std::vector<Fill*> get_fills() const { return fills; }

  /** function to retrieve the vector of Functions
   *  @return vector of Functions
   */
  std::vector<Function*> get_func() const { return functions; }

  /** function to retrieve the the Bounds of the plot
   *  @return Bounds of the image
   */
  Bounds *get_bounds() const { return bounds; }

  /** function to retrieve the width of the plot
   *  @return width
   */
  int get_width() const;

  /** function to retrieve the height of the plot
   *  @return height
   */
  int get_height() const;
};

#endif // PLOT_H
