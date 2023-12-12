# Math Function Renderer

## Overview

This project is a Math Function Renderer that allows users to plot mathematical functions and visualize the resulting plots. The key components of the project include the `Reader`, `Expr`, and `ExprParser` classes, forming the foundation of the rendering process. The expression tree is represented using vectors.

## Classes and Components

1. **Bounds**
    - Represents the bounds of the plot.

2. **Color**
    - Represents an RGB color value.

3. **Exception**
    - Defines the `PlotException` class, which is thrown in case of fatal errors.

4. **Expr**
    - Represents an expression node type.

5. **ExprParser**
    - Parses an expression and builds an expression tree using vectors.

6. **Fill**
    - Represents a fill directive, holding information about two function names, opacity, color, and fill type.

7. **Function**
    - Represents a function to be plotted, including its name, expression, and associated RGB value.

8. **Image**
    - Holds information about the image, including height, width, and an array of Color objects representing pixel RGB values.

9. **Plot**
    - Combines information from other directives, such as bounds, functions, and fills, forming the basis of the plot.

10. **Reader**
    - Reads a plot file to populate a `Plot` object.

11. **Renderer**
    - Renders a `Plot` object to produce an `Image`.

## Design and Implementation Notes

- The project employs a modular design with separate classes for different components.
- Error handling is centralized in the `main.cpp` file, catching errors thrown in other classes.

## Example Plot

Here is an example plot input file (`input/example04.txt`):

```plaintext
Plot 0 -2.5 40 2.5 640 480

Function fn1 ( sin x )

Function fn2 ( * 1.6 ( cos x ) )

Color fn1 100 100 255

Color fn2 100 255 100

FillBetween fn1 fn2 0.4 128 0 200
```

This example produces the following image:
![Example Image](https://github.com/jinhonglin-ryan/Math_Function_Renderer/blob/main/expected/example04.png)

Explanation of the example plot:

- The `Plot` directive specifies the plot's region and image dimensions.
- Two `Function` directives define functions to be plotted (`fn1` and `fn2`).
- Two `Color` directives set the colors for each function.
- The `FillBetween` directive fills the area between `fn1` and `fn2` with a specified color and opacity.

## Getting Started

1. Clone the repository.
2. Compile and run the program using `main.cpp`.
3. Create your own plot input files or modify existing ones.

Feel free to explore and visualize various mathematical functions using this Math Function Renderer!