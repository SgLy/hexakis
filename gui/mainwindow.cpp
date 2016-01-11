#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QTransform>

#include <ctime>

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
	qsrand (std::time(NULL));
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
	ui->graphicsView->fitInView(QRectF(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE), Qt::KeepAspectRatio);
}

void MainWindow::on_timer_timeout()
{
}

void MainWindow::drawBoard(const board &b)
{
	scene->clear();
	int row = BOARD_HEIGHT - 1;
	for (board::row r : b.map) {
		for (size_t i = 0; i<BOARD_WIDTH; i++)
		{
			if (r.size() > i && r[i]) {
				scene->addRect(i * BOARD_TILE_SIZE,
					row * BOARD_TILE_SIZE, BOARD_TILE_SIZE,
					BOARD_TILE_SIZE, QPen (),
					QBrush (QColor(Qt::red)));
			}
		}
		row--;
	}
}
