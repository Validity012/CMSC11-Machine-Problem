# Lee Go! Scrum Playbook

A beginner's guide to how the team will run Scrum on Taiga from November 12 until the Final Build sprint ends on December 3, 2026.

## 1. Scrum in five minutes

Scrum means building the game in short, fixed time boxes called sprints, and ending each one with something that runs. You do not plan everything up front. You pick a small slice of work, finish it, show it, and learn from it before picking the next slice.

Every sprint repeats four routines: planning, a daily standup, a review, and a retrospective. Section 6 explains each one.

| Term | What it means for us |
| --- | --- |
| Product backlog | The full to-do list for the game, ordered by importance. In Taiga it is the Backlog page. |
| User story | One feature written from the player's view, such as "Lee can jump over gaps." In Taiga it is a User Story. |
| Task | A piece of a story that one person can finish in about a day. In Taiga it is a card on the Taskboard. |
| Story points | A relative size for a story (1, 2, 3, 5). A bigger number means more work or more unknowns. Points are not hours. |
| Sprint | A fixed time box with one goal. Ours run about a week. In Taiga it is a Sprint. |
| Sprint goal | One sentence saying what must work when the sprint ends. |
| Increment | The working build at the end of a sprint. It must compile and run. |
| Velocity | The points the team actually finishes in a sprint. We use it to plan the next sprint. |

## 2. Team roles

Scrum has three roles, and your project titles map onto them: the Project Manager acts as Product Owner, and all three of you are Developers. The Product Owner decides what gets built and in what order. The team decides how much it can finish in a sprint.

| Role | Who | What they do |
| --- | --- | --- |
| Product Owner (Project Manager) | Chrivin C. Omega | Owns the Backlog and its order. Writes and prioritizes user stories. Decides when a story meets its acceptance notes. Cuts scope when time runs short. |
| Scrum Master | Chrivin C. Omega | Runs planning, standups, review, and retro. Keeps Taiga accurate. Removes blockers. Reminds the team of the rules in this playbook. |
| Art and Dev Lead | Rich S. Plaza | Makes the pixel art and builds game code. |
| QA and Music Lead | Joseph Franco Senaca | Tests each build before the sprint review, checks stories against the Definition of Done, and makes the music and sound effects. |
| Developers | All three members | Estimate stories, break them into tasks, pick up tasks, write code and assets, review each other's work. |

The Scrum Master does not boss anyone. The job is to keep the process working. Rotate it each sprint if the team prefers.

## 3. Sprint plan

The team runs three sprints that end on December 3. Each has one goal, and Core Prototype and Final Build overlap from Nov 23 to Nov 26. The closed "Planning & Proposal" sprint (Nov 8 to 10) counts as Sprint 0.

| Sprint | Dates | Sprint goal | What we demo at the review |
| --- | --- | --- | --- |
| 1: Greybox | Nov 12 to Nov 20 | Lee runs and jumps on a blockout level with tile collision. | The build opens and Lee moves, jumps, and collides with tiles. |
| 2: Core prototype | Nov 21 to Nov 26 | A player can start from the launcher, open the main menu, and play Level 1 with bubbles, a walker enemy, hearts, and lives. | The Core Prototype (Deliverable 2), sprint ends Nov 26. |
| 3: Final build | Nov 23 to Dec 3 | The full game runs from the installer to the ending: three levels, the Goalie boss, save and scores, and the final report. | A full run and the defense rehearsal, before the final defense. |

A sprint goal is a promise about what works, not a list of tasks. If a sprint ends and the goal is not met, say so at the review and move the unfinished stories to the next sprint.

## 4. Taiga setup

Do these steps once, in order, so the board matches the plan. Menu names can differ slightly by Taiga version.

1. **Fix the sprints.** The board already has the three sprints: Greybox (Nov 12 to 20), Core Prototype (Nov 21 to 26), and Final Build (Nov 23 to Dec 3). Epics are the workstreams, so the old UI/UX, Art Assets, and Project Management sprints are no longer used.
2. **Create epics.** An epic is a group of related stories, not a time box. Turn on Epics in Admin if you do not see them. Create these six: Engine, Gameplay, UI/UX, Art and Audio, Delivery, and Project Management.
3. **Add the user stories.** Create the stories from section 5 on the Backlog page. Set the points, link each story to its epic, and drag it into its sprint.
4. **Write a "Done when" line.** Put one sentence in each story's description saying how you will know it works, such as "Done when Lee lands on a tile and cannot fall through it."
5. **Break stories into tasks at sprint planning.** Open the sprint's Taskboard and add tasks under each story. A task is about a day of work, starts with a verb, and has one person in the assignee field. Do not put names in titles.
6. **Use the columns the same way every time.** See the table below.
7. **Finish stories, not sprints.** Taiga marks a sprint closed when all its stories are Done. At the review, move anything unfinished to the next sprint.

| Column | Meaning |
| --- | --- |
| New | Not started. |
| In Progress | Someone is working on it. Keep it to two cards per person. |
| Ready for Test | The code or asset is on a branch and ready for review. The QA Lead tests it. |
| Done or Closed | Stories end at Done and tasks end at Closed, once the card meets the Definition of Done in section 7. Only the Scrum Master moves a card here. |
| Needs Info | Blocked. Add a comment saying what is missing, and tell the Scrum Master. |

## 5. Starting backlog

### Epics

An epic is a group of related stories. The six epics below hold 44 stories and 95 points. The five game epics hold 25 of the stories and 67 of the points, and Project Management holds the rest.

| Epic | What it covers | Done when | Stories | Points |
| --- | --- | --- | --- | --- |
| Engine | Window, game loop, player movement, tile collision, level loading | Lee runs, jumps, and collides with tiles on a map loaded from a text file | 5 | 12 |
| Gameplay | Levels, enemies, bubbles, hearts, lives, items, and the Goalie boss | All three levels can be played from the start to the ending scene | 10 | 27 |
| UI/UX | Console launcher and main menu | A player can start, continue, or quit, and bad input never crashes the launcher or menu | 2 | 6 |
| Art and Audio | Pixel art for Lee, tiles, enemies, the Goalie, and items, plus music and sound effects | Every character and tile uses final pixel art, and music plays | 3 | 9 |
| Delivery | Installer, save and continue, high scores, final report, and progress video | The installer works on a clean computer, progress and scores persist, and the report is submitted | 5 | 13 |
| Project Management | Defense practice and the project-management work: documents, Taiga, GitHub, and reviews | Every member can explain the code, and the project documents are up to date | 19 | 28 |

### Stories

The table lists the game stories as they stand on the Taiga board, with the card numbers #25 to #49 and #75. The project-management stories (#50 to #67) live only in Taiga. The points are first guesses, so replace them with your real velocity after Sprint 1.

For sizing, call 1 point about 2 hours of one person's focused work. At 2 hours a day each, the team has about 3 points a day. Taiga holds 35 points in Greybox, 26 in Core Prototype, and 30 in Final Build, so check each sprint's points against its days at planning. The Should and Could stories are the first to cut.

| Story | Epic | Points | Priority | Sprint |
| --- | --- | --- | --- | --- |
| Project files and raylib spike | Engine | 2 | Must | 1 |
| Main game loop and window | Engine | 2 | Must | 1 |
| Player movement and controls | Engine | 3 | Must | 1 |
| Tile collision | Engine | 3 | Must | 1 |
| Environment blockout | Gameplay | 2 | Must | 2 |
| Console launcher with validated input | UI/UX | 3 | Must | 2 |
| Main menu | UI/UX | 3 | Must | 2 |
| Level file loader | Engine | 2 | Must | 2 |
| Level 1 layout | Gameplay | 2 | Must | 2 |
| Bubbles, HUD, and 1UP at 70 | Gameplay | 2 | Must | 2 |
| Walker enemy and stomp | Gameplay | 3 | Must | 2 |
| Hearts and lives | Gameplay | 2 | Must | 2 |
| Pixel art: Lee and tiles | Art and Audio | 3 | Must | 1 |
| Installer skeleton and clean-PC test | Delivery | 2 | Must | 2 |
| Progress video | Delivery | 2 | Should | 2 |
| Towel glide | Gameplay | 2 | Must | 3 |
| Toothpaste projectile | Gameplay | 2 | Must | 3 |
| Levels 2 and 3 | Gameplay | 5 | Must | 3 |
| Goalie boss | Gameplay | 5 | Must | 3 |
| Ending scene | Gameplay | 2 | Must | 3 |
| Pixel art: enemies, Goalie, items | Art and Audio | 3 | Must | 2 |
| Final installer | Delivery | 1 | Must | 3 |
| Final report and screenshots | Delivery | 5 | Must | 3 |
| Defense practice | Project Management | 2 | Must | 3 |
| Save, continue, and high scores | Delivery | 3 | Should | 3 |
| Music and sound effects | Art and Audio | 3 | Could | 3 |

Each story above is a card on the Taiga board with the same name, so you can find it by its number there.

## 6. How a sprint runs

Each sprint has the same four routines, and the whole set costs under two hours per sprint. The Scrum Master schedules them and keeps them short.

| Routine | When | Length | What happens |
| --- | --- | --- | --- |
| Sprint planning | First day of the sprint | 30 minutes | Read the sprint goal. Pull stories from the top of the Backlog until the points match the team's capacity. Break each story into tasks and assign them. |
| Daily standup | Every day, posted in the group chat by 10:00 | 2 minutes to write | Each person posts the three lines below. Talk live only if someone is blocked. |
| Sprint review | Last day of the sprint | 20 minutes | Run the build together. The Product Owner accepts a story only if it works and meets its "Done when" line. Move unfinished stories to the next sprint. |
| Retrospective | Right after the review | 15 minutes | Each person answers: what went well, what slowed us down, and one thing to change next sprint. Write the change on the Taiga wiki. |

Copy this into the chat each day:

```text
Done since last post:
Doing today:
Blocked by:
```

At planning, finish by checking one thing: does the total of the pulled stories fit the points you can really do? If not, remove the lowest-priority story before the sprint starts, not halfway through.

## 7. Team rules

These rules decide when a story may enter a sprint, when it counts as finished, and how code moves from a branch to `main`.

### Definition of Ready

A story may be pulled into a sprint only if:

- It has a "Done when" line in its description.
- It has points and an epic.
- Nobody is waiting on an unanswered question about it.
- It can be finished within one sprint. If not, split it.

### Definition of Done

A story is Done only when all of these are true:

- It compiles with zero errors and zero warnings (`-Wall -Wextra`).
- It follows snake\_case and 4-space indentation, and every function has a comment header.
- It uses no global variables.
- A second member reviewed it and can explain it.
- The QA Lead ran the build and checked the "Done when" line.
- It is merged to `main`, and `main` still builds and runs.

### Git and Taiga workflow

1. Pull the latest `main`, then make one branch per card, named `TG-<ref>-<short-description>`, for example `TG-28-tile-collision`.
2. Start each commit message with the Taiga reference, such as `TG-28 #in-progress add tile collision check`. The GitHub webhook is on, so the commit also moves the card (see the Team Quick Guide).
3. Open a pull request and move the card to Ready for Test.
4. A second member reviews it. Merge only after the review passes.
5. The Scrum Master moves the card to Done (stories) or Closed (tasks) when the Definition of Done is met.

### Working agreements

- Everyone puts in at least 2 hours a day while finals run. Post your standup even on days you did nothing.
- If you are blocked for more than a day, move the card to Needs Info and tell the Scrum Master.
- Do not start a new task until your Ready for Test cards have a reviewer.
- Never push straight to `main`.
- Changes to the scope or the order of stories go through the Product Owner.

## 8. Tracking progress

After each sprint, add up the points of the stories that reached Done. That number is your velocity, and it replaces the guesses in section 5 when you plan the next sprint.

Taiga counts points only when a story is Done, so a 5-point story shows nothing until it is fully done. Keep stories small and close them as they finish, not all on the last day. A burndown line that stays flat and then drops at the end means work is not being closed.

| Signal | What to do |
| --- | --- |
| Halfway through a sprint, less than a third of the points are Done | The Scrum Master asks what is blocked. The Product Owner picks one story to drop. |
| A story is unfinished after two sprints | Split it into smaller stories. |
| Sprint 3 starts with more points than your velocity | Cut in this order: music and sound effects, save and high scores, then shorten Levels 2 and 3. |
| A teammate misses two standups in a row | The Scrum Master asks directly and the team moves their tasks. |

Never cut the graded deliverables: the zero-warning build, the installer, the final report, and the defense practice.
