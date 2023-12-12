#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "func.h"
#include "bounds.h"

class Fill {
private:
  std::string f1_name;
  std::string f2_name;
  const float m_opacity;
  const Color color;
  const int fill_type; // 1 = FillAbove, 2 = FillBelow, 3 = FillBetween

public:
  /** constructor for the FillAbove and FillBelow fills
   *  @param f1 function name
   *  @param opacity opacity
   *  @param r color value
   *  @param g color value
   *  @param b color value
   *  @param type of fill, 1 for FillAbove, 2 for FillBelow, 3 for FillBetween
   */
  Fill(std::string f1, const float opacity, uint8_t r, uint8_t g, uint8_t b, const int type);

  /** constructor for the FillBetween type of fill
   *  @param f1 function name
   *  @param opacity opacity
   *  @param r color value
   *  @param g color value
   *  @param b color value
   *  @param type of fill
   */
  Fill(std::string f1, std::string f2, const float opacity, uint8_t r, uint8_t g, uint8_t b, const int type);

  /** The destructor releases allocated memory as needed to avoid leaks. */
  ~Fill();

  /** to get the function name for the FillAbove and FillBelow function, and 
   *  the first function for the FillBetween function
   *  @return function name
   */
  std::string get_f1_name() const { return f1_name; }

  /** to get the second function name for the FillBetween function
   *  @return function name
   */
  std::string get_f2_name() const { return f2_name; }

  /** to get the according first Function object using the function names
   *  @param funcs vector of functions
   *  @param f1_name function name to look for
   *  @return function object
   */
  Function* get_f1 (std::vector<Function*> funcs, std::string f1_name) const;

  /** to get the according second Function object using the function names
   *  @param funcs vector of functions
   *  @param f1_name function name to look for
   *  @return function object
   */
  Function* get_f2 (std::vector<Function*> funcs, std::string f2_name) const;

  /** helper function to gain access to the private field opacity
   *  @return opacity value
   */
  float get_opacity () const { return m_opacity; }

  /** helper function to gain access to the private field color
   *  @return color object
   */
  Color get_color () const { return color; }

  /** helper function to gain access to the private field fill
   *  @return fill type, 1 for FillAbove, 2 for FillBelow, 3 for FillBetween
   */
  int get_fill_type () const { return fill_type; }
};

#endif // FILL_H
