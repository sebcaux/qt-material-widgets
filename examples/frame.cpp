#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include "frame.h"

Frame::Frame(QWidget *parent)
    : QWidget(parent),
      _edit(new QTextEdit),
      _layout(new QHBoxLayout)
{
    setLayout(_layout);

    _layout->addWidget(new QLabel("placeholder"));

    QFont font("monospace");
    font.setPixelSize(12);

    _edit->setTextInteractionFlags(Qt::TextBrowserInteraction);
    _edit->setFont(font);
    _edit->setWordWrapMode(QTextOption::NoWrap);
    _layout->addWidget(_edit);

    _layout->setStretch(0, 1);
    _layout->setStretch(1, 1);

    //setMinimumHeight(300);
}

Frame::~Frame()
{
}

void Frame::setCodeSnippet(const QString &snippet)
{
    _edit->setText(snippet);
}

void Frame::setWidget(QWidget *widget)
{
    QWidget *old = _layout->itemAt(0)->widget();
    _layout->replaceWidget(old, widget);
    old->deleteLater();
}
