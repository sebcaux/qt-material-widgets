#ifndef QTMATERIALCHECKABLE_H
#define QTMATERIALCHECKABLE_H

#include <QtWidgets/QAbstractButton>

class QtMaterialCheckablePrivate;

class QtMaterialCheckable : public QAbstractButton
{
    Q_OBJECT

public:
    enum LabelPosition
    {
        LabelPositionLeft,
        LabelPositionRight,
    };

    explicit QtMaterialCheckable(QWidget *parent = nullptr);
    ~QtMaterialCheckable() override;

    void setLabelPosition(LabelPosition placement);
    LabelPosition labelPosition() const;

    void setUseThemeColors(bool value);
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

    QSize sizeHint() const override;

protected:
    QtMaterialCheckable(QtMaterialCheckablePrivate &d, QWidget *parent = nullptr);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void setupProperties();

    const QScopedPointer<QtMaterialCheckablePrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialCheckable)
    Q_DECLARE_PRIVATE(QtMaterialCheckable)
};

#endif  // QTMATERIALCHECKABLE_H
