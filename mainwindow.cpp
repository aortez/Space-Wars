#include <QDockWidget>
#include "BoxOfShapes.h"
#include "Circle.h"
#include "InteractiveBoxOfShapes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vec2f.h"
#include "SharedPtr.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi( this );

    BoxOfShapes* display = new  InteractiveBoxOfShapes( this, 600, 600 );
    ui->mGridLayout->addWidget( display );
    ui->mStatusBar->showMessage( "status ok" );

    QObject::connect( display, SIGNAL( numShapesChanged( int ) ), this, SLOT( setNumShapes(int) ) );
    QObject::connect( ui->mResetButton, SIGNAL( pressed() ), display, SLOT( resetWorld() ) );
    QObject::connect( display, SIGNAL( fpsChanged( int ) ), ui->mFpsLabelValue, SLOT( setNum(int) ) );

    shared_ptr< Shape > circle( new Circle( Vec2f(), 0.1, Vec3f( 1, 0, 0 ) ) );
    display->addShape( circle );

    /*std::shared_ptr<Shape> rect(
                     new Rect2f(
                        Vec2f( 0, 0 ),
                        5.0f,
                        5.0f,
                        0,
                        Vec3f( 1.0f, 1.0f, 0 )
                    )
                );*/
    //shared_ptr< Shape > rect( new Rect2f() );

    //display->addShape( rect );
}

MainWindow::~MainWindow( void )
{
    delete ui;
}

void MainWindow::setNumShapes( int numShapes )
{
    ui->mStatusBar->showMessage( tr( "Num shapes: %1" ).arg( numShapes ) );
}
