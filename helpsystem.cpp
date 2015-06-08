#include "helpsystem.h"
#include "ui_helpsystem.h"
#include <QDebug>
HelpSystem::HelpSystem(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::HelpSystem)
{
    ui->setupUi(this);

    model = new QFileSystemModel;
    model->setRootPath(QCoreApplication::applicationDirPath());
    ui->helpFileTree->setModel(model);
    ui->helpFileTree->setRootIndex(model->index(QCoreApplication::applicationDirPath()));
    qDebug() << QCoreApplication::applicationDirPath();
}

HelpSystem::~HelpSystem()
{
    delete ui;


}

void HelpSystem::on_helpFileTree_doubleClicked(const QModelIndex &index)
{
    QString fPath = this->model->filePath(index);
    ui->helpDisplay->setSource(QUrl(fPath));
}
