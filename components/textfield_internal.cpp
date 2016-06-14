#include "textfield_internal.h"
#include "textfield.h"

TextFieldStateMachine::TextFieldStateMachine(TextField *parent)
    : QStateMachine(parent),
      textField(parent)
{
}

TextFieldStateMachine::~TextFieldStateMachine()
{
}
