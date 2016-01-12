#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QTimer>
#include <QSettings>

#include "../lib/board.h"
#include "../lib/normal_game.h"

namespace Ui {
	class MainWindow;
}
class MainWindow:public QMainWindow {
Q_OBJECT public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	QGraphicsScene *scene, *nextScene;
private:
	Ui::MainWindow *ui;
	QTimer *timer;
	void redraw ();
	void drawTile (int x, int y, int color);
	void drawBoard (const board &b);
	void drawBlock (const block &b);
	void drawNext (const block &b);
	void drawPreview (const block &b);
	void refreshScore();
	normal_game *game;
	enum {STATE_INIT, STATE_RUNNING, STATE_PAUSE} state;
	void restartTimer();
	int score;
	void doEraseRows();
	void mode_switch();
	QSettings *settings;
	bool dropPreview;
	void refreshSettings(bool store = false);
protected:
	void resizeEvent (QResizeEvent *event);
	void keyReleaseEvent(QKeyEvent * event);
private slots:
	void on_pushButton_clicked();
	void timer_timeout();
	void on_actionStart_Game_triggered();
	void on_actionSettings_triggered();
};

#endif				// MAINWINDOW_H
