#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QTimer>

#include "../lib/board.h"
#include "../lib/normal_game.h"

namespace Ui {
	class MainWindow;
}
class MainWindow:public QMainWindow {
Q_OBJECT public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	QGraphicsScene *scene;
private:
	Ui::MainWindow *ui;
	QTimer *timer;
	void drawTile (int x, int y);
	void drawBoard (const board &b);
	void drawBlock (const block &b);
	normal_game *game;
	enum {STATE_INIT, STATE_RUNNING, STATE_PAUSE} state;
protected:
	void resizeEvent (QResizeEvent *event);
private slots:
	void on_pushButton_clicked();
	void timer_timeout();
};

#endif				// MAINWINDOW_H
