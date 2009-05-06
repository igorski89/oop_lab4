/*
 *  shape.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>

class Shape {
protected:
    //location
    float x;
    float y;
    //size
    float h;
    float w;
    //visibility
    bool visible;
    //color
    int red;
    int green;
    int blue;
    
public:
    float getX() const;
    float getY() const;
    void setLocation(float x, float y);
    
    float getWidth() const;
    float getHeight() const;
    void setSize(float h, float w);
    
    //bounds
    virtual float getMinX() const;
    virtual float getMinY() const;
    virtual float getMaxX() const;
    virtual float getMaxY() const;
    
    bool isVisible() const;
    void setVisible(bool visible);
    
    int getRed() const;
    int getBlue() const;
    int getGreen() const;
    void setColor(int r, int g, int b);
    
    virtual void draw(QPainter *renderArea);
    virtual void setScale(float scalef);
    
    Shape();
    Shape(float x, float y, float h, float w, float r, float g, float b);
    Shape(const Shape& shape);
    virtual ~Shape() { };

    Shape& operator=(const Shape& shape);
    bool operator==(const Shape& shape) const;
};

#endif
