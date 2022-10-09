#ifndef QTMATERIALSWITCH_P_H
#define QTMATERIALSWITCH_P_H

#include <QColor>
#include <QtGlobal>

class QStateMachine;
class QState;
class QtMaterialSwitch;
class QtMaterialSwitchTrack;
class QtMaterialSwitchThumb;
class QtMaterialSwitchRippleOverlay;

class QtMaterialSwitchPrivate
{
    Q_DISABLE_COPY(QtMaterialSwitchPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSwitch)

public:
    QtMaterialSwitchPrivate(QtMaterialSwitch *q);
    ~QtMaterialSwitchPrivate();

    void init();
    void setupProperties();

    QtMaterialSwitch *const q_ptr;
    QtMaterialSwitchTrack *track;
    QtMaterialSwitchThumb *thumb;
    QtMaterialSwitchRippleOverlay *rippleOverlay;
    QStateMachine *stateMachine;
    QState *offState;
    QState *onState;
    Qt::Orientation orientation;
    QColor disabledColor;
    QColor activeColor;
    QColor inactiveColor;
    QColor trackColor;
    QColor textColor;
    bool useThemeColors;
};

#endif  // QTMATERIALSWITCH_P_H
