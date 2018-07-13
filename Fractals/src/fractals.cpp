// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "fractals.h"
#include <math.h>       /* sqrt */
#include "gwindow.h"    /* graphics */
using namespace std;

void drawSierpinskiHelper(double x, double y, double s, int order, GWindow& window) {
    // base
    // height = (root 3)* (size/2) = sqrt(3)*(size/2)
    // height is found by property of right triangles
    int h = sqrt(3)*(s/2);
    if (order == 1) {
        window.drawLine(x, y, x + s, y); // top line of triangle
        window.drawLine(x, y, x + (s/2), y + h); // left line of triangle
        window.drawLine(x + s, y, x + (s/2), y + h); // right line of triangle
        return;
    }
    else {
        drawSierpinskiHelper(x, y, s/2, order - 1, window);
        drawSierpinskiHelper(x + (s/2), y, s/2, order - 1, window);
        drawSierpinskiHelper(x + (s/4), y + (h/2), s/2, order - 1, window);
    }
}

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {
    if ((order < 0) | (x < 0) | (y < 0) | (size < 0)) {
        string s = "";
        // throw a string exception
        throw s;
    } else if (order > 0) {
        drawSierpinskiHelper(x, y, size, order, window);
    }

    return;

}

void drawTree(GWindow& gw, double x, double y, double size, int order) {
    // TODO: write this function

}
