#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include "qpyconsole.h"
#include <boost/python.hpp>
#include "pythonInterface/pyInterface.cpp"
#include <string>

QString int2lc3str(int num);
QString uint16_t2lc3str(uint16_t);
QString GetTranslation(QString mInst);
QString bool2String(bool b){
    QString res;
    if(b) res = "1";
    else res = "0";
    return res;
}

using namespace boost::python;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helpSystem = new HelpSystem(this);
    helpSystem->hide();

    this->setWindowTitle("QtLC3");


    //Create the python console
    QMainWindow* pymw = new QMainWindow(this);
    pymw->setMinimumSize(640, 480);
    QPyConsole *pyConsole = QPyConsole::getInstance(pymw, "NOTE: DO NOT create a new sim object\n \
    Please use 'pylc3.sim' as you simulator object");
    pymw->setFocusProxy((QWidget*)pyConsole);
    pymw->setCentralWidget((QWidget*)pyConsole);

    dock = new QDockWidget;
    dock->setWindowTitle("Python Console");
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(pymw);
    this->layout()->setContentsMargins(10,10,10,10);
    dock->hide();
    qDebug() << "Done creating console";

    //Must be done after pyconsole
    mSim = new simulator();

    //Add the GUI Hooks to the simulator
    mSim->setOnMemChanged([this](uint16_t address, uint16_t newVal){
        QTableWidgetItem* mItem = ui->tableMem->item(address, 2); //Get the data
        mItem->setText("x" + QString("%1").arg(newVal,4, 16, QChar('0')));
        //Will Do translation here too
    } );

    updateRegs = [this](){
            ui->tableMem->setCurrentCell(mSim->getPC(), 1);
            ui->lineR8->setText(uint16_t2lc3str(mSim->getPC()));
            ui->lineR0->setText(uint16_t2lc3str(mSim->getReg(0)));
            ui->lineR1->setText(uint16_t2lc3str(mSim->getReg(1)));
            ui->lineR2->setText(uint16_t2lc3str(mSim->getReg(2)));
            ui->lineR3->setText(uint16_t2lc3str(mSim->getReg(3)));
            ui->lineR4->setText(uint16_t2lc3str(mSim->getReg(4)));
            ui->lineR5->setText(uint16_t2lc3str(mSim->getReg(5)));
            ui->lineR6->setText(uint16_t2lc3str(mSim->getReg(6)));
            ui->lineR7->setText(uint16_t2lc3str(mSim->getReg(7)));
            ui->lineN->setText(bool2String(mSim->getPcsrBit('n')));
            ui->lineZ->setText(bool2String(mSim->getPcsrBit('z')));
            ui->lineP->setText(bool2String(mSim->getPcsrBit('p')));

            setCurrentRow((int) mSim->getPC() & 0xFFFF);
        };

    //Go ahead and update the registers
    mSim->setOnEndOfCycle(updateRegs);

    mSim->setRefreshGUIMemHook([this](){
        for(int address = 0; address < 65536; ++address){
            QTableWidgetItem* mItem = ui->tableMem->item(address, 2); //Get the data
            mItem->setText("x" + QString("%1").arg(mSim->memory[address],4, 16, QChar('0')));

        }
    });

    try{
        object main_namespace = pyConsole->getMainNamespace();
        object simulator_module((handle<>(PyImport_ImportModule("pylc3"))));

        main_namespace["pylc3"] = simulator_module;
        scope(simulator_module).attr("sim") = ptr(&(*mSim));
    } catch(error_already_set){
        PyErr_Print();
    }

    //Create the Memory space
    for(int i = 0; i < 65536; ++i){
          QTableWidgetItem* mItem = new QTableWidgetItem;
          QTableWidgetItem* mItemD = new QTableWidgetItem;
          QTableWidgetItem* mItemT = new QTableWidgetItem;
          QString nop = "x0000";
          QString trans = GetTranslation(nop);
          mItemD->setText(nop);
          mItem->setText("x" + QString("%1").arg(i,4, 16, QChar('0')));
          mItemT->setText(trans);
          ui->tableMem->setItem(i,1,mItem);
          ui->tableMem->setItem(i,2,mItemD);
          ui->tableMem->setItem(i,3,mItemT);
    }
    updateRegs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Open Program"), QDir::currentPath(), tr("Object Files (*.obj);;All files (*.*)"));
    std::string fname = filename.toLatin1().constData();
    mSim->loadBinFile(fname);
    int rowId = ((int) mSim->getPC() & 0xFFFF);
    ui->tableMem->setCurrentCell(rowId, 1);

}

void MainWindow::on_actionReset_triggered()
{
    
}

void MainWindow::on_actionStep_triggered()
{
    
}

void MainWindow::on_actionNext_triggered()
{
    mSim->stepN(1);
}

void MainWindow::on_actionContinue_triggered()
{
    mSim->run();
}

void MainWindow::createGrid(){

}

void MainWindow::on_actionAbout_triggered()
{
//    QMessageBox mAbout(this);
    QMessageBox::about(this, "About LC3-sim", "This QT LC3 Simulator was written by:\n Michael Bartling And Jimmy Brisson\nmichael.bartling15@gmail.com\ngithub.com/mbartling\n\nUniversity of Texas at Austin\nComputer Architecture and Embedded Processing Group.\nSpring 2015");
}

int lc3hex2int(QString& mStr){
    QString temp = mStr;
    bool ok;
    int res = temp.remove(0,1).toInt(&ok,16);
    qDebug() << "Converting from x to int status: " << ok;
    return res;

}

QString int2lc3str(int num){
    return QString("x%1").arg(num,4, 16, QChar('0'));
}
QString uint16_t2lc3str(uint16_t num){
    return QString("x%1").arg(num,4, 16, QChar('0'));
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

void MainWindow::on_lineMem_returnPressed()
{
    QString mAddr = ui->lineMem->text();
    bool ok;
    mAddr.remove(0,1);
    int mLoc = mAddr.toInt(&ok, 16);
    if(ok){
        ui->tableMem->setCurrentCell(mLoc, 1);
    }
}
void MainWindow::setCurrentRow(int rowId){
    ui->tableMem->setCurrentCell(rowId, 1);

}
QString GetTranslation(QString mInst){
    QString res;
    if(mInst == "x0000") res = "NOP";
    else res = ".FILL " + mInst;

    return res;
}

void MainWindow::on_actionConsole_triggered()
{

}

void MainWindow::on_actionHelp_Me_triggered()
{
    helpSystem->show();
}

void MainWindow::on_actionPython_Console_triggered()
{
    dock->show();
}

void MainWindow::onMemChanged(uint16_t address, uint16_t newVal){
    QTableWidgetItem* mItem = ui->tableMem->item(address, 2); //Get the data
    mItem->setText("x" + QString("%1").arg(newVal,4, 16, QChar('0')));
    //Will Do translation here too
}

