#ifndef TEXTFIELD_INTERNAL_H
#define TEXTFIELD_INTERNAL_H

#include <QStateMachine>

class TextField;

class TextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    TextFieldStateMachine(TextField *parent);
    ~TextFieldStateMachine();

    void setProgress(qreal progress);
    inline qreal progress() const { return _progress; }

private:
    Q_DISABLE_COPY(TextFieldStateMachine)

    TextField *const textField;
    qreal _progress;
};

#endif // TEXTFIELD_INTERNAL_H
