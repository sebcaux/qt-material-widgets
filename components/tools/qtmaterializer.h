#ifndef QTMATERIALIZER_H
#define QTMATERIALIZER_H

#include "../qtmaterialwidgets.h"

class QLabel;

class QTMATERIALWIDGETS_EXPORT QtMaterializer
{
public:
    static QLabel *materialise(QLabel *label);
};

#endif  // QTMATERIALIZER_H
