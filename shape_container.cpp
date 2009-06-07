/*
 *  shape_container.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 20.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "shape_container.h"
#include <sstream>

ShapeContainer::ShapeContainer():Shape() {
    this->setSelected(false);
    this->setColor(255,0,0);
}

ShapeContainer::ShapeContainer(float x, float y, float w, float h, int r, int g, int b):Shape(x,y,w,h,r,g,b) {
    this->setSelected(true);
}

ShapeContainer::ShapeContainer(Shape* shape) {
    this->setVisible(true);
    this->selected = false;
    this->setColor(1.0, 0.0, 0.0);
    this->add(shape);
    this->recalculateBounds();
}

void ShapeContainer::eraseAll() {
    int shapes_size = shapes.size();
    for(int i=0; i<shapes_size; i++)
        delete shapes[i];
}

ShapeContainer::~ShapeContainer() {
//    int shapes_size = shapes.size();
//    for(int i=0; i<shapes_size; i++)
//        delete shapes[i];
}

void ShapeContainer::setScale(float scalef) {
    int shapes_size = shapes.size();
    for(int i=0; i<shapes_size; i++)
        shapes[i]->setScale(scalef);
    this->recalculateBounds(); 
}

bool ShapeContainer::isSelected() const {
    return this->selected;
}

std::string ShapeContainer::toString() {
    std::stringstream str_s;
    str_s << "ShapeContainer " << x << "," << y << "," << w << "," << h << "," << red << "," << green << "," << blue << std::endl;
//    for (std::vector<Shape*>::iterator it=shapes.begin();it < shapes.back();it++)
//        str_s << (*it)->toString().c_str();
    int shapes_size = shapes.size();
    for(int i=0; i<shapes_size; i++)
        str_s << shapes[i]->toString();
    return str_s.str();
}

void ShapeContainer::setSelected(bool selected) {
    this->selected = selected;
}

std::vector<Shape*> ShapeContainer::getShapes() {
    return this->shapes;
}

void ShapeContainer::add(Shape* shape) {
    this->shapes.push_back(shape);
    if (shapes.size() > 1) 
        shape->setColor(shapes[0]->getRed(), shapes[0]->getGreen(), shapes[0]->getBlue());
    
    this->recalculateBounds();
}

Rectangle* ShapeContainer::addRectangle(float x, float y, float w, float h, int r, int g, int b) {
    Rectangle *rect = new Rectangle(x,y,w,h,r,g,b);
    this->add(rect);
    return rect;
}

Circle* ShapeContainer::addCircle(float x, float y, float radius, int r, int g, int b) {
    Circle *circle = new Circle(x,y,radius,r,g,b);
    this->add(circle);
    return circle;
}

void ShapeContainer::remove(Shape* shape) {
    std::vector<Shape*>::iterator it;
    for(it=shapes.begin(); it<shapes.end(); it++)
        if (*it == shape) shapes.erase(it);
    this->recalculateBounds();
}

void ShapeContainer::recalculateBounds() {
    int shapes_size = shapes.size();
    
    float minX = shapes[0]->getMinX();
    float minY = shapes[0]->getMinY();
    float maxX = shapes[0]->getMaxX();
    float maxY = shapes[0]->getMaxY();
    for(int i=1; i<shapes_size; i++){
        if (shapes[i]->getMinX() < minX) minX = shapes[i]->getMinX();
        if (shapes[i]->getMinY() < minY) minY = shapes[i]->getMinY();
        if (shapes[i]->getMaxX() > maxX) maxX = shapes[i]->getMaxX();
        if (shapes[i]->getMaxY() > maxY) maxY = shapes[i]->getMaxY();
    }
    
    this->setLocation(minX, minY);
    this->setSize(maxX-minX, maxY-minY);
}

void ShapeContainer::move(float dx, float dy) {
    this->setLocation(this->getX()+dx, this->getY()+dy);
    std::vector<Shape*>::iterator it;
    for (it=shapes.begin();it<shapes.end();it++)
        (*it)->setLocation((*it)->getX()+dx, (*it)->getY()+dy);
}

void ShapeContainer::draw(QPainter *renderArea) {
    if (this->isSelected()) {
//        renderArea->setBrush(QBrush(QColor(getRed(),getGreen(),getBlue()),Qt::SolidPattern));
        renderArea->setPen(QColor(getRed(),getGreen(),getBlue()));
        renderArea->drawLine(getX(),getY(),getX(),getY()+getHeight());
        renderArea->drawLine(getX(),getY()+getHeight(),getX()+getWidth(),getY()+getHeight());
        renderArea->drawLine(getX()+getWidth(),getY()+getHeight(),getX()+getWidth(),getY());
        renderArea->drawLine(getX()+getWidth(),getY(),getX(),getY());
    }
    if (this->isVisible()){
        int shapes_size = shapes.size();
        for(int i=0; i<shapes_size; i++) {
            Shape *shape = shapes[i];
            shape->draw(renderArea);
        }
    }
}
