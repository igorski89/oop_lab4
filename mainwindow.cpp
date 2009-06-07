#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenu>
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <fstream>
#include <QFile>
#include <QStringList>

//MainWindow::MainWindow(QWidget *parent):QWidget(parent)
MainWindow::MainWindow() {
    this->resize(640,480);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newFileAction = new QAction(tr("&New"),this);
    newFileAction->setShortcuts(QKeySequence::New);
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));
    fileMenu->addAction(newFileAction);

    QAction *openAction = new QAction(tr("&Open"),this);
    openAction->setShortcuts(QKeySequence::Open);
//    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    fileMenu->addAction(openAction);

    QAction *saveAsAction = new QAction(tr("&Save As..."),this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
    fileMenu->addAction(saveAsAction);



//    ShapeContainer *cont = new ShapeContainer();
//    cont->addCircle(150,150,75,100,122,122);
//    cont->setSelected(true);
//    this->shapeContainers.push_back(cont);
//    this->setCurrentContainer(cont);
}

MainWindow::~MainWindow()
{
//    currShape->eraseAll();
//    delete currShape;
}

void MainWindow::newFile() {
    for(unsigned int i = 0; i < shapeContainers.size(); i++) {
        shapeContainers[i]->eraseAll();
        delete shapeContainers[i];
    }
    shapeContainers.clear();
    setCurrentContainer(NULL);
    repaint();
}

void MainWindow::open() {
//    std::cout << "opening file " << std::endl;
     QFileDialog::Options options;
     QString selectedFilter;
     QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("open file"),
                                 QString(""),
                                 tr("All Files (*);;Text Files (*.txt)"),
                                 &selectedFilter,
                                 options);
     if (!fileName.isEmpty()) {
         std::ifstream data(fileName.toStdString().c_str(), std::ios_base::in);
         while(!data.eof()){
             bool ok;
             std::string line;
             std::getline(data,line);
//             std::cout << "line = " << line << std::endl;
             if (line == "") continue;
             std::cout << "ShapeContainer" << std::endl;
             ShapeContainer *cont = new ShapeContainer();
             QStringList cont_list = QString(line.c_str()).split(" ");
             QStringList cont_par = cont_list[1].split(",");
             cont->setLocation(cont_par.at(0).toFloat(),cont_par.at(1).toFloat());
             cont->setColor(cont_par.at(4).toInt(&ok,10),cont_par.at(5).toInt(&ok,10),cont_par.at(6).toInt(&ok,10));
             cont->setSelected(true);
             while( line != "***") {
//                 std::cout << line << std::endl;
                 QStringList list = QString(line.c_str()).split(" ");
                 QStringList par = list[1].split(",");
                 if (list[0] == "Shape"){
                     float x = par.at(0).toFloat(), y = par.at(1).toFloat(), w = par.at(2).toFloat(), h = par.at(3).toFloat();
                     int r = par.at(4).toInt(&ok,10), g = par.at(5).toInt(&ok,10), b = par.at(6).toInt(&ok,10);
                     std::cout << "Shape("<<x<<","<<y<<","<<","<<w<<","<<h<<","<<r<<","<<g<<","<<b<<")"<<std::endl;
                     Shape* shape = new Shape(x,y,w,h,r,g,b);
                     cont->add(shape);

                 } else if (list[0] == "Rectangle") {
                     float x = par.at(0).toFloat(), y = par.at(1).toFloat(), w = par.at(2).toFloat(), h = par.at(3).toFloat();
                     int r = par.at(4).toInt(&ok,10), g = par.at(5).toInt(&ok,10), b = par.at(6).toInt(&ok,10);
                     std::cout << "Rectangle(" << x << "," << y << "," << w << "," <<h<<","<<r<<","<<g<<","<<b<<")"<<std::endl;
                     Shape *rect = new Rectangle(x,y,w,h,r,g,b);
                     cont->add(rect);
                 } else if (list[0] == "Circle") {
                     float x = par.at(0).toFloat(), y = par.at(1).toFloat(), radius = par.at(2).toFloat();
                     int r = par.at(3).toInt(&ok,10), g = par.at(4).toInt(&ok,10), b = par.at(5).toInt(&ok,10);
                     std::cout << "Circle("<<x<<","<<y<<","<<radius<<","<<r<<","<<g<<","<<b<<")"<<std::endl;
                     Shape* circle = new Circle(x,y,radius,r,g,b);
                     cont->add(circle);
                 }
                std::getline(data,line);
             }
             shapeContainers.push_back(cont);
             std::cout << "***" << std::endl;
         }
         data.close();
         if (shapeContainers.size()>0) setCurrentContainer(shapeContainers[0]);
     }
}

void MainWindow::saveAs() {
//    std::cout << "saving file " << std::endl;
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save to file"),
                                                    QString(""),
                                                    tr("All Files (*);;Text Files (*.txt)"),
                                                    &selectedFilter,
                                                    options);
    if (!fileName.isEmpty()) {
        std::cout << fileName.toStdString() << std::endl;
        std::ofstream data(fileName.toStdString().c_str(), std::ios_base::out);
        for (std::vector<ShapeContainer*>::iterator it = shapeContainers.begin();it < shapeContainers.end(); it++){
            data << (*it)->toString();
            data << "***" << std::endl;
        }
        data.close();
    }
}

void MainWindow::setCurrentContainer(ShapeContainer *cont){
    currShapeContainer = cont;
//    curr_shape_cont->setSelected(true);
    if (currShapeContainer != NULL) currShapeContainer->setVisible(true);
    for (std::vector<ShapeContainer*>::iterator it=shapeContainers.begin();it<shapeContainers.end();it++)
        if (currShapeContainer != (*it))
            (*it)->setVisible(false);
}

void MainWindow::mergeShapesWithCurrent(){
    if (currShapeContainer == NULL) return;
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
    if (currShapeContainer == NULL) return;
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
    if (shapeContainers.size() > 0) {
        if (currShapeContainer == NULL) {
            setCurrentContainer(shapeContainers.front());
        }
        else if (currShapeContainer == shapeContainers.back())
            setCurrentContainer(shapeContainers.front());
        else {
            int shape_size = shapeContainers.size() - 1;
            for(int i=0; i < shape_size; i++)
                if (currShapeContainer == shapeContainers[i])
                    setCurrentContainer(shapeContainers[i+1]);
        }
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
        if (currShapeContainer != NULL)  currShapeContainer->move(0,-10);
    } else if (event->key() == Qt::Key_S) {
        if (currShapeContainer != NULL) currShapeContainer->move(0,10);
    } else if (event->key() == Qt::Key_A) {
        if (currShapeContainer != NULL) currShapeContainer->move(-10,0);
    } else if (event->key() == Qt::Key_D) {
        if (currShapeContainer != NULL) currShapeContainer->move(10,0);
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
        if (currShapeContainer != NULL) currShapeContainer->setScale(2.0);
    } else if (event->key() == Qt::Key_X) {
        //scaling down
        if (currShapeContainer != NULL) currShapeContainer->setScale(0.5);
    } else if (event->key() == Qt::Key_M) {
        //merging shapes
        if (currShapeContainer != NULL) mergeShapesWithCurrent();
    }
    this->repaint();
}
