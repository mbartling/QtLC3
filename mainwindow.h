#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createGrid();
private slots:
    void on_actionOpen_triggered();
    
    void on_actionReset_triggered();
    
    void on_actionStep_triggered();
    
    void on_actionNext_triggered();
    
    void on_actionContinue_triggered();
    
    void on_actionAbout_triggered();

    void on_GoButton_clicked();

private:
    Ui::MainWindow *ui;
//    enum {numRegs = 8};
//    QGroupBox *gridGroupBox;
//    QLabel *regLabels[numRegs];
//    QLineEdit *regLines[numRegs];
//    QListWidget *ListMemory;
};

#endif // MAINWINDOW_H
