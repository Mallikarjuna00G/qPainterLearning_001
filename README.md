# QPainter Learning Sandbox

This repository is dedicated to learning [QPainter](https://doc.qt.io/qt-6.8/qpainter.html) in Qt 6.8 through structured, hands-on executable examples.

## Project Structure

- **[learningPlan.md](docs/learningPlan.md)**: Outlines the high-level intent and goals of the learning project.
- **[roadmapChecklist.md](docs/roadmapChecklist.md)**: A detailed 7-Day Precision Vector Tracker checklist mapped to every topic in the official `QPainter` documentation.

## Goals

1. **Precision Vector Control**: Master Qt's vector drawing pipeline, primitive drawing methods, transform matrices, and path stroking.
2. **Procedural Rendering**: Build a TikZ-style mini-engine rendering nodes, labels, and Bézier curves.
3. **Multi-device Export**: Render procedural graphics to widgets, SVGs, and high-quality PDFs.

## How to Run

Since these projects are standalone CMake executables, the easiest way to run them is directly through the IDE:
1. Open **Qt Creator**.
2. Select **File > Open File or Project...**
3. Navigate into a specific project folder (e.g., `qPainter_001`) and select its `CMakeLists.txt` file.
4. Configure the project using your installed Qt Kit.
5. Click the green **Run** button (or press `Ctrl+R`) to build and launch the application.

## Development Environment

<p align="left">
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" width="48" height="48" alt="C++ Logo" />&nbsp;
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/qt/qt-original.svg" width="48" height="48" alt="Qt Logo" />&nbsp;
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cmake/cmake-original.svg" width="48" height="48" alt="CMake Logo" />&nbsp;
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/llvm/llvm-original.svg" width="48" height="48" alt="LLVM/Clang Logo" />&nbsp;
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/git/git-original.svg" width="48" height="48" alt="Git Logo" />&nbsp;
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/linux/linux-original.svg" width="48" height="48" alt="Linux Logo" />&nbsp;
</p>

This project is built and tested using the following toolchain:

| Tool | Version |
| :--- | :--- |
| **Qt** | `6.8.3` |
| **Qt Creator** | `20.0.1` |
| **C++ Standard**| `C++17` |
| **Compiler** | `Clang 19.1.7` |
| **CMake** | `3.31.6` |
| **Ninja** | `1.12.1` |
| **Git** | `2.47.3` |

## Topics Covered

As we progress through the repository, we are actively logging the specific Qt classes and concepts we have proven in code.

**Tech Stack:**
![C++17](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-6.8.3-41CD52?logo=qt&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.31.6-064F8C?logo=cmake&logoColor=white)
![Ninja](https://img.shields.io/badge/Ninja-1.12.1-black)
![LLVM/Clang](https://img.shields.io/badge/LLVM%2FClang-19.1.7-blue)
![Git](https://img.shields.io/badge/Git-2.47.3-F05032?logo=git&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?logo=linux&logoColor=black)

**Core Drawing Pipeline:**
![QPainter](https://img.shields.io/badge/Core-QPainter-purple)
![QPaintDevice](https://img.shields.io/badge/Core-QPaintDevice-purple)
![QWidget](https://img.shields.io/badge/UI-QWidget-brightgreen)
![QPaintEvent](https://img.shields.io/badge/Event-QPaintEvent-blue)
![QResizeEvent](https://img.shields.io/badge/Event-QResizeEvent-blue)
