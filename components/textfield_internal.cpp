#include "textfield_internal.h"
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QDebug>
#include "textfield.h"

TextFieldStateMachine::TextFieldStateMachine(TextField *parent)
    : QStateMachine(parent),
      textField(parent),
      label(0),
      _normalState(new QState),
      _focusedState(new QState),
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

    animation = new QPropertyAnimation(this, "progress");
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->setDuration(340);
    transition->addAnimation(animation);

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(_normalState);
    _focusedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress");
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(340);
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
    label = widget;

    if (label)
    {
        QPropertyAnimation *animation;

        animation = new QPropertyAnimation(label, "offset");
        animation->setDuration(210);
        animation->setEasingCurve(QEasingCurve::OutCubic);
        addDefaultAnimation(animation);

        animation = new QPropertyAnimation(label, "color");
        animation->setDuration(210);
        addDefaultAnimation(animation);
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
    QPalette p;
    p.setColor(QPalette::Normal, QPalette::Base, textField->backgroundColor());
    textField->setPalette(p);

    if (label)
    {
        const int m = textField->textMargins().top();

        _focusedState->assignProperty(label, "offset", QPointF(0, 0-m));

        if (textField->text().isEmpty()) {
            _normalState->assignProperty(label, "offset", QPointF(0, 26));
        } else {
            _normalState->assignProperty(label, "offset", QPointF(0, 0-m));
        }
        _focusedState->assignProperty(label, "color", textField->inkColor());
        _normalState->assignProperty(label, "color", textField->hintColor());
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
    QFont f;
    f.setPointSizeF(parent->labelFontSize());
    f.setStyleName("Medium");
    f.setLetterSpacing(QFont::PercentageSpacing, 102);
    setFont(f);
}

TextFieldLabel::~TextFieldLabel()
{
}

void TextFieldLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

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
