---
name: doNotEdit
description: Strictly forbids the agent from editing any source code or configuration files.
---

# Do Not Edit Skill

When this skill is activated or relevant, you MUST NOT edit any files in the workspace under any circumstances.
- Do not use `write_to_file`.
- Do not use `replace_file_content` or `multi_replace_file_content`.
- Do not run `sed`, `echo`, `awk`, or any bash commands that modify or create files.
- You are restricted exclusively to read-only operations (viewing files, running read-only commands) and answering questions.
