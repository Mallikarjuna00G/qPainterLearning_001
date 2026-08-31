# QPainter 7-Day Precision Vector Tracker

## Core Philosophy & Context
- **The Ultimate Goal**: Achieve the precision, procedural rendering, and capabilities of LaTeX's TikZ engine using Qt's `QPainter`.
- **The Methodology**: We are taking deliberate "baby steps". We learn and execute one `QPainter` method at a time. This sequence is NOT dictated by the top-to-bottom order of the official Qt documentation, but rather by a structured, logical progression that is highly suitable for a beginner learner.
- **The Output**: Each logical step or method grouping results in a dedicated, executable project (e.g., `qPainter_001`, `qPainter_002`). We do not move forward until the current method is proven in working code.

This document serves as the master tracking sheet and context anchor to ensure we methodically cover every aspect of the `QPainter` pipeline without losing sight of the end goal.

---

- ✅ **Day 1: Paint Pipeline, State Stack & Basic Settings**
  - ✅ Widget paint lifecycle: Implement [QWidget::paintEvent(QPaintEvent*)](https://doc.qt.io/qt-6.8/qwidget.html#paintEvent) and [QWidget::resizeEvent(QResizeEvent*)](https://doc.qt.io/qt-6.8/qwidget.html#resizeEvent)
    - [qPainter_001](../qPainter_001)
    - [qPainter_002](../qPainter_002)
    - [qPainter_003](../qPainter_003)
  - ✅ Initialize & manage painter: Use [QPainter::begin(QPaintDevice*)](https://doc.qt.io/qt-6.8/qpainter.html#begin), [QPainter::end()](https://doc.qt.io/qt-6.8/qpainter.html#end), and verify with [QPainter::isActive()](https://doc.qt.io/qt-6.8/qpainter.html#isActive)
    - [qPainter_001](../qPainter_001)
  - ✅ Understand paint architecture: Relationship between [QPainter](https://doc.qt.io/qt-6.8/qpainter.html), [QPaintDevice](https://doc.qt.io/qt-6.8/qpaintdevice.html), and [QPaintEngine](https://doc.qt.io/qt-6.8/qpaintengine.html)
    - [listOfProjects.md (Architectural Note)](listOfProjects.md)
  - ✅ State Stack isolation: Save and restore painter settings via [QPainter::save()](https://doc.doc.qt.io/qt-6.8/qpainter.html#save) and [QPainter::restore()](https://doc.qt.io/qt-6.8/qpainter.html#restore)
    - [qPainter_004](../qPainter_004)
  - ✅ Basic rendering hints: Enable [QPainter::Antialiasing](https://doc.qt.io/qt-6.8/qpainter.html#RenderHint-enum) and [QPainter::TextAntialiasing](https://doc.qt.io/qt-6.8/qpainter.html#RenderHint-enum) via [QPainter::setRenderHint()](https://doc.qt.io/qt-6.8/qpainter.html#setRenderHint) for smooth vector drawing from the start
    - [qPainter_005](../qPainter_005)
  - ✅ Font management: Set and inspect active fonts using [QPainter::setFont()](https://doc.qt.io/qt-6.8/qpainter.html#setFont), [QPainter::font()](https://doc.qt.io/qt-6.8/qpainter.html#font), [QPainter::fontInfo()](https://doc.qt.io/qt-6.8/qpainter.html#fontInfo), and [QPainter::fontMetrics()](https://doc.qt.io/qt-6.8/qpainter.html#fontMetrics)
    - [qPainter_006](../qPainter_006)
  - ✅ Layout Direction: Control text layout flow using [QPainter::setLayoutDirection()](https://doc.qt.io/qt-6.8/qpainter.html#setLayoutDirection) and [QPainter::layoutDirection()](https://doc.qt.io/qt-6.8/qpainter.html#layoutDirection)
    - [qPainter_014](../qPainter_014)

- ✅ **Day 2: Pens, Brushes, Gradients & Drawing Primitives**
  - ✅ Coordinate precision: Test integer vs floating-point primitives (`QPoint` vs `QPointF`, `QLine` vs `QLineF`, `QRect` vs `QRectF`, `QPolygon` vs `QPolygonF`)
    - [qPainter_007](../qPainter_007)
  - ✅ Points & Lines: Draw primitives using [QPainter::drawPoint()](https://doc.qt.io/qt-6.8/qpainter.html#drawPoint), [QPainter::drawPoints()](https://doc.qt.io/qt-6.8/qpainter.html#drawPoints), [QPainter::drawLine()](https://doc.qt.io/qt-6.8/qpainter.html#drawLine), and [QPainter::drawLines()](https://doc.qt.io/qt-6.8/qpainter.html#drawLines)
    - [qPainter_008](../qPainter_008)
  - ✅ Fills & Erasing: Perform solid fills with [QPainter::fillRect()](https://doc.qt.io/qt-6.8/qpainter.html#fillRect) and clear areas with [QPainter::eraseRect()](https://doc.qt.io/qt-6.8/qpainter.html#eraseRect)
    - [qPainter_009](../qPainter_009)
  - ✅ Curved shapes: Draw curves using [QPainter::drawEllipse()](https://doc.qt.io/qt-6.8/qpainter.html#drawEllipse), [QPainter::drawArc()](https://doc.qt.io/qt-6.8/qpainter.html#drawArc), [QPainter::drawPie()](https://doc.qt.io/qt-6.8/qpainter.html#drawPie), and [QPainter::drawChord()](https://doc.qt.io/qt-6.8/qpainter.html#drawChord)
    - [qPainter_010](../qPainter_010)
    - [qPainter_011](../qPainter_011)
  - ✅ Rectangles: Draw outlines and shapes using [QPainter::drawRect()](https://doc.qt.io/qt-6.8/qpainter.html#drawRect), [QPainter::drawRects()](https://doc.qt.io/qt-6.8/qpainter.html#drawRects), and [QPainter::drawRoundedRect()](https://doc.qt.io/qt-6.8/qpainter.html#drawRoundedRect)
    - [qPainter_012](../qPainter_012)
  - ✅ Polygons & Polylines: Draw multisided vector paths using [QPainter::drawPolygon()](https://doc.qt.io/qt-6.8/qpainter.html#drawPolygon), [QPainter::drawPolyline()](https://doc.qt.io/qt-6.8/qpainter.html#drawPolyline), and [QPainter::drawConvexPolygon()](https://doc.qt.io/qt-6.8/qpainter.html#drawConvexPolygon)
    - [qPainter_013](../qPainter_013)
  - ✅ Pen customization: Set pen width, caps ([Qt::FlatCap](https://doc.qt.io/qt-6.8/qt.html#PenCapStyle-enum), [Qt::SquareCap](https://doc.qt.io/qt-6.8/qt.html#PenCapStyle-enum), [Qt::RoundCap](https://doc.qt.io/qt-6.8/qt.html#PenCapStyle-enum)), joins ([Qt::MiterJoin](https://doc.qt.io/qt-6.8/qt.html#PenJoinStyle-enum), [Qt::BevelJoin](https://doc.qt.io/qt-6.8/qt.html#PenJoinStyle-enum), [Qt::RoundJoin](https://doc.qt.io/qt-6.8/qt.html#PenJoinStyle-enum)), and custom dash patterns using [QPen::setDashPattern()](https://doc.qt.io/qt-6.8/qpen.html#setDashPattern)
    - [qPainter_015](../qPainter_015)
  - ✅ Brush & Background options: Set [QPainter::setBrush()](https://doc.qt.io/qt-6.8/qpainter.html#setBrush), configure [QPainter::setBackgroundMode()](https://doc.qt.io/qt-6.8/qpainter.html#setBackgroundMode) ([Qt::OpaqueMode](https://doc.qt.io/qt-6.8/qt.html#BGMode-enum) vs [Qt::TransparentMode](https://doc.qt.io/qt-6.8/qt.html#BGMode-enum)), background colors using [QPainter::setBackground()](https://doc.qt.io/qt-6.8/qpainter.html#setBackground), and brush origin using [QPainter::setBrushOrigin()](https://doc.qt.io/qt-6.8/qpainter.html#setBrushOrigin)
    - [qPainter_016](../qPainter_016)
  - ✅ Gradient fills: Apply [QLinearGradient](https://doc.qt.io/qt-6.8/qlineargradient.html), [QRadialGradient](https://doc.qt.io/qt-6.8/qradialgradient.html), and [QConicalGradient](https://doc.qt.io/qt-6.8/qconicalgradient.html) to vector primitives
    - [qPainter_017](../qPainter_017)

- ✅ **Day 3: Coordinate Systems, Affine Transforms & Matrix Operations**
  - ✅ Basic transformations: Apply translation using [QPainter::translate()](https://doc.qt.io/qt-6.8/qpainter.html#translate), scaling using [QPainter::scale()](https://doc.qt.io/qt-6.8/qpainter.html#scale), rotation using [QPainter::rotate()](https://doc.qt.io/qt-6.8/qpainter.html#rotate), and shearing using [QPainter::shear()](https://doc.qt.io/qt-6.8/qpainter.html#shear)
    - [qPainter_018](../qPainter_018)
  - ✅ Matrix operations: Inspect and manipulate the transformation matrix using [QPainter::worldTransform()](https://doc.qt.io/qt-6.8/qpainter.html#worldTransform), [QPainter::setWorldTransform()](https://doc.qt.io/qt-6.8/qpainter.html#setWorldTransform), [QPainter::resetTransform()](https://doc.qt.io/qt-6.8/qpainter.html#resetTransform), [QPainter::deviceTransform()](https://doc.qt.io/qt-6.8/qpainter.html#deviceTransform), and [QPainter::combinedTransform()](https://doc.qt.io/qt-6.8/qpainter.html#combinedTransform)
    - [qPainter_019](../qPainter_019)
  - ✅ Logical-to-Physical mapping: Implement window-to-viewport transformations using [QPainter::setWindow()](https://doc.qt.io/qt-6.8/qpainter.html#setWindow) / [QPainter::window()](https://doc.qt.io/qt-6.8/qpainter.html#window) and [QPainter::setViewport()](https://doc.qt.io/qt-6.8/qpainter.html#setViewport) / [QPainter::viewport()](https://doc.qt.io/qt-6.8/qpainter.html#viewport)
    - [qPainter_020](../qPainter_020)
  - ✅ Polar coordinate helper: Construct a polar-to-Cartesian function `(r, theta) -> QPointF` to assist circular drawings
    - [qPainter_021](../qPainter_021)
- ✅ **Day 4: Complex Geometry & Bézier Curves (QPainterPath)**
  - ✅ Path construction: Construct shapes using [QPainterPath::moveTo()](https://doc.qt.io/qt-6.8/qpainterpath.html#moveTo), [QPainterPath::lineTo()](https://doc.qt.io/qt-6.8/qpainterpath.html#lineTo), [QPainterPath::cubicTo()](https://doc.qt.io/qt-6.8/qpainterpath.html#cubicTo), and [QPainterPath::quadTo()](https://doc.qt.io/qt-6.8/qpainterpath.html#quadTo)
    - [qPainter_022](../qPainter_022)
    - [qPainter_023](../qPainter_023)
  - ✅ Path drawing actions: Draw outline and fill paths using [QPainter::drawPath()](https://doc.qt.io/qt-6.8/qpainter.html#drawPath), [QPainter::fillPath()](https://doc.qt.io/qt-6.8/qpainter.html#fillPath), and [QPainter::strokePath()](https://doc.qt.io/qt-6.8/qpainter.html#strokePath)
    - [qPainter_024](../qPainter_024)
  - ✅ Path fill rules: Compare [Qt::WindingFill](https://doc.qt.io/qt-6.8/qt.html#FillRule-enum) and [Qt::OddEvenFill](https://doc.qt.io/qt-6.8/qt.html#FillRule-enum) fill behaviors
    - [qPainter_025](../qPainter_025)
  - ✅ Stroking & outlines: Use [QPainterPathStroker](https://doc.qt.io/qt-6.8/qpainterpathstroker.html) for complex outlines and adjust curve error tolerance with [QPainterPathStroker::setCurveThreshold()](https://doc.qt.io/qt-6.8/qpainterpathstroker.html#setCurveThreshold)
    - [qPainter_026](../qPainter_026)
  - ✅ Vector calculations: Calculate tangents and midpoints along curves to place arrowheads dynamically
    - [qPainter_027](../qPainter_027)

- ✅ **Day 5: Text Metrics, Anchors, Clipping & Composition Modes**
  - ✅ Precise text measurements: Measure text bounding boxes using [QFontMetricsF::boundingRect()](https://doc.qt.io/qt-6.8/qfontmetricsf.html#boundingRect) and [QPainter::boundingRect()](https://doc.qt.io/qt-6.8/qpainter.html#boundingRect-1)
    - [qPainter_028](../qPainter_028)
    - [qPainter_029](../qPainter_029)
  - ✅ Anchor structures: Build node anchors (e.g. North, South, East, West, Center) for placement of multi-line text labels
    - [qPainter_030](../qPainter_030)
  - ✅ Clipping regions: Restrict rendering areas using [QPainter::setClipRect()](https://doc.qt.io/qt-6.8/qpainter.html#setClipRect), [QPainter::setClipRegion()](https://doc.qt.io/qt-6.8/qpainter.html#setClipRegion), [QPainter::setClipPath()](https://doc.qt.io/qt-6.8/qpainter.html#setClipPath), and query clip state with [QPainter::hasClipping()](https://doc.qt.io/qt-6.8/qpainter.html#hasClipping), [QPainter::clipRegion()](https://doc.qt.io/qt-6.8/qpainter.html#clipRegion), and [QPainter::clipPath()](https://doc.qt.io/qt-6.8/qpainter.html#clipPath)
    - [qPainter_031](../qPainter_031)
  - ✅ Composition Modes: Apply Porter-Duff compositing rules using [QPainter::setCompositionMode()](https://doc.qt.io/qt-6.8/qpainter.html#setCompositionMode) and test modes like [QPainter::CompositionMode_SourceOver](https://doc.qt.io/qt-6.8/qpainter.html#CompositionMode-enum), [QPainter::CompositionMode_Source](https://doc.qt.io/qt-6.8/qpainter.html#CompositionMode-enum), and [QPainter::CompositionMode_Clear](https://doc.qt.io/qt-6.8/qpainter.html#CompositionMode-enum)
    - [qPainter_032](../qPainter_032)

- ⏳ **Day 6: Images, Pixmaps, Pictures & Performance Optimization**
  - ✅ Raster images & pixmaps: Draw pixmaps and images using [QPainter::drawPixmap()](https://doc.qt.io/qt-6.8/qpainter.html#drawPixmap), [QPainter::drawImage()](https://doc.qt.io/qt-6.8/qpainter.html#drawImage), and [QPainter::drawTiledPixmap()](https://doc.qt.io/qt-6.8/qpainter.html#drawTiledPixmap)
    - [qPainter_033](../qPainter_033)
  - ✅ Device Pixel Ratio: Handle high-resolution drawing by inspecting [QPixmap::devicePixelRatio()](https://doc.qt.io/qt-6.8/qpixmap.html#devicePixelRatio) on high-DPI displays
    - [qPainter_034](../qPainter_034)
  - ✅ Serialized recording: Record and replay drawing operations using [QPicture](https://doc.qt.io/qt-6.8/qpicture.html) and [QPainter::drawPicture()](https://doc.qt.io/qt-6.8/qpainter.html#drawPicture)
    - [qPainter_035](../qPainter_035)
  - ✅ Image scaling quality: Test the [QPainter::SmoothPixmapTransform](https://doc.qt.io/qt-6.8/qpainter.html#RenderHint-enum) render hint to handle scaling interpolation smoothly
    - [qPainter_036](../qPainter_036)
  - ✅ Rendering hints query: Inspect all active state hints at runtime using [QPainter::renderHints()](https://doc.qt.io/qt-6.8/qpainter.html#renderHints)
    - [qPainter_037](../qPainter_037)
  - ⏳ Performance and formats: Test performance difference on Raster backend formats (premultiplied [QImage::Format_ARGB32_Premultiplied](https://doc.qt.io/qt-6.8/qimage.html#Format-enum), [QImage::Format_RGB32](https://doc.qt.io/qt-6.8/qimage.html#Format-enum)) and learn how OpenGL graphics acceleration works with [QOpenGLWidget](https://doc.qt.io/qt-6.8/qopenglwidget.html)

- ⏳ **Day 7: Document Serialization (SVG/PDF) & Procedural Graph Mini-Engine**
  - ⏳ SVG generator: Set up a CMake project targeting `Qt6::Svg` and redirect painting to [QSvgGenerator](https://doc.qt.io/qt-6.8/qsvggenerator.html) to produce vector XML output
  - ⏳ PDF writer: Export high-quality print documents by redirecting painting to [QPdfWriter](https://doc.qt.io/qt-6.8/qpdfwriter.html)
  - ⏳ TikZ-Style Mini-Engine: Build an application with a `Node` structure (text, bounding box, anchor points) and connect them procedurally using curved Bézier paths, rendering simultaneously to screen (widget), SVG, and PDF