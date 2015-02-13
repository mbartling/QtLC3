#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QVBoxLayout *mainLayout = new QVBoxLayout;
    ui->setupUi(this);
//    createGrid();

//    mainLayout->addWidget(gridGroupBox);
    for(int i = 0; i < 65536; ++i){
//        ui->listMem->addItem("x" + QString("%1").arg(i,4, 16, QChar('0')));
//        ui->tableMem->item(i,0)->setText("x" + QString("%1").arg(i,4, 16, QChar('0')));
          QTableWidgetItem* mItem = new QTableWidgetItem;
          QTableWidgetItem* mItemD = new QTableWidgetItem;
          mItemD->setText("x0000");
          mItem->setText("x" + QString("%1").arg(i,4, 16, QChar('0')));
          ui->tableMem->setItem(i,1,mItem);
          ui->tableMem->setItem(i,2,mItemD);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    
}

void MainWindow::on_actionReset_triggered()
{
    
}

void MainWindow::on_actionStep_triggered()
{
    
}

void MainWindow::on_actionNext_triggered()
{
    
}

void MainWindow::on_actionContinue_triggered()
{
    
}

void MainWindow::createGrid(){
//    gridGroupBox = new QGroupBox(tr("Memory View"));
//    QGridLayout *layout = new QGridLayout;
//    for(int i = 0; i < numRegs; ++i){
//        regLabels[i] = new QLabel(tr("R%1:").arg(i));
//        regLines[i] = new QLineEdit;
//        layout->addWidget(regLabels[i],i,0);
//        layout->addWidget(regLines[i],i,1);
//    }

//    ListMemory = new QListWidget;
//    layout->addWidget(ListMemory);

//    gridGroupBox->setLayoout(layout);
}

void MainWindow::on_actionAbout_triggered()
{
//    QMessageBox mAbout(this);
    QMessageBox::about(this, "About LC3-sim", "This QT LC3 Simulator was written by:\n Michael Bartling\nmichael.bartling15@gmail.com\ngithub.com/mbartling\n\nUniversity of Texas at Austin\nComputer Architecture and Embedded Processing Group.\nSpring 2015");
}

void MainWindow::on_GoButton_clicked()
{
    QString mAddr = ui->lineMem->text();
    bool ok;
    mAddr.remove(0,1);
    int mLoc = mAddr.toInt(&ok, 16);
    if(ok){
        ui->tableMem->setCurrentCell(mLoc, 1);
    }
}
