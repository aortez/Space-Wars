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

    BoxOfShapes* world = new  InteractiveBoxOfShapes( this, 600, 600 );
    ui->mGridLayout->addWidget( world );
    ui->mStatusBar->showMessage( "status ok" );

    QObject::connect( world, SIGNAL( numShapesChanged( int ) ), this, SLOT( setNumShapes(int) ) );
    QObject::connect( ui->mResetButton, SIGNAL( pressed() ), world, SLOT( resetWorld() ) );
    QObject::connect( world, SIGNAL( fpsChanged( int ) ), ui->mFpsLabelValue, SLOT( setNum(int) ) );

    shared_ptr< Shape > circle( new Circle( Vec2f(), 0.1, Vec3f( 1, 0, 0 ) ) );
    world->addShape( circle );
}

MainWindow::~MainWindow( void )
{
    delete ui;
}

void MainWindow::setNumShapes( int numShapes )
{
    ui->mStatusBar->showMessage( tr( "Num shapes: %1" ).arg( numShapes ) );
}
