#ifndef QTMATERIALPAPER_H
#define QTMATERIALPAPER_H

#include <QWidget>

class QtMaterialPaperPrivate;

class QtMaterialPaper : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialPaper(QWidget *parent = nullptr);
    ~QtMaterialPaper() override;

    bool useThemeColors() const;
    void setUseThemeColors(bool value);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    const QScopedPointer<QtMaterialPaperPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialPaper)
    Q_DECLARE_PRIVATE(QtMaterialPaper)

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif  // QTMATERIALPAPER_H
