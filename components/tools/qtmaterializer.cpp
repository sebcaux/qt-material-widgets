#include "qtmaterializer.h"

#include "materializer/qtmaterializerlabel.h"

QLabel *QtMaterializer::materialise(QLabel *label)
{
    new QtMaterializerLabel(label);
    return label;
}
