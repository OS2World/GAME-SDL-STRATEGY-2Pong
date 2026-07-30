#ifndef SDL_MIXER_COMPAT_H
#define SDL_MIXER_COMPAT_H

/* Include SDL2_mixer for type definitions (Mix_Chunk, Mix_Music, etc.).
 * On OS/2 ArcaOS the SDL2_mixer DLL does not export Mix_PlayChannelTimed,
 * which is what the SDL2 header's Mix_PlayChannel macro expands to.
 * We intercept the macro here and redirect to mix_play_compat(), a plain
 * C function whose PUBDEF can be satisfied by sdl2mix_compat.o. */
#include <SDL2/SDL_mixer.h>

#ifdef Mix_PlayChannel
#undef Mix_PlayChannel
#endif
#define Mix_PlayChannel(channel, chunk, loops) mix_play_compat((channel), (chunk), (loops))

#ifdef __cplusplus
extern "C" {
#endif
int mix_play_compat(int channel, Mix_Chunk *chunk, int loops);
#ifdef __cplusplus
}
#endif

#endif /* SDL_MIXER_COMPAT_H */
