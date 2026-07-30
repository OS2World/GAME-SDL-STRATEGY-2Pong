# 2Pong for OS/2 and ArcaOS

2Pong is an open-source Pong clone with powerups, multiple game modes, and network play.
This repository contains the original source code with an OS/2 / ArcaOS port.

- **Original version:** 1.0a by Kirsh et al.
- **OS/2 port version:** 1.0.1a by Martin Iturbide

## Screenshot

*(screenshot here)*

## Game Modes

- **Regular** — single player vs. AI, with powerups (Easy / Medium / Hard)
- **Classic** — single ball, no powerups
- **Quick Play** — random difficulty
- **Network** — two players over UDP (Server / Client)

### Powerups

Powerups appear randomly during play and affect ball speed or count:

| Powerup | Effect |
|---------|--------|
| Double Speed | Ball moves twice as fast |
| Half Speed | Ball moves at half speed |
| Inc Speed | Gradually increases ball speed |
| Dec Speed | Gradually decreases ball speed |
| Split | Ball splits into two |

## Controls

| Key | Action |
|-----|--------|
| Mouse | Move paddle (in-game) |
| Keyboard arrows | Move paddle |
| P | Pause / return to menu |
| Escape | Quit match / back in menu |
| Alt + Enter | Toggle fullscreen |

## Requirements (OS/2 / ArcaOS)

The following packages must be installed from the ArcaOS RPM repository (ANPM):

| Package | Library used |
|---------|--------------|
| SDL 1.2 | `SDL.dll` |
| SDL_mixer | `SDL_mixer.dll` |
| SDL_net | `SDL_net.dll` |
| libxml2 | `xml2.dll` |

Build tools required:

- GCC 9.2 / kLIBC (from ArcaOS RPM)
- GNU Make
- GNU sed (for the one-time SDL header patch)

## Building from Source

### Step 1 — Patch the SDL header (run once)

There is a type conflict between `SDL_config_os2.h` and the kLIBC `sys/types.h`
for `uintptr_t`. The included script patches the SDL header to resolve it:

```
patch-sdl.cmd
```

Check `patch-sdl.log` to confirm the patch succeeded. This only needs to be run once per installation.

### Step 2 — Build

From the `2Pong-Source\` directory:

```
compile-2pong.cmd
```

Build output is logged to `compile-2pong.log`. On success, `2pong.exe` is produced
in the `2Pong-Source\` directory.

To rebuild from scratch:

```
compile-2pong.cmd clean
compile-2pong.cmd
```

### Build files added for OS/2

| File | Purpose |
|------|---------|
| `src/Makefile.os2` | OS/2 Makefile for GCC 9.2 / kLIBC / WLINK |
| `src/2pong.def` | Module definition file (BLDLEVEL, WINDOWAPI subsystem) |
| `compile-2pong.cmd` | Wrapper that sets linker environment and calls make |
| `patch-sdl.cmd` | One-time SDL header patch |


## Running

Run from the `2Pong-Source\` directory so that `conf.xml` and the `src/data/`
assets are found at the expected relative paths:

```
run-2pong.cmd
```

Or directly:

```
2pong.exe
```

## OS/2 Port Notes

The port targets ArcaOS with GCC 9.2 / kLIBC and SDL 1.2. Changes made to the
original source:

- Fixed a crash in `GetNode()` (`menu.cpp`) where the recursive return value was
  discarded and `return NULL` was commented out, causing a NULL pointer dereference
  when walking the XML menu tree.
- Fixed a logic bug in `net.cpp`: `(KMOD_RSHIFT || KMOD_LSHIFT)` was always `true`
  (non-zero constants); corrected to `(event.key.keysym.mod & (KMOD_RSHIFT | KMOD_LSHIFT))`.
- Fixed a missing-braces bug in `game.cpp` that caused the `SDLK_p` key check to
  execute on any event type, not only `SDL_KEYDOWN`.
- Resolved a `uintptr_t` redefinition conflict between `SDL_config_os2.h` and
  kLIBC `sys/types.h` via `patch-sdl.cmd`.
- Added Alt+Enter fullscreen toggle.
- Added BLDLEVEL metadata via `2pong.def`.
- Fixed numerous compiler warnings (narrowing conversions, uninitialized variables,
  char-subscript issues, sprintf buffer sizes, member init order).

## Original Credits

- Kirsh
- Nazgul
- Limburger
- Grooveygr
- Xetrov
- MatanH
- Noam
- Eskorbuto
- Chaka
- SantaTron
- bgo-


## OS/2 Port

- Martin Iturbide 

## License

This program is released under the **GPL**.
