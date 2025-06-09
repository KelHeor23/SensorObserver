#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColor>

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton(QWidget* parent = nullptr);

    QColor color() const;
    void setColor(const QColor& newColor);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void chooseColor();

signals:
    void colorChanged(const QColor&);

private:
    QColor m_color = Qt::black;
    void updateButton();
};

#endif // COLORBUTTON_H
