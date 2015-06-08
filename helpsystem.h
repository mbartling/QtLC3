#ifndef HELPSYSTEM_H
#define HELPSYSTEM_H

#include <QDockWidget>
#include <QTreeView>
#include <QFileSystemModel>

namespace Ui {
class HelpSystem;
}

class HelpSystem : public QDockWidget
{
    Q_OBJECT

public:
    explicit HelpSystem(QWidget *parent = 0);
    ~HelpSystem();

private slots:
    void on_helpFileTree_doubleClicked(const QModelIndex &index);

private:
    Ui::HelpSystem *ui;
    QFileSystemModel *model;
};

#endif // HELPSYSTEM_H
