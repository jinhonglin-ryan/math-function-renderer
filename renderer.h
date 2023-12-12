#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  const Plot &m_plot;
  Image *m_img;

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

public:
  Renderer(const Plot &plot);
  ~Renderer();

  Image *render();

private:

  /** check if the pixel is in the bounds of the Fill
   *  @param row
   *  @param col
   *  @param bounds the bounds of the plot
   *  @param fill the instructions for the fill
   *  @return true if is in the bounds, false if not
   */
  bool in_fill(int row, int col, Bounds bounds, Fill& fill) const;

  /** find the color after blending the base color and the fill color
   *  @param orig_color base color
   *  @param fill_color color to blend with
   *  @param opacity opacity to blend the two colors
   *  @return Color object
   */
  Color blend_color(const Color& orig_color, const Color& fill_color, float opacity) const;

  /** carries out the coloring of the area above/below/between the functions */
  void render_fill();

  /** carries out the coloring of the functions */
  void render_func();
};

#endif // RENDERER_H
