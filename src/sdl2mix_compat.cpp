/* sdl2mix_compat.cpp
 * On OS/2 ArcaOS the SDL2_mixer DLL does not export Mix_PlayChannelTimed.
 * SDL_mixer_compat.h redirects Mix_PlayChannel to mix_play_compat() so
 * balls.o never generates an IMPDEF for Mix_PlayChannelTimed at all.
 *
 * mix_play_compat is a regular C function (plain PUBDEF in OMF) that
 * WLINK can match against the EXTDEF in balls.o without symbol-format issues.
 *
 * TODO: if audio is needed, replace the stub body with a call to whatever
 * function SDL2_MIXER.DLL actually exports (check with: ar -x SDL2_mixer_dll.a
 * and then: nm *.o | grep -i mix_play).
 */

/* Include the compat header so mix_play_compat is declared consistently. */
#include "SDL_mixer_compat.h"

int mix_play_compat(int channel, Mix_Chunk *chunk, int loops)
{
    (void)channel;
    (void)chunk;
    (void)loops;
    return 0; /* silent stub — see TODO above */
}
