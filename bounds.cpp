#include "bounds.h"
#include "exception.h"

// Constructor to assign input parameters to the fields
Bounds::Bounds(float x_min, float x_max, float y_min, float y_max) {
    if (x_max > x_min && y_max > y_min) {
        xmin = x_min;
        ymin = y_min;
        xmax = x_max;
        ymax = y_max;
    }
    else {
        // throw error when x_min > x_max or y_min > y_max
        throw PlotException("Error: invalid plot bounds");
    }
}

// Helper functions to get access to the the private fields
float Bounds::get_xmin() {
    return xmin;
}
float Bounds::get_xmax() {
    return xmax;
}
float Bounds::get_ymin() {
    return ymin;
}
float Bounds::get_ymax() {
    return ymax;
}
