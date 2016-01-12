#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

#include <QSize>
#include <QTransform>
#include <QDebug>
#include <QGraphicsTextItem>

#include <ctime>

#include "consts.h"
#include "color_table.h"

MainWindow::MainWindow (QWidget * parent):
QMainWindow (parent), ui (new Ui::MainWindow)
{
	ui->setupUi (this);
	scene = new QGraphicsScene (0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE);
	scene->setBackgroundBrush(QBrush(QColor(Qt::white)));
	ui->graphicsView->setScene (scene);
	nextScene = new QGraphicsScene (0, 0, 4*BOARD_TILE_SIZE, 4*BOARD_TILE_SIZE);
	nextScene->setBackgroundBrush(QBrush(QColor(Qt::black)));
	ui->nextView->setScene(nextScene);
	timer = new QTimer (this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
	srand (std::time(NULL));
	game = new normal_game (BOARD_WIDTH, BOARD_HEIGHT);
	state = STATE_INIT;
	setWindowState(Qt::WindowMaximized);
	settings = new QSettings(SETTINGS_ORGNIZATION, SETTINGS_APPLICATION);
	refreshSettings();
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
	ui->nextView->fitInView(QRectF(0, 0, 4*BOARD_TILE_SIZE,
		4*BOARD_TILE_SIZE), Qt::KeepAspectRatio);
}

void MainWindow::restartTimer()
{
	timer->start(interval);
}

void MainWindow::mode_switch()
{
	ui->graphicsView->fitInView(QRectF(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE), Qt::KeepAspectRatio);
	ui->nextView->fitInView(QRectF(0, 0, 4*BOARD_TILE_SIZE,
		4*BOARD_TILE_SIZE), Qt::KeepAspectRatio);
	switch (state) {
	case STATE_INIT:
		game->Reset();
		game->Start();
		drawNext(game->next);
		state = STATE_RUNNING;
		score = 0;
		refreshScore();
		ui->pushButton->setText("Pause");
		ui->actionStart_Game->setText("Pause");
		goto start_timer;
	case STATE_RUNNING:
		game->Pause();
		timer->stop();
		ui->pushButton->setText("Resume");
		ui->actionStart_Game->setText("Resume");
		state = STATE_PAUSE;
		return;
	case STATE_PAUSE:
		game->Resume();
		ui->pushButton->setText("Pause");
		ui->actionStart_Game->setText("Pause");
		state = STATE_RUNNING;
		goto start_timer;
	}
	start_timer:
	restartTimer ();
	redraw();
}

void MainWindow::on_pushButton_clicked()
{
	mode_switch();
}

void MainWindow::timer_timeout()
{
	if (state != STATE_RUNNING) return;
	if (game->Drop()) {
		finishJudge();
		drawNext(game->next);
		int erases = game->EraseRows();
		for(int i = 0; i<erases; i++)
		{
			score += (i+1) * 100;
		}
		refreshScore();

	}
	qDebug() << game->now.start_point.x << " "
		<< game->now.start_point.y;
	redraw();
}

void MainWindow::redraw()
{
	if(state != STATE_RUNNING) return;
	drawBoard (game->brd);
	drawBlock (game->now);
	if (dropPreview) drawPreview (game->now.FakeDropToBottom(game->brd));
}

void MainWindow::drawTile(int x, int y, int color)
{
	scene->addRect(x * BOARD_TILE_SIZE,
		y * BOARD_TILE_SIZE, BOARD_TILE_SIZE,
		BOARD_TILE_SIZE, QPen (),
		QBrush (QColor(tile_color_table[color].r,
			tile_color_table[color].g, tile_color_table[color].b)));
}

void MainWindow::drawBoard(const board &b)
{
	scene->clear();
	scene->addRect(0, 0, BOARD_WIDTH * BOARD_TILE_SIZE,
		BOARD_HEIGHT * BOARD_TILE_SIZE, QPen(),
		QBrush(QColor(Qt::black)));
	int row = BOARD_HEIGHT - 1;
	for (board::row r : b.map) {
		for (size_t i = 0; i<BOARD_WIDTH; i++) {
			if (r.size() > i && r[i]) {
				drawTile (i,row, r[i]);
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
					i + b.start_point.x, b.shape.color);
			}
		}
	}
}

void MainWindow::drawNext(const block &b)
{
	nextScene->clear();
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (b.shape.b[i][j]) {
				nextScene->addRect(j * BOARD_TILE_SIZE,
					i * BOARD_TILE_SIZE, BOARD_TILE_SIZE,
					BOARD_TILE_SIZE, QPen (),
					QBrush (QColor(
					tile_color_table[b.shape.color].r,
					tile_color_table[b.shape.color].g,
					tile_color_table[b.shape.color].b)));
			}
		}
	}
}

void MainWindow::drawPreview(const block &b)
{
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if (b.shape.b[i][j]) {
				scene->addRect(
					(j + b.start_point.y) * BOARD_TILE_SIZE,
					(i + b.start_point.x) * BOARD_TILE_SIZE,
					BOARD_TILE_SIZE, BOARD_TILE_SIZE,
					QPen (), QBrush (QColor(
					tile_color_table[b.shape.color].r,
					tile_color_table[b.shape.color].g,
					tile_color_table[b.shape.color].b,
					128)));
			}
		}
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	int erases = 0;
	if (event->key() == Qt::Key_P) {
		mode_switch();
		return;
	}
	switch (state) {
	case STATE_RUNNING:
		switch (event->key()) {
		case Qt::Key_Space:
			game->DropToBottom();
			finishJudge();
			drawNext(game->next);
			erases = game->EraseRows();
			for(int i = 0; i<erases; i++)
			{
				score += (i+1) * 100;
			}
			refreshScore();
			goto redraw;
		case Qt::Key_Left:
			game->MoveLeft();
			goto redraw;
		case Qt::Key_Right:
			game->MoveRight();
			goto redraw;
		case Qt::Key_Up:
			game->Rotate();
			goto redraw;
		case Qt::Key_Down:
			timer_timeout ();
			goto redraw;
		default:
			QMainWindow::keyReleaseEvent(event);
			return;
		}
		redraw:
		redraw ();
		return;
	case STATE_INIT:
		if (event->key() == Qt::Key_Space)
			mode_switch();
		else {
			QMainWindow::keyReleaseEvent(event);
			return;
		}
		return;
	case STATE_PAUSE:
		return;
	}
}

void MainWindow::refreshScore()
{
	ui->label_score->setText(QString::asprintf("%d",score));
}

void MainWindow::on_actionStart_Game_triggered()
{
	mode_switch();
}

void MainWindow::on_actionSettings_triggered()
{
	if (state == STATE_RUNNING) mode_switch();
	SettingsDialog* dialog = new SettingsDialog(this);
	dialog->dropPreview = dropPreview;
	dialog->interval = interval;
	dialog->init_settings();
	dialog->setModal(true);
	dialog->exec();
	dropPreview = dialog->dropPreview;
	interval = dialog->interval;
	qDebug() << "dropPreview:" << dropPreview;
	qDebug() << "interval:" << interval;
	refreshSettings(true);
}

void MainWindow::refreshSettings(bool store)
{
	if (store) {
		settings->beginGroup("Gaming");
		settings->setValue("DropPreview",dropPreview);
		settings->setValue("Interval",interval);
		settings->endGroup();
	}
	else {
		settings->beginGroup("Gaming");
		dropPreview = settings->value
			("DropPreview",SETTINGS_DROPPREVIEW_DEFAULT).toBool();
		interval = settings->value
			("Interval",SETTINGS_INTERVAL_DEFAULT).toInt();
		settings->endGroup();
	}
}

void MainWindow::finishJudge()
{
	if(game->now.isHitBoard(game->brd)) {
		state = STATE_INIT;
		int w = BOARD_WIDTH * BOARD_TILE_SIZE;
		int h = BOARD_HEIGHT * BOARD_TILE_SIZE;
		qDebug() << "Game Over";
		scene->clear();
		drawBoard(game->brd);
		scene->addRect(w/4, h/2 - h/8, w/2, h/8, QPen(),
			QBrush(QColor(255,255,255,64)));
		QGraphicsTextItem *ti = scene->addText
			("Game Over.",QFont("serif",BOARD_TILE_SIZE,700));
		ti->setPos(w/4+BOARD_TILE_SIZE,
			h/2 - h/8 + BOARD_TILE_SIZE);
		timer->stop();
		ui->pushButton->setText("Start Game");
		ui->actionStart_Game->setText("Start Game");
	}
}
