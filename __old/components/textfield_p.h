#ifndef TEXTFIELD_P_H
#define TEXTFIELD_P_H

#include <QObject>
#include <QColor>

class TextField;
class TextFieldStateMachine;
class TextFieldLabel;

class TextFieldPrivate
{
    Q_DISABLE_COPY(TextFieldPrivate)
    Q_DECLARE_PUBLIC(TextField)

public:
    TextFieldPrivate(TextField *q);
    void init();

    TextField             *const q_ptr;
    TextFieldLabel        *label;
    TextFieldStateMachine *machine;
    QColor                 textColor;
    QColor                 backgroundColor;
    QColor                 inkColor;
    QColor                 underlineColor;
    QColor                 hintColor;
    QString                labelString;
    qreal                  labelFontSize;
    bool                   showLabel;
    bool                   useThemeColors;
};

#endif // TEXTFIELD_P_H
