# Worlds Sound Fix 

This fixes some issues with WorldsPlayer sounds.

Notably: Lengthy pauses in moving between rooms with sounds.

## How to use

1. Using the [latest release](releases/latest), copy the files to whereever `gamma.dll` is located.
1. Run `patch_sound_fix.bat`
1. (64-bit Windows only) Run `midi_patch.exe`. Check that there is now an `mciseq.dll` in that directory.

## How it works
1. Rewrites use of `SND_PURGE` when silencing sounds to the more modern setting of a NULL sound.
1. Changes a `Sleep(4)` to `Sleep(0)` in `mciseq.dll`, as documented by https://www.virtualdub.org/blog2/entry_077.html

## Limitations
1. I didn't make a 32-bit version of `midi_patch.exe`
1. `Sleep(0)` might not work properly on Windows XP
1. Future versions of `mciseq.dll` could look drastically different, and the code might not correctly find the place to patch. This patcher is not robust, though it checks to see if there's exactly one location to patch.

## Uninstalling

1. Delete `gamma.dll` and rename `gamma.dll~` to `gamma.dll`
1. Delete the `mciseq.dll` in the directory that contains `gamma.dll`

## Non-WorldsPlayer games

This code was tested with Worlds.com WorldsPlayer. However, these programs may be useful for other games. There are a lot of complaints about games that pause when loading MIDIs, so `midi_patch.exe` may help those.

I'm not aware of people having issues with `SND_PURGE` in older games, but it is possible. `sound_fix.dll` could help with those, although the included .bat file patches `gamma.dll`, which is WorldsPlayer specific. 