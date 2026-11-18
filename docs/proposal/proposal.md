# Lee Go! Machine Problem Proposal

Nov 9, 2026 · @Chrivin

Lee Go! is a keyboard-only, Mario-style 2D platformer written in procedural C with raylib, built by three students over three one-week Scrum sprints.

## 1. Project Overview

Lee Go! follows Lee, a BS Computer Science student who badly needs a bath, across three levels of obstacles and enemies. The game is lighthearted, comedic, and safe for work.

| Item | Details |
| --- | --- |
| Application title | Lee Go! |
| Course | CMSC 11 Fundamentals of Programming 1 / Math 153 Computer Programming 1, First Semester AY 2026-2027 |
| Deliverable | Machine Problem, Deliverable 1: Project Proposal |
| Domain concept | 2D-Graphic Application: a traditional side-scrolling platformer inspired by Super Mario |
| Language and paradigm | C, procedural |
| Tools | Code::Blocks IDE, raylib (bundled with the program), Git, Taiga.io (Scrum board), Inno Setup (installer) |
| Team members | \[Name 1\], \[Name 2\], \[Name 3\] |
| Laboratory section | \[Section\] |
| Laboratory instructor | \[Instructor Name\] |
| Date submitted | November 9, 2026 |

The course specification lists traditional 2D games such as Pac-Man and Space Invaders as target domains and allows external graphics libraries such as raylib when they are packaged with the program (Deliverable 4). We are asking the instructor to confirm that a Mario-style platformer built on raylib fits this domain.

## 2. Story, Objective and Win/Lose Conditions

Lee has not showered in far too long, and every step toward the bathroom is blocked by something. Each of the three levels is a stage of his journey, and each hides an item he needs. In the final level the bath is guarded by a hockey goalie, the Goalie.

**Ending scene.** After Lee defeats the Goalie, the game ends with a short scene kept strictly safe for work:

> **Goalie:** But that's my bath :< \
**Lee:** Maybe the real bath was the friends we made along the way.

The scene closes with both characters sharing the bath peacefully, followed by the credits.

| Rule | Details |
| --- | --- |
| Objective | Guide Lee through all three levels, collect the item in each, and reach the bath |
| Win condition | Defeat the Goalie in Level 3, finish the ending scene, and reach the bath |
| Health | Lee has a health bar. Each hit from an enemy, hazard, or Goalie attack removes one health point. |
| Lives | Lee starts with 3 lives. Emptying the health bar or falling into a pit costs one life and respawns Lee at the start of the level. |
| Lose condition | Losing all lives ends the run on the Game Over screen |
| Extra life (1UP) | Popping 70 bubbles grants one extra life, repeating at every 70 bubbles |
| Score | High scores combine total completion time and total bubbles popped. Every entry belongs to Lee, so no name entry is needed. |

## 3. Gameplay Mechanics

The game is fully keyboard-controlled. No mouse input is used anywhere, which keeps the input layer small and matches the Mario-style feel.

### 3.1 Player Controls

| Action | Key |
| --- | --- |
| Move left / right | Left and Right arrow keys (or A / D) |
| Jump | Space (hold for a higher jump) |
| Glide (after obtaining the towel) | Hold Space while in the air |
| Shoot (after obtaining the toothpaste) | X |
| Pause | P or Esc |
| Menu navigation | Up/Down arrows and Enter |

### 3.2 Core Mechanics

1. **Movement and platforming.** Lee runs, jumps, and lands on tile platforms with gravity and grid-based collision.
2. **Stomp attack.** As in Super Mario, Lee defeats walking enemies by jumping on them. Touching an enemy from the side or below costs one health point.
3. **Health and lives.** A health bar absorbs hits. When it empties, Lee loses a life and respawns at the start of the level.
4. **Bubble popping (replaces coins).** Bubbles float around each map and pop on touch. The total carries across the run, and every 70 bubbles awards a 1UP.
5. **Special items.** Each level holds one required item (see Section 4). Items unlock abilities or act as keys.
6. **Projectile attack.** From Level 2, Lee fires toothpaste at enemies and the Goalie. Fire rate is unlimited but limited by a short cooldown.
7. **Side-scrolling camera.** The camera follows Lee across maps wider than the screen.
8. **Goalie boss fight.** The final level features a boss with hit points and a learnable attack pattern.

## 4. Levels, Items and Enemies

The base version has three short levels, each playable in roughly one to two minutes. Lee only reaches the bath at the very end of the game; the earlier levels end by opening a door or moving to the next stage.

| Level | Theme | Item | Effect | Level end |
| --- | --- | --- | --- | --- |
| 1 | Campus / dorm | Towel | Grants the glide ability for the rest of the game | Door leading to a locker |
| 2 | Bathroom corridor | Toothpaste (shampoo is the alternative) | Grants a projectile attack with a cooldown | Door to the next stage |
| 3 | Ice rink / arena | Soap | The key to the bath; required to open the way | The bath, guarded by the Goalie |

### Enemies and obstacles

| Type | Behavior | How Lee deals with it |
| --- | --- | --- |
| Walker | Patrols a platform back and forth | Stomp it, or hit it with a projectile |
| Spike hazard | Stationary | Cannot be stomped. Jump over it. |
| The Goalie (final boss) | Moves forward and backward and fires dirt or pucks along both the x and y axes. The final projectile type is decided during development. | Learn the pattern, dodge, and hit with projectiles until its hit points run out |

Pits, platform gaps, and floating bubbles complete each level. Bouncy obstacles and additional enemy types are stretch goals.

## 5. Game Flow and Screens

The program starts in a short console launcher, then opens the game window. The launcher is where the program's validated `scanf` input lives.

1. **Console launcher.** Asks the player to choose New Game, Continue, or Quit. Continue appears only if a save file exists. Input is checked with `scanf` return values, the input buffer is flushed, and invalid choices are re-prompted.
2. **Main menu (game window).** New Game, Continue, How to Play, High Scores, Exit.
3. **How to Play screen.** Controls, item effects, and objectives.
4. **Level gameplay.** The HUD shows health, lives, bubbles popped, items collected, and the current level.
5. **Pause menu.** Resume, Restart Level, Return to Main Menu.
6. **Level Complete screen.** Summary of bubbles popped, time, and items collected.
7. **Game Over screen.** Retry or return to the main menu.
8. **Ending cutscene.** Goalie and Lee dialogue, then the credits and high score entry for Lee.

&#91;embedded content: game flow, 12 steps and 2 decisions\]

The launcher feeds the main menu. Gameplay loops through respawns and levels, and a run ends at Game Over or the ending cutscene.

## 6. Feature Roadmap

Features are ranked so that the team can cut from the bottom of the list if a sprint runs short.

| Priority | Features |
| --- | --- |
| Must-have (base version) | Console launcher with validated input; main menu; movement, jumping, gravity and tile collision; three playable levels loaded from text files; stomp combat; health bar and 3 lives; bubbles with a 1UP every 70; towel glide, toothpaste projectile and soap key; Goalie boss; ending scene; Game Over and Win screens; pixel art for all characters and tiles |
| Should-have | Pause menu; How to Play screen; Continue from a save file; high score list ranked by time and bubbles; royalty-free 8-bit background music |
| Bonus (File I/O) | Save and load progress (`lee_save.txt`); persistent high scores (`lee_scores.txt`); level maps read from `level1.txt` to `level3.txt` |
| Stretch goals | Checkpoints; more levels; bouncy obstacles and extra enemy types; secret areas; sound effects |

## 7. Technical Plan: Mapping to the C Procedural Requirements

### 7.1 Modular Functions and Structure

The program is split into `.c` files with matching headers. Each header holds function prototypes, each source file holds the definitions, and `main()` only coordinates the overall flow. Read-only data such as a tile coordinate or an item ID is passed by value. State that changes, such as the player, enemy arrays, and game state, is passed by address.

| Module | Responsibility |
| --- | --- |
| main.c | Program entry, initialization, main loop dispatch |
| game.c / game.h | Game state control, level flow, win and lose logic |
| player.c / player.h | Movement, jumping, gliding, health, lives, items |
| enemy.c / enemy.h | Enemy spawning, patrol logic, stomp detection, Goalie boss behavior |
| projectile.c / projectile.h | Toothpaste shots, Goalie projectiles, cooldown, hit checks |
| level.c / level.h | Level loading, tile map, collision checks, goals |
| bubble.c / bubble.h | Bubble placement, popping, 1UP tracking |
| render.c / render.h | Drawing the world, sprites, HUD, menus, and cutscenes |
| audio.c / audio.h | Background music playback |
| input.c / input.h | Console launcher, validated input, keyboard handling |
| save.c / save.h | Save and load progress, high scores (file I/O) |

### 7.2 Data Structures (Structs and Arrays)

Struct names use snake\_case. Arrays manage enemies, bubbles, projectiles, level tiles, and high score entries.

| Struct | Purpose | Key fields |
| --- | --- | --- |
| player\_t | Lee's position, movement, and progress | x, y, x velocity, y velocity, health, lives, bubbles popped, item flags (towel, toothpaste, soap), on\_ground and gliding flags, shot cooldown |
| enemy\_t | One enemy or the Goalie | x, y, x velocity, type (walker, hazard, goalie), hit points, active flag |
| projectile\_t | One toothpaste shot or Goalie projectile | x, y, x velocity, y velocity, owner, active flag |
| bubble\_t | One floating bubble | x, y, popped flag |
| level\_t | One level's map and contents | level number, width, height, tile map (2D char array), enemy array and count, bubble array and count |
| score\_entry\_t | One high score record | name (always "LEE"), time in seconds, bubbles popped |
| game\_t | The whole game state, held in main() and passed by address | player, current level, score entries, game state (menu, playing, paused, game over, ending) |

### 7.3 Pointers and Memory

- Functions such as `update_player(player_t *player, const level_t *level)` modify game objects through pointers.
- Struct fields are accessed with the arrow operator (`->`).
- Arrays of enemies, bubbles, and projectiles are navigated with indexing and pointer arithmetic.
- A single `game_t` variable is declared in `main()` and passed by address to every module, which avoids global variables.

### 7.4 Characters and Strings

- Character arrays store dialogue lines, high score names, and file paths.
- `<string.h>` functions (`strcpy`, `strncpy`, `strlen`, `strcmp`) handle names, dialogue, and parsing of save and level files.
- `<ctype.h>` functions (`toupper`, `isalpha`, `isdigit`, `isspace`) clean and validate launcher input, such as accepting `n`, `N`, `c`, or `C`.

### 7.5 Defensive Input Validation and Buffer Flushing

Gameplay input uses raylib key-state functions. Because the player never types a name, the console launcher is where text input is read and validated.

- Every `scanf` call checks its return value.
- A dedicated function, `flush_input_buffer()`, clears leftover characters from stdin before any later `getchar` or `%c` read.
- Launcher and menu choices are range-checked, and invalid input triggers a re-prompt instead of a crash or a skipped read.

### 7.6 Data Persistence

| File | Format and contents |
| --- | --- |
| lee\_save.txt | Written with `fprintf` and read with `fscanf`: current level, health, lives, bubbles popped, item flags, elapsed time |
| lee\_scores.txt | Name, time, and bubble total per line; loaded at startup and updated after each completed run |
| level1.txt, level2.txt, level3.txt | Text tile maps plus enemy and bubble positions, read with `fopen` and `fgets` or `fscanf` |

Every file operation checks that `fopen` succeeded and calls `fclose` afterward. Loading levels from text files lets the team edit maps without recompiling.

### 7.7 Code Style Compliance

| Standard | How the team will comply |
| --- | --- |
| snake\_case naming | All variables, arrays, and functions (for example `update_player`, `bubble_count`) |
| Indentation | 4 spaces per block level, applied consistently |
| Function headers | A comment block before every function stating its purpose, parameters (by value or by address), and return value |
| No global variables | All state lives in `main()` and moves through parameters; only `#define` or `const` constants are global |
| Zero errors and warnings | Compile in Code::Blocks with `-Wall -Wextra` from day one and fix every warning |

## 8. Art, Audio and Assets

| Area | Plan |
| --- | --- |
| Art style | Pixel art on a 16x16 tile grid, scaled up in the raylib window. One team member is the dedicated pixel artist and also codes. |
| Art scope | Lee (idle, run, jump, glide, shoot, hurt), walker enemy, spike hazard, Goalie, bubbles, items, and one tileset per level theme |
| Placeholders | Colored rectangles stand in for sprites until art is ready, so programming is never blocked by art |
| Music | One or two royalty-free 8-bit tracks, with the license and source credited in the game credits and the final report |
| Licensing | All art is original to the team. Any third-party asset is properly licensed and credited. |
| Packaging | raylib, assets, music, and any DLLs ship inside the Inno Setup installer so nothing else must be installed |

## 9. Project Management (Scrum)

The team runs three one-week Scrum sprints, one per remaining course week. Work is tracked on a Taiga.io board, and the code lives in a shared Git repository. Each member commits about 2 hours per day, which is roughly 6 team hours per day and about 126 hours over three weeks.

### 9.1 Roles

| Role | Who | Responsibility |
| --- | --- | --- |
| Product Owner and Scrum Master | \[Member 1\] | Owns the backlog and priorities, runs the ceremonies, removes blockers, and keeps the team on scope |
| Developer | \[Member 1\], \[Member 2\], \[Member 3\] | All three members design, code, test, and review. The pixel artist is \[Member 3\]. |

### 9.2 Sprint Plan

| Sprint | Dates | Sprint goal | Review output |
| --- | --- | --- | --- |
| 1 | Nov 9 to Nov 15 | Proposal submitted, raylib spike working, project and repository skeleton, player movement with gravity and tile collision | Lee runs and jumps on a test map |
| 2 | Nov 16 to Nov 22 | Core prototype: console launcher, main menu, Level 1 loaded from a text file, bubbles with 1UP, walker enemy with stomp, health and lives, first sprites | Core Prototype (Deliverable 2) |
| 3 | Nov 23 to Nov 29 | Levels 2 and 3, towel, toothpaste and soap, Goalie boss, ending scene, save and high scores, music, installer, final report, defense practice | Final submission and live defense |

### 9.3 Ceremonies and Tools

| Practice | How we run it |
| --- | --- |
| Sprint planning | At the start of each sprint, the team pulls stories from the backlog into the sprint on Taiga |
| Daily standup | 10 minutes, asynchronous in the group chat each day: what I did, what I will do, what blocks me |
| Sprint review | At the end of each sprint, the team demos the running build and checks it against the sprint goal |
| Retrospective | 15 minutes after each review: what worked, what did not, one change for the next sprint |
| Board | Taiga.io, with columns New, In Progress, In Review, and Done, and one user story per feature |
| Version control | Shared Git repository. Each feature gets its own branch, and `main` must always compile. |

### 9.4 Definition of Done

A story moves to Done only when all of these are true:

- [ ] It compiles in Code::Blocks with zero errors and zero warnings (`-Wall -Wextra`)
- [ ] It follows snake\_case, 4-space indentation, and has a comment header on every function
- [ ] It uses no global variables
- [ ] It was reviewed by a second team member who can explain it
- [ ] It was merged to `main` and the build still runs

## 10. Schedule and Division of Work

### 10.1 Course Milestones

| Course week | Milestone | Team tasks |
| --- | --- | --- |
| 13 | Team formation and concept selection | Finalize the concept, set up the Code::Blocks project, repository, and Taiga board |
| 14 | Milestone 1: Proposal Review | Submit this proposal, present the architecture to the instructor, run the raylib spike, begin the core engine (window, loop, player movement) |
| 15 | Milestone 3: Core Prototype | Submit the prototype: launcher, main menu, player, collision, Level 1 draft, bubbles, basic structs and functions. Test the installer on a clean computer. |
| 16 | Milestone 4: Final Submission and Defense | Levels 2 and 3, items, Goalie boss, ending scene, save system, installer, final report, and live oral defense |

### 10.2 Division of Work

Every member writes code, and each member reviews another member's work in rotation: Member 1 reviews Member 2, Member 2 reviews Member 3, and Member 3 reviews Member 1. All members must be able to explain every module in the live defense.

| Member | Primary focus |
| --- | --- |
| \[Member 1\] (Product Owner and Scrum Master) | Game loop, game state, player mechanics, tile collision, console launcher and validated input, installer |
| \[Member 2\] | Level loading, enemies, Goalie boss, projectiles, bubbles, and items |
| \[Member 3\] (pixel artist) | All pixel art, rendering and HUD, menus, cutscene, audio, save and high score file I/O, final report |

### 10.3 Gantt Chart

ww

Bars run from each task's first to last day and are colored by lead owner. The chart follows the three sprints in Section 9 and the course milestones in Section 10.1.

## 11. Deliverables Plan

| # | Deliverable | Our plan |
| --- | --- | --- |
| 1 | Project Proposal | This document |
| 2 | Core Prototype | Console launcher, main menu, player movement and jumping, Level 1 draft from a text file, tile collision, bubble popping, walker enemy with stomp |
| 3 | C Source Code and Code::Blocks Project | Modular `.c` and `.h` files with a `.cbp` that compiles with zero errors and zero warnings |
| 4 | Installer / Executable Bundle | Inno Setup installer with a desktop shortcut. raylib, assets, music, and any DLLs are packaged so nothing else needs to be installed. |
| 5 | Written Final Report | Architecture, struct definitions, memory layout, file formats, user manual, and full-window screenshots named after their source file (for example `main_1.jpg`) |
| 6 | Live Oral Demonstration | All members present, run test scenarios, and explain logic and memory use |

## 12. Risks and Mitigation

| Risk | Likelihood | Mitigation |
| --- | --- | --- |
| Nobody on the team has used raylib | High | Run a one-day raylib spike in Sprint 1 (window, moving rectangle, keyboard input) before any feature work |
| Finals week limits available time | High | Plan for 2 hours per day per member, keep Sprint 1 small, and cut from the Should-have and Stretch lists first |
| Collision and physics bugs take too long | Medium | Build and test player and tile collision first, and keep tiles simple and grid-based |
| Scope too large for three weeks | Medium | Prioritize Must-have features, keep levels short, and treat extra levels and polish as stretch goals |
| Art becomes a bottleneck | Medium | Use colored-rectangle placeholders so code never waits on sprites, and finish Lee and tiles first |
| Merge conflicts between three people | Medium | One branch per feature, small commits, reviews before merging, and `main` always compiles |
| Graphics library packaging problems in the installer | Medium | Test the installer on a clean computer by the Core Prototype milestone |
| Compiler warnings near the deadline | Low | Compile with `-Wall -Wextra` from day one and fix warnings as we go |
| Uneven workload | Low | Daily async standups, a visible Taiga board, and rotating code reviews |

## 13. Content and Academic Integrity Statement

All game content, including dialogue, the ending, and visuals, is kept safe for work and appropriate for a school setting.

Lee Go! is an original work inspired by the platformer genre. All code is written by the team. All art is original to the team, and any third-party asset, such as the 8-bit music, is royalty-free or properly licensed and credited in the game and the final report. The team follows the course's academic integrity policy.

Prepared by \[Team Name / Members\] for the CMSC 11 / Math 153 Machine Problem.
