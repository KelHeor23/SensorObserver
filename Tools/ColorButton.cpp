#include "ColorButton.h"

#include "ColorButton.h"
#include <QColorDialog>
#include <QPainter>
#include <QStyleOption>

ColorButton::ColorButton(QWidget* parent)
    : QPushButton(parent)
{
    setText(" "); // Пустой текст для места под цвет
    connect(this, &QPushButton::clicked, this, &ColorButton::chooseColor);
    updateButton();
}

QColor ColorButton::color() const {
    return m_color;
}

void ColorButton::setColor(const QColor& newColor) {
    if (newColor != m_color) {
        m_color = newColor.isValid() ? newColor : Qt::black;
        updateButton();
    }
}

void ColorButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);

    // Рисуем цветной прямоугольник внутри кнопки
    QPainter painter(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    // Вычисляем область для цвета (с отступами)
    QRect colorRect = option.rect.adjusted(4, 4, -4, -4);

    painter.setBrush(m_color);
    painter.setPen(m_color.darker());
    painter.drawRect(colorRect);
}

void ColorButton::chooseColor() {
    QColor newColor = QColorDialog::getColor(
        m_color,
        this,
        "Выберите цвет",
        QColorDialog::ShowAlphaChannel
        );

    if (newColor.isValid()) {
        setColor(newColor);
    }
}

void ColorButton::updateButton() {
    setToolTip(m_color.name(QColor::HexArgb));
    update(); // Требуем перерисовки
}
