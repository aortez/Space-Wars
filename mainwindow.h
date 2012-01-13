#pragma once
#include <QMainWindow>
#include "Rect2f.h"

namespace Ui {
    class MainWindow;
}

class MainWindow
        : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setNumShapes( int numShapes );

private:
    Ui::MainWindow *ui;
};
