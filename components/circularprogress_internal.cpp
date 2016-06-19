#include "circularprogress_internal.h"
#include "circularprogress.h"

CircularProgressDelegate::CircularProgressDelegate(CircularProgress *parent)
    : progress(parent),
      _dashOffset(0),
      _dashLength(89)
{
}

CircularProgressDelegate::~CircularProgressDelegate()
{
}

void CircularProgressDelegate::setDashOffset(qreal offset)
{
    _dashOffset = offset;
    progress->update();
}

qreal CircularProgressDelegate::dashOffset() const
{
    return _dashOffset;
}

void CircularProgressDelegate::setDashLength(qreal value)
{
    _dashLength = value;
    progress->update();
}

qreal CircularProgressDelegate::dashLength() const
{
    return _dashLength;
}
