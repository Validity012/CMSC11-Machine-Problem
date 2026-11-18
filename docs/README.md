# Project documents

The submitted record for the Lee Go! machine problem. The living version of most of this material is the [project wiki](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/home); these files are what gets handed in.

| Document | Markdown | PDF | Owner |
| --- | --- | --- | --- |
| Machine problem proposal | [proposal/proposal.md](proposal/proposal.md) | [proposal/proposal.pdf](proposal/proposal.pdf) | Chrivin |
| Scrum playbook | [playbook/scrum-playbook.md](playbook/scrum-playbook.md) | [playbook/scrum-playbook.pdf](playbook/scrum-playbook.pdf) | Chrivin |
| Team quick guide | [quick-guide/team-quick-guide.md](quick-guide/team-quick-guide.md) | [quick-guide/team-quick-guide.pdf](quick-guide/team-quick-guide.pdf) | Chrivin |
| Status report 01, 18 November | - | [reports/2026-11-18-status-report.pdf](reports/2026-11-18-status-report.pdf) | Chrivin |

## Layout

```
docs/
├── README.md
├── proposal/       proposal.md, proposal.pdf
├── playbook/       scrum-playbook.md, scrum-playbook.pdf
├── quick-guide/    team-quick-guide.md, team-quick-guide.pdf
└── reports/        YYYY-MM-DD-status-report.pdf
```

## Conventions

- One folder per document. Folder name matches the document, files use kebab-case.
- No version numbers in file names. Git history is the version.
- Reports go in `reports/`, named `YYYY-MM-DD-status-report.pdf`. They are generated from the board, so they have no Markdown source.
- When a decision changes the plan, update the playbook, the wiki, and the PDF in the same commit.
- The README at the repository root carries the build steps and the project overview.

## Where the rest lives

| Material | Location |
| --- | --- |
| Gameplay, controls, enemies | [Wiki: gameplay](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/gameplay) |
| Module layout and code standards | [Wiki: architecture](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/architecture) |
| Build, installer, save files | [Wiki: build and run](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/build-and-run) |
| Board, branches, Definition of Done | [Wiki: workflow](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/workflow) |
| Sprint dates, points, meetings | [Wiki: sprints](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/sprints) |
| Page templates | [Wiki: templates](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/templates) |
