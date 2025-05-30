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
    int maximum() const { return m_maximum; }
    QColor color() const { return m_color; }

public slots:
    void setValue(int value);

    void setMaximum(int maximum);

    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    int m_value;
    int m_maximum;
    QColor m_color;
};
#endif // COLORPROGRESSBAR_H
