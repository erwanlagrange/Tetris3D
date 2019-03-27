#include "widgettetris.h"
#include "ui_widgettetris.h"

WidgetTetris::WidgetTetris(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTetris)
{
    ui->setupUi(this);
    resize(600,600);
}

WidgetTetris::~WidgetTetris()
{
    delete ui;
}
