#ifndef QTMATERIALTEXTFIELD_P_H
#define QTMATERIALTEXTFIELD_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialTextField;
class QtMaterialTextFieldStateMachine;
class QtMaterialTextFieldLabel;

class QtMaterialTextFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialTextFieldPrivate)
    Q_DECLARE_PUBLIC(QtMaterialTextField)

public:
    QtMaterialTextFieldPrivate(QtMaterialTextField *q);
    virtual ~QtMaterialTextFieldPrivate();

    void init();

    QtMaterialTextField *const q_ptr;

    QtMaterialTextFieldStateMachine *stateMachine;
    QtMaterialTextFieldLabel *label;

    QString labelText;
    qreal labelFontSize;
    bool labelVisible;
    bool inputLineVisible;

    bool useThemeColors;
    QColor textColor;
    QColor labelColor;
    QColor inkColor;
    QColor inputLineColor;
};

#endif  // QTMATERIALTEXTFIELD_P_H
