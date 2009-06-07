#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "shape_container.h"
#include <QKeyEvent>


//class MainWindow : public QWidget
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
//    MainWindow(QWidget *parent = 0);
    MainWindow();
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


private slots:
    void newFile();
    void open();
    void saveAs();

};

#endif // MAINWINDOW_H
