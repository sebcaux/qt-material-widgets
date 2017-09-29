#ifndef CHECKABLE_H
#define CHECKABLE_H

#include <QAbstractButton>

class CheckablePrivate;

/*
 * @TODO: add option for showing label on the left of icon
 */

class Checkable : public QAbstractButton
{
    Q_OBJECT

public:
    explicit Checkable(QWidget *parent = 0);
    virtual ~Checkable();

    void setUseThemeColors(bool state);
    bool useThemeColors() const;

    void setCheckedColor(const QColor &color);
    QColor checkedColor() const;

    void setUncheckedColor(const QColor &color);
    QColor uncheckedColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setCheckedIcon(const QIcon &icon);
    QIcon checkedIcon() const;

    void setUncheckedIcon(const QIcon &icon);
    QIcon uncheckedIcon() const;

    QSize sizeHint() const;

protected:
    Checkable(CheckablePrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    virtual void assignProperties();

    const QScopedPointer<CheckablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Checkable)
    Q_DECLARE_PRIVATE(Checkable)
};

#endif // CHECKABLE_H
