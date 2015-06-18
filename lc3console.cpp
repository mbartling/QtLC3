#include "lc3console.h"
#include "ui_lc3console.h"

lc3Console::lc3Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lc3Console)
{
    ui->setupUi(this);
}

lc3Console::~lc3Console()
{
    delete ui;
}


void lc3Console::on_consoleLineEdit_textEdited(const QString &arg1)
{
    for(auto c : arg1){
        ui->lc3History->appendPlainText(QString(c) + QString(""));
        char ch = c.toLatin1();
        mSim->memWrite(0xFE02, (uint16_t) ch); //Set KBDR
        mSim->memWrite(0xFE00, 0x8000); //Setting bit[15] in KBSR
    }
}

void lc3Console::on_consoleLineEdit_returnPressed()
{
    ui->consoleLineEdit->clear();
    ui->lc3History->appendPlainText("<ENTER>");
    char ch = '\n';
    mSim->memWrite(0xFE02, (uint16_t) ch); //Set KBDR
    mSim->memWrite(0xFE00, 0x8000); //Setting bit[15] in KBSR
}

void lc3Console::setSimulator(simulator* sim){
    mSim = sim;
}
