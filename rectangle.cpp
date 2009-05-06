/*
 *  rectangle.cpp
 *  oop_lab3
 *
 *  Created by Igor Evsukov on 19.04.09.
 *  Copyright 2009 Igor Evsukov. All rights reserved.
 *
 */

#include "rectangle.h"

void Rectangle::draw(QPainter *renderArea){
    if (this->isVisible()){
//        renderArea->setBrush(QBrush(QColor(getRed(),getGreen(),getBlue()),Qt::SolidPattern));
        QColor curr_color(getRed(),getGreen(),getBlue());
        renderArea->setPen(curr_color);
        renderArea->setBrush(QBrush(curr_color,Qt::SolidPattern));
        renderArea->drawRect(getX(),getY(),getWidth(),getHeight());
    }
}

Rectangle& Rectangle::operator=(const Rectangle& rect) {
    this->setLocation(rect.getX(), rect.getY());
    this->setSize(rect.getWidth(), rect.getHeight());
    this->setColor(rect.getRed(), rect.getGreen(), rect.getBlue());
    this->setVisible(rect.isVisible());
    return *this;    
}

bool Rectangle::operator==(const Rectangle& rect) const {
    if (this->getX() == rect.getX() && this->getY() == rect.getY() &&
        this->getWidth() == rect.getWidth() && this->getHeight() == rect.getHeight() &&
        this->isVisible() == rect.isVisible() &&
        this->getRed() == rect.getRed() &&
        this->getGreen() == rect.getGreen() &&
        this->getBlue() == rect.getBlue())
        return true;
    else return false;
}
