#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "shape_container.h"
#include <QKeyEvent>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    std::vector<ShapeContainer*> shapeContainers;
    ShapeContainer *currShapeContainer;


    void setCurrentContainer(ShapeContainer* cont);
    void selectNextContainer();
    void mergeShapesWithCurrent();
    void changeCurrentShapeColorOnIntersection();
    

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
