#ifndef QTMATERIALSELECTFIELD_P_H
#define QTMATERIALSELECTFIELD_P_H

#include <QtGlobal>
#include <QString>
#include <QColor>

class QtMaterialSelectField;
class QtMaterialOverlayWidget;
class QtMaterialCollapsibleMenu;

class QtMaterialSelectFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialSelectFieldPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSelectField)

public:
    QtMaterialSelectFieldPrivate(QtMaterialSelectField *q);
    ~QtMaterialSelectFieldPrivate();

    void init();

    QtMaterialSelectField     *const q_ptr;
    QtMaterialOverlayWidget   *menuOverlay;
    QtMaterialCollapsibleMenu *menu;
    QString                    selectedText;
    QString                    placeholderText;
    QColor                     underlineColor;
    QColor                     placeholderColor;
    QColor                     foregroundColor;
    QColor                     highlightedColor;
    QColor                     disabledColor;
    int                        selectedIndex;
    bool                       useThemeColors;
};

#endif // QTMATERIALSELECTFIELD_P_H
