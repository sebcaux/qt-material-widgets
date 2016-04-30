// #ifndef STYLE_H
// #define STYLE_H
//
// #include <QCommonStyle>
//
// class Style : public QCommonStyle
// {
//     Q_OBJECT
//
// public:
//     static Style &instance()
//     {
//         static Style instance;
//         return instance;
//     }
//
//     void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
//                        const QWidget *w = 0) const Q_DECL_OVERRIDE;
//     void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
//                      const QWidget *w = 0) const Q_DECL_OVERRIDE;
//
//     QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const Q_DECL_OVERRIDE;
//     void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
//                             const QWidget *w = 0) const Q_DECL_OVERRIDE;
//     QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
//                          const QWidget *w = 0) const Q_DECL_OVERRIDE;
//
//     int pixelMetric(PixelMetric m, const QStyleOption *opt = 0, const QWidget *widget = 0) const Q_DECL_OVERRIDE;
//
// private:
//     Style() {}
//
//     Style(Style const&);
//     void operator=(Style const&);
// };
//
// #endif // STYLE_H
//
