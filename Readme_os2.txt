2Pong for OS/2 and ArcaOS
==========================
Version 1.0.1a
Port date: 2026-07-29
Ported by: Martin Iturbide


About
-----
2Pong is an open-source Pong clone with powerups, multiple game modes,
and network play over UDP.  Play against the AI or challenge another
player over the network.


Game Modes
----------
  Regular     Single player vs. AI with powerups (Easy / Medium / Hard)
  Classic     Single ball, no powerups
  Quick Play  Random difficulty
  Network     Two players over UDP (Server / Client)


Controls
--------
  Mouse           Move paddle
  Arrow keys      Move paddle
  P               Pause / return to menu
  Escape          Quit match / back in menu
  Alt + Enter     Toggle fullscreen


Requirements
------------
The following libraries must be installed on your OS/2 or ArcaOS system.
Use ANPM (ArcaOS Package Manager) or the yum command line tool.

  SDL 1.2
    yum install SDL

  SDL_mixer (music and sound effects)
    yum install SDL_mixer

  SDL_net (network game support)
    yum install SDL_net

  libxml2 (menu configuration)
    yum install libxml2

To install all at once:

    yum install SDL SDL_mixer SDL_net libxml2


First-time Setup
----------------
Before running 2Pong for the first time, run the SDL header patch script
to fix a type conflict between SDL 1.2 and the kLIBC headers:

    patch-sdl.cmd

This only needs to be done once per installation.  Check patch-sdl.log
to confirm it completed successfully.


Running
-------
Run 2pong.exe from the 2Pong-Source\ directory, or use the included
launch script:

    run-2pong.cmd

The game reads its menu configuration from conf.xml and loads its assets
from src\data\, so the working directory must be 2Pong-Source\.


License
-------
GNU General Public License (GPL)


Original Credits
----------------
  Kirsh, Nazgul, Limburger, Grooveygr, Xetrov, MatanH,
  Noam, Eskorbuto, Chaka, SantaTron, bgo-

  Contact: kirsh@softhome.net


Links
-----
  Original project:  (original source location)
  OS/2 repository:   https://github.com/OS2World/GAME-ACTION-2Pong
