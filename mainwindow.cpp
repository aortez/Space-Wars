#include <QDockWidget>
#include "BoxOfShapes.h"
#include "Circle.h"
#include "InteractiveBoxOfShapes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vec2f.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this );

    BoxOfShapes* display = new  InteractiveBoxOfShapes( this, 600, 600 );
    this->setCentralWidget( display );
    ui->mStatusBar->showMessage( "hello" );
//    ui->mGridLayout->addWidget( display, 0, 0, 1, 1 );
    QObject::connect( display, SIGNAL( numShapesChanged( int ) ), this, SLOT( setNumShapes(int) ) );
    shared_ptr< Shape > circle(
                new Circle(
                    Vec2f( 0, 0 ),
                    0.1,
                    Vec3f( 1, 0, 0 ) ) );

    display->AddShape( circle );


}

MainWindow::~MainWindow( void )
{
    delete ui;
}

void MainWindow::setNumShapes( int numShapes )
{
    ui->mStatusBar->showMessage( tr( "Num shapes: %1" ).arg( numShapes ) );
}
