#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class About;
class FlatButtonExamples;
class RaisedButtonExamples;
class IconButtonExamples;
class AppBarExamples;
class TabsExamples;
class TableExamples;
class SliderExamples;
class ToggleExamples;
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

    QStackedLayout       *const _layout;
    FlatButtonExamples   *const _flatButtonExamples;
    RaisedButtonExamples *const _raisedButtonExamples;
    IconButtonExamples   *const _iconButtonExamples;
    AppBarExamples       *const _appBarExamples;
    TabsExamples         *const _tabsExamples;
    TableExamples        *const _tableExamples;
    SliderExamples       *const _sliderExamples;
    ToggleExamples       *const _toggleExamples;
    About                *const _about;
};

#endif // MAINWINDOW_H
