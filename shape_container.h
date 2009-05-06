/*
 *  shape_container.h
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */
#ifndef SHAPE_CONTAINER_H
#define SHAPE_CONTAINER_H

#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include <vector>

class ShapeContainer: public Shape {
protected:
    bool selected;
    std::vector<Shape*> shapes;
//    float scaleFactor;
public:
//    float getScaleFactor() const;
//    void setScaleFactor(float newScaleFactor);
    
    bool isSelected() const;
    void setSelected(bool selected);
    
    std::vector<Shape*> getShapes();
    
    ShapeContainer();
    ShapeContainer(float x, float y, float w, float h, int r, int g, int b);
    ShapeContainer(Shape* shape);
    ~ShapeContainer();
    
    void add(Shape* shape);
    void remove(Shape* shape);
    void eraseAll();
    
    Rectangle* addRectangle(float x, float y, float w, float h, int r, int g, int b);
    Circle* addCircle(float x, float y, float radius, int r, int g, int b);
    
    virtual void draw(QPainter *renderArea);
    virtual void setScale(float scalef);
    void move(float dx, float dy);
    virtual void recalculateBounds();
};

#endif
