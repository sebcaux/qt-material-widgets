#ifndef QTMATERIALIZERLABEL_H
#define QTMATERIALIZERLABEL_H

#include <QObject>

class QLabel;

class QtMaterializerLabel : public QObject
{
    Q_OBJECT
public:
    explicit QtMaterializerLabel(QLabel *parent = nullptr);

protected:
    QLabel *_label;

    void updateFont();
    void updateColors();

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif  // QTMATERIALIZERLABEL_H
