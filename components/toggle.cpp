#include <QAbstractButton>
#include "toggle.h"
#include "../lib/rippleoverlay.h"

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
}

Toggle::~Toggle()
{
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}

