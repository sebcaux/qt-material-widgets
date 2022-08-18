#ifndef QTMATERIALTEXTFIELD_H
#define QTMATERIALTEXTFIELD_H

#include <QLineEdit>

#include <QColor>

class QtMaterialTextFieldPrivate;

class QtMaterialTextField : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(bool labelVisible READ labelVisible WRITE setLabelVisible)
    Q_PROPERTY(qreal labelFontSize READ labelFontSize WRITE setLabelFontSize)
    Q_PROPERTY(QString labelText READ labelText WRITE setLabelText)
    Q_PROPERTY(bool inputLineVisible READ inputLineVisible WRITE setInputLineVisible)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor)
    Q_PROPERTY(QColor inkColor READ inkColor WRITE setInkColor)
    Q_PROPERTY(QColor inputLineColor READ inputLineColor WRITE setInputLineColor)

public:
    explicit QtMaterialTextField(QWidget *parent = nullptr);
    ~QtMaterialTextField() override;

    bool labelVisible() const;
    void setLabelVisible(bool value);

    qreal labelFontSize() const;
    void setLabelFontSize(qreal size);

    QString labelText() const;
    void setLabelText(const QString &label);

    bool inputLineVisible() const;
    void setInputLineVisible(bool value);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor textColor() const;
    void setTextColor(const QColor &color);
    QColor labelColor() const;
    void setLabelColor(const QColor &color);
    QColor inkColor() const;
    void setInkColor(const QColor &color);
    QColor inputLineColor() const;
    void setInputLineColor(const QColor &color);

protected:
    QtMaterialTextField(QtMaterialTextFieldPrivate &d, QWidget *parent = nullptr);

    const QScopedPointer<QtMaterialTextFieldPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialTextField)
    Q_DECLARE_PRIVATE(QtMaterialTextField)

    // QWidget interface
protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALTEXTFIELD_H
