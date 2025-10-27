#ifndef COLORPROGRESSBAR_H
#define COLORPROGRESSBAR_H

#include <QWidget>
#include <QPainter>

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
    void setValue(double value);
    void setMinimum(double minimum);
    void setMaximum(double maximum);
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
