#ifndef QTMATERIALLABEL_H
#define QTMATERIALLABEL_H

#include <QLabel>

#include "lib/qtmaterialtheme.h"

class QtMaterialLabelPrivate;

class QtMaterialLabel : public QLabel
{
    Q_OBJECT

public:
    explicit QtMaterialLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit QtMaterialLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QtMaterialLabel(const QString &text, Material::FontType fontType, QWidget *parent = nullptr);
    ~QtMaterialLabel() override;

    Material::FontType fontType() const;
    void setFontType(Material::FontType fontType);

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor color() const;
    void setColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialLabelPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialLabel)
    Q_DECLARE_PRIVATE(QtMaterialLabel)

    // QWidget interface
protected:
    bool event(QEvent *event) override;
};

#endif  // QTMATERIALLABEL_H
