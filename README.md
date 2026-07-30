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
| SDL2 | `SDL2.dll` |
| SDL2_mixer | `SDL2_mixer.dll` |
| SDL2_net | `SDL2_net.dll` |
| libxml2 | `xml2.dll` |

Build tools required:

- GCC 9.2 / kLIBC (from ArcaOS RPM)
- GNU Make

## Building from Source

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
| `src/SDL_mixer_compat.h` | Redirects `Mix_PlayChannel` away from unexported `Mix_PlayChannelTimed` |
| `src/sdl2mix_compat.cpp` | Stub implementation for `mix_play_compat` |
| `compile-2pong.cmd` | Wrapper that sets linker environment and calls make |


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

The port targets ArcaOS with GCC 9.2 / kLIBC and SDL2. Changes made to the
original source:

**SDL 1.2 → SDL2 migration**

- Replaced `SDL_SetVideoMode` with `SDL_CreateWindow` + `SDL_GetWindowSurface`.
- All rendering targets a fixed-size virtual surface (`SDL_CreateRGBSurface`);
  `PresentScreen()` scales it to the window via `SDL_BlitScaled`, providing
  correct letterboxed fullscreen without requiring a display-mode change.
- `SDL_WINDOW_FULLSCREEN_DESKTOP` used for fullscreen toggle (Alt+Enter); the
  OS/2 DIVE driver does not support display-mode switching.
- Mouse coordinates translated from window space to game space via
  `WindowToGameCoords()` so menus remain clickable in fullscreen.
- `SDL_Flip` / `SDL_UpdateRects` replaced by `PresentScreen()` throughout.
- `SDL_DisplayFormat` / `SDL_DisplayFormatAlpha` replaced by
  `SDL_ConvertSurfaceFormat(..., SDL_PIXELFORMAT_ARGB8888, 0)`.
- `SDL_GetKeyState` replaced by `SDL_GetKeyboardState`; all `SDLK_*` arrow and
  space constants replaced by `SDL_SCANCODE_*` equivalents.
- `SDL_WM_SetCaption` / `SDL_WM_SetIcon` replaced by `SDL_SetWindowTitle` /
  `SDL_SetWindowIcon`.
- `SDL_SRCCOLORKEY` flag replaced by `SDL_TRUE`.

**OS/2 SDL2_mixer workaround**

- The OS/2 SDL2_mixer build (2021) does not export `Mix_PlayChannelTimed`.
  Because the SDL2 header defines `Mix_PlayChannel` as a macro expanding to
  `Mix_PlayChannelTimed`, any call generates an unresolved IMPDEF reference.
  `SDL_mixer_compat.h` `#undef`s the macro and replaces it with a local stub
  (`mix_play_compat`), which satisfies the linker without requiring the missing
  export. Sound effects are currently silent as a result.

**Bug fixes carried from the SDL1 port**

- Fixed a crash in `GetNode()` (`menu.cpp`) where the recursive return value was
  discarded, causing a NULL pointer dereference when walking the XML menu tree.
- Fixed a logic bug in `net.cpp`: `(KMOD_RSHIFT || KMOD_LSHIFT)` was always `true`
  (non-zero constants); corrected to `(event.key.keysym.mod & (KMOD_RSHIFT | KMOD_LSHIFT))`.
- Fixed a missing-braces bug in `game.cpp` that caused the `SDLK_p` key check to
  execute on any event type, not only `SDL_KEYDOWN`.
- Fixed paddle speed spike on game start: `myold` now initialised from the actual
  mouse position before the game loop, preventing a large first-frame delta.
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
