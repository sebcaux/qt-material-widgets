#include "about.h"

About::About(QWidget *parent)
    : QLabel(parent)
{
    setFrameShape(QFrame::NoFrame);
    setText(
        "<center>"
        "<h1>Qt Material Desktop Widgets</h1>"
        "<p>&copy; 2016 Laserpants Inc.</p>"
        "</center>"
    );
}

About::~About()
{
}
