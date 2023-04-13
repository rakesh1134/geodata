#include "utils.h"
#include <QMessageBox>

void display_message(const QString& s)
{
    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.exec();
}

void display_error_message(const QString& s)
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(s);
    msgBox.exec();
}
