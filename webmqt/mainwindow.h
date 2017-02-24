#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_gobutton_clicked();

    void on_filein_textChanged(const QString &arg1);

    void on_fileoutin_textChanged(const QString &arg1);

    void on_startfromcheck_stateChanged(int arg1);

    void on_durationcheck_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
