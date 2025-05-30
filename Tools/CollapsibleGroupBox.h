#ifndef COLLAPSIBLEGROUPBOX_H
#define COLLAPSIBLEGROUPBOX_H

#include <QWidget>
#include <QGroupBox>
#include <QToolButton>
#include <QStyle>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

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
