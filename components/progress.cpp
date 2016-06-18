#include "progress.h"
#include "progress_p.h"

ProgressPrivate::ProgressPrivate(Progress *q)
    : q_ptr(q)
{
}

ProgressPrivate::~ProgressPrivate()
{
}

void ProgressPrivate::init()
{
}

Progress::Progress(QWidget *parent)
    : QWidget(parent),
      d_ptr(new ProgressPrivate(this))
{
    d_func()->init();
}

Progress::~Progress()
{
}
