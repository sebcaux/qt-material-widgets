#include "autocompletesettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <qtmaterialautocomplete.h>

#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include "qtmaterialflatbutton.h"
#include <QtWidgets/QGraphicsDropShadowEffect>

AutoCompleteSettingsEditor::AutoCompleteSettingsEditor(QWidget *parent)
    : QWidget(parent),
      //ui(new Ui::AutoCompleteSettingsForm),
      m_autocomplete(new QtMaterialAutoComplete)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    //ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);


    /*
    Xyz *xyz = new Xyz(m_autocomplete);
    xyz->setParent(canvas);
    */


    //Menu *menu = new Menu;
    //menu->setParent(xyz);

    //menu->move(220, 140);
    //menu->move(pos());

    //qDebug() << menu->parentWidget()->mapFromGlobal(QPoint(0, 0));
    //qDebug() << menu->mapToGlobal(QPoint(0, 0));

    layout->addWidget(m_autocomplete);
    layout->setAlignment(m_autocomplete, Qt::AlignCenter);

    setupForm();

    //m_autocomplete->installEventFilter(xyz);
}

AutoCompleteSettingsEditor::~AutoCompleteSettingsEditor()
{
    //delete ui;
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

// ----

Xyz::Xyz(QtMaterialAutoComplete *input, QWidget *parent)
    : QtMaterialOverlayWidget(parent),
      m_input(input),
      m_menu(new Menu)
{
    m_menu->setParent(this);
}

Xyz::~Xyz()
{
}

bool Xyz::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize: {
        QtMaterialAutoComplete *widget = static_cast<QtMaterialAutoComplete *>(obj);
        if (widget) {
            m_menu->move(widget->pos() + QPoint(0, m_input->height() + 6));
            m_menu->setFixedWidth(m_input->width());
        }
        break;
    }
    case QEvent::ParentChange:
        qDebug() << "Parent change";
    default:
        break;
    }
    return QtMaterialOverlayWidget::eventFilter(obj, event);
}

void Xyz::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(8);

    painter.setPen(pen);

    painter.drawRect(rect());
}


Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    setGraphicsEffect(effect);

    setMinimumWidth(300);

    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuLayout->setContentsMargins(0, 8, 0, 8);

    setLayout(menuLayout);

    QtMaterialFlatButton *fb1 = new QtMaterialFlatButton("Maps");
    QtMaterialFlatButton *fb2 = new QtMaterialFlatButton("Books");
    QtMaterialFlatButton *fb3 = new QtMaterialFlatButton("Flights");

    QFont font("Roboto", 12, QFont::Normal);
    //fb1->setIcon(QtMaterialTheme::icon("toggle", "star"));

    fb1->setFont(font);
    fb2->setFont(font);
    fb3->setFont(font);

    fb1->setTextAlignment(Qt::AlignLeft);
    fb2->setTextAlignment(Qt::AlignLeft);
    fb3->setTextAlignment(Qt::AlignLeft);

    fb1->setMinimumHeight(50);
    fb2->setMinimumHeight(50);
    fb3->setMinimumHeight(50);

    fb1->setHaloVisible(false);
    fb2->setHaloVisible(false);
    fb3->setHaloVisible(false);

    menuLayout->addWidget(fb1);
    menuLayout->addWidget(fb2);
    menuLayout->addWidget(fb3);

    menuLayout->setSpacing(0);

    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

Menu::~Menu()
{
}

//QSize Menu::sizeHint() const
//{
//    return QSize(300, 100);
//}

bool Menu::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        break;
    case QEvent::ParentChange:
    default:
        break;
    }
    return QWidget::event(event);
}

void Menu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    //painter.fillRect(rect(), Qt::white);

    //QPen pen;
    //pen.setColor(Qt::blue);
    //pen.setWidth(4);

    //painter.setPen(pen);

    //painter.drawRect(rect());
}
