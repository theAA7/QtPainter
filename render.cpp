#include "render.h"

#include <QPainter>

Render::Render(QWidget *parent)
    : QWidget(parent)
{
    shape = None;
    transformed = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize Render::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize Render::sizeHint() const
{
    return QSize(400, 200);
}

void Render::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void Render::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void Render::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}


void Render::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}


void Render::paintEvent(QPaintEvent * /* event */)
{
    //Точки
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 40),
        QPoint(90, 70)
    };

//    QRect rect(10, 20, 80, 60);

    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);

    //Поворот
    if (transformed) {
        painter.translate(250, -90);
        painter.rotate(60.0);
    }

    //Сглаживание
    painter.setRenderHint(QPainter::Antialiasing, true);

    //Форма фигуры
    switch (shape) {
            case None:
                painter.setBrush(QBrush(Qt::NoBrush)); // Отрисовываем пустоту
                break;
            case Line:
                painter.drawLine(190, 100, 300, 200); // Отрисовываем линию
                break;
            case Rect:
                painter.drawRect(170, 100, 200, 150); // Отрисовываем прямоугольник
                break;
            case Polygon:
                painter.translate(180, 90);
                painter.scale(2, 2);
                painter.drawPolygon(points, 4);
                break;
            case Circle:
                painter.drawEllipse(190, 100, 150, 150); // Отрисовываем круг
                break;
            case Ellipse:
                painter.drawEllipse(150, 100, 250, 150); // Отрисовываем эллипс
                break;
            case Arc:
                painter.drawArc(150, 100, 250, 180, 30 * 16, 120 * 16); // Отрисовываем дугу
                break;
            case Chord:
                 painter.drawChord(150, 100, 250, 200, 30 * 16, 120 * 16); // Отрисовываем сегмент
                break;
            case Pie:
                  painter.drawPie(150, 100, 250, 200, 30 * 16, 120 * 16); // Отрисовываем сектор
                break;
            }

 //           painter.restore();
}
