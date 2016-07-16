#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MenuPlus;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

protected slots:
    void slider1Changed(int value);
    void slider2Changed(int value);
    void slider3Changed(int value);
    void slider4Changed(int value);
    void button1Pressed();
    void button2Pressed();
    void button3Pressed();
    void button4Pressed();

private:
    void _initMenu() const;

    MenuPlus *_menu;
};

/*
class About;
class FlatButtonExamples;
class RaisedButtonExamples;
class IconButtonExamples;
class AppBarExamples;
class TabsExamples;
class TableExamples;
class SliderExamples;
class ToggleExamples;
class RadioButtonExamples;
class CheckboxExamples;
class TextFieldExamples;
class ListExamples;
class AvatarExamples;
class MenuExamples;
class IconMenuExamples;
class QStackedLayout;
class Snackbar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void showWidget(QAction *action);
    void addMsg();
    void addInstantMsg();

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
    RadioButtonExamples  *const _radioButtonExamples;
    CheckboxExamples     *const _checkboxExamples;
    TextFieldExamples    *const _textFieldExamples;
    ListExamples         *const _listExamples;
    AvatarExamples       *const _avatarExamples;
    MenuExamples         *const _menuExamples;
    IconMenuExamples     *const _iconMenuExamples;
    About                *const _about;
    Snackbar *snackbar;
};

*/

#endif // MAINWINDOW_H
