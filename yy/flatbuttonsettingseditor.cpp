#include "yy/flatbuttonsettingseditor.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QLayout>
#include <QPainter>
#include <QColorDialog>
#include <QGroupBox>
#include <QDebug>
#include "xx/qtmaterialflatbutton.h"

FlatButtonSettingsEditor::FlatButtonSettingsEditor(QWidget *parent)
    : QWidget(parent),
      m_flatbutton(new QtMaterialFlatButton("I am flat"))
{
    QCheckBox *checkbox;
    QComboBox *combo;
    QLabel *label;
    QLineEdit *edit;
    QSlider *slider;
    QVBoxLayout *vlayout;
    QHBoxLayout *groupboxlayout;
    QGridLayout *grid;
    QGroupBox *groupbox;

    vlayout = new QVBoxLayout;
    setLayout(vlayout);

    groupbox = new QGroupBox;
    groupbox->setTitle("Properties");
    groupboxlayout = new QHBoxLayout;
    groupbox->setLayout(groupboxlayout);

    QVBoxLayout *vlayout2 = new QVBoxLayout;

    groupboxlayout->addLayout(vlayout2);
    groupboxlayout->addSpacing(40);

    vlayout->addStretch(1);
    vlayout->addWidget(m_flatbutton);
    m_flatbutton->setFixedWidth(400);
    vlayout->setAlignment(m_flatbutton, Qt::AlignCenter);

    connect(m_flatbutton, SIGNAL(toggled(bool)), this, SLOT(buttonToggled()));

    vlayout->addSpacing(40);

    vlayout->addWidget(groupbox);

    //

    checkbox = new QCheckBox;
    checkbox->setText("Disabled");
    vlayout2->addWidget(checkbox);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(settingDisabledToggled(bool)));

    //

    checkbox = new QCheckBox;
    checkbox->setText("Checkable");
    vlayout2->addWidget(checkbox);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(settingCheckableToggled(bool)));
    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(buttonToggled()));

    //

    m_checkedCheckbox = new QCheckBox;
    m_checkedCheckbox->setText("Checked");
    m_checkedCheckbox->setDisabled(true);
    vlayout2->addWidget(m_checkedCheckbox);

    connect(m_checkedCheckbox, SIGNAL(clicked(bool)), this, SLOT(setButtonChecked(bool)));

    //

    checkbox = new QCheckBox;
    checkbox->setText("Show halo");
    checkbox->setChecked(true);
    vlayout2->addWidget(checkbox);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(settingShowHaloToggled(bool)));

    //

    checkbox = new QCheckBox;
    checkbox->setText("Transparent background");
    checkbox->setChecked(true);
    vlayout2->addWidget(checkbox);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(settingTransparentBgToggled(bool)));

    //

    checkbox = new QCheckBox;
    checkbox->setText("Icon");
    vlayout2->addWidget(checkbox);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(settingIconToggled(bool)));

    //

    vlayout2->addStretch();

    //

    grid = new QGridLayout;

    label = new QLabel("Button role");

    combo = new QComboBox;
    combo->addItem("Default");
    combo->addItem("Primary");
    combo->addItem("Secondary");

    grid->addWidget(label, 0, 0);
    grid->addWidget(combo, 0, 2);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(settingRoleChanged(int)));

    //

    label = new QLabel("Ripple style");

    combo = new QComboBox;
    combo->addItem("Positioned");
    combo->addItem("Centered");

    grid->addWidget(label, 1, 0);
    grid->addWidget(combo, 1, 2);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(settingRipplePositionChanged(int)));

    //

    label = new QLabel("Hover style");

    m_overlayStyleCombo = new QComboBox;
    m_overlayStyleCombo->addItem("No overlay");
    m_overlayStyleCombo->addItem("Tinted");
    m_overlayStyleCombo->addItem("Gray");
    m_overlayStyleCombo->setCurrentIndex(0);

    grid->addWidget(label, 2, 0);
    grid->addWidget(m_overlayStyleCombo, 2, 2);

    connect(m_overlayStyleCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(settingOverlayStyleChanged(int)));

    //

    label = new QLabel("Icon placement");

    combo = new QComboBox;
    combo->addItem("Left");
    combo->addItem("Right");

    grid->addWidget(label, 3, 0);
    grid->addWidget(combo, 3, 2);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(settingIconPlacementChanged(int)));

    //

    label = new QLabel("Corner radius");
    m_cornerRadiusEdit = new QLineEdit;
    m_cornerRadiusEdit->setReadOnly(true);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 220);
    slider->setSliderPosition(m_flatbutton->cornerRadius());
    m_cornerRadiusEdit->setText("3");

    grid->setColumnStretch(2, 3);

    grid->addWidget(label, 4, 0);
    grid->addWidget(m_cornerRadiusEdit, 4, 1);
    grid->addWidget(slider, 4, 2);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(settingCornerRadiusChanged(int)));

    //

    label = new QLabel("Overlay opacity");
    m_baseOpacityEdit = new QLineEdit;
    m_baseOpacityEdit->setReadOnly(true);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setSliderPosition(m_flatbutton->baseOpacity()*100);

    QString s;
    s.setNum(m_flatbutton->baseOpacity());
    m_baseOpacityEdit->setText(s);

    grid->addWidget(label, 5, 0);
    grid->addWidget(m_baseOpacityEdit, 5, 1);
    grid->addWidget(slider, 5, 2);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(settingBaseOpacityChanged(int)));

    //

    label = new QLabel("Icon size");
    m_iconSizeEdit = new QLineEdit;
    m_iconSizeEdit->setReadOnly(true);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(4, 148);
    slider->setSliderPosition(m_flatbutton->iconSize().width());
    m_iconSizeEdit->setText(QString::number(slider->value()));

    grid->addWidget(label, 6, 0);
    grid->addWidget(m_iconSizeEdit, 6, 1);
    grid->addWidget(slider, 6, 2);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(settingIconSizeChanged(int)));

    //

    label = new QLabel("Font size");
    m_fontSizeEdit = new QLineEdit;
    m_fontSizeEdit->setReadOnly(true);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(10, 80);
    slider->setSliderPosition(m_flatbutton->fontSize()*2);

    s.setNum(m_flatbutton->fontSize());
    m_fontSizeEdit->setText(s);

    grid->addWidget(label, 7, 0);
    grid->addWidget(m_fontSizeEdit, 7, 1);
    grid->addWidget(slider, 7, 2);

    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(settingFontSizeChanged(int)));

    //

    label = new QLabel("Button text");

    edit = new QLineEdit("I am flat");

    grid->addWidget(label, 8, 0);
    grid->addWidget(edit, 8, 1, 1, 2);

    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(settingButtonTextChanged(QString)));

    //

    groupboxlayout->addLayout(grid);
    grid = new QGridLayout;

    groupbox = new QGroupBox;
    groupbox->setTitle("Colors");
    groupbox->setLayout(grid);

    vlayout->addWidget(groupbox);

    //

    QCheckBox *themeColorsCheckbox;

    themeColorsCheckbox = new QCheckBox;
    themeColorsCheckbox->setText("Use theme colors");
    themeColorsCheckbox->setChecked(true);
    grid->addWidget(themeColorsCheckbox, 9, 0, 1, 2);

    connect(themeColorsCheckbox, SIGNAL(clicked(bool)), this, SLOT(settingThemeColorsToggled(bool)));

    //

    label = new QLabel("Background color");
    m_backgroundColorValue = new QPushButton("Click to select");
    m_backgroundColorValue->setFlat(true);

    label->setDisabled(true);
    m_backgroundColorValue->setDisabled(true);

    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), label, SLOT(setDisabled(bool)));
    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), m_backgroundColorValue, SLOT(setDisabled(bool)));

    connect(m_backgroundColorValue, SIGNAL(clicked(bool)), this, SLOT(selectBackgroundColor()));

    grid->addWidget(label, 10, 0);
    grid->addWidget(m_backgroundColorValue, 10, 1);

    //

    label = new QLabel("Foreground color");
    m_foregroundColorValue = new QPushButton("Click to select");
    m_foregroundColorValue->setFlat(true);

    label->setDisabled(true);
    m_foregroundColorValue->setDisabled(true);

    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), label, SLOT(setDisabled(bool)));
    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), m_foregroundColorValue, SLOT(setDisabled(bool)));

    connect(m_foregroundColorValue, SIGNAL(clicked(bool)), this, SLOT(selectForegroundColor()));

    grid->addWidget(label, 11, 0);
    grid->addWidget(m_foregroundColorValue, 11, 1);

    //

    label = new QLabel("Overlay color");
    m_overlayColorValue = new QPushButton("Click to select");
    m_overlayColorValue->setFlat(true);

    label->setDisabled(true);
    m_overlayColorValue->setDisabled(true);

    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), label, SLOT(setDisabled(bool)));
    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), m_overlayColorValue, SLOT(setDisabled(bool)));

    connect(m_overlayColorValue, SIGNAL(clicked(bool)), this, SLOT(selectOverlayColor()));

    grid->addWidget(label, 12, 0);
    grid->addWidget(m_overlayColorValue, 12, 1);

    //

    label = new QLabel("Disabled background color");
    m_disabledBackgroundColorValue = new QPushButton("Click to select");
    m_disabledBackgroundColorValue->setFlat(true);

    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), label, SLOT(setDisabled(bool)));
    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), m_disabledBackgroundColorValue, SLOT(setDisabled(bool)));

    label->setDisabled(true);
    m_disabledBackgroundColorValue->setDisabled(true);

    connect(m_disabledBackgroundColorValue, SIGNAL(clicked(bool)), this, SLOT(selectDisabledBackgroundColor()));

    grid->addWidget(label, 13, 0);
    grid->addWidget(m_disabledBackgroundColorValue, 13, 1);

    //

    label = new QLabel("Disabled foreground color");
    m_disabledForegroundColorValue = new QPushButton("Click to select");
    m_disabledForegroundColorValue->setFlat(true);

    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), label, SLOT(setDisabled(bool)));
    connect(themeColorsCheckbox, SIGNAL(toggled(bool)), m_disabledForegroundColorValue, SLOT(setDisabled(bool)));

    connect(m_disabledForegroundColorValue, SIGNAL(clicked(bool)), this, SLOT(selectDisabledForegroundColor()));

    label->setDisabled(true);
    m_disabledForegroundColorValue->setDisabled(true);

    grid->addWidget(label, 14, 0);
    grid->addWidget(m_disabledForegroundColorValue, 14, 1);

    //

    vlayout->addStretch(1);
}

FlatButtonSettingsEditor::~FlatButtonSettingsEditor()
{
}

void FlatButtonSettingsEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect r(m_flatbutton->geometry());

    painter.fillRect(r.adjusted(-160, -60, 160, 60), Qt::white);

    QWidget::paintEvent(event);
}

void FlatButtonSettingsEditor::settingDisabledToggled(bool value)
{
    m_flatbutton->setDisabled(value);
}

void FlatButtonSettingsEditor::settingCheckableToggled(bool value)
{
    m_flatbutton->setCheckable(value);
    m_checkedCheckbox->setEnabled(value);
    m_checkedCheckbox->setChecked(false);
}

void FlatButtonSettingsEditor::setButtonChecked(bool value)
{
    m_flatbutton->setChecked(value);
}

void FlatButtonSettingsEditor::settingShowHaloToggled(bool value)
{
    m_flatbutton->setHaloVisible(value);
}

void FlatButtonSettingsEditor::settingTransparentBgToggled(bool value)
{
    m_flatbutton->setBackgroundMode(value ? Qt::TransparentMode : Qt::OpaqueMode);
}

void FlatButtonSettingsEditor::settingThemeColorsToggled(bool value)
{
    m_flatbutton->setUseThemeColors(value);
}

void FlatButtonSettingsEditor::settingIconToggled(bool value)
{
    if (value) {
        m_flatbutton->setIcon(QIcon("../qt-material-widgets/ic_star_black_24px.svg"));
    } else {
        m_flatbutton->setIcon(QIcon());
    }
}

void FlatButtonSettingsEditor::settingRoleChanged(int index)
{
    switch (index)
    {
    case 0:
        m_flatbutton->setRole(XXMaterial::Default);
        break;
    case 1:
        m_flatbutton->setRole(XXMaterial::Primary);
        break;
    case 2:
        m_flatbutton->setRole(XXMaterial::Secondary);
        break;
    default:
        break;
    }
}

void FlatButtonSettingsEditor::settingRipplePositionChanged(int index)
{
    switch (index)
    {
    case 0:
        m_flatbutton->setRippleStyle(XXMaterial::PositionedRipple);
        break;
    case 1:
        m_flatbutton->setRippleStyle(XXMaterial::CenteredRipple);
        break;
    default:
        break;
    }
}

void FlatButtonSettingsEditor::settingOverlayStyleChanged(int index)
{
    switch (index)
    {
    case 0:
        m_flatbutton->setOverlayStyle(XXMaterial::NoOverlay);
        break;
    case 1:
        m_flatbutton->setOverlayStyle(XXMaterial::TintedOverlay);
        break;
    case 2:
        m_flatbutton->setOverlayStyle(XXMaterial::GrayOverlay);
        break;
    default:
        break;
    }
}

void FlatButtonSettingsEditor::settingIconPlacementChanged(int index)
{
    switch (index)
    {
    case 0:
        m_flatbutton->setIconPlacement(XXMaterial::LeftIcon);
        break;
    case 1:
        m_flatbutton->setIconPlacement(XXMaterial::RightIcon);
        break;
    default:
        break;
    }
}

void FlatButtonSettingsEditor::settingCornerRadiusChanged(int value)
{
    m_flatbutton->setCornerRadius(value);
    m_cornerRadiusEdit->setText(QString::number(value));
}

void FlatButtonSettingsEditor::settingBaseOpacityChanged(int value)
{
    const qreal r = static_cast<qreal>(value)/100;
    m_flatbutton->setBaseOpacity(r);

    QString s;
    s.setNum(r);
    m_baseOpacityEdit->setText(s);
}

void FlatButtonSettingsEditor::settingIconSizeChanged(int value)
{
    m_flatbutton->setIconSize(QSize(value, value));
    m_iconSizeEdit->setText(QString::number(value));
}

void FlatButtonSettingsEditor::settingFontSizeChanged(int value)
{
    const qreal r = static_cast<qreal>(value)/2;
    m_flatbutton->setFontSize(r);

    QString s;
    s.setNum(r);
    m_fontSizeEdit->setText(s);
}

void FlatButtonSettingsEditor::settingButtonTextChanged(QString text)
{
    m_flatbutton->setText(text);
}

void FlatButtonSettingsEditor::buttonToggled()
{
    m_checkedCheckbox->setChecked(m_flatbutton->isChecked());
}

void FlatButtonSettingsEditor::selectBackgroundColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_flatbutton->setBackgroundColor(color);
        m_backgroundColorValue->setText(color.name(QColor::HexRgb));
    }
}

void FlatButtonSettingsEditor::selectForegroundColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_flatbutton->setForegroundColor(color);
        m_foregroundColorValue->setText(color.name(QColor::HexRgb));
    }
}

void FlatButtonSettingsEditor::selectOverlayColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_flatbutton->setOverlayColor(color);
        m_overlayColorValue->setText(color.name(QColor::HexRgb));
        m_overlayStyleCombo->setCurrentIndex(1);
    }
}

void FlatButtonSettingsEditor::selectDisabledBackgroundColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_flatbutton->setDisabledBackgroundColor(color);
        m_disabledBackgroundColorValue->setText(color.name(QColor::HexRgb));
    }
}

void FlatButtonSettingsEditor::selectDisabledForegroundColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        m_flatbutton->setDisabledForegroundColor(color);
        m_disabledForegroundColorValue->setText(color.name(QColor::HexRgb));
    }
}
