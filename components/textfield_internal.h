#ifndef TEXTFIELD_INTERNAL_H
#define TEXTFIELD_INTERNAL_H

#include <QStateMachine>

class TextField;

class TextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    TextFieldStateMachine(TextField *parent);
    ~TextFieldStateMachine();

private:
    Q_DISABLE_COPY(TextFieldStateMachine)

    TextField *const textField;
};

#endif // TEXTFIELD_INTERNAL_H
