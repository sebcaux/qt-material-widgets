#include "autocompletesettingseditor.h"

#include <QDebug>
#include <QVBoxLayout>

#include <qtmaterialautocomplete.h>

AutoCompleteSettingsEditor::AutoCompleteSettingsEditor(QWidget *parent)
    : SettingsEditor(parent),
      m_autocomplete(new QtMaterialAutoComplete)
{
    //_canvas->setMinimumHeight(900);

    QVBoxLayout *layout = new QVBoxLayout;
    _canvas->setLayout(layout);

    QStringList states = {"Alabama",        "Alaska",
                          "American Samoa", "Arizona",
                          "Arkansas",       "California",
                          "Colorado",       "Connecticut",
                          "Delaware",       "District of Columbia",
                          "Florida",        "Georgia",
                          "Guam",           "Hawaii",
                          "Idaho",          "Illinois",
                          "Indiana",        "Iowa",
                          "Kansas",         "Kentucky",
                          "Louisiana",      "Maine",
                          "Maryland",       "Massachusetts",
                          "Michigan",       "Minnesota",
                          "Mississippi",    "Missouri",
                          "Montana",        "Nebraska",
                          "Nevada",         "New Hampshire",
                          "New Jersey",     "New Mexico",
                          "New York",       "North Carolina",
                          "North Dakota",   "Northern Marianas Islands",
                          "Ohio",           "Oklahoma",
                          "Oregon",         "Pennsylvania",
                          "Puerto Rico",    "Rhode Island",
                          "South Carolina", "South Dakota",
                          "Tennessee",      "Texas",
                          "Utah",           "Vermont",
                          "Virginia",       "Virgin Islands",
                          "Washington",     "West Virginia",
                          "Wisconsin",      "Wyoming"};

    m_autocomplete->setDataSource(states);

    layout->addWidget(m_autocomplete);
    layout->addSpacing(600);
    layout->setAlignment(m_autocomplete, Qt::AlignCenter);

    setupForm();
}

AutoCompleteSettingsEditor::~AutoCompleteSettingsEditor()
{
}

void AutoCompleteSettingsEditor::setupForm()
{
}

void AutoCompleteSettingsEditor::updateWidget()
{
}

void AutoCompleteSettingsEditor::selectColor()
{
}
