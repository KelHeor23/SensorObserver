#include "CollapsibleGroupBox.h"

CollapsibleGroupBox::CollapsibleGroupBox(QWidget *parent)
    : QWidget(parent), isExpanded(true) {
    // Кнопка для сворачивания/разворачивания
    toggleButton = new QToolButton(this);
    toggleButton->setStyleSheet("QToolButton { border: none; }");
    toggleButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toggleButton->setArrowType(Qt::ArrowType::DownArrow);
    toggleButton->setCheckable(false);

    // Заголовок
    headerLabel = new QToolButton(this);
    headerLabel->setStyleSheet("QToolButton { border: none; }");
    headerLabel->setCheckable(false);

    // Заголовочный layout
    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(toggleButton);
    headerLayout->addWidget(headerLabel);
    headerLayout->addStretch();

    // Контентная область
    contentWidget = new QWidget(this);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(12, 0, 0, 0);

    // Основной layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(contentWidget);

    // Сигналы/слоты
    connect(toggleButton, &QToolButton::clicked, this, &CollapsibleGroupBox::toggle);
    connect(headerLabel, &QToolButton::clicked, this, &CollapsibleGroupBox::toggle);
}

void CollapsibleGroupBox::setTitle(const QString &title) {
    headerLabel->setText(title);
}

void CollapsibleGroupBox::addWidget(QWidget *widget) {
    contentLayout->addWidget(widget);
}

void CollapsibleGroupBox::addLayout(QLayout *layout) {
    QWidget* container = new QWidget(this);
    container->setLayout(layout);
    contentLayout->addWidget(container);
}

void CollapsibleGroupBox::setExpanded(bool expanded) {
    if (isExpanded != expanded) {
        toggle();
    }
}

bool CollapsibleGroupBox::expanded() const {
    return isExpanded;
}

void CollapsibleGroupBox::toggle() {
    isExpanded = !isExpanded;
    contentWidget->setVisible(isExpanded);
    toggleButton->setArrowType(isExpanded ? Qt::DownArrow : Qt::RightArrow);
    updateGeometry();
}
