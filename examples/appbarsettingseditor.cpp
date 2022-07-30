#include "appbarsettingseditor.h"

#include <QColorDialog>
#include <QVBoxLayout>

#include <lib/qtmaterialtheme.h>
#include <qtmaterialappbar.h>
#include <qtmaterialiconbutton.h>

AppBarSettingsEditor::AppBarSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      ui(new Ui::AppBarSettingsForm),
      m_appBar(new QtMaterialAppBar)
{
    ui->setupUi(_settingsWidget);

    QLabel *label = new QLabel("Inbox");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setForegroundRole(QPalette::Foreground);
    label->setContentsMargins(6, 0, 0, 0);

    QPalette palette = label->palette();
    palette.setColor(label->foregroundRole(), Qt::white);
    label->setPalette(palette);

    label->setFont(QFont("Roboto", 18, QFont::Normal));

    QtMaterialIconButton *button = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    button->setIconSize(QSize(24, 24));
    m_appBar->appBarLayout()->addWidget(button);
    m_appBar->appBarLayout()->addWidget(label);
    m_appBar->appBarLayout()->addStretch(1);
    button->setColor(Qt::white);
    button->setFixedWidth(42);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);
    //_canvas->setMaximumHeight(300);
    layout->addWidget(m_appBar);
    layout->addStretch(1);

    setupForm();

    connect(ui->useThemeColorsCheckBox, &QAbstractButton::toggled, this, &AppBarSettingsEditor::updateWidget);
    connect(ui->backgroundColorToolButton, &QAbstractButton::pressed, this, &AppBarSettingsEditor::selectColor);
}

AppBarSettingsEditor::~AppBarSettingsEditor()
{
    delete ui;
}

void AppBarSettingsEditor::setupForm()
{
    ui->useThemeColorsCheckBox->setChecked(m_appBar->useThemeColors());
}

void AppBarSettingsEditor::updateWidget()
{
    m_appBar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void AppBarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec() != 0)
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("backgroundColorToolButton" == senderName)
        {
            m_appBar->setBackgroundColor(color);
            ui->backgroundColorLineEdit->setText(color.name(QColor::HexRgb));
        }
    }
    setupForm();
}
