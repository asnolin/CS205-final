//
// Written by Ragdoll (Contributed by Yile Li)
//

#ifndef TEAM_VIRTUAL_SHAPES_H
#define TEAM_VIRTUAL_SHAPES_H

#include "graphics.h"
#include <cmath>

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    int x;
    int y;
};

//Abstract
class Shape {
protected:
    color fill;
    point position;

public:
    //constructors
    Shape();

    Shape(color c);

    Shape(point p);

    Shape(color c, point p);

    //getters
    color get_fill() const;

    point get_position() const;

    int getX() const;

    int getY() const;

    //setters
    void set_fill(color f);

    void set_fill(double r, double g, double b);

    void set_position(point p);

    void set_position(int x_in, int y_in);

    virtual void draw() const = 0;

    virtual void move(point in);

    virtual void move(int x, int y);
};

class Rectangles : public Shape {
private:
    double width;
    double height;
public:
    //constructors
    Rectangles();

    Rectangles(double w, double h);

    Rectangles(double w, double h, color f, point p);

    //getters
    double get_width() const;

    double get_height() const;

    //setters
    void set_width(double w);

    void set_height(double h);

    bool pointOverlap(int x, int y);

    virtual void draw() const override;

};

class Circle : public Shape {
private:
    double radius;
public:
    // Constructors
    Circle();

    Circle(double r);

    Circle(double r, color f, point p);

    // getters
    double get_radius() const;

    // setters
    void set_radius(double r);

    //need an circle object to determined whether collision or not
    bool circleCollision(Circle obj) const;

    virtual void draw() const override;

};


#endif //TEAM_VIRTUAL_SHAPES_H
