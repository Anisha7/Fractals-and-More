// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "fractals.h"
#include <math.h>       /* sqrt */
#include "gwindow.h"    /* graphics */
using namespace std;

// recursively draws equilateral triangles
void drawSierpinskiHelper(double x, double y, double s, int order, GWindow& window) {
    // height = (root 3)* (size/2) = sqrt(3)*(size/2)
    // height is found by property of right triangles
    int h = sqrt(3)*(s/2);

    // base case
    if (order == 1) {
        window.drawLine(x, y, x + s, y); // top line of triangle
        window.drawLine(x, y, x + (s/2), y + h); // left line of triangle
        window.drawLine(x + s, y, x + (s/2), y + h); // right line of triangle
        return;
    }
    // recursive case
    else {
        drawSierpinskiHelper(x, y, s/2, order - 1, window);
        drawSierpinskiHelper(x + (s/2), y, s/2, order - 1, window);
        drawSierpinskiHelper(x + (s/4), y + (h/2), s/2, order - 1, window);
    }
}

// call to draw the sierpinski triangle
void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {

    if ((order < 0) | (x < 0) | (y < 0) | (size < 0)) {
        string s = "Invalid input: values must be greater than 0!";
        // throw a string exception
        throw s;

    } else if (order > 0) {
        drawSierpinskiHelper(x, y, size, order, window);
    }

    return;

}

// recursively draws all tree branches
void drawTreeHelper(double x, double y, double s, int order, GWindow& gw, double angle, double max) {
    // base
    if (order == max) {
        return;
    }

    // set color
    if (order >= max - 1) {
        gw.setColor("#2e8b57");
    } else {
        gw.setColor("#8b7765");
    }

    // draw
    if (order == 0) {
        gw.drawPolarLine(x, y, s, angle);
        drawTreeHelper(x, y - s , s/2, order + 1, gw, 45, max);
    }
    else {
        for (int i = 0; i < 7; i++) {
            // set color
            if (order >= max - 1) {
                gw.setColor("#2e8b57");
            } else {
                gw.setColor("#8b7765");
            }

            // draw line
            gw.drawPolarLine(x, y, s, angle);

            // this part is not yet working properly
            double rad = angle*(PI/180);
            double xdiff = (s)*(cos(rad));
            double ydiff = (s)*(sin(rad));



            // recursive call
            drawTreeHelper(x + xdiff, y - ydiff, s/2, order + 1, gw, angle - (45), max);

            // change angle
            angle += 15;
        }

    }
}

// call to draw tree
void drawTree(GWindow& gw, double x, double y, double size, int order) {

    if ((order < 0) | (x < 0) | (y < 0) | (size < 0)) {
        string s = "Invalid input: values must be greater than 0!";
        // throw a string exception
        throw s;

    } else if (order > 0) {
        drawTreeHelper(x + size/2, y + size, size, 0, gw, 90, order);
        //drawTreeLeaves();
    }

    return;

}

// recursively draws all tree branches
void drawTreeHelper1(double x, double y, double s, int order, GWindow& gw, double angle) {
    // base case
    if (order == 1) {
        gw.setColor("#2e8b57");
        gw.drawPolarLine(x, y, s, angle);
        return;
    }
    else {
        // to do
        // new x = x1 - ((size/2)*(cos(angle))
        // new y = y1 - ((size/2)*(sin(angle))
        // each time, angle changes by 15
        angle = angle + (angle/2);
        gw.setColor("#8b7765");
        for (int i = 0; i < 7; i++) {
            angle += 15;
            drawTreeHelper1(x - ((s/2)*(cos(angle))), y - ((s/2)*(sin(angle))), s/2, order - 1, gw, angle );
        }
    }
}
