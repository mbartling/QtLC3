#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include "helpsystem.h"
#include "simulator.hpp"
#include "pyInterface.hpp"
#include "simulator-internals.hpp"

#include <vector>
#include "qpyconsole.h"

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
    void setCurrentRow(int rowId);
private slots:
    void on_actionOpen_triggered();
    
    void on_actionReset_triggered();
    
    void on_actionStep_triggered();
    
    void on_actionNext_triggered();
    
    void on_actionContinue_triggered();
    
    void on_actionAbout_triggered();

    void on_GoButton_clicked();

    void on_lineMem_returnPressed();

    void on_actionConsole_triggered();

    void on_actionHelp_Me_triggered();
    void on_actionPython_Console_triggered();

    void on_tableMem_cellDoubleClicked(int row, int column);

    void on_actionOpen_Python_Script_triggered();

private:
    Ui::MainWindow *ui;
    HelpSystem *helpSystem;
    QDockWidget *dockPy;
    QDockWidget *dockConsole;
    simulator* mSim;
    std::function<void (void)> updateRegs;
    std::vector<std::string> fileVec; //Maintain a list of loaded files
    QPyConsole *pyConsole;
};

#endif // MAINWINDOW_H
