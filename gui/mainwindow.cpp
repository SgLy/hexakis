#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QTransform>
#include <QDebug>

#include <ctime>

#include "consts.h"

MainWindow::MainWindow (QWidget * parent):
QMainWindow (parent), ui (new Ui::MainWindow)
{
	ui->setupUi (this);
	scene = new QGraphicsScene (0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE);
	scene->setBackgroundBrush(QBrush(QColor(Qt::white)));
	ui->graphicsView->setScene (scene);
	timer = new QTimer (this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
	qsrand (std::time(NULL));
	game = new normal_game (BOARD_WIDTH, BOARD_HEIGHT);
	state = STATE_INIT;
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

void MainWindow::restartTimer()
{
	timer->start(300);
}

void MainWindow::on_pushButton_clicked()
{
	ui->graphicsView->fitInView(QRectF(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE), Qt::KeepAspectRatio);
	switch (state) {
	case STATE_INIT:
		game->Start();
		state = STATE_RUNNING;
		goto start_timer;
	case STATE_RUNNING:
		;
	case STATE_PAUSE:
		;
	}
	start_timer:
	restartTimer ();
	drawBoard (game->brd);
	drawBlock (game->now);
}

void MainWindow::timer_timeout()
{
	if (state != STATE_RUNNING) return;
	qDebug() << game->Drop();
	drawBoard (game->brd);
	qDebug() << " " << game->now.start_point.x << " "
		<< game->now.start_point.y << "\n";
	drawBlock (game->now);
}

void MainWindow::drawTile(int x, int y)
{
	scene->addRect(x * BOARD_TILE_SIZE,
		y * BOARD_TILE_SIZE, BOARD_TILE_SIZE,
		BOARD_TILE_SIZE, QPen (),
		QBrush (QColor(Qt::red)));
}

void MainWindow::drawBoard(const board &b)
{
	scene->clear();
	scene->addRect(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE, QPen(),
		QBrush(QColor(Qt::black)));
	int row = BOARD_HEIGHT - 1;
	for (board::row r : b.map) {
		for (size_t i = 0; i<BOARD_WIDTH; i++)
		{
			if (r.size() > i && r[i]) {
				drawTile (i,row);
			}
		}
		row--;
	}
}

void MainWindow::drawBlock(const block &b)
{
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (b.shape.b[i][j]) {
				drawTile (j + b.start_point.y,
					i + b.start_point.x);
			}
		}
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Space:
		goto restart_timer;
	case Qt::Key_Left:
		game->MoveLeft();
		goto restart_timer;
	case Qt::Key_Right:
		game->MoveRight();
		goto restart_timer;
	case Qt::Key_Up:
		game->Rotate();
		goto restart_timer;
	case Qt::Key_Down:
		timer_timeout ();
		goto restart_timer;
	default:
		QMainWindow::keyReleaseEvent(event);
		return;
	}
	restart_timer:
	restartTimer();
}
