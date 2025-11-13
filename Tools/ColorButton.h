/**
 * \file ColorButton.h
 * \brief Кнопка выбора цвета с предпросмотром.
 * \details Наследует QPushButton, открывает QColorDialog и эмитит signal colorChanged.
 */

#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QPushButton>
#include <QColor>
#endif

/**\class ColorButton
 * \brief Кнопка выбора цвета с предпросмотром.
 * \details Эмитирует сигнал colorChanged при изменении.
 */

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton(QWidget* parent = nullptr);

    QColor color() const;
    void setColor(const QColor& newColor);

protected:
    /** \brief Рисует текущий цвет внутри кнопки. */
    void paintEvent(QPaintEvent* event) override;

private slots:
    /** \brief Открывает диалог выбора цвета (с альфа‑каналом). */
    void chooseColor();

signals:
    void colorChanged(const QColor&);

private:
    QColor m_color = Qt::black;
    void updateButton();
};

#endif // COLORBUTTON_H
