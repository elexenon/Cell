// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customMaskDialog.h"
#include "../../CellUI/Widgets/Launcher.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QLabel>

customMaskDialog::customMaskDialog(QWidget *parent):
    QWidget(parent),
    animi(new QPropertyAnimation(this)),
    targetWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    dialog(new QFrame(this)),
    labelOption(new QLabel(dialog)),
    labelHint(new QLabel(dialog))
{
    init();
}

void customMaskDialog::init()
{
    // Set "This"
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addStretch(10);
    mainLayout->addWidget(dialog);
    mainLayout->addStretch(15);

    setLayout(mainLayout);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    // Set Dialog
    dialog->setAutoFillBackground(true);
    dialog->setStyleSheet(CHAR2STR("QFrame{background-color:rgb(247,247,247);}"));
    dialog->setFixedHeight(300);

    CellUiGlobal::setCustomTextLabel(labelOption, CHAR2STR("Microsoft YaHei UI"), 24, CHAR2STR("选项主题"));
    CellUiGlobal::setCustomTextLabel(labelHint,   CHAR2STR("Microsoft YaHei UI Light"), 15, CHAR2STR("进行一些描述。"));

    QVBoxLayout *VLayoutLabel = new QVBoxLayout;
    VLayoutLabel->setMargin(0);
    VLayoutLabel->setSpacing(25);
    VLayoutLabel->addWidget(labelOption);
    VLayoutLabel->addWidget(labelHint);
    VLayoutLabel->addStretch();

    QHBoxLayout *HLayoutOptionWidget = new QHBoxLayout;
    HLayoutOptionWidget->setAlignment(Qt::AlignmentFlag::AlignVCenter);
    HLayoutOptionWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *VLayoutDialog = new QVBoxLayout(dialog);
    VLayoutDialog->setContentsMargins(300, 50, 0, 0);
    VLayoutDialog->setSpacing(25);
    VLayoutDialog->addLayout(VLayoutLabel);
    VLayoutDialog->addLayout(HLayoutOptionWidget);
}

void customMaskDialog::setOptionText(const QString &text)
{
    labelOption->setText(text);
}

void customMaskDialog::setHintText(const QString &text)
{
    labelHint->setText(text);
}

void customMaskDialog::setOptionWidget(QWidget *widget)
{
    (void)widget;
}

void customMaskDialog::switchOpacity(int sValue, int eValue)
{
    animi->setPropertyName("opacity");
    animi->setTargetObject(this);
    animi->setDuration(150);
    animi->setEasingCurve(QEasingCurve::Linear);
    animi->setStartValue(sValue);
    animi->setEndValue(eValue);
    animi->start(QAbstractAnimation::KeepWhenStopped);
}

void customMaskDialog::fade()
{
    connect(animi, &QPropertyAnimation::finished, this, &customMaskDialog::close);

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    eff->setOpacity(1);
    this->setGraphicsEffect(eff);

    animi->setTargetObject(eff);
    animi->setPropertyName("opacity");
    animi->setDuration(150);
    animi->setEasingCurve(QEasingCurve::Linear);
    animi->setStartValue(1);
    animi->setEndValue(0);
    animi->start(QAbstractAnimation::DeleteWhenStopped);
}

void customMaskDialog::setOpacity(int value)
{
    mOpacity = value;
    update();
}

void customMaskDialog::showEvent(QShowEvent *e)
{
    (void)e;
    if(targetWidget == nullptr) return;
    switchOpacity(0, 170);
}

void customMaskDialog::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.fillRect(this->rect(),QColor(0,0,0,mOpacity));
}

void customMaskDialog::mousePressEvent(QMouseEvent *event)
{
    Qt::MouseButton button = event->button();
    if(!(button == Qt::LeftButton)) return;
    if(dialog->geometry().contains(event->pos())) return;
    fade();
}
