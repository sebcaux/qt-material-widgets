#ifndef SLIDERSTATEMACHINE_H
#define SLIDERSTATEMACHINE_H

#include <QStateMachine>

class Slider;
class SliderThumb;
class SliderTrack;

class SliderStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    SliderStateMachine(Slider *parent, SliderThumb *thumb, SliderTrack *track);
    ~SliderStateMachine();

signals:
    void changedToMinimum();
    void changedFromMinimum();
    void sliderEnabled();
    void sliderDisabled();
    void noFocusMouseEnter();
    void noFocusMouseLeave();

private:
    Q_DISABLE_COPY(SliderStateMachine)
};

#endif // SLIDERSTATEMACHINE_H
