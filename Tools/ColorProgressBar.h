#ifndef COLORPROGRESSBAR_H
#define COLORPROGRESSBAR_H

#include <QWidget>
#include <QPainter>

class ColorProgressBar : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ColorProgressBar(QWidget *parent = nullptr);

    int value() const { return m_value; }
    int minimum() const { return m_minimum; }
    int maximum() const { return m_maximum; }
    QColor color() const { return m_color; }

public slots:
    void setValue(int value);
    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    int m_value;
    int m_minimum = 0;   // Добавлено минимальное значение
    int m_maximum = 1000;
    QColor m_color = Qt::blue;
};
#endif // COLORPROGRESSBAR_H
