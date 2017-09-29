#ifndef DRAWER_INTERNAL_H
#define DRAWER_INTERNAL_H

#include <QStateMachine>

class Drawer;

class DrawerStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit DrawerStateMachine(Drawer *drawer);
    ~DrawerStateMachine();

    void setOffset(int offset);
    inline int offset() const { return m_offset; }

    void updatePropertyAssignments();

signals:
    void enterOpenedState();
    void enterClosedState();

private:
    Q_DISABLE_COPY(DrawerStateMachine)

    Drawer *const m_drawer;
    QState *const m_openState;
    QState *const m_closedState;
    int           m_offset;
};

#endif // DRAWER_INTERNAL_H
