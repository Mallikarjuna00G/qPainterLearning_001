# QPainter Mastery 🎨

Welcome to the **QPainter Mastery** repository! 

This repository is the final culmination of a massive 41-project curriculum dedicated entirely to mastering 2D graphics rendering in the Qt framework using `QPainter`.

Over the course of this journey, we have systematically covered everything from drawing basic shapes and text, to complex matrix transformations, real-time pixel manipulation, and multi-format document serialization (SVG, PNG, PDF).

## 🗺️ Documentation & Progress Tracking

The repository is highly documented. Please refer to the following trackers in the `docs/` directory to navigate the projects:

1. **[Roadmap Checklist](docs/roadmapChecklist.md)**: A chronological, day-by-day curriculum outlining the learning path and linking to the specific projects that implement those concepts.
2. **[List of Projects](docs/listOfProjects.md)**: A detailed encyclopedia of all 41 projects. For each project, you will find a brief summary, key takeaways, and a Mermaid class diagram mapping its architecture.
3. **[Method Tracker (Heatmap)](docs/methodTracker.md)**: A comprehensive checklist tracking our usage of every single `QPainter` method across the entire Qt API to guarantee 100% conceptual coverage.

## 🚀 Key Milestones

- **Projects 01-15**: Core geometry, brushes, pens, and font rendering.
- **Projects 16-25**: QPainterPaths, Bézier curves, and complex polygon manipulation.
- **Projects 26-35**: Coordinate system transformations (Translate, Rotate, Scale) and logical viewports.
- **Projects 36-38**: Composition modes, clipping, and `QImage` memory buffer manipulation.
- **Projects 39-41**: Hardware-agnostic serialization to `QSvgGenerator` (Vector XML), `QImage` (Raster PNG), and `QPdfWriter` (High-Res Print PDF).

## 🛠️ Building the Projects

Every project is completely self-contained in its own directory with a dedicated `CMakeLists.txt` file.

To run a project (e.g., `qPainter_041`):
1. Open Qt Creator.
2. Navigate to `File > Open File or Project...`
3. Select the `CMakeLists.txt` inside the specific project folder (e.g., `qPainter_041/CMakeLists.txt`).
4. Select your Qt Kit (e.g., Qt 6.8.0 GCC).
5. Build and run!
