//
// Created by Ragdoll on 2017/12/7.
//

#include <cmath>
#include "Shape.h"

Shape::Shape() {
}

Shape::Shape(color c) {
    fill = c;
}

Shape::Shape(point p) {
    position = p;
}

Shape::Shape(color c, point p) {
    fill = c;
    position = p;
}

color Shape::get_fill() const {
    return fill;
}

point Shape::get_position() const {
    return position;
}

int Shape::getX() const {
    return position.x;
}

int Shape::getY() const {
    return position.y;
}

void Shape::set_fill(color c) {
    fill = c;
}

void Shape::set_fill(double r, double g, double b) {
    fill = {r, g, b};
}

void Shape::set_position(point p) {
    position = p;
}

void Shape::set_position(int x_in, int y_in) {
    position = {x_in, y_in};
}

Rectangles::Rectangles() : Shape(), width(0), height(0) {}

Rectangles::Rectangles(double w, double h) : Shape() {
    set_width(w);
    set_height(h);
}

Rectangles::Rectangles(double w, double h, color f, point p) : Shape(f, p) {
    set_width(w);
    set_height(h);
}

double Rectangles::get_width() const {
    return width;
}

double Rectangles::get_height() const {
    return height;
}

void Rectangles::set_width(double w) {
    if (w < 0) {
        width = 0;
    } else {
        width = w;
    }
}

void Rectangles::set_height(double h) {
    if (h < 0) {
        height = 0;
    } else {
        height = h;
    }
}

bool Rectangles::pointOverlap(int x, int y) {
    if (x > getX() && x < getX() + width && y > getY() && y < getY() + height) {
        return true;
    }
    return false;
}

void Rectangles::draw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    // top left corner
    glVertex2i(position.x, position.y);
    // bottom left corner
    glVertex2i(position.x, position.y + height);
    // bottom right corner
    glVertex2i(position.x + width, position.y + height);
    // top right corner
    glVertex2i(position.x + width, position.y);
    glEnd();
}

void Shape::move(point in) {
    position.x += in.x;
    position.y += in.y;
}

void Shape::move(int x, int y) {
    set_position(position.x + x, position.y + y);
}

Circle::Circle() : Shape() {}

Circle::Circle(double r) : Shape() {
    set_radius(r);
}

Circle::Circle(double r, color f, point p) : Shape(f, p) {
    set_radius(r);
}

double Circle::get_radius() const {
    return radius;
}

void Circle::set_radius(double r) {
    if (r < 0) {
        radius = 0;
    } else {
        radius = r;
    }
}

bool Circle::circleCollision(Circle obj) const {
    return sqrt(pow(getX() - obj.getX(), 2) +
                pow(getY() - obj.getY(), 2)) < get_radius() + obj.get_radius();
}

void Circle::draw() const {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2i(position.x, position.y);
    for (double i = 0; i <= 2.0 * 3.14 + 0.05; i += 2.0 * 3.14 / 360) {
        glVertex2i(position.x + get_radius() * cos(i), position.y + get_radius() * sin(i));
    }
    glEnd();
}