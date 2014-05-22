#ifndef WIZARD_H
#define WIZARD_H

#include <QDialog>
#include <modelFile/modelFile.h>
#include "viewer.h"

namespace Ui {
class Wizard;
}

class Wizard : public QDialog
{
    Q_OBJECT
    
public:
    explicit Wizard(QString stl, QWidget *parent = 0);
    ~Wizard();
    void setOrientation(std::string orientation);
    QString getPart();
    
private slots:
    void on_front_clicked();

    void on_bottom_clicked();

    void on_top_clicked();

    void on_back_clicked();

    void on_left_clicked();

    void on_right_clicked();

private:
    QString stl;
    std::string orientation;
    Ui::Wizard *ui;
    SimpleModel model;
    Viewer *viewer;
};

#endif // WIZARD_H
