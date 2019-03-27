#ifndef WIDGETTETRIS_H
#define WIDGETTETRIS_H

#include <QWidget>

namespace Ui {
class WidgetTetris;
}

class WidgetTetris : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTetris(QWidget *parent = nullptr);
    ~WidgetTetris();

private:
    Ui::WidgetTetris *ui;
};

#endif // WIDGETTETRIS_H
