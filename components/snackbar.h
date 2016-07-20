#ifndef SNACKBAR_H
#define SNACKBAR_H

#include <QWidget>

class SnackbarPrivate;
class SnackbarStateMachine;

/*
 * @TODO: Allow dismiss on blur
 */

class Snackbar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int autoHideDuration WRITE setAutoHideDuration READ autoHideDuration)

public:
    explicit Snackbar(QWidget *parent = 0);
    ~Snackbar();

    void setAutoHideDuration(int duration);
    int autoHideDuration() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setTextColor(const QColor &color);
    QColor textColor() const;

    void setFontSize(qreal size);
    qreal fontSize() const;

    void setBoxWidth(int width);
    int boxWidth() const;

public slots:
    void addMessage(const QString &message, bool instant = false);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void dequeue();

    const QScopedPointer<SnackbarPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Snackbar)
    Q_DECLARE_PRIVATE(Snackbar)

    friend class SnackbarStateMachine;
};

#endif // SNACKBAR_H
