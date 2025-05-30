#include "ColorProgressBar.h"

ColorProgressBar::ColorProgressBar(QWidget *parent)
    : QWidget(parent), m_value(0), m_maximum(100), m_color(Qt::blue) {}

void ColorProgressBar::setValue(int value) {
    m_value = qBound(0, value, m_maximum);
    update();
}

void ColorProgressBar::setMaximum(int maximum) {
    m_maximum = maximum;
    update();
}

void ColorProgressBar::setColor(const QColor &color) {
    m_color = color;
    update();
}

void ColorProgressBar::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем фон
    painter.setPen(Qt::NoPen);
    painter.setBrush(palette().window());
    painter.drawRoundedRect(rect(), 3, 3);

    // Рассчитываем прогресс
    qreal ratio = static_cast<qreal>(m_value) / m_maximum;
    int fillWidth = static_cast<int>(ratio * width());

    // Рисуем заполнение
    QRect fillRect(0, 0, fillWidth, height());
    painter.setBrush(m_color);
    painter.drawRoundedRect(fillRect, 3, 3);
}
