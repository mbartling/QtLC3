#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include "qpyconsole.h"
#include "lc3console.h"
#include <boost/python.hpp>
#include "pythonInterface/pyInterface.cpp"
#include "simulator-internals.hpp"
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
    helpSystem->setWindowTitle("Help");
    helpSystem->setObjectName("Help");
    this->addDockWidget(Qt::RightDockWidgetArea, helpSystem);
    helpSystem->hide();

    this->setWindowTitle("QtLC3");


    //Create the python console
    QMainWindow* pymw = new QMainWindow(this);
    pymw->setMinimumSize(640, 480);
    QPyConsole *pyConsole = QPyConsole::getInstance(pymw, "NOTE: DO NOT create a new sim object\n \
    Please use 'pylc3.sim' as you simulator object");
    pymw->setFocusProxy((QWidget*)pyConsole);
    pymw->setCentralWidget((QWidget*)pyConsole);

    dockPy = new QDockWidget;
    dockPy->setWindowTitle("Python Console");
    this->addDockWidget(Qt::RightDockWidgetArea, dockPy);
    dockPy->setWidget(pymw);
    this->layout()->setContentsMargins(10,10,10,10);
    dockPy->hide();

    //Create the LC3 Console
    QMainWindow* mConsoleW = new QMainWindow(this);
    mConsoleW->setMinimumSize(640, 480);
    lc3Console *mConsole = new lc3Console(mConsoleW);
    mConsoleW->setFocusProxy((QWidget*)mConsole);
    mConsoleW->setCentralWidget((QWidget*)mConsole);

    dockConsole = new QDockWidget;
    dockConsole->setWindowTitle("LC3 Terminal");
    dockConsole->setObjectName("LC3 Terminal");
    this->addDockWidget(Qt::RightDockWidgetArea, dockConsole);
    dockConsole->setWidget(mConsoleW);
    dockConsole->hide();
    tabifyDockWidget(dockPy, dockConsole);
    qDebug() << "Done creating console";
    tabifyDockWidget(dockConsole, helpSystem);
    //Must be done after pyconsole
    mSim = new simulator();

    //Add the GUI Hooks to the simulator
    mSim->setOnMemChanged([this](uint16_t address, uint16_t newVal){
        QTableWidgetItem* mItem = ui->tableMem->item(address, 2); //Get the data
        //mItem->setText("x" + QString("%1").arg(newVal,4, 16, QChar('0')));
        //Will Do translation here too
        QString instText = "x" + QString("%1").arg(newVal,4, 16, QChar('0'));
        QString trannyText = GetTranslation(instText);
        mItem->setText(instText);

        QTableWidgetItem* mItem2 = ui->tableMem->item(address, 3); //Set the translation
        mItem2->setText(trannyText); //I am the whole tranny
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

    //Add the simulator to the console
    mConsole->setSimulator(mSim);
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
    fileVec.push_back(fname);
    mSim->loadBinFile(fname);
    int rowId = ((int) mSim->getPC() & 0xFFFF);
    ui->tableMem->setCurrentCell(rowId, 1);

}

void MainWindow::on_actionReset_triggered()
{
    //First reload all of the Programs
    for(auto fname : fileVec){
        mSim->loadBinFile(fname);
        int rowId = ((int) mSim->getPC() & 0xFFFF);
        ui->tableMem->setCurrentCell(rowId, 1);
    }
    //Clear the Registers
    for(int i = 0; i < 8; ++i){
        mSim->setReg(i, 0);
    }
}

void MainWindow::on_actionStep_triggered()
{
     mSim->stepN(1);
}

void MainWindow::on_actionNext_triggered()
{
    mSim->nextN(1);
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
    //qDebug() << "Converting from x to int status: " << ok;
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
    QString result;
    if(mInst == "x0000") res = "NOP";
    else{// res = ".FILL " + mInst;
        uint16_t inst = (uint16_t) lc3hex2int(mInst);
        switch (inst2opcode(inst)) {
        case ADD:
                if (inst2steering(inst)) {
                    result = QString("ADD R") + QString((char) '0' + inst2sr1(inst)) \
                        + QString(", ") + uint16_t2lc3str(inst2imm5(inst));
                } else {
                    result = QString("ADD R") + QString((char) '0' + inst2sr1(inst)) \
                        + QString(", R") + QString((char) '0' + inst2sr2(inst));
                }
                break;

        case AND:
            if (inst2steering(inst)) {
                result = QString("AND R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", R") + QString((char) '0' + inst2sr1(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm5(inst));
            } else {
                result = QString("AND R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", R") + QString((char) '0' + inst2sr1(inst)) \
                    + QString(", R") + QString((char) '0' + inst2sr2(inst));
            }
            break;

        case NOT:
            result = QString("NOT R") + QString((char) '0' + inst2sr1(inst));
            break;
        case LD:
            result = QString("LD R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm9(inst));
            break;
        case LDI:
            result = QString("LDI R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm9(inst));
            break;
        case ST:
            result = QString("ST R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm9(inst));
            break;
        case STI:
            result = QString("STI R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm9(inst));
            break;
        case LEA:
            result = QString("LEA R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm9(inst));
            break;

        case LDR:
            result = QString("LDR R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", R") + QString((char) '0' + inst2sr1(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm6(inst));
            break;
        case STR:
            result = QString("LDR R") + QString((char) '0' + inst2dr(inst)) \
                    + QString(", R") + QString((char) '0' + inst2sr1(inst)) \
                    + QString(", ") + uint16_t2lc3str(inst2imm6(inst));
            break;

        case BR:
        { //Freaking scope rules
            QString qN = (inst2n(inst)) ? QString("n") : QString("");
            QString qZ = (inst2z(inst)) ? QString("z") : QString("");
            QString qP = (inst2p(inst)) ? QString("p") : QString("");

            result = QString("BR") + qN + qZ + qP \
                    + QString(" ") + uint16_t2lc3str(inst2imm9(inst));
            break;
        }// Google it for an interesting read
        case JSR:
            result = QString("JSR");
            if (inst2n(inst))
                result += uint16_t2lc3str(inst2imm11(inst));
            else
                result += QString("R R") + QString((char) '0' + inst2sr1(inst));
            break;
        case JMP:
            if(inst2sr1(inst) == 7){
                result = QString("RET");
            }
            else {
                result = QString("JMP");
                result += QString(" R") + QString((char) '0' + inst2sr1(inst));
            }
            break;

        case TRAP:
            result = QString("TRAP ") + uint16_t2lc3str(inst2trapvec8(inst));
            break;

        case RTI:
            result = QString("RTI");
            break;

        default:
                result = QString("RESERVED");
        }
        //qDebug() << result;
        res = result;
    }
    return res;
}

void MainWindow::on_actionConsole_triggered()
{
    dockConsole->show();
}

void MainWindow::on_actionHelp_Me_triggered()
{
    helpSystem->show();
}

void MainWindow::on_actionPython_Console_triggered()
{
    dockPy->show();
}



