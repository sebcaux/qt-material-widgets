#include "circularprogress_internal.h"

CircularProgressDelegate::CircularProgressDelegate(CircularProgress *parent)
    : QObject(parent),
      progress(parent),
      _dashOffset(0),
      _dashLength(89),
      _angle(0)
{
}

CircularProgressDelegate::~CircularProgressDelegate()
{
}

