/*
 *  shape.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "shape.h"

Shape::Shape(){
    this->setLocation(0, 0);
    this->setSize(0, 0);
//    this->visible = false;
    this->setVisible(false);
    this->setColor(0.0,0.0,0.0);
}

Shape::Shape(float x, float y, float w, float h, float r, float g, float b) {
    this->setLocation(x,y);
    this->setSize(w,h);
    this->setVisible(true);
    this->setColor(r,g,b);
}

Shape::Shape(const Shape& shape) {
    this->setLocation(shape.getX(), shape.getY());
    this->setSize(shape.getHeight(), shape.getWidth());
    this->setColor(shape.getRed(), shape.getGreen(), shape.getBlue());
    this->setVisible(shape.isVisible());
}

float Shape::getX() const{ return x; }
float Shape::getY() const{ return y; }
void  Shape::setLocation(float x, float y) { 
    this->x = x; 
    this->y = y; 
}

float Shape::getWidth() const{ return w; }
float Shape::getHeight() const{ return h; }
void  Shape::setSize(float w, float h){ 
    this->h = h; 
    this->w = w; 
}

void Shape::setScale(float scalef) {
    this->h *= scalef;
    this->w *= scalef;
}

float Shape::getMinX() const { return this->x; }
float Shape::getMinY() const { return this->y; }
float Shape::getMaxX() const { return this->x+this->w; }
float Shape::getMaxY() const { return this->y+this->h; }

bool  Shape::isVisible() const { return visible; }
void  Shape::setVisible(bool visible) { this->visible = visible; }

int Shape::getRed() const{ return red; }
int Shape::getGreen() const{ return green; }
int Shape::getBlue() const{ return blue; }
void  Shape::setColor(int r, int g, int b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}

void Shape::draw(QPainter *renderArea) { };

Shape& Shape::operator=(const Shape& shape) {
    this->setLocation(shape.getX(), shape.getY());
    this->setSize(shape.getHeight(), shape.getWidth());
    this->setColor(shape.getRed(), shape.getGreen(), shape.getBlue());
    this->setVisible(shape.isVisible());
    return *this;
}

bool Shape::operator==(const Shape& shape) const {
    if (this->getX() == shape.getX() && this->getY() == shape.getY() &&
        this->getWidth() == shape.getWidth() && this->getHeight() == shape.getHeight() &&
        this->isVisible() == shape.isVisible() &&
        this->getRed() == shape.getRed() &&
        this->getGreen() == shape.getGreen() &&
        this->getBlue() == shape.getBlue())
        return true;
    else return false;
}
