#ifndef QTMATERIALBUTTONLISTPRIVATE_H
#define QTMATERIALBUTTONLISTPRIVATE_H

#include <QColor>
#include <QIcon>
#include <QVBoxLayout>

class QtMaterialButtonList;
class QtMaterialFlatButton;

class QtMaterialButtonListPrivate
{
    Q_DISABLE_COPY(QtMaterialButtonListPrivate)
    Q_DECLARE_PUBLIC(QtMaterialButtonList)

public:
    QtMaterialButtonListPrivate(QtMaterialButtonList *q);
    ~QtMaterialButtonListPrivate();

    void init();

    QtMaterialFlatButton *createButton(const QString &text, const QIcon &icon = QIcon());

    QtMaterialButtonList *const q_ptr;

    QList<QtMaterialFlatButton *> buttons;

    bool useThemeColors;
    QColor foregroundColor;
    QColor backgroundColor;
};

#endif  // QTMATERIALBUTTONLISTPRIVATE_H
