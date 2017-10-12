#include "qtmaterialautocomplete.h"
#include "qtmaterialautocomplete_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include "qtmaterialflatbutton.h"

/*!
 *  \class QtMaterialAutoCompletePrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q)
    : QtMaterialTextFieldPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::~QtMaterialAutoCompletePrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAutoCompletePrivate::init()
{
    Q_Q(QtMaterialAutoComplete);

    menu       = new QWidget;
    menuLayout = new QVBoxLayout;
    maxWidth   = 0;

    menu->setParent(q->parentWidget());

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    menu->setGraphicsEffect(effect);
    menu->setLayout(menuLayout);
    menu->setVisible(false);

    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);

    QObject::connect(q, SIGNAL(textChanged(QString)), q, SLOT(updateResults(QString)));

    //

    QStringList states =
      { "Alabama"
      , "Alaska"
      , "American Samoa"
      , "Arizona"
      , "Arkansas"
      , "California"
      , "Colorado"
      , "Connecticut"
      , "Delaware"
      , "District of Columbia"
      , "Florida"
      , "Georgia"
      , "Guam"
      , "Hawaii"
      , "Idaho"
      , "Illinois"
      , "Indiana"
      , "Iowa"
      , "Kansas"
      , "Kentucky"
      , "Louisiana"
      , "Maine"
      , "Maryland"
      , "Massachusetts"
      , "Michigan"
      , "Minnesota"
      , "Mississippi"
      , "Missouri"
      , "Montana"
      , "Nebraska"
      , "Nevada"
      , "New Hampshire"
      , "New Jersey"
      , "New Mexico"
      , "New York"
      , "North Carolina"
      , "North Dakota"
      , "Northern Marianas Islands"
      , "Ohio"
      , "Oklahoma"
      , "Oregon"
      , "Pennsylvania"
      , "Puerto Rico"
      , "Rhode Island"
      , "South Carolina"
      , "South Dakota"
      , "Tennessee"
      , "Texas"
      , "Utah"
      , "Vermont"
      , "Virginia"
      , "Virgin Islands"
      , "Washington"
      , "West Virginia"
      , "Wisconsin"
      , "Wyoming"
    };
    foreach (QString state, states) {
        dataSource.push_back(state);
    }
}

/*!
 *  \class QtMaterialAutoComplete
 */

QtMaterialAutoComplete::QtMaterialAutoComplete(QWidget *parent)
    : QtMaterialTextField(*new QtMaterialAutoCompletePrivate(this), parent)
{
    d_func()->init();
}

QtMaterialAutoComplete::~QtMaterialAutoComplete()
{
}

void QtMaterialAutoComplete::updateResults(QString text)
{
    Q_D(QtMaterialAutoComplete);

    QStringList results;
    QString trimmed(text.trimmed());

    if (!trimmed.isEmpty()) {
        QString lookup(trimmed.toLower());
        QStringList::iterator i;
        for (i = d->dataSource.begin(); i != d->dataSource.end(); ++i) {
            if (i->toLower().startsWith(lookup)) {
                results.push_back(*i);
            }
        }
    }

    const int diff = results.length() - d->menuLayout->count();
    QFont font("Roboto", 12, QFont::Normal);

    if (diff > 0) {
        for (int c = 0; c < diff; c++) {
            QtMaterialFlatButton *item = new QtMaterialFlatButton;
            item->setFont(font);
            item->setTextAlignment(Qt::AlignLeft);
            item->setCornerRadius(0);
            item->setHaloVisible(false);
            item->setFixedHeight(50);
            d->menuLayout->addWidget(item);
        }
    } else if (diff < 0) {
        for (int c = 0; c < -diff; c++) {
            QWidget *widget = d->menuLayout->itemAt(0)->widget();
            if (widget) {
                d->menuLayout->removeWidget(widget);
                delete widget;
            }
        }
    }

    QFontMetrics *fm = new QFontMetrics(font);
    d->maxWidth = 0;

    for (int i = 0; i < results.count(); ++i) {
        QWidget *widget = d->menuLayout->itemAt(i)->widget();
        QtMaterialFlatButton *item;
        if ((item = static_cast<QtMaterialFlatButton *>(widget))) {
            QString text = results.at(i);
            QRect rect = fm->boundingRect(text);
            d->maxWidth = qMax(d->maxWidth, rect.width());
            item->setText(text);
        }
    }

    if (!results.count()) {
        d->menu->hide();
    } else if (d->menu->isHidden()) {
        d->menu->show();
    }

    d->menu->setFixedHeight(results.length()*50);
    d->menu->setFixedWidth(qMax(d->maxWidth + 24, width()));
    d->menu->update();
}

bool QtMaterialAutoComplete::QtMaterialAutoComplete::event(QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize: {
        d->menu->move(pos() + QPoint(0, height() + 6));
        break;
    }
    case QEvent::ParentChange: {
        QWidget *widget = static_cast<QWidget *>(parent());
        if (widget) {
            d->menu->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QtMaterialTextField::event(event);
}
