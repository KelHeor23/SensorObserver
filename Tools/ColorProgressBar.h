/**
 * \file ColorProgressBar.h
 * \brief Простой виджет прогресс‑бара с настраиваемым цветом и диапазоном.
 * \details Поддерживает свойства Qt (value/maximum/color), перерисовывается при изменении значения.
 */

#ifndef COLORPROGRESSBAR_H
#define COLORPROGRESSBAR_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QWidget>
#include <QPainter>
#endif

/**\class ColorProgressBar
 * \brief Виджет прогресс‑бара с произвольным цветом и диапазоном.
 * \details Имеет свойства Qt: value, maximum, color.
 */

class ColorProgressBar : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ColorProgressBar(QWidget *parent = nullptr);

    double value() const { return m_value; }
    double minimum() const { return m_minimum; }
    double maximum() const { return m_maximum; }
    QColor color() const { return m_color; }

public slots:
    /** \brief Устанавливает текущее значение и инициирует перерисовку. */
    void setValue(double value);
    /** \brief Устанавливает минимум шкалы. */
    void setMinimum(double minimum);
    /** \brief Устанавливает максимум шкалы. */
    void setMaximum(double maximum);
    /** \brief Задаёт цвет заполнения. */
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    double m_value;
    double m_minimum = 0;   // Добавлено минимальное значение
    double m_maximum = 1000;
    QColor m_color = Qt::blue;
};
#endif // COLORPROGRESSBAR_H
