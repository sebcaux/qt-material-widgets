#ifndef EXAMPLEVIEW_H
#define EXAMPLEVIEW_H

#include <QScrollArea>

class ExampleView : public QScrollArea
{
    Q_OBJECT

public:
    explicit ExampleView(QWidget *parent = 0);
    ~ExampleView();

    void setWidget(QWidget *widget);

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private:
    QWidget *_widget;
};

#endif // EXAMPLEVIEW_H
