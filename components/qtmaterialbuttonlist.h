#ifndef QTMATERIALBUTTONLIST_H
#define QTMATERIALBUTTONLIST_H

#include "qtmaterialwidgets.h"

#include <QIcon>
#include <QWidget>

class QtMaterialButtonListPrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialButtonList : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QtMaterialButtonList(QWidget *parent = nullptr);
    ~QtMaterialButtonList() override;

    void addButton(const QString &text);
    void addButton(const QIcon &icon, const QString &text);
    void insertButton(int index, const QString &text);
    void insertButton(int index, const QIcon &icon, const QString &text);

    QString buttonText(int index) const;
    void setButtonText(int index, const QString &text);

    QIcon buttonIcon(int index) const;
    void setButtonIcon(int index, const QIcon &icon);

    int count() const;

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialButtonListPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialButtonList)
    Q_DECLARE_PRIVATE(QtMaterialButtonList)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif  // QTMATERIALBUTTONLIST_H
