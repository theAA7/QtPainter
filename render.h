#ifndef RENDER_H
#define RENDER_H


#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class Render : public QWidget
{
    Q_OBJECT

public:
    enum Shape { None, Line, Polygon, Rect, Circle, Ellipse, Arc,
                 Chord, Pie };

    Render (QWidget *parent = 0);

public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setTransformed(bool transformed);
    void setScaled(bool scaled);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    bool transformed;
    bool scaled;
};

#endif // RENDER_H
