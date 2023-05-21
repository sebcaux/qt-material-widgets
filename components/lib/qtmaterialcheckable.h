#ifndef QTMATERIALCHECKABLE_H
#define QTMATERIALCHECKABLE_H

#include "../qtmaterialwidgets.h"

#include <QAbstractButton>

class QtMaterialCheckablePrivate;

class QTMATERIALWIDGETS_EXPORT QtMaterialCheckable : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(QtMaterialCheckable::LabelPosition labelPosition READ labelPosition WRITE setLabelPosition)
    Q_PROPERTY(QIcon checkedIcon READ checkedIcon WRITE setCheckedIcon)
    Q_PROPERTY(QIcon uncheckedIcon READ uncheckedIcon WRITE setUncheckedIcon)
    Q_PROPERTY(QColor checkedColor READ checkedColor WRITE setCheckedColor)
    Q_PROPERTY(QColor uncheckedColor READ uncheckedColor WRITE setUncheckedColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor disabledColor READ disabledColor WRITE setDisabledColor)

public:
    enum LabelPosition
    {
        LabelPositionLeft,
        LabelPositionRight,
    };

    explicit QtMaterialCheckable(QWidget *parent = nullptr);
    ~QtMaterialCheckable() override;

    LabelPosition labelPosition() const;
    void setLabelPosition(LabelPosition placement);

    QIcon checkedIcon() const;
    void setCheckedIcon(const QIcon &icon);
    QIcon uncheckedIcon() const;
    void setUncheckedIcon(const QIcon &icon);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor checkedColor() const;
    void setCheckedColor(const QColor &color);
    QColor uncheckedColor() const;
    void setUncheckedColor(const QColor &color);
    QColor textColor() const;
    void setTextColor(const QColor &color);
    QColor disabledColor() const;
    void setDisabledColor(const QColor &color);

protected:
    QtMaterialCheckable(QtMaterialCheckablePrivate &d, QWidget *parent = nullptr);

    virtual void setupProperties();

    const QScopedPointer<QtMaterialCheckablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCheckable)
    Q_DECLARE_PRIVATE(QtMaterialCheckable)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALCHECKABLE_H
