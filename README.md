
DESIGN:
1. Implemented the Reader, Expr and ExprParser classes, which are the foundation stones of this project. 
    used 'vector' to represent the expression as a tree. 
2. Implemented the Bounds class that holds the values of the bounds of the functions, 
    and the Color class that holds the value of RGB of a pixel.
3. Implemented the Image class that holds the values of the image's height and width, 
    and an array of Color objects which has RGBs of all pixels in this image.
4. Implemented the Function class that holds the name of the function, its expression, and its associated RGB value.
5. Implemented the Fill class that holds two function names (the second one for FillBetween directive), 
    the opacity and the color that is associated with the Fill directive, and an integer value indicating the type of 
    the Fill (1 = FillAbove, 2 = FillBelow, 3 = FillBetween).
6. Implemented the Plot class that holds fields that represent plot bounds, image, functions and fills. 
    Basically, the Plot directive includes the information of all other directives.
7. Implemented the Render class that holds the plot and the image. The 'render' function in Render renders the Fill 
    and the Functions.
8. Implemented main.cpp so that it catches all the errors thrown in other classes.



*Design and implementation notes*

Files	            Class defined	    Notes
bounds.h/cpp	    Bounds	            represents the bounds of the plot
color.h	            Color	            represents an RGB color value
exception.h/cpp	    PlotException	    exception type thrown if a fatal error occurs
expr.h/cpp	        Expr	            expression node type
expr_parser.h/cpp	ExprParser	        parses an expression and builds an expression tree
fill.h/cpp	        Fill	            represents a fill directive
func.h/cpp	        Function	        represents a function to be plotted
image.h/cpp	        Image	            image data, can be written as a PNG file
main.cpp	        n/a	                main function: reads plot input, renders it to PNG
plot.h/cpp	        Plot	            represents the plot directives (the plot object)
reader.h/cpp	    Reader	            reads plot file to populate a Plot object
renderer.h/cpp	    Renderer	        renders a Plot object to produce an Image


*An example plot*

Here is an example plot input file. (input/example04.txt)

Plot 0 -2.5 40 2.5 640 480
Function fn1 ( sin x )
Function fn2 ( * 1.6 ( cos x ) )
Color fn1 100 100 255
Color fn2 100 255 100
FillBetween fn1 fn2 0.4 128 0 200

This plot produces the following image: 
![Example Image](https://github.com/jinhonglin-ryan/Math_Function_Renderer/blob/main/expected/example04.png)

Here is a quick overview of the meaning of the example plot input file:

The Plot directive indicates that the plot will show the region of the x/y coordinate plane where 0≤x≤40 and −2.5≤y≤2.5, and the generated image will have the dimensions 640x480

The first Function directive indicates that the function called fn1 will plot the function y=sinx

The second Function directive indicates that the function called fn2 will plot the function y=1.6(cosx)

The first Color directive indicates that the plot of fn1 will use the color (100,100,255)
 (colors are RGB triples, with color component values in the range 0–255)

The second Color directive indicates that the function called fn2 will use the color (100,255,100)

The FillBetween directive indicates that the area between fn1 and fn2 should be filled with the color (128,0,200)at an opacity of 0.4

