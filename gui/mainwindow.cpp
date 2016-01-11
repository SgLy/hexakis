#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QTransform>

#include "consts.h"

MainWindow::MainWindow (QWidget * parent):
QMainWindow (parent), ui (new Ui::MainWindow)
{
	ui->setupUi (this);
	scene = new QGraphicsScene (0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE);
	scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
	ui->graphicsView->setScene (scene);
	timer = new QTimer (this);
	connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

MainWindow::~MainWindow ()
{
	delete ui;
}

void MainWindow::resizeEvent (QResizeEvent *event)
{
	QMainWindow::resizeEvent (event);
	ui->graphicsView->fitInView(QRectF(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE), Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_timer_timeout()
{

}
