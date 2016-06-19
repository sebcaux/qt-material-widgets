#include "progress_internal.h"
#include "progress.h"

ProgressDelegate::ProgressDelegate(Progress *parent)
    : QObject(parent),
      progress(parent)
{
}

ProgressDelegate::~ProgressDelegate()
{
}

void ProgressDelegate::setOffset(qreal offset)
{
    _offset = offset;
    progress->update();
}

qreal ProgressDelegate::offset() const
{
    return _offset;
}
