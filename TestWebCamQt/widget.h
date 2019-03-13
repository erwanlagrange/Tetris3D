#ifndef WIDGET_H
#define WIDGET_H

#include "opencv2/opencv.hpp"
#include <QWidget>

using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    VideoCapture * webCam_;
    QTimer * timer;
    VideoCapture cap;
    CascadeClassifier face_cascade;

private slots:
    void updatePicture();

};

#endif // WIDGET_H
