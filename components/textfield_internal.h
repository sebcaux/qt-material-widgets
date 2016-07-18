#ifndef TEXTFIELD_INTERNAL_H
#define TEXTFIELD_INTERNAL_H

#include <QStateMachine>
#include <QWidget>

class QPropertyAnimation;
class TextField;
class TextFieldLabel;

class TextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    TextFieldStateMachine(TextField *parent);
    ~TextFieldStateMachine();

    void setLabel(TextFieldLabel *widget);

    void setProgress(qreal progress);
    inline qreal progress() const { return _progress; }

protected slots:
    void assignProperties();

private:
    Q_DISABLE_COPY(TextFieldStateMachine)

    friend class TextField;

    TextField      *const textField;
    QState         *const _normalState;
    QState         *const _focusedState;
    TextFieldLabel       *_label;
    QPropertyAnimation   *_offsetAnimation;
    QPropertyAnimation   *_colorAnimation;
    qreal                 _progress;
};

class TextFieldLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal scale WRITE setScale READ scale)
    Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    TextFieldLabel(TextField *parent);
    ~TextFieldLabel();

    inline void setScale(qreal scale)
    { _scale = scale; update(); }
    inline qreal scale() const
    { return _scale; }

    inline void setOffset(const QPointF &pos)
    { _posX = pos.x(); _posY = pos.y(); update(); }
    inline QPointF offset() const
    { return QPointF(_posX, _posY); }

    inline void setColor(const QColor &color)
    { _color = color; update(); }
    inline QColor color() const
    { return _color; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(TextFieldLabel)

    TextField *const label;
    qreal            _scale;
    qreal            _posX;
    qreal            _posY;
    QColor           _color;
};

#endif // TEXTFIELD_INTERNAL_H
