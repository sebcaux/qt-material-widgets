#ifndef FLATBUTTONSETTINGSMANAGER_H
#define FLATBUTTONSETTINGSMANAGER_H

#include <QWidget>

class QLabel;
class QPushButton;
class QCheckBox;
class QtMaterialFlatButton;
class QComboBox;
class QLineEdit;

class FlatButtonSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FlatButtonSettingsEditor(QWidget *parent = 0);
    ~FlatButtonSettingsEditor();

protected:
    void paintEvent(QPaintEvent *event);

protected slots:
    void settingDisabledToggled(bool value);
    void settingCheckableToggled(bool value);
    void setButtonChecked(bool value);
    void settingShowHaloToggled(bool value);
    void settingTransparentBgToggled(bool value);
    void settingThemeColorsToggled(bool value);
    void settingIconToggled(bool value);
    void settingRoleChanged(int index);
    void settingRipplePositionChanged(int index);
    void settingOverlayStyleChanged(int index);
    void settingIconPlacementChanged(int index);
    void settingCornerRadiusChanged(int value);
    void settingBaseOpacityChanged(int value);
    void settingIconSizeChanged(int value);
    void settingFontSizeChanged(int value);
    void settingButtonTextChanged(QString text);
    void buttonToggled();
    void selectBackgroundColor();
    void selectForegroundColor();
    void selectOverlayColor();
    void selectDisabledBackgroundColor();
    void selectDisabledForegroundColor();

private:
    QtMaterialFlatButton *m_flatbutton;
    QPushButton          *m_backgroundColorValue;
    QPushButton          *m_foregroundColorValue;
    QPushButton          *m_overlayColorValue;
    QPushButton          *m_disabledBackgroundColorValue;
    QPushButton          *m_disabledForegroundColorValue;
    QComboBox            *m_overlayStyleCombo;
    QLineEdit            *m_cornerRadiusEdit;
    QLineEdit            *m_baseOpacityEdit;
    QLineEdit            *m_iconSizeEdit;
    QLineEdit            *m_fontSizeEdit;
    QCheckBox            *m_checkedCheckbox;
};

#endif // FLATBUTTONSETTINGSMANAGER_H
