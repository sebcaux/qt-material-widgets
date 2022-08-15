#ifndef QTMATERIALICONBUTTON_H
#define QTMATERIALICONBUTTON_H

#include <QAbstractButton>

class QtMaterialIconButtonPrivate;

class QtMaterialIconButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit QtMaterialIconButton(const QIcon &icon, QWidget *parent = nullptr);
    ~QtMaterialIconButton() override;

    QSize sizeHint() const override;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    QtMaterialIconButton(QtMaterialIconButtonPrivate &d, QWidget *parent = nullptr);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<QtMaterialIconButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialIconButton)
    Q_DECLARE_PRIVATE(QtMaterialIconButton)
};

#endif  // QTMATERIALICONBUTTON_H
