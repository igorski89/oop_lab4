#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QWidget(parent)
{
    this->resize(640,480);

    ShapeContainer *cont = new ShapeContainer();
    cont->addCircle(150,150,75,100,122,122);
    cont->setSelected(true);
    this->shapeContainers.push_back(cont);
    this->setCurrentContainer(cont);
}

MainWindow::~MainWindow()
{
//    currShape->eraseAll();
//    delete currShape;
}

void MainWindow::setCurrentContainer(ShapeContainer *cont){
    currShapeContainer = cont;
//    curr_shape_cont->setSelected(true);
    currShapeContainer->setVisible(true);
    for (std::vector<ShapeContainer*>::iterator it=shapeContainers.begin();it<shapeContainers.end();it++)
        if (currShapeContainer != (*it))
            (*it)->setVisible(false);
}

void MainWindow::mergeShapesWithCurrent(){
    float x11 = currShapeContainer->getMinX();
    float y11 = currShapeContainer->getMinY();
    float x12 = currShapeContainer->getMaxX();
    float y12 = currShapeContainer->getMaxY();
    for (unsigned int i = 0; i < shapeContainers.size(); i++) {
        ShapeContainer* step_shape_cont = shapeContainers[i];
        if (currShapeContainer != step_shape_cont) {
            float x21 = step_shape_cont->getMinX();
            float y21 = step_shape_cont->getMinY();
            float x22 = step_shape_cont->getMaxX();
            float y22 = step_shape_cont->getMaxY();
            //проверям условия пересечения
            if (x11 < x22 && x12 > x21 && y11 < y22 && y12 > y21) {
                std::vector<Shape*> shapes = step_shape_cont->getShapes();
                for(std::vector<Shape*>::iterator sh_it=shapes.begin();sh_it<shapes.end();sh_it++)
                    currShapeContainer->add((*sh_it));

                shapeContainers.erase(shapeContainers.begin()+i);
                delete step_shape_cont;
                i = 0;
            }
        }
    }
}

void MainWindow::changeCurrentShapeColorOnIntersection() {
    float x11 = currShapeContainer->getMinX();
    float y11 = currShapeContainer->getMinY();
    float x12 = currShapeContainer->getMaxX();
    float y12 = currShapeContainer->getMaxY();
    for (unsigned int i = 0; i < shapeContainers.size(); i++) {
        ShapeContainer* step_shape_cont = shapeContainers[i];
        if (currShapeContainer != step_shape_cont) {
            float x21 = step_shape_cont->getMinX();
            float y21 = step_shape_cont->getMinY();
            float x22 = step_shape_cont->getMaxX();
            float y22 = step_shape_cont->getMaxY();
            //проверям условия пересечения
            if (x11 < x22 && x12 > x21 && y11 < y22 && y12 > y21) {
                Shape* inter_shape = step_shape_cont->getShapes()[0];
                int r = inter_shape->getRed();
                int g = inter_shape->getGreen();
                int b = inter_shape->getBlue();
                std::vector<Shape*> curr_shapes = currShapeContainer->getShapes();
                if (r != curr_shapes[0]->getRed() || b != curr_shapes[0]->getBlue() || g != curr_shapes[0]->getGreen()) {
                    for(std::vector<Shape*>::iterator it=curr_shapes.begin();it<curr_shapes.end();it++)
                        (*it)->setColor(r,g,b);
                }
                break;
            }
        }
    }
}

void MainWindow::selectNextContainer(){
    if (currShapeContainer == shapeContainers.back())
        setCurrentContainer(shapeContainers.front());
    else {
        int shape_size = shapeContainers.size() - 1;
        for(int i=0; i < shape_size; i++)
            if (currShapeContainer == shapeContainers[i])
                setCurrentContainer(shapeContainers[i+1]);
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter *renderArea = new QPainter(this);
    renderArea->setRenderHint(QPainter::Antialiasing);
    changeCurrentShapeColorOnIntersection();
    for(std::vector<ShapeContainer*>::iterator it=shapeContainers.begin(); it < shapeContainers.end(); it++)
        if ((*it) != currShapeContainer)
            (*it)->draw(renderArea);
    if (currShapeContainer != NULL) currShapeContainer->draw(renderArea);

    delete renderArea;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W){
        currShapeContainer->move(0,-10);
    } else if (event->key() == Qt::Key_S) {
        currShapeContainer->move(0,10);
    } else if (event->key() == Qt::Key_A) {
        currShapeContainer->move(-10,0);
    } else if (event->key() == Qt::Key_D) {
        currShapeContainer->move(10,0);
    } else if (event->key() == Qt::Key_Tab) {
        //selecting next shape container
        this->selectNextContainer();
    } else if (event->key() == Qt::Key_1) {
        //adding shape container with circle
        ShapeContainer *new_circle = new ShapeContainer();
//        new_circle->addCircle(width()/2,height()/2,50,255*rand()/(float)RAND_MAX, 255*rand()/(float)RAND_MAX, 255*rand()/(float)RAND_MAX);
        new_circle->addCircle(width()/2,height()/2,50,100, 100, 100);
        new_circle->setSelected(true);
        shapeContainers.push_back(new_circle);
        setCurrentContainer(new_circle);
    } else if (event->key() == Qt::Key_2) {
        //adding shape container with rectangle
        ShapeContainer *new_rectangle = new ShapeContainer();
        new_rectangle->addRectangle(width()/2,height()/2,100,100,125,125,25);
        new_rectangle->setSelected(true);
        shapeContainers.push_back(new_rectangle);
        setCurrentContainer(new_rectangle);
    } else if (event->key() == Qt::Key_P) {
        //toggle animation
        //забьем
    } else if (event->key() == Qt::Key_Z) {
        //scaling up
        currShapeContainer->setScale(2.0);
    } else if (event->key() == Qt::Key_X) {
        //scaling down
        currShapeContainer->setScale(0.5);
    } else if (event->key() == Qt::Key_M) {
        //merging shapes
        mergeShapesWithCurrent();
    }
    this->repaint();
}
