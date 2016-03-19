#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class About;
class FlatButtonExamples;
class IconButtonExamples;
class AppBarExamples;
class QStackedLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void showWidget(QAction *action);

private:
    void _initWidget();
    void _initMenu() const;

    QStackedLayout     *const _layout;
    FlatButtonExamples *const _flatButtonExamples;
    IconButtonExamples *const _iconButtonExamples;
    AppBarExamples     *const _appBarExamples;
    About              *const _about;
};

#endif // MAINWINDOW_H
