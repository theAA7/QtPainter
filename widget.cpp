#include "render.h"
#include "widget.h"
#include <QtWidgets>

const int IdRole = Qt::UserRole;

Widget::Widget()
{
    renderArea = new Render;
    setMinimumSize(565,500);

//  Shape
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("None"), Render::None);
    shapeComboBox->addItem(tr("Линия"), Render::Line);
    shapeComboBox->addItem(tr("Прямоугольник"), Render::Rect);
    shapeComboBox->addItem(tr("Многоугольник"), Render::Polygon);
    shapeComboBox->addItem(tr("Круг"), Render::Circle);
    shapeComboBox->addItem(tr("Эллипс"), Render::Ellipse);
    shapeComboBox->addItem(tr("Дуга"), Render::Arc);
    shapeComboBox->addItem(tr("Сегмент"), Render::Chord);
    shapeComboBox->addItem(tr("Сектор"), Render::Pie);

    shapeLabel = new QLabel(tr("&Shape:"));
    shapeLabel->setBuddy(shapeComboBox);


// Pen Width
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 20);
    penWidthSpinBox->setSpecialValueText(tr("0 (default)"));

    penWidthLabel = new QLabel(tr("Pen &Width:"));
    penWidthLabel->setBuddy(penWidthSpinBox);


//  Pen Style
    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoPen));

    penStyleLabel = new QLabel(tr("&Pen Style:"));
    penStyleLabel->setBuddy(penStyleComboBox);


//  Brush (заливка)
    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
    brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));

    brushStyleLabel = new QLabel(tr("&Заливка:"));
    brushStyleLabel->setBuddy(brushStyleComboBox);

//  Options
    otherOptionsLabel = new QLabel(tr("Опции:"));
    rotateCheckBox = new QCheckBox(tr("&Повернуть"));
    scaleCheckBox = new QCheckBox(tr("&Увеличить"));


//  Connection (slots)
    connect(shapeComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &Widget::shapeChanged);
    connect(penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Widget::penChanged);
    connect(penStyleComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &Widget::penChanged);
    connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::activated),
            this, &Widget::brushChanged);
    connect(rotateCheckBox, &QAbstractButton::toggled,
            renderArea, &Render::setTransformed);
    connect(scaleCheckBox, &QAbstractButton::toggled,
            renderArea, &Render::setScaled);


//  Adding widgets
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    mainLayout->addWidget(shapeLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(shapeComboBox, 2, 1);
    mainLayout->addWidget(penWidthLabel, 3, 0, Qt::AlignRight);
    mainLayout->addWidget(penWidthSpinBox, 3, 1);
    mainLayout->addWidget(penStyleLabel, 4, 0, Qt::AlignRight);
    mainLayout->addWidget(penStyleComboBox, 4, 1);
    mainLayout->addWidget(brushStyleLabel, 2, 2, Qt::AlignRight);
    mainLayout->addWidget(brushStyleComboBox, 2, 3);
    mainLayout->addWidget(otherOptionsLabel, 5, 0, Qt::AlignRight);
    mainLayout->addWidget(rotateCheckBox, 5, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(scaleCheckBox, 5, 2, 1, 2, Qt::AlignRight);
    setLayout(mainLayout);

    shapeChanged();
    penChanged();
    brushChanged();

//  Window Title
    setWindowTitle(tr("Графические примитивы"));
}

// Methods for parameters
void Widget::shapeChanged()
{
    Render::Shape shape = Render::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());

    renderArea->setShape(shape);
}


void Widget::penChanged()
{
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
            penStyleComboBox->currentIndex(), IdRole).toInt());

    renderArea->setPen(QPen(Qt::blue, width, style));
}


void Widget::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
            brushStyleComboBox->currentIndex(), IdRole).toInt());

    renderArea->setBrush(QBrush(Qt::green, style));
}
