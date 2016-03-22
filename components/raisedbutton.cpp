#include "raisedbutton.h"
#include "lib/customshadoweffect.h"

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(parent)
{
    CustomShadowEffect *effect = new CustomShadowEffect;
    setGraphicsEffect(effect);
}

RaisedButton::~RaisedButton()
{
}
