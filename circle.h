/*
 *  circle.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <string>

class Circle: public Shape {
protected:
    float radius;
public:
    float getRadius() const;
    void setRadius(float radius);
    
    //bounds - штука не квадратная, надо перегрузить
    virtual float getMinX() const;
    virtual float getMinY() const;
    virtual float getMaxX() const;
    virtual float getMaxY() const;    
    
    Circle();
    Circle(float x, float y, float radius, int r, int g, int b);
    Circle(const Circle& circle);
    
    virtual void draw(QPainter *renderArea);
    virtual void setScale(float scalef);
    virtual std::string toString();
    
    Circle& operator=(const Circle& circle);
    bool operator==(const Circle& circle) const;
};

#endif
