#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/objdetect/objdetect.hpp>

#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QTimer>
#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Camera * widgetCamera = new Camera();
}


Widget::~Widget()
{
    delete ui;
}
