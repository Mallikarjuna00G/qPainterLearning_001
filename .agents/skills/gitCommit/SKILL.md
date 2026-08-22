---
name: gitCommit
description: Standardized procedure for committing changes to git without pushing.
---

When the user asks you to commit changes, or when the `gitCommit` skill is triggered, you MUST strictly follow this exact sequence using the `run_command` tool:
1. Run `git status` to see what has changed.
2. Run `git add <files>` to stage the necessary files (or `git add .` if appropriate).
3. Run `git commit -m "<good_descriptive_message>"` to commit the changes.
4. Run `git status` again to confirm the working tree is clean.
5. You MUST NOT run `git push`. Leave pushing entirely to the user.
