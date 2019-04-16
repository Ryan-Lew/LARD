#ifndef OTHERCONTROL_H
#define OTHERCONTROL_H

#include <QWidget>

namespace Ui {
class Othercontrol;
}

class Othercontrol : public QWidget
{
    Q_OBJECT

public:
    explicit Othercontrol(QWidget *parent = 0);
    ~Othercontrol();

private:
    Ui::Othercontrol *ui;
};

#endif // OTHERCONTROL_H
