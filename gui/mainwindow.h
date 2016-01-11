#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QTimer>

#include "../lib/board.h"

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
	void drawBoard (const board &b);
protected:
	void resizeEvent (QResizeEvent *event);
private slots:
	void on_pushButton_clicked();
	void on_timer_timeout();
};

#endif				// MAINWINDOW_H
