#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;
QT_END_NAMESPACE
class Render;

//! [0]
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();

private slots:
    void shapeChanged();
    void penChanged();
    void brushChanged();

private:
    Render *renderArea;
    QLabel *shapeLabel;
    QLabel *penWidthLabel;
    QLabel *penStyleLabel;
    QLabel *brushStyleLabel;
    QLabel *otherOptionsLabel;
    QComboBox *shapeComboBox;
    QSpinBox *penWidthSpinBox;
    QComboBox *penStyleComboBox;
    QComboBox *brushStyleComboBox;
    QCheckBox *rotateCheckBox;
};
//! [0]
#endif // WIDGET_H
