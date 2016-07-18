#include "textfield_internal.h"
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QDebug>
#include <QFontDatabase>
#include "textfield.h"

TextFieldStateMachine::TextFieldStateMachine(TextField *parent)
    : QStateMachine(parent),
      textField(parent),
      _normalState(new QState),
      _focusedState(new QState),
      _label(0),
      _offsetAnimation(0),
      _colorAnimation(0),
      _progress(0)
{
    addState(_normalState);
    addState(_focusedState);

    setInitialState(_normalState);

    QEventTransition *transition;
    QPropertyAnimation *animation;

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(_focusedState);
    _normalState->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(_normalState);
    _focusedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    _normalState->assignProperty(this, "progress", 0);
    _focusedState->assignProperty(this, "progress", 1);

    assignProperties();

    connect(textField, SIGNAL(textChanged(QString)), this, SLOT(assignProperties()));
}

TextFieldStateMachine::~TextFieldStateMachine()
{
}

void TextFieldStateMachine::setLabel(TextFieldLabel *widget)
{
    if (_label) {
        delete _label;
    }
    if (_offsetAnimation) {
        removeDefaultAnimation(_offsetAnimation);
        delete _offsetAnimation;
    }
    if (_colorAnimation) {
        removeDefaultAnimation(_colorAnimation);
        delete _colorAnimation;
    }

    _label = widget;

    if (_label)
    {
        _offsetAnimation = new QPropertyAnimation(_label, "offset", this);
        _offsetAnimation->setDuration(210);
        _offsetAnimation->setEasingCurve(QEasingCurve::OutCubic);
        addDefaultAnimation(_offsetAnimation);

        _colorAnimation = new QPropertyAnimation(_label, "color", this);
        _colorAnimation->setDuration(210);
        addDefaultAnimation(_colorAnimation);
    }

    assignProperties();
}

void TextFieldStateMachine::setProgress(qreal progress)
{
    _progress = progress;
    textField->update();
}

void TextFieldStateMachine::assignProperties()
{
    //QPalette p;
    //p.setColor(QPalette::Normal, QPalette::Base, textField->backgroundColor());
    //textField->setPalette(p);

    if (_label)
    {
        const int m = textField->textMargins().top();

        _focusedState->assignProperty(_label, "offset", QPointF(0, 0-m));

        if (textField->text().isEmpty()) {
            _normalState->assignProperty(_label, "offset", QPointF(0, 26));
        } else {
            _normalState->assignProperty(_label, "offset", QPointF(0, 0-m));
        }
        _focusedState->assignProperty(_label, "color", textField->inkColor());
        _normalState->assignProperty(_label, "color", textField->hintColor());

        if (0 != _label->offset().y() && !textField->text().isEmpty()) {
            _label->setOffset(QPointF(0, 0-m));
        } else if (!textField->hasFocus() && _label->offset().y() <= 0 && textField->text().isEmpty()) {
            _label->setOffset(QPointF(0, 26));
        }
    }
}

TextFieldLabel::TextFieldLabel(TextField *parent)
    : QWidget(parent),
      label(parent),
      _scale(1),
      _posX(0),
      _posY(26),
      _color(parent->hintColor())
{
    //QFont f;
    //f.setPointSizeF(parent->labelFontSize());
    //f.setStyleName("Medium");
    //f.setLetterSpacing(QFont::PercentageSpacing, 102);
    //setFont(f);

    QFontDatabase db;
    QFont font(db.font("Roboto", "Medium", parent->labelFontSize()));
    font.setLetterSpacing(QFont::PercentageSpacing, 102);
    setFont(font);
}

TextFieldLabel::~TextFieldLabel()
{
}

void TextFieldLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!label->hasLabel()) {
        return;
    }

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(_scale, _scale);
    painter.setPen(_color);
    painter.setOpacity(1);

    QPointF pos(2 + _posX, height()-36 + _posY);
    painter.drawText(pos.x(), pos.y(), label->label());

#ifdef DEBUG_LAYOUT
    painter.setPen(Qt::red);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect());
#endif
}
