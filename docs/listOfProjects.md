# List of Projects

## qPainter_001

- [qPainter_001](../qPainter_001)
- **Brief:** The simplest starting point for QPainter: initializing the painter pipeline on a custom QWidget via paintEvent() and drawing a diagonal vector line.

**Topics:**
- Overriding [QWidget::paintEvent(QPaintEvent*)](https://doc.qt.io/qt-6.8/qwidget.html#paintEvent)
- RAII painter initialization: [QPainter::QPainter(QPaintDevice*)](https://doc.qt.io/qt-6.8/qpainter.html#QPainter-1)
- Checking painter status: [QPainter::isActive()](https://doc.qt.io/qt-6.8/qpainter.html#isActive)
- Drawing basic lines: [QPainter::drawLine()](https://doc.qt.io/qt-6.8/qpainter.html#drawLine)

**Key Takeaway: The `paintEvent` Gateway**
- **The Only Place to Draw**: Any custom drawing using `QPainter` **must** take place inside the overridden `QWidget::paintEvent(QPaintEvent*)` method (or a function called directly by it). Outside this method, the widget's drawing surface is locked.
- **Automatic Execution**: The Qt event loop automatically calls this method whenever the widget needs to be drawn on the screen (e.g., initial show, resize, or when uncovered). We do not call it manually.

**Key Takeaway: The `QPainter painter(this)` Initialization**

That line is the core of how you start drawing in Qt. Let's break down exactly what `QPainter painter(this);` is doing:
- **`QPainter`**: This is the Qt class that acts as your digital paintbrush. It holds all the functions for drawing lines, shapes, and text.
- **`painter`**: This is simply the name of the local variable (the object) we are creating.
- **`(this)`**: This is the most important part. By passing `this` to the constructor, you are telling the `QPainter` exactly what surface to draw on. In this context, `this` refers to the `CanvasWidget` itself. A `QWidget` is a type of `QPaintDevice`, which means it is a valid canvas.

- **RAII (Resource Acquisition Is Initialization)**: By creating `painter` as a local stack variable, we guarantee safe initialization and cleanup. The constructor automatically calls `begin(this)` to open the drawing pipeline, and the destructor automatically calls `end()` to flush the drawing and clean up when the function exits.
- **Polymorphism and `QPaintDevice`**: The constructor expects a `QPaintDevice*`. Because `QWidget` inherits from `QPaintDevice`, passing `this` is perfectly valid. This powerful inheritance design means the exact same `QPainter` commands can be used to draw on screens (`QWidget`), images (`QPixmap`), or even export to PDFs (`QPdfWriter`), as they are all `QPaintDevice`s.

```mermaid
classDiagram
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
```

**Key Takeaway: `painter.isActive()` and Deactivation**
- **Sanity Checking**: `isActive()` returns a boolean confirming whether the painter successfully locked onto the canvas and initialized. If you try to paint outside of `paintEvent`, this will return `false`, saving you from issuing drawing commands into the void.
- **Manual Deactivation**: You can manually deactivate a painter by calling `painter.end()`. This is useful if you need to temporarily unlock the canvas so another specialized painting class can take over. (Note: when using the RAII initialization, `end()` is called automatically for you when the object goes out of scope).

**Key Takeaway: The Unused `QPaintEvent` Parameter**
- **Signature Requirement**: We are completely ignoring the `QPaintEvent *event` parameter in our code. We must include it simply because C++ requires our function signature to perfectly match Qt's original `QWidget::paintEvent(QPaintEvent*)` in order to successfully override it.

![Method: QWidget::paintEvent](https://img.shields.io/badge/Method-QWidget%3A%3ApaintEvent-blue) ![Method: QPainter::drawLine](https://img.shields.io/badge/Method-QPainter%3A%3AdrawLine-blue)

---

## qPainter_002
- [qPainter_002](../qPainter_002)
- **Brief**: Drawing dynamically relative to the window size by querying `width()` and `height()` directly inside `paintEvent`, without explicitly overriding `resizeEvent`.

**Topics:**
- Widget dimensions: [QWidget::width()](https://doc.qt.io/qt-6.8/qwidget.html#width-prop) and [QWidget::height()](https://doc.qt.io/qt-6.8/qwidget.html#height-prop)

**Key Takeaway: Dynamic Drawing via Event Loop**
- **Automatic Repaints**: Qt's event loop automatically schedules a `paintEvent` whenever the widget is resized by the user or the OS. 
- **Real-time Querying**: Because `paintEvent` is called *after* the resize happens, querying `width()` and `height()` directly inside the `paintEvent` guarantees you are always drawing against the fresh, current dimensions of the window. You do not strictly *need* to override `resizeEvent` just to achieve scalable drawing!

**Key Takeaway: Overrides and Unused Parameters**
- **Function Overrides**: C++ requires that when we override a virtual function like `QWidget::paintEvent`, our signature must match exactly. 
- **Unused Parameters**: We are completely ignoring the `QPaintEvent *event` parameter in our code. We must include it simply to satisfy the override requirement. While unused now, it holds data (like `rect()` and `region()`) for future optimizations.

```mermaid
classDiagram
    QEvent <|-- QPaintEvent
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        +width() const int
        +height() const int
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
```

![Method: QWidget::width](https://img.shields.io/badge/Method-QWidget%3A%3Awidth-blue) ![Method: QWidget::height](https://img.shields.io/badge/Method-QWidget%3A%3Aheight-blue)

---

## qPainter_003
- [qPainter_003](../qPainter_003)
- **Brief**: Overriding `QWidget::resizeEvent(QResizeEvent*)` to intercept window size changes for logging, calculations, or optimization prior to the drawing phase.

**Topics:**
- Event Interception: [QWidget::resizeEvent(QResizeEvent*)](https://doc.qt.io/qt-6.8/qwidget.html#resizeEvent)
- Event Data Payload: [QResizeEvent::size()](https://doc.qt.io/qt-6.8/qresizeevent.html#size)
- Base Class Delegation: `QWidget::resizeEvent(event)`

**Key Takeaway: The Event Lifecycle**
- **Interception Point**: By overriding `resizeEvent`, we can hook into the exact moment the operating system dictates a size change, *before* the painting phase happens. This is critical for complex engines (like TikZ) where heavy mathematics or layout recalculations should be cached here rather than recalculated 60 times a second inside `paintEvent`.
- **Event Payload (`QResizeEvent`)**: Unlike `paintEvent` where we ignored the parameter, `QResizeEvent` carries highly useful payload data, specifically `event->size()`, which tells us exactly what the new dimensions are going to be.
- **Base Class Delegation**: It is a critical Qt best practice to pass the event back up the chain by calling `QWidget::resizeEvent(event);` at the end of our override. This ensures that the underlying engine still handles its own internal housekeeping.

**FAQ: Why separate math from painting?**
- **Q:** *If `paintEvent` fires rapidly during a resize anyway, why bother moving the heavy math to `resizeEvent`?*
- **A:** During an active window drag, both events do indeed fire rapidly on a loop. However, the massive performance savings happen *when you are not resizing the window*. The OS fires `paintEvent` for dozens of non-resize reasons (e.g., hovering, animating, uncovering the window from behind another app, Alt-Tabbing). In all of these non-resize scenarios, `paintEvent` fires, but `resizeEvent` NEVER fires. By caching heavy math in `resizeEvent`, your app skips all calculations when the window is simply uncovered or hovered over, allowing `paintEvent` to instantly redraw the cached geometry without stuttering.

```mermaid
classDiagram
    QEvent <|-- QResizeEvent
    
    class QResizeEvent {
        +size() const QSize
        +oldSize() const QSize
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        +width() const int
        +height() const int
        #paintEvent(event: QPaintEvent*) virtual void
        #resizeEvent(event: QResizeEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
        #resizeEvent(event: QResizeEvent*) override void
    }
```

![Method: QWidget::resizeEvent](https://img.shields.io/badge/Method-QWidget%3A%3AresizeEvent-blue) ![Method: QResizeEvent::size](https://img.shields.io/badge/Method-QResizeEvent%3A%3Asize-blue)

---

## Architectural Note: The Holy Trinity of Qt Painting
Before we start modifying the state of our painter (changing colors and thickness), it is critical to understand the three core classes that allow Qt's graphics system to work identically across multiple platforms and formats:

1. **`QPainter` (The Artist)**: This is the class you interact with (e.g., `painter.drawLine()`). It holds the current settings (pen color, font, brush) and tells the system *what* to draw.
2. **`QPaintDevice` (The Canvas)**: This represents the physical surface you are drawing on. It is a 2D space with a width, height, and coordinate system. `QWidget`, `QPixmap`, `QImage`, and `QPdfWriter` all inherit from `QPaintDevice`.
   - *When will we use this?* Currently, our `QWidget` acts as the canvas. In **Day 6 (Advanced Graphics & Off-Screen Rendering)**, we will dynamically swap the canvas to a `QImage` to export PNGs, and a `QPdfWriter` to export PDFs.
3. **`QPaintEngine` (The Translator)**: This class is completely hidden from you. It sits between the Artist and the Canvas. If you draw on a `QWidget`, the internal engine translates your line into low-level OpenGL, Metal, or Direct2D commands. If you draw on a `QPdfWriter`, the PDF engine translates that exact same `drawLine()` command into a PDF vector string.
   - *When will we use this?* **Never.** Application developers treat this as a black box. It is exclusively touched by internal Qt engineers porting the framework to new hardware.

This separation of concerns is the secret sauce. It is why the exact same complex math from your TikZ engine can render perfectly to a 4K monitor, save to a PNG, or export to a PDF, without you having to write three different versions of your code!

---

## qPainter_004
- [qPainter_004](../qPainter_004)
- **Brief**: Managing the "Artist's" State Stack. Because `QPainter` is the only class in the Trinity that holds styling data, we must use `save()` and `restore()` to backup and reset its brain (Pens and Brushes) to prevent cross-contamination.

**Topics:**
- Push state: [QPainter::save()](https://doc.qt.io/qt-6.8/qpainter.html#save)
- Pop state: [QPainter::restore()](https://doc.qt.io/qt-6.8/qpainter.html#restore)
- Pen creation: [QPen](https://doc.qt.io/qt-6.8/qpen.html) and [QPainter::setPen()](https://doc.qt.io/qt-6.8/qpainter.html#setPen)

**Key Takeaway: The Golden Bracket**
- **State Isolation**: When drawing complex, modular components (like nodes in a graph), it is critical that one component doesn't leak its styling (like a thick red outline) onto the next component. Wrapping your styling modifications in a `painter.save()` and `painter.restore()` bracket guarantees that the painter's state resets to exactly how you found it.

```mermaid
classDiagram
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        +width() const int
        +height() const int
        #paintEvent(event: QPaintEvent*) virtual void
    }

    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    class QPainter {
        +save() void
        +restore() void
        +setPen(pen: QPen) void
    }
    
    class QPen {
        +QPen(color: QColor)
        +setWidth(width: int) void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QPen : Instantiates
    QPainter ..> QPen : Manages State
```

![Method: QPainter::save](https://img.shields.io/badge/Method-QPainter%3A%3Asave-blue) ![Method: QPainter::restore](https://img.shields.io/badge/Method-QPainter%3A%3Arestore-blue) ![Method: QPainter::setPen](https://img.shields.io/badge/Method-QPainter%3A%3AsetPen-blue)

---

## qPainter_005
- [qPainter_005](../qPainter_005)
- **Brief**: Eliminating jagged pixelation by configuring the Painter with the `QPainter::Antialiasing` render hint.

**Topics:**
- Render Hints: [QPainter::setRenderHint()](https://doc.qt.io/qt-6.8/qpainter.html#setRenderHint) and [QPainter::Antialiasing](https://doc.qt.io/qt-6.8/qpainter.html#RenderHint-enum)

**Key Takeaway: Buttery Smooth Vectors**
- By default, Qt is optimized for raw performance and draws shapes using hard pixel edges (aliasing). For modern vector graphics (like TikZ diagrams), setting the `Antialiasing` flag is mandatory to activate sub-pixel color blending, resulting in smooth, professional curves and diagonal lines. This hint only affects screen/image rendering; it is completely ignored when rendering to pure vector devices like SVG or PDF, where the viewer handles smoothing.

```mermaid
classDiagram
    QEvent <|-- QPaintEvent
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        +width() const int
        +height() const int
        #paintEvent(event: QPaintEvent*) virtual void
    }

    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    class QPainter {
        +setRenderHint(hint: RenderHint, on: bool) void
    }
    
    class RenderHint {
        <<enumeration>>
        Antialiasing
        TextAntialiasing
        SmoothPixmapTransform
    }
    
    CanvasWidget ..> QPainter : Instantiates
    QPainter ..> RenderHint : Uses
```

![Method: QPainter::setRenderHint](https://img.shields.io/badge/Method-QPainter%3A%3AsetRenderHint-blue)

---

## qPainter_006
- [qPainter_006](../qPainter_006)
- **Brief**: Managing fonts and calculating pixel-perfect text boundaries using `QFontMetrics`.

**Topics:**
- Fonts: [QFont](https://doc.qt.io/qt-6.8/qfont.html), [QPainter::setFont()](https://doc.qt.io/qt-6.8/qpainter.html#setFont), and [QPainter::font()](https://doc.qt.io/qt-6.8/qpainter.html#font)
- Metrics & Info: [QFontMetrics](https://doc.qt.io/qt-6.8/qfontmetrics.html), [QPainter::fontMetrics()](https://doc.qt.io/qt-6.8/qpainter.html#fontMetrics), [QFontInfo](https://doc.qt.io/qt-6.8/qfontinfo.html), and [QPainter::fontInfo()](https://doc.qt.io/qt-6.8/qpainter.html#fontInfo)

**Key Takeaway: The Text Baseline and Font Metrics**
- When drawing text, the Y-coordinate provided to `drawText()` is not the geometric top of the string, but the **baseline** (the invisible line that letters sit on). To perfectly center text inside a shape (like a node), you must use `QFontMetrics` to measure the exact `horizontalAdvance()` and `height()` of the string in the active font. You calculate the geometric top-left corner of the shape, and then add `QFontMetrics::ascent()` to the Y-coordinate to correctly position the text's baseline.
- **Font Abstraction**: When you request a `QFont`, the operating system might substitute it with a similar fallback font if it's missing. While `QPainter::font()` returns what you asked for, `QPainter::fontInfo()` reveals the *actual* font Qt ended up rendering on the screen.

```mermaid
classDiagram
    QEvent <|-- QPaintEvent
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        +width() const int
        +height() const int
        #paintEvent(event: QPaintEvent*) virtual void
    }

    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    class QPainter {
        +setFont(font: QFont) void
        +font() QFont
        +fontInfo() QFontInfo
        +fontMetrics() QFontMetrics
        +drawText(x: int, y: int, text: QString) void
    }
    
    class QFont {
        +QFont(family: QString, pointSize: int, weight: int)
        +family() QString
    }
    
    class QFontInfo {
        +family() QString
    }
    
    class QFontMetrics {
        +horizontalAdvance(text: QString) int
        +height() int
        +ascent() int
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QFont : Instantiates
    CanvasWidget ..> QFontMetrics : Uses
    CanvasWidget ..> QFontInfo : Uses
    QPainter ..> QFont : Manages State
    QPainter ..> QFontInfo : Creates / Returns
    QPainter ..> QFontMetrics : Creates / Returns
```

![Method: QPainter::setFont](https://img.shields.io/badge/Method-QPainter%3A%3AsetFont-blue) ![Method: QPainter::font](https://img.shields.io/badge/Method-QPainter%3A%3Afont-blue) ![Method: QPainter::fontInfo](https://img.shields.io/badge/Method-QPainter%3A%3AfontInfo-blue) ![Method: QPainter::fontMetrics](https://img.shields.io/badge/Method-QPainter%3A%3AfontMetrics-blue)

---

## qPainter_007
- [qPainter_007](../qPainter_007)
- **Brief**: Introduction to sub-pixel coordinate precision for smooth vector geometries.

**Topics:**
- Floating-Point Primitives: [QPointF](https://doc.qt.io/qt-6.8/qpointf.html), [QLineF](https://doc.qt.io/qt-6.8/qlinef.html), [QRectF](https://doc.qt.io/qt-6.8/qrectf.html)
- `QPainter` drawing overloads: [QPainter::drawLine(const QLineF&)](https://doc.qt.io/qt-6.8/qpainter.html#drawLine), [QPainter::drawRect(const QRectF&)](https://doc.qt.io/qt-6.8/qpainter.html#drawRect)

**Key Takeaway: Integer Truncation vs. Mathematical Precision**
- When drawing procedurally (especially intersections or angled lines), coordinates are rarely perfect integers. Standard integer geometry classes (`QPoint`, `QRect`) implicitly truncate decimal values (e.g., `50.75` becomes `50`). This causes shapes to geometrically "snap" to the pixel grid, destroying mathematical accuracy and sub-pixel antialiasing. We must habitually use floating-point geometry (`*F` suffix) to feed exact decimal coordinates to `QPainter`.

```mermaid
classDiagram
    class QPainter {
        +drawLine(line: QLineF) void
        +drawRect(rect: QRectF) void
    }
    
    class QPointF {
        +QPointF(xpos: qreal, ypos: qreal)
    }
    
    class QLineF {
        +QLineF(pt1: QPointF, pt2: QPointF)
    }
    
    class QRectF {
        +QRectF(left: qreal, top: qreal, width: qreal, height: qreal)
    }
    
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QPointF : Instantiates
    CanvasWidget ..> QLineF : Instantiates
    CanvasWidget ..> QRectF : Instantiates
    
    QLineF ..> QPointF : Constructs with
    
    QPainter ..> QLineF : Receives
    QPainter ..> QRectF : Receives
```

![Method: QPainter::drawLine](https://img.shields.io/badge/Method-QPainter%3A%3AdrawLine-blue) ![Method: QPainter::drawRect](https://img.shields.io/badge/Method-QPainter%3A%3AdrawRect-blue)

---

## qPainter_008
- [qPainter_008](../qPainter_008)
- **Brief**: High-performance batch drawing of points and lines.

**Topics:**
- Batch Primitives: [QPainter::drawPoints()](https://doc.qt.io/qt-6.8/qpainter.html#drawPoints), [QPainter::drawLines()](https://doc.qt.io/qt-6.8/qpainter.html#drawLines)
- Containers: `QList<T>`, C-Style Arrays

**Key Takeaway: Graphics Pipeline Efficiency**
- Calling `drawPoint()` or `drawLine()` thousands of times in a loop forces the graphics engine to context-switch constantly. By packing all your geometric primitives into a single array (or `QList`) and passing it to the batch `drawPoints()` or `drawLines()` overloads, the GPU (or underlying raster engine) processes the entire batch in a single highly optimized pass. This is critical for drawing large grids, complex TikZ nodes, or dense scatter plots.

```mermaid
classDiagram
    class QPainter {
        +drawPoints(points: const QPointF*, pointCount: int) void
        +drawLines(lines: QList) void
        +setPen(pen: QPen) void
    }
    
    class QPen {
        +QPen(color: Qt::GlobalColor, width: int)
    }
    
    class QPointF {
        +QPointF(xpos: qreal, ypos: qreal)
    }
    
    class QLineF {
        +QLineF(x1: qreal, y1: qreal, x2: qreal, y2: qreal)
    }
    
    class QList {
        +append(value: QLineF) void
    }
    
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    class GlobalHelpers {
        <<free functions>>
        +batchDrawPoints(painter: QPainter&) void
        +batchDrawLines(painter: QPainter&) void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> GlobalHelpers : Calls
    
    GlobalHelpers ..> QPainter : Receives
    GlobalHelpers ..> QPointF : Instantiates (Array)
    GlobalHelpers ..> QList : Instantiates
    GlobalHelpers ..> QLineF : Instantiates
    GlobalHelpers ..> QPen : Instantiates
    
    QList *-- QLineF : Contains
    
    QPainter ..> QPointF : Receives (Array)
    QPainter ..> QList : Receives
    QPainter ..> QPen : Receives
```
![Method: QPainter::drawPoints](https://img.shields.io/badge/Method-QPainter%3A%3AdrawPoints-blue) ![Method: QPainter::drawLines](https://img.shields.io/badge/Method-QPainter%3A%3AdrawLines-blue)

---

## qPainter_009
- [qPainter_009](../qPainter_009)
- **Brief**: Fast solid fills and geometric erasing.

**Topics:**
- Direct Manipulation: [QPainter::fillRect()](https://doc.qt.io/qt-6.8/qpainter.html#fillRect), [QPainter::eraseRect()](https://doc.qt.io/qt-6.8/qpainter.html#eraseRect)

**Key Takeaway: Direct Screen Painting**
- Unlike standard `drawRect()` which strokes a path using the current `QPen` and fills it using the current `QBrush`, `fillRect()` is a highly optimized fast-path that ignores the pen/brush and blasts a raw color (or gradient) directly into the rectangle bounds. 
- `eraseRect()` is mathematically identical to drawing a rectangle filled with the widget's default background color (`window()` color), effectively punching a hole through previously rendered layers. This is significantly cheaper computationally than using complex clipping paths to mask out regions.

```mermaid
classDiagram
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class QPainter {
        +fillRect(rectangle: QRectF, color: Qt::GlobalColor) void
        +eraseRect(rectangle: QRectF) void
    }
    
    class QRectF {
        +QRectF(left: qreal, top: qreal, width: qreal, height: qreal)
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QRectF : Instantiates
    
    QPainter ..> QRectF : Receives
```

![Method: QPainter::fillRect](https://img.shields.io/badge/Method-QPainter%3A%3AfillRect-blue) ![Method: QPainter::eraseRect](https://img.shields.io/badge/Method-QPainter%3A%3AeraseRect-blue)

---

## qPainter_010
- [qPainter_010](../qPainter_010)
- **Brief**: Drawing curved shapes using bounding boxes and 1/16th degree integer angles.

**Topics:**
- Drawing Primitives: [QPainter::drawEllipse()](https://doc.qt.io/qt-6.8/qpainter.html#drawEllipse), [QPainter::drawArc()](https://doc.qt.io/qt-6.8/qpainter.html#drawArc), [QPainter::drawPie()](https://doc.qt.io/qt-6.8/qpainter.html#drawPie), [QPainter::drawChord()](https://doc.qt.io/qt-6.8/qpainter.html#drawChord)

**Key Takeaway: The Bounding Box Architecture**
- Almost all GUI rendering engines (including Qt) define curves by their enclosing `QRectF` rather than a mathematical center point and radius. This allows the GPU/Rasterizer to instantly calculate clipping boundaries and determine exactly which screen pixels need to be evaluated, maximizing graphics performance.
- For partial curves (Arcs, Pies, Chords), angles are provided as integers representing `1/16ths of a degree`. This legacy design decision (inherited from X11) provided sub-degree precision ($0.0625^\circ$) without the severe performance penalty of using floating-point math on 1990s hardware.

```mermaid
classDiagram
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +SixteenthsOfADegree : int$
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    class QPainter {
        +drawEllipse(rectangle: QRectF) void
        +drawArc(rectangle: QRectF, startAngle: int, spanAngle: int) void
        +drawPie(rectangle: QRectF, startAngle: int, spanAngle: int) void
        +drawChord(rectangle: QRectF, startAngle: int, spanAngle: int) void
    }
    
    class QRectF {
        +QRectF(left: qreal, top: qreal, width: qreal, height: qreal)
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QRectF : Instantiates
    
    QPainter ..> QRectF : Receives
```

![Method: QPainter::drawEllipse](https://img.shields.io/badge/Method-QPainter%3A%3AdrawEllipse-blue) ![Method: QPainter::drawArc](https://img.shields.io/badge/Method-QPainter%3A%3AdrawArc-blue) ![Method: QPainter::drawPie](https://img.shields.io/badge/Method-QPainter%3A%3AdrawPie-blue) ![Method: QPainter::drawChord](https://img.shields.io/badge/Method-QPainter%3A%3AdrawChord-blue)

---

## qPainter_011
- [qPainter_011](../qPainter_011)
- **Brief**: Building an intuitive math abstraction layer (TikZ-style API) over Qt's bounding box requirements.

**Topics:**
- Architectural Patterns: Inline Helper Functions, Stateless Functional Wrappers, Overload Resolution.

**Key Takeaway: The Stateless Abstraction Pattern**
- By creating `inline` helper methods within `canvaswidget.hpp`, we successfully decoupled mathematical intent (centers and radii) from Qt's rendering requirements (bounding boxes and $1/16^{\text{th}}$ degrees) without sacrificing any CPU performance or introducing heavy stateful wrapper classes. 
- The design allows the user to write clean `paintEvent` code (`drawPieIntuitive(...)`) while ensuring that the "Highlander Rule" of Qt rendering is respected (only one `QPainter` active per widget, passed dynamically by reference).

```mermaid
classDiagram
    QWidget <|-- CanvasWidget
    
    class CanvasWidget {
        +SixteenthsOfADegree : int$
        #paintEvent(event: QPaintEvent*) override void
        +determineBoundingBox(center: QPointF, radius: qreal) QRectF
        +drawArcIntuitive(painter: QPainter&, center: QPointF, ...) QRectF
        +drawChordIntuitive(painter: QPainter&, center: QPointF, ...) QRectF
        +drawPieIntuitive(painter: QPainter&, center: QPointF, ...) QRectF
    }
    
    class QPainter {
        +drawEllipse(center: QPointF, rx: qreal, ry: qreal) void
        +drawArc(rectangle: QRectF, startAngle: int, spanAngle: int) void
        +drawPie(rectangle: QRectF, startAngle: int, spanAngle: int) void
        +drawChord(rectangle: QRectF, startAngle: int, spanAngle: int) void
    }
    
    CanvasWidget ..> QPainter : Passes by Reference
```

![Method: QPainter::drawEllipse](https://img.shields.io/badge/Method-QPainter%3A%3AdrawEllipse-blue) ![Method: QPainter::drawArc](https://img.shields.io/badge/Method-QPainter%3A%3AdrawArc-blue) ![Method: QPainter::drawPie](https://img.shields.io/badge/Method-QPainter%3A%3AdrawPie-blue) ![Method: QPainter::drawChord](https://img.shields.io/badge/Method-QPainter%3A%3AdrawChord-blue)

---

## qPainter_012
- [qPainter_012](../qPainter_012)
- **Brief**: Drawing standard rectangles, batched rectangle lists, and dynamically scaling rounded rectangles.

**Topics:**
- Drawing Primitives: [QPainter::drawRect()](https://doc.qt.io/qt-6.8/qpainter.html#drawRect), [QPainter::drawRects()](https://doc.qt.io/qt-6.8/qpainter.html#drawRects), [QPainter::drawRoundedRect()](https://doc.qt.io/qt-6.8/qpainter.html#drawRoundedRect)

**Key Takeaway: Batch Rendering and Dynamic Radii**
- Passing a `QList<QRectF>` into `drawRects()` allows Qt to batch-render massive grids or tilemaps with a single draw call, bypassing the heavy overhead of iterating `drawRect()` in a native C++ loop.
- `drawRoundedRect()` is incredibly flexible thanks to the `Qt::SizeMode` enum. `Qt::AbsoluteSize` enforces exact pixel curves (e.g. `15.0`), ensuring UI borders don't stretch irregularly when a widget resizes. `Qt::RelativeSize` (measured $0.0-100.0$) creates fluid borders that scale dynamically with the aspect ratio, making it effortless to generate pill shapes or dynamic circular avatars.

```mermaid
classDiagram
    class QPainter {
        +drawRect(rect: QRectF) void
        +drawRects(rectangles: QList) void
        +drawRoundedRect(rect: QRectF, xRadius: qreal, yRadius: qreal, mode: Qt::SizeMode) void
    }
    
    class QRectF {
        +QRectF(left: qreal, top: qreal, width: qreal, height: qreal)
    }
    
    class Qt {
        <<namespace>>
    }
    
    class SizeMode {
        <<enumeration>>
        AbsoluteSize
        RelativeSize
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    Qt *-- SizeMode : contains
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QRectF : Instantiates
    CanvasWidget ..> SizeMode : Uses
    
    QPainter ..> QRectF : Receives
    QPainter ..> SizeMode : Receives
```

![Method: QPainter::drawRect](https://img.shields.io/badge/Method-QPainter%3A%3AdrawRect-blue) ![Method: QPainter::drawRects](https://img.shields.io/badge/Method-QPainter%3A%3AdrawRects-blue) ![Method: QPainter::drawRoundedRect](https://img.shields.io/badge/Method-QPainter%3A%3AdrawRoundedRect-blue)

---

## qPainter_013
- [qPainter_013](../qPainter_013)
- **Brief**: Exploring complex vector paths by comparing open Polylines, closed Polygons, and highly optimized Convex Polygons.

**Topics:**
- Vector Paths: [QPolygonF](https://doc.qt.io/qt-6.8/qpolygonf.html), [QPainter::drawPolyline()](https://doc.qt.io/qt-6.8/qpainter.html#drawPolyline), [QPainter::drawPolygon()](https://doc.qt.io/qt-6.8/qpainter.html#drawPolygon), [QPainter::drawConvexPolygon()](https://doc.qt.io/qt-6.8/qpainter.html#drawConvexPolygon)

**Key Takeaway: The Fill Rule of Open vs. Closed Paths**
- **`drawPolyline`**: Strictly defines an open, continuous stroke. Because it has no "inside", it completely ignores the active `QBrush` and only renders the `QPen`.
- **`drawPolygon`**: Defines a closed shape by automatically connecting the final point back to the first point. It fully respects the active `QBrush` to fill its interior.

**Key Takeaway: The Convex Optimization**
- Mathematical Convexity: A convex shape (like a Triangle or Hexagon) has no internal angles greater than 180 degrees (i.e., no "dents").
- Performance: Because convex shapes are mathematically simple, the rasterization engine can use a significantly faster algorithm to fill them. By explicitly calling `drawConvexPolygon()`, you bypass the heavy mathematics required to fill complex, self-intersecting polygons (like a 5-pointed star). *Warning: Passing a non-convex shape to this method results in visual corruption.*

```mermaid
classDiagram
    class QPainter {
        +drawPolyline(points: QPolygonF) void
        +drawPolygon(points: QPolygonF) void
        +drawConvexPolygon(points: QPolygonF) void
        +setBrush(brush: QBrush) void
    }
    
    class QPolygonF {
        +QPolygonF(points: std::initializer_list~QPointF~)
    }
    
    class QPointF {
        +QPointF(xpos: qreal, ypos: qreal)
    }
    
    class QBrush {
        +QBrush(color: Qt::GlobalColor)
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QPolygonF : Instantiates
    CanvasWidget ..> QPointF : Instantiates
    CanvasWidget ..> QBrush : Instantiates
    
    QPolygonF *-- QPointF : Contains
    
    QPainter ..> QPolygonF : Receives
    QPainter ..> QBrush : Receives
```

![Method: QPainter::drawPolyline](https://img.shields.io/badge/Method-QPainter%3A%3AdrawPolyline-blue) ![Method: QPainter::drawPolygon](https://img.shields.io/badge/Method-QPainter%3A%3AdrawPolygon-blue) ![Method: QPainter::drawConvexPolygon](https://img.shields.io/badge/Method-QPainter%3A%3AdrawConvexPolygon-blue)

---

## qPainter_014
- [qPainter_014](../qPainter_014)
- **Brief**: Managing text alignment for localization using `QPainter::setLayoutDirection()`.

**Topics:**
- Global State: [QPainter::setLayoutDirection()](https://doc.qt.io/qt-6.8/qpainter.html#setLayoutDirection), [Qt::LayoutDirection](https://doc.qt.io/qt-6.8/qt.html#LayoutDirection-enum)

**Key Takeaway: Alignment Mirroring**
- When drawing text via `QPainter::drawText(QRect, int flags, QString)` using standard alignment flags (e.g. `Qt::AlignLeft`), changing the layout direction to `Qt::RightToLeft` automatically "mirrors" the alignment. `Qt::AlignLeft` visually behaves like `Qt::AlignRight`.
- This is a critical feature for building UIs that support RTL languages (like Arabic or Hebrew) because it prevents you from needing to manually rewrite all of your layout logic; Qt simply inverts the horizontal text flow automatically.
- *Developer Discovery*: If you bypass the standard alignment flags and use the `QTextOption` overload of `drawText` without explicitly configuring it for RTL, the text will ignore the painter's Layout Direction and fall back to LTR!

```mermaid
classDiagram
    class QPainter {
        +setLayoutDirection(direction: Qt::LayoutDirection) void
        +drawText(rectangle: QRectF, flags: int, text: QString) void
        +drawText(rectangle: QRectF, text: QString, option: QTextOption) void
    }
    
    class Qt {
        <<namespace>>
    }
    
    class LayoutDirection {
        <<enumeration>>
        LeftToRight
        RightToLeft
        LayoutDirectionAuto
    }
    
    class AlignmentFlag {
        <<enumeration>>
        AlignLeft
        AlignRight
        AlignVCenter
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    Qt *-- LayoutDirection : contains
    Qt *-- AlignmentFlag : contains
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> LayoutDirection : Uses
    CanvasWidget ..> AlignmentFlag : Uses
    
    QPainter ..> LayoutDirection : Receives
```

![Method: QPainter::setLayoutDirection](https://img.shields.io/badge/Method-QPainter%3A%3AsetLayoutDirection-blue)

---

## qPainter_015
- [qPainter_015](../qPainter_015)
- **Brief**: Deep dive into `QPen` styling including custom dash patterns, line caps, and corner joins.

**Topics:**
- Pen Caps: `Qt::FlatCap`, `Qt::SquareCap`, `Qt::RoundCap`
- Pen Joins: `Qt::MiterJoin`, `Qt::BevelJoin`, `Qt::RoundJoin`
- Dash Patterns: `QPen::setDashPattern()`

**Key Takeaway: Cap Bleed**
- A critical detail of `Qt::SquareCap` and `Qt::RoundCap` is that they extend *past* the mathematical start and end coordinates of the line by exactly half of the pen's width. If drawing thick lines near the edge of a clipping box or bounding rect, `Qt::FlatCap` is the only safe cap that remains strictly inside the geometric coordinates.

**Key Takeaway: Custom Dashes**
- Rather than relying on the standard `Qt::DashLine` or `Qt::DotLine`, you can feed `setDashPattern()` an exact sequence of multipliers (e.g. `[4.0, 2.0, 1.0, 2.0]` for solid, empty, solid, empty). These numbers are multiplied by the `QPen`'s width to determine the exact pixel length of each dash and gap, allowing you to perfectly recreate complex SVG strokes or Morse-code-style borders.

```mermaid
classDiagram
    class QPainter {
        +setPen(pen: QPen) void
        +drawLine(x1: int, y1: int, x2: int, y2: int) void
        +drawPolyline(points: QPolygonF) void
    }
    
    class QPen {
        +setWidth(width: int) void
        +setCapStyle(style: PenCapStyle) void
        +setJoinStyle(style: PenJoinStyle) void
        +setDashPattern(pattern: QList) void
    }
    
    class Qt {
        <<namespace>>
    }
    
    class PenCapStyle {
        <<enumeration>>
        FlatCap
        SquareCap
        RoundCap
    }
    
    class PenJoinStyle {
        <<enumeration>>
        MiterJoin
        BevelJoin
        RoundJoin
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    Qt *-- PenCapStyle : contains
    Qt *-- PenJoinStyle : contains
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QPen : Instantiates
    CanvasWidget ..> PenCapStyle : Uses
    CanvasWidget ..> PenJoinStyle : Uses
    
    QPainter ..> QPen : Receives
    QPen ..> PenCapStyle : Receives
    QPen ..> PenJoinStyle : Receives
```

![Method: QPen::setWidth](https://img.shields.io/badge/Method-QPen%3A%3AsetWidth-blue) ![Method: QPen::setCapStyle](https://img.shields.io/badge/Method-QPen%3A%3AsetCapStyle-blue) ![Method: QPen::setJoinStyle](https://img.shields.io/badge/Method-QPen%3A%3AsetJoinStyle-blue) ![Method: QPen::setDashPattern](https://img.shields.io/badge/Method-QPen%3A%3AsetDashPattern-blue)

---

## qPainter_016
- [qPainter_016](../qPainter_016)
- **Brief**: Exploring `QBrush` patterns, manipulating transparent vs opaque background modes, and controlling the brush origin to anchor patterns to shapes rather than the window.

**Topics:**
- Brush Patterns: `Qt::CrossPattern`, `Qt::DiagCrossPattern`
- Background Modes: `Qt::TransparentMode` (default) vs `Qt::OpaqueMode`
- Brush Origin: `QPainter::setBrushOrigin()`

**Key Takeaway: The "Opaque" Text Gotcha**
- When `setBackgroundMode(Qt::OpaqueMode)` is active, it doesn't just fill the empty space in hatched brush patterns—it also draws a solid colored box behind all text rendered with `drawText()`. This is highly useful for making text readable over busy backgrounds, but can be a surprise if left active accidentally. Always use `save()` and `restore()`!

**Key Takeaway: The Sliding Window Effect**
- By default, brush patterns are universally anchored to `(0,0)` of the window. If you draw a shape, it acts like a sliding window revealing a static wallpaper behind it. To make a pattern "stick" to a shape as it moves across the screen, you must use `setBrushOrigin()` to anchor the texture's starting point to the shape's local coordinates.

```mermaid
classDiagram
    class QPainter {
        +setBrush(brush: QBrush) void
        +setBackgroundMode(mode: BGMode) void
        +setBackground(brush: QBrush) void
        +setBrushOrigin(x: int, y: int) void
        +drawRect(x: int, y: int, width: int, height: int) void
        +drawText(x: int, y: int, text: QString) void
    }
    
    class QBrush {
        +QBrush(color: Qt::GlobalColor, style: Qt::BrushStyle)
    }
    
    class Qt {
        <<namespace>>
    }
    
    class BrushStyle {
        <<enumeration>>
        SolidPattern
        CrossPattern
        DiagCrossPattern
    }
    
    class BGMode {
        <<enumeration>>
        TransparentMode
        OpaqueMode
    }
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    Qt *-- BrushStyle : contains
    Qt *-- BGMode : contains
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QBrush : Instantiates
    CanvasWidget ..> BrushStyle : Uses
    CanvasWidget ..> BGMode : Uses
    
    QPainter ..> QBrush : Receives
    QPainter ..> BGMode : Receives
```

![Method: QPainter::setBrush](https://img.shields.io/badge/Method-QPainter%3A%3AsetBrush-blue) ![Method: QPainter::setBackgroundMode](https://img.shields.io/badge/Method-QPainter%3A%3AsetBackgroundMode-blue) ![Method: QPainter::setBackground](https://img.shields.io/badge/Method-QPainter%3A%3AsetBackground-blue) ![Method: QPainter::setBrushOrigin](https://img.shields.io/badge/Method-QPainter%3A%3AsetBrushOrigin-blue) ![Method: QPainter::drawText](https://img.shields.io/badge/Method-QPainter%3A%3AdrawText-blue)

---

## qPainter_017
- [qPainter_017](../qPainter_017)
- **Brief**: Mastering smooth vector color transitions across lines, circles, and cones using Qt's gradient classes and spread modes.

**Topics:**
- Linear Gradients: `QLinearGradient`
- Radial Gradients: `QRadialGradient`
- Conical Gradients: `QConicalGradient`
- Gradient Spread Behaviors: `QGradient::PadSpread`, `QGradient::RepeatSpread`, `QGradient::ReflectSpread`

**Key Takeaway: The Brush Pipeline**
- Gradients in Qt are not independent painting operations. They are complex color patterns fed directly into a standard `QBrush`. Once a gradient is assigned to a brush, standard primitives like `drawRect` and `drawEllipse` will automatically paint using the gradient's interpolation mathematics.

**Key Takeaway: Spread Modes**
- If a shape is physically larger than the geometric bounding box defined by a `QLinearGradient` or `QRadialGradient`, the `setSpread()` property determines what happens to the remaining empty space. `PadSpread` (default) simply holds and stretches the final color value. `RepeatSpread` performs a harsh loop back to 0%. `ReflectSpread` bounces back and forth, smoothly interpolating forward and backward for seamless repeating textures.

```mermaid
classDiagram
    class QPainter {
        +setBrush(brush: QBrush) void
        +drawRect(x: int, y: int, width: int, height: int) void
        +drawEllipse(x: int, y: int, width: int, height: int) void
    }
    
    class QBrush {
        +QBrush(gradient: QGradient)
    }
    
    class QGradient {
        +setColorAt(position: qreal, color: QColor) void
        +setSpread(spread: Spread) void
    }
    
    class QLinearGradient {
        +QLinearGradient(x1: qreal, y1: qreal, x2: qreal, y2: qreal)
    }
    
    class QRadialGradient {
        +QRadialGradient(cx: qreal, cy: qreal, radius: qreal)
    }
    
    class QConicalGradient {
        +QConicalGradient(cx: qreal, cy: qreal, angle: qreal)
    }
    
    class Spread {
        <<enumeration>>
        PadSpread
        ReflectSpread
        RepeatSpread
    }
    
    QGradient <|-- QLinearGradient
    QGradient <|-- QRadialGradient
    QGradient <|-- QConicalGradient
    
    QGradient *-- Spread : contains
    
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QLinearGradient : Instantiates
    CanvasWidget ..> QRadialGradient : Instantiates
    CanvasWidget ..> QConicalGradient : Instantiates
    CanvasWidget ..> QBrush : Instantiates
    
    QPainter ..> QBrush : Receives
    QBrush ..> QGradient : Receives
```

![Method: QPainter::setBrush](https://img.shields.io/badge/Method-QPainter%3A%3AsetBrush-blue) ![Method: QPainter::drawRect](https://img.shields.io/badge/Method-QPainter%3A%3AdrawRect-blue) ![Method: QPainter::drawEllipse](https://img.shields.io/badge/Method-QPainter%3A%3AdrawEllipse-blue) ![Method: QGradient::setColorAt](https://img.shields.io/badge/Method-QGradient%3A%3AsetColorAt-blue) ![Method: QGradient::setSpread](https://img.shields.io/badge/Method-QGradient%3A%3AsetSpread-blue)

---

## qPainter_018
- [qPainter_018](../qPainter_018)
- **Brief**: Introduction to Affine Transformations. Instead of drawing shapes at different geometric coordinates, we move, scale, rotate, and shear the coordinate system itself while drawing the shapes at `(0,0)`.

**Topics:**
- Translation: `QPainter::translate()`
- Scaling: `QPainter::scale()`
- Rotation: `QPainter::rotate()`
- Shearing: `QPainter::shear()`

**Key Takeaway: The Inverted Y-Axis Gotcha**
- In standard Cartesian math (where Y points up), a positive horizontal shear shifts the *top* of a shape to the right, creating a right-leaning shape (like *italic* text).
- Because Qt's Y-axis points **down**, positive Y values push the X coordinate to the right. This means the *bottom* of the shape is pushed to the right, causing the shape to visually lean to the **left**! To create a standard right-leaning shear in Qt, you must pass a negative horizontal shear value.

```mermaid
classDiagram
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class QWidget {
        #paintEvent(event: QPaintEvent*) virtual void
    }
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
        -drawGridAndRect(painter: QPainter&, label: QString) void
    }
    
    class QPainter {
        +translate(dx: qreal, dy: qreal) void
        +scale(sx: qreal, sy: qreal) void
        +rotate(angle: qreal) void
        +shear(sh: qreal, sv: qreal) void
        +save() void
        +restore() void
    }
    
    CanvasWidget ..> QPainter : Instantiates
```

![Method: QPainter::translate](https://img.shields.io/badge/Method-QPainter%3A%3Atranslate-blue) ![Method: QPainter::scale](https://img.shields.io/badge/Method-QPainter%3A%3Ascale-blue) ![Method: QPainter::rotate](https://img.shields.io/badge/Method-QPainter%3A%3Arotate-blue) ![Method: QPainter::shear](https://img.shields.io/badge/Method-QPainter%3A%3Ashear-blue)

---

## qPainter_019
- [qPainter_019](../qPainter_019)
- **Brief**: Peeling back the abstraction layer of `QPainter`'s convenience transformation methods to inspect and manually manipulate the underlying `QTransform` matrix engine.

**Topics:**
- Inspecting Matrix State: `QPainter::worldTransform()`
- Resetting Matrix State: `QPainter::resetTransform()`
- Overriding Matrix State: `QPainter::setWorldTransform()`
- `QTransform` API

**Key Takeaway: The `QTransform` Blueprint**
- `QPainter` drives its coordinate system using a 3x3 Affine Transformation matrix. Every time you call a convenience method like `painter.rotate()`, Qt performs trigonometry to update 4 cells in this matrix simultaneously.

| Matrix Cell | Qt Method Equivalent | What it controls | Default (Identity) |
| :---: | :--- | :--- | :---: |
| **`m11`** | `scale(sx, ...)` | **Horizontal Scale** (X stretch) | `1.0` |
| **`m12`** | `shear(..., sv)` | **Vertical Shear** (Skews Y based on X) | `0.0` |
| **`m13`** | *(Advanced)* | Horizontal Projection (Perspective) | `0.0` |
| **`m21`** | `shear(sh, ...)` | **Horizontal Shear** (Skews X based on Y) | `0.0` |
| **`m22`** | `scale(..., sy)` | **Vertical Scale** (Y stretch) | `1.0` |
| **`m23`** | *(Advanced)* | Vertical Projection (Perspective) | `0.0` |
| **`m31`** | `translate(dx, ...)` | **Horizontal Translation** (Move X) | `0.0` |
| **`m32`** | `translate(..., dy)` | **Vertical Translation** (Move Y) | `0.0` |
| **`m33`** | *(Advanced)* | Global Scale / Projection factor | `1.0` |

```mermaid
classDiagram
    QPaintDevice <|-- QWidget
    QObject <|-- QWidget
    QWidget <|-- CanvasWidget
    
    class CanvasWidget {
        +~CanvasWidget() override
        #paintEvent(event: QPaintEvent*) override void
        -printMatrix(label: QString, t: QTransform) void
    }
    
    class QPainter {
        +worldTransform() QTransform
        +setWorldTransform(matrix: QTransform, combine: bool) void
        +resetTransform() void
        +translate(dx: qreal, dy: qreal) void
        +scale(sx: qreal, sy: qreal) void
    }
    
    class QTransform {
        +translate(dx: qreal, dy: qreal) QTransform
        +scale(sx: qreal, sy: qreal) QTransform
        +rotate(angle: qreal) QTransform
        +shear(sh: qreal, sv: qreal) QTransform
        +m11() qreal
        +m12() qreal
        +m13() qreal
        +m21() qreal
        +m22() qreal
        +m23() qreal
        +m31() qreal
        +m32() qreal
        +m33() qreal
    }
    
    CanvasWidget ..> QPainter : Instantiates
    CanvasWidget ..> QTransform : Inspects
    QPainter ..> QTransform : Returns / Receives
```

![Method: QPainter::worldTransform](https://img.shields.io/badge/Method-QPainter%3A%3AworldTransform-blue) ![Method: QPainter::setWorldTransform](https://img.shields.io/badge/Method-QPainter%3A%3AsetWorldTransform-blue) ![Method: QPainter::resetTransform](https://img.shields.io/badge/Method-QPainter%3A%3AresetTransform-blue)