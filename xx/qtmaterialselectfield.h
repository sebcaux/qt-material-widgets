#ifndef QTMATERIALSELECTFIELD_H
#define QTMATERIALSELECTFIELD_H

#include <QWidget>

class QtMaterialSelectFieldPrivate;
class QtMaterialMenuItem;

class QtMaterialSelectField : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialSelectField(QWidget *parent = 0);
    ~QtMaterialSelectField();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void addItem(const QString &text);
    QtMaterialMenuItem *itemAt(int index) const;

    void setPlaceholderText(const QString &text);
    QString placeholderText() const;

    void setUseThemeColors(bool value);
    bool useThemeColors() const;

    void setUnderlineColor(const QColor &color);
    QColor underlineColor() const;

    void setPlaceholderColor(const QColor &color);
    QColor placeholderColor() const;

    void setForegroundColor(const QColor &color);
    QColor foregroundColor() const;

    void setHighlightedColor(const QColor &color);
    QColor highlightedColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

signals:
    void itemSelected(int index);

public slots:
    void setSelectedIndex(int index);
    void clearSelection();

protected slots:
    void makeTransparent();
    void makeOpaque();
    void collapseDelayed();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<QtMaterialSelectFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialSelectField)
    Q_DECLARE_PRIVATE(QtMaterialSelectField)
};

#endif // QTMATERIALSELECTFIELD_H
