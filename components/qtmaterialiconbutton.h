#ifndef QTMATERIALICONBUTTON_H
#define QTMATERIALICONBUTTON_H

#include <QAbstractButton>

class QtMaterialIconButtonPrivate;

class QtMaterialIconButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit QtMaterialIconButton(const QIcon &icon = QIcon(), QWidget *parent = nullptr);
    ~QtMaterialIconButton() override;

    bool useThemeColors() const;
    void setUseThemeColors(bool value);

    QColor color() const;
    void setColor(const QColor &color);

    QColor disabledColor() const;
    void setDisabledColor(const QColor &color);

protected:
    QtMaterialIconButton(QtMaterialIconButtonPrivate &d, QWidget *parent = nullptr);

    const QScopedPointer<QtMaterialIconButtonPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialIconButton)
    Q_DECLARE_PRIVATE(QtMaterialIconButton)

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALICONBUTTON_H
