# Lee Go! Team Quick Guide

Everything you need to work on Lee Go! with Taiga and GitHub, in plain words. Your commits update Taiga automatically.

## The big picture

We build the game in short rounds called sprints, and every piece of work is a card in Taiga. An epic holds stories, a story holds tasks, and a sprint decides when we do them.

| Word | What it means | Example from our board |
| --- | --- | --- |
| Epic | A big area of the game | #19 Engine, #20 Gameplay, #21 Art and Audio, #22 UI/UX, #23 Delivery, #24 Project Management |
| Story | One feature we deliver | #28 Tile Collision |
| Task | One small job inside a story, about a day of work. You add these yourself. | Write the function that checks if Lee touches a tile |
| Sprint | A time box where we finish a set of stories | Greybox, Core Prototype, Final Build |
| Points | How big a story is (1, 2, 3, 5). Points are not hours. | Tile Collision is 3 points |

## A card's life

&#91;embedded content: card lifecycle, 4 columns\]

A blocked task goes to Needs Info instead of sitting in In Progress. Tasks end at Closed, and stories end at Done.

## Your day-to-day

Here is one card from start to finish, using #28 Tile Collision as the example. Swap in the number of your own card.

**Use any editor you like.** VS Code, Vim, or anything else you already know is fine. Set it to insert 4 spaces instead of tabs. The only rule is that the code must still build with zero warnings (-Wall -Wextra) before you push. The course needs a Code::Blocks project file only for the final submission, and Chrivin will set that up, so you do not need to install Code::Blocks. If you add a new `.c` file, add a matching header too, like the other modules.

**Add your own tasks.** Your cards are already set up, so you can start right away. Inside your story you can add as many tasks as you need. You decide what the work is as you build, so add a task whenever you find something that needs doing, and put your name on it.

1. **Find your card.** Your cards are already set up and assigned to you. Open the sprint Taskboard, find yours, and move it to In Progress when you start. Keep at most two cards In Progress at a time.
2. **Get the latest code.** Run `git checkout main`, then `git pull`.
3. **Make a branch.** Run `git checkout -b task-28-tile-collision`. One branch per card.
4. **Work and commit often.** Start every commit message with the card number, like `TG-28 #in-progress add tile collision check`. The first one moves your card to In Progress.
5. **Compile with zero warnings.** Build with warnings on (-Wall -Wextra) before every push. A warning means it is not ready.
6. **Push and open a pull request.** Run `git push -u origin task-28-tile-collision`, then open a pull request on GitHub.
7. **Ask for a review.** Make a commit like `TG-28 #ready-for-test`, and message a teammate in the group chat.
8. **Merge after the review passes.** The reviewer must be able to explain your code. Then merge into `main`.
9. **QA tests it.** The QA Lead runs the build and reports back. The Scrum Master then moves the card to Done, and only the Scrum Master closes cards.

## Commit messages that update Taiga

Our GitHub webhook is on, so a commit message can move a card for you. Write `TG-` and the card number, then `#` and the new status word, then what you did.

```text
TG-28 #in-progress add tile collision check
TG-28 #ready-for-test fix warnings and open pull request
```

The status word must match the kind of card. A story ends at Done, and a task ends at Closed.

| Card kind | Status | Commit word | Who sets it |
| --- | --- | --- | --- |
| Story | In progress | `#in-progress` | You |
| Story | Ready for test | `#ready-for-test` | You |
| Story | Done | `#done` | Scrum Master only |
| Task | In progress | `#in-progress` | You |
| Task | Ready for test | `#ready-for-test` | You |
| Task | Needs info | `#needs-info` | You, when blocked |
| Task | Closed | `#closed` | Scrum Master only |

If the card does not move, check these four things:

- You pushed the commit. The webhook runs on a push to GitHub, not on a local commit.
- The card number is right. Look at the number next to the card name in Taiga.
- The status word is spelled exactly as in the table, in lowercase with dashes.
- The word fits the kind of card. `#closed` does nothing on a story, and `#done` does nothing on a task.

The link goes one way only. A commit can change Taiga, but moving a card in Taiga does not change GitHub.

## Sprints and meetings

We have three sprints, and each one ends with a build that runs. Check Taiga for the live dates and points.

| Sprint | Dates | Goal | Points |
| --- | --- | --- | --- |
| Greybox | Nov 12 to Nov 20 | Lee runs and jumps on a blockout level with tile collision | 35 |
| Core Prototype | Nov 21 to Nov 26 | Start from the launcher, open the menu, and play Level 1 with bubbles, a walker enemy, hearts, and lives | 26 |
| Final Build | Nov 23 to Dec 3 | The full game runs from the installer to the ending, and the report is done | 30 |

Each sprint has the same four short meetings:

| Meeting | When | What we do |
| --- | --- | --- |
| Planning | First day of the sprint, 30 minutes | Read the sprint goal, check that the stories fit our time, and confirm who owns each card |
| Standup | Every day, posted in the group chat by 10:00 | Post the three lines below. It takes 2 minutes. |
| Review | Last day of the sprint, 20 minutes | Run the build together and check each story against its "Done when" line |
| Retro | Right after the review, 15 minutes | Say what went well, what slowed us down, and one thing to change |

Copy this into the chat each day:

```text
Done since last post:
Doing today:
Blocked by:
```

## Rules

A card is Done only when all of these are true:

- It compiles with zero errors and zero warnings (-Wall -Wextra).
- The code uses snake\_case and 4-space indentation, and every function has a comment header.
- It uses no global variables.
- A second member reviewed it and can explain it.
- The QA Lead ran the build and it works.
- It is merged into `main`, and `main` still builds.

The four things we never do:

- Never push straight to `main`.
- Never use `#done` or `#closed` unless you are the Scrum Master.
- Never leave a card in In Progress when you are stuck. Use `#needs-info` and tell the group.
- Never skip the daily standup post, even on a day you did nothing.

## Quick answers

When something goes wrong, find your situation and do the next step.

| If this happens | Do this |
| --- | --- |
| You are stuck for more than a day | Commit with `#needs-info`, or move the card to Needs Info, and post in the group chat what you are missing |
| Your card is too big | Add tasks to your story to break it down. If it still feels too big, tell the Scrum Master. |
| You found a bug | Add an Issue in Taiga with the steps to repeat it |
| You are behind | Say so in your standup post so the Project Manager can move or cut work |
| You do not know what to pick next | Check the cards assigned to you on the sprint Taskboard. If you have none left, ask the Project Manager. |
| You want to change the plan | Ask the Project Manager before you build it |

Who to ask:

| Person | Role | Ask about |
| --- | --- | --- |
| Chrivin C. Omega | Project Manager | What to build next, priorities, and cutting scope |
| Chrivin C. Omega | Scrum Master | Taiga, meetings, blockers, and getting a card to Done |
| Rich S. Plaza | Art & Dev Lead | Pixel art and game code |
| Franco Senaca&#32; | QA & Music lead | Testing, bugs, and music |
