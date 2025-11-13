/**
 * \file CollapsibleGroupBox.h
 * \brief Сворачиваемая группа (header + содержимое).
 * \details Заголовок с треугольником, кнопка-развёртка, анимации не используются; виджет меняет видимость контента.
 */

#ifndef COLLAPSIBLEGROUPBOX_H
#define COLLAPSIBLEGROUPBOX_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QWidget>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#endif

/**\class CollapsibleGroupBox
 * \brief Группа с заголовком, которую можно сворачивать/разворачивать.
 * \details Хранит кнопки заголовка и контейнер контента, меняет видимость по toggle().
 */

class CollapsibleGroupBox : public QWidget {
    Q_OBJECT
public:
    explicit CollapsibleGroupBox(QWidget* parent = nullptr);

    void setTitle(const QString& title);

    void addWidget(QWidget* widget);

    // Добавление лейаута
    void addLayout(QLayout* layout);

    void setExpanded(bool expanded);

    bool expanded() const;
    /** \brief Переключает видимость содержимого и иконку стрелки. */

public slots:
    void toggle();

private:
    QToolButton* toggleButton;
    QToolButton* headerLabel;
    QWidget* contentWidget;
    QVBoxLayout* mainLayout;
    QVBoxLayout* contentLayout;
    bool isExpanded;
};

#endif // COLLAPSIBLEGROUPBOX_H
