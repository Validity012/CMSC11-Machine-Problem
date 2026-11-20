# Lee Go!

A keyboard-only, Mario-style 2D platformer written in procedural C with [raylib](https://www.raylib.com/).

Lee is a BS Computer Science student who has not showered in days, a streak too long and risky to share. Amid side eyes and stares in the library, he has only one thing on his mind: a shower. He must cross three levels of obstacles and enemies to reach the dormitory bathrooms, where a hockey goalie stands guard. The game is lighthearted, comedic, and safe for work.

> Machine Problem for **CMSC 11 Fundamentals of Programming 1**, First Semester, AY 2026-2027.
> University of the Philippines Tacloban, College of Science

---

## Table of Contents

- [Gameplay](#gameplay)
- [Controls](#controls)
- [Tools and Technologies](#tools-and-technologies)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Documentation](#documentation)
- [Code Standards](#code-standards)
- [Development Workflow](#development-workflow)
- [Timeline](#timeline)
- [Status](#status)
- [Team](#team)
- [Credits](#credits)
- [Academic Integrity](#academic-integrity)

---

## Gameplay

**Goal:** guide Lee through every level, collect the required item in each, and reach the shower and bath at the end. Defeat the Goalie in Level 3, watch the ending scene, and reach the bath to win.

### Core mechanics

- **Movement and platforming:** Lee runs, jumps, and lands on platforms with gravity and tile collision.
- **Stomp attack:** As in Super Mario, Lee defeats enemies by jumping on them. Touching an enemy from the side or below hurts him.
- **Side-scrolling camera:** The camera follows Lee across maps wider than the screen.
- **Bubble popping:** Bubbles float around each map and pop when Lee touches them. They replace coins.

### Hearts, lives, and 1UP

| Concept | How it works |
| --- | --- |
| Hearts | Each hit from an enemy, hazard, or Goalie attack removes one heart. |
| Lives | Lee starts with 3 lives. When the hearts run out or Lee falls into a pit, he loses a life and tries the level again from the start with full hearts. |
| 1UP | Pop **70 bubbles** to earn one extra life. The bubble count carries across the run. |
| Game Over | Losing every life ends the run. |

### Levels and items

Lee starts in the library and works his way to the dormitory.

| Level | Setting | Item | What it does |
| --- | --- | --- | --- |
| 1 | Library | Towel | Unlocks the glide ability for the rest of the game |
| 2 | Dormitory corridors | Toothpaste (or shampoo) | Unlocks a projectile attack with a short cooldown |
| 3 | Dormitory bathrooms | Soap | The key to the bath, required to finish the game |

### Enemies and obstacles

- **Walkers** patrol platforms. Stomp them or hit them with a projectile.
- **Spikes** are stationary hazards that cannot be stomped.
- **The Goalie** is the final boss. It moves forward and backward and fires projectiles along both axes. Learn the pattern and hit it until its hit points run out.

### High scores

Scores combine total completion time and total bubbles popped. Every run belongs to Lee, so there is no name entry.

---

## Controls

The game is keyboard only.

| Action | Key |
| --- | --- |
| Move left / right | Left and Right arrows (or A / D) |
| Jump | Space (hold for a higher jump) |
| Glide (after the towel) | Hold Space while in the air |
| Shoot (after the toothpaste) | X |
| Pause | P or Esc |
| Menu navigation | Up / Down arrows and Enter |

---

## Tools and Technologies

| Purpose | Tool |
| --- | --- |
| Language | C (procedural) |
| Graphics framework | raylib |
| Build system | CMake 3.14 or newer |
| Editor | Any editor. Code::Blocks is used for the final submission |
| Version control | GitHub |
| Version management and Scrum board | Taiga.io |
| Deployment | Inno Setup |

---

## Getting Started

### Requirements

- A C compiler (MinGW-w64, MSVC, or GCC)
- CMake 3.14 or newer
- raylib. CMake uses a local install when it finds one and downloads a compatible release otherwise.

### Build and run from source

1. Clone the repository.
2. Configure: `cmake -S . -B build`
3. Build: `cmake --build build`
4. Run the executable in `build/`. On Windows the file is `CMSC11-Machine-Problem.exe`.

The build must finish with zero errors and zero warnings.

On launch, a short console window asks you to choose **New Game**, **Continue**, or **Quit**. The game window opens after that.

### Install from the installer

Run the Inno Setup installer (`LeeGoSetup.exe`). It installs the game with raylib, assets, and music packaged together and adds a desktop shortcut. No other install is needed.

---

## Project Structure

```
CMSC11-Machine-Problem/
├── CMakeLists.txt       build configuration
├── docs/                project management documents
├── src/                 .c source files
│   ├── main.c           entry point and main loop dispatch
│   ├── game.c           game state, level flow, win and lose logic
│   ├── player.c         movement, jumping, gliding, hearts, lives, items
│   ├── enemy.c          walkers, hazards, stomp detection, Goalie boss
│   ├── projectile.c     toothpaste shots, Goalie projectiles, cooldowns
│   ├── level.c          level loading, tile map, collision checks
│   ├── bubble.c         bubble placement, popping, 1UP tracking
│   ├── render.c         world, sprites, HUD, menus, cutscene
│   ├── audio.c          background music and sound effects
│   ├── input.c          console launcher and validated input
│   └── save.c           save/load and high scores
├── include/             matching .h files
├── Assets/
│   ├── sprites/         pixel art
│   └── music/           music and sound effects
├── levels/              level1.txt, level2.txt, level3.txt
└── installer/           Inno Setup script
```

### Data files

| File | Contents |
| --- | --- |
| `lee_save.txt` | Current level, hearts, lives, bubbles popped, item flags, elapsed time |
| `lee_scores.txt` | Time and bubble total for each completed run |
| `level1.txt` to `level3.txt` | Text tile maps with enemy and bubble positions |

---

## Documentation

Project management documents live in `docs/`:

| File | Contents |
| --- | --- |
| `docs/proposal/` | Machine problem proposal, Markdown and PDF |
| `docs/playbook/` | How the team runs Scrum: roles, sprint plan, rules, Markdown and PDF |
| `docs/quick-guide/` | Day-to-day Taiga and GitHub routine, Markdown and PDF |
| `docs/reports/` | Status reports, newest first |

The living version is the [project wiki](https://tree.taiga.io/project/validity012-cmsc11-machine-problem/wiki/home), which carries gameplay, architecture, build, workflow, sprint, and team pages. Update the wiki when a decision changes. The files here are the submitted record.

---

## Code Standards

This project follows the course's procedural C rules:

- **snake_case** for all variables, arrays, and functions.
- **4-space indentation**, applied consistently.
- A **comment header before every function** stating its purpose, parameters (by value or by address), and return value.
- **No global variables.** All state lives in a single `game_t` variable in `main()` and is passed by address. Only `#define` and `const` constants are global.
- Pointers, structs, and arrays for game objects, with `->` for field access through pointers.
- `scanf` return values are always checked, and `flush_input_buffer()` clears stdin before later reads.
- Zero compiler warnings with `-Wall -Wextra`.

---

## Development Workflow

The team follows an agile, Scrum-based process. Work is tracked on Taiga (project: **CMSC11 Machine Problem**) and code lives on GitHub.

- **Board columns:** stories move New, Ready, In Progress, Ready for Test, Needs Info, Done. Tasks end at Closed, not Done.
- **Branches:** one branch per card, named `TG-<ref>-<short-description>`, for example `TG-28-tile-collision`. `main` must always compile.
- **Reviews:** every change is reviewed by a second member before it is merged.
- **Daily standup:** a short async post in the group chat. What I did, what I will do, what blocks me.

### Definition of Done

A card is done only when all of these are true:

- [ ] It compiles with zero errors and zero warnings (`-Wall -Wextra`)
- [ ] It follows snake_case, 4-space indentation, and has a comment header on every function
- [ ] It uses no global variables
- [ ] A second member reviewed it and can explain it
- [ ] The QA Lead ran the build and checked the story's "Done when" line
- [ ] It is merged to `main` and the build still runs

---

## Timeline

Three sprints, ending 3 December 2026. Each one ends with a build that runs.

| Sprint | Dates | Points | Focus |
| --- | --- | --- | --- |
| Greybox | Nov 12 to Nov 20 | 35 | raylib spike, game loop, player movement, tile collision, blockout, first art |
| Core Prototype | Nov 21 to Nov 26 | 26 | Console launcher, menus and HUD, Level 1 with bubbles and stomp, hearts and lives, installer clean-PC test |
| Final Build | Nov 23 to Dec 3 | 30 | Levels 2 and 3, glide and projectile, Goalie boss, ending scene and music, save and high scores, final installer, final report, defense practice |

Core Prototype and Final Build overlap from November 23 to 26 so boss and level work starts before the prototype demo. The defense rehearsal sits inside Final Build, and the defense date comes from the course schedule.

---

## Status

As of 18 November 2026, Greybox is in progress with 16 of 35 points closed.

- [x] Proposal submitted
- [ ] Greybox prototype: main game loop, kinematics, collisions, control mapping, environment blockout
- [ ] Console launcher and main menu
- [ ] Level 1 with bubbles, walker enemy, stomp, hearts and lives
- [ ] Levels 2 and 3 with towel, toothpaste, and soap
- [ ] Goalie boss and ending scene
- [ ] Save/continue and high scores
- [ ] Installer and final report

---

## Team

| Name | Role |
| --- | --- |
| Omega, Chrivin C. | Product Owner, Scrum Master |
| Plaza, Rich S. | Art and Dev Lead |
| Senaca, Joseph Franco | QA and Music Lead |

All three are developers. The Product Owner owns the backlog and its order; the Scrum Master keeps Taiga and the meetings working.

Laboratory section: G
Laboratory instructor: Mr. Ronnie M.  Ramirez II

---

## Credits

- Built with [raylib](https://www.raylib.com/), which is licensed under the zlib license.
- All pixel art, music, sound effects, and graphics are created by the project team.

---

## Academic Integrity

All code and assets in this repository were created by the team. The team follows the course's academic integrity policy.
