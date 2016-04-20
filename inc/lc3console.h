#ifndef LC3CONSOLE_H
#define LC3CONSOLE_H

#include <QWidget>
#include "simulator.hpp"

namespace Ui {
class lc3Console;
}

class lc3Console : public QWidget
{
    Q_OBJECT

public:
    explicit lc3Console(QWidget *parent = 0);
    ~lc3Console();
    void setSimulator(simulator*);
private slots:

    void on_consoleLineEdit_textEdited(const QString &arg1);

    void on_consoleLineEdit_returnPressed();

private:
    Ui::lc3Console *ui;
    simulator *mSim;
};

#endif // LC3CONSOLE_H
