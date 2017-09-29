#ifndef FRAME_H
#define FRAME_H

#include <QWidget>

class QTextEdit;
class QHBoxLayout;

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = 0);
    ~Frame();

    void setCodeSnippet(const QString &snippet);
    void setWidget(QWidget *widget);

private:
    QTextEdit   *const _edit;
    QHBoxLayout *const _layout;
};

#endif // FRAME_H
