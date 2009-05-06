/*
 *  circle.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "circle.h"
//#include <GLUT/GLUT.h>
#include <math.h>

Circle::Circle(){
    this->setLocation(0, 0);
    this->setSize(0, 0);
    this->setRadius(0);
    this->setVisible(false);
    this->setColor(0.0, 0.0, 0.0);
}

Circle::Circle(float x, float y, float radius, int r, int g, int b) {
    this->setLocation(x, y);
    this->setSize(2*radius, 2*radius);
    this->setRadius(radius);
    this->setVisible(true);
    this->setColor(r, g, b);
}

Circle::Circle(const Circle& circle) : Shape() {
    this->setLocation(circle.getX(), circle.getY());
    this->setRadius(circle.getRadius());
    this->setVisible(circle.isVisible());
    this->setColor(circle.getRed(), circle.getGreen(), circle.getBlue());
}

float Circle::getRadius() const {
    return radius;
}
void Circle::setRadius(float radius) {
    this->radius = radius;
    this->w = 2*radius;
    this->h = 2*radius;
}

void Circle::setScale(float scalef) {
    this->setRadius(this->getRadius()*scalef);
}

float Circle::getMinX() const { return x-radius; }
float Circle::getMinY() const { return y-radius; }
float Circle::getMaxX() const { return x+radius; }
float Circle::getMaxY() const { return y+radius; }

void Circle::draw(QPainter *renderArea) {
    if (this->isVisible()){

//        renderArea->setPen(QColor(getRed(),getGreen(),getBlue()));
//        renderArea->setBrush(QBrush(QColor(getRed(),getGreen(),getBlue()),Qt::SolidPattern));
        QColor curr_color(getRed(),getGreen(),getBlue());
        renderArea->setPen(curr_color);
        renderArea->setBrush(QBrush(curr_color,Qt::SolidPattern));
        renderArea->drawEllipse(QPointF(getX(),getY()),radius,radius);
    }
}

Circle& Circle::operator=(const Circle& circle) {
    this->setLocation(circle.getX(), circle.getY());
    this->setRadius(circle.getRadius());
    this->setVisible(circle.isVisible());
    this->setColor(circle.getRed(), circle.getGreen(), circle.getBlue());
    return *this;
}

bool Circle::operator==(const Circle& circle) const {
    if (this->getX() == circle.getX() && this->getY() == circle.getY() &&
        this->getRadius() == circle.getRadius() &&
        this->isVisible() == circle.isVisible() &&
        this->getRed() == circle.getRed() &&
        this->getGreen() == circle.getGreen() &&
        this->getBlue() == circle.getBlue())
        return true;
    else return false;    
}
