#include "qtmaterialtextfield_internal.h"

#include "qtmaterialtextfield.h"

#include <QEventTransition>
#include <QPainter>
#include <QPropertyAnimation>

/*!
 *  \class QtMaterialTextFieldStateMachine
 *  \internal
 */

QtMaterialTextFieldStateMachine::QtMaterialTextFieldStateMachine(QtMaterialTextField *parent)
    : QStateMachine(parent),
      m_textField(parent),
      m_normalState(new QState),
      m_focusedState(new QState),
      m_label(nullptr),
      m_offsetAnimation(nullptr),
      m_colorAnimation(nullptr),
      m_progress(0.0)
{
    Q_ASSERT(parent);

    addState(m_normalState);
    addState(m_focusedState);

    setInitialState(m_normalState);

    QEventTransition *transition;
    QPropertyAnimation *animation;

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(m_focusedState);
    m_normalState->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(m_normalState);
    m_focusedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "progress", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(310);
    transition->addAnimation(animation);

    m_normalState->assignProperty(this, "progress", 0);
    m_focusedState->assignProperty(this, "progress", 1);

    setupProperties();

    connect(m_textField, &QLineEdit::textChanged, this, &QtMaterialTextFieldStateMachine::setupProperties);
}

QtMaterialTextFieldStateMachine::~QtMaterialTextFieldStateMachine()
{
}

void QtMaterialTextFieldStateMachine::setLabel(QtMaterialTextFieldLabel *label)
{

    delete m_label;

    if (m_offsetAnimation != nullptr)
    {
        removeDefaultAnimation(m_offsetAnimation);
        delete m_offsetAnimation;
    }

    if (m_colorAnimation != nullptr)
    {
        removeDefaultAnimation(m_colorAnimation);
        delete m_colorAnimation;
    }

    m_label = label;

    if (m_label != nullptr)
    {
        m_offsetAnimation = new QPropertyAnimation(m_label, "offset", this);
        m_offsetAnimation->setDuration(210);
        m_offsetAnimation->setEasingCurve(QEasingCurve::OutCubic);
        addDefaultAnimation(m_offsetAnimation);

        m_colorAnimation = new QPropertyAnimation(m_label, "color", this);
        m_colorAnimation->setDuration(210);
        addDefaultAnimation(m_colorAnimation);
    }

    setupProperties();
}

void QtMaterialTextFieldStateMachine::setupProperties()
{
    if (m_label != nullptr)
    {
        const int m = m_textField->textMargins().top();

        if (m_textField->text().isEmpty())
        {
            m_normalState->assignProperty(m_label, "offset", QPointF(0, 26));
        }
        else
        {
            m_normalState->assignProperty(m_label, "offset", QPointF(0, 12 - m));
        }

        m_focusedState->assignProperty(m_label, "offset", QPointF(0, 12 - m));
        m_focusedState->assignProperty(m_label, "color", m_textField->inkColor());
        m_focusedState->assignProperty(m_label, "scale", 0.5);
        m_normalState->assignProperty(m_label, "color", m_textField->labelColor());
        m_normalState->assignProperty(m_label, "scale", 1);

        if (m_label->offset().y() != 0 && !m_textField->text().isEmpty())
        {
            m_label->setOffset(QPointF(0, 12 - m));
        }
        else if (!m_textField->hasFocus() && m_label->offset().y() <= 0 && m_textField->text().isEmpty())
        {
            m_label->setOffset(QPointF(0, 26));
        }
        m_label->setColor(m_textField->labelColor());
    }

    m_textField->update();
}

/*!
 *  \class QtMaterialTextFieldLabel
 *  \internal
 */

QtMaterialTextFieldLabel::QtMaterialTextFieldLabel(QtMaterialTextField *parent)
    : QWidget(parent),
      m_textField(parent),
      m_scale(1),
      m_posX(0),
      m_posY(26),
      m_color(parent->labelColor())
{
    Q_ASSERT(parent);

    QFont font("Roboto", parent->labelFontSize() * 2, QFont::Medium);
    font.setLetterSpacing(QFont::PercentageSpacing, 102);
    setFont(font);
}

QtMaterialTextFieldLabel::~QtMaterialTextFieldLabel()
{
}

/*!
 *  \reimp
 */
void QtMaterialTextFieldLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (!m_textField->labelVisible())
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scale, m_scale);
    painter.setPen(m_color);
    painter.setOpacity(1);

    QPointF pos(2 + m_posX, height() - 36 + m_posY);
    painter.drawText(pos, m_textField->labelText());
}
