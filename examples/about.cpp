#include "about.h"

About::About(QWidget *parent)
    : QLabel(parent)
{
    setFrameShape(QFrame::NoFrame);
    setText(
        "<center>"
        "<h1>About</h1>"
        "<p>Lorem ipsum, blah blah</p>"
        "</center>"
    );
}

About::~About()
{
}
