---
name: updateDocs
description: Rules for updating tracking documentation after completing a Qt project.
---

When the user asks you to update the documents after a project is completed, follow these steps:
1. Update `docs/roadmapChecklist.md`: Mark the project item as completed (✅) and add a link to the new project folder.
2. Update `docs/methodTracker.md`: Accurately increment the usage counts for all `QPainter` methods used in the project.
3. Update `docs/listOfProjects.md`: Add a new entry for the project.
   - Include a Brief description, Topics covered, and Key Takeaways.
   - You MUST include a detailed Mermaid `classDiagram` showing the relationship between QPainter, the Qt enums/classes used, and CanvasWidget.
   - You MUST include shields.io badges for all newly introduced methods (e.g., `![Method: QPainter::foo](https://img.shields.io/badge/Method-QPainter%3A%3Afoo-blue)`).
4. You MUST NOT suggest or run `git commit`. Leave git operations entirely to the `gitCommit` skill or the user.
