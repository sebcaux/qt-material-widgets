#ifndef EXAMPLEVIEW_H
#define EXAMPLEVIEW_H

#include <QScrollArea>

class QGridLayout;

class ExampleView : public QScrollArea
{
    Q_OBJECT

public:
    explicit ExampleView(QWidget *parent = 0);
    ~ExampleView();

    void setWidget(QWidget *widget);

private:
    QWidget           *_widget;
    QGridLayout *const _layout;
};

#endif // EXAMPLEVIEW_H
