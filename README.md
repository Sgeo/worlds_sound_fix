= Worlds Sound Fix =
This fixes some issues with WorldsPlayer sounds.

== How to use ==

Using the latest release, copy the files to whereever gamma.dll is located, then run patch_sound_fix.bat.

== How it works == 
1. Rewrites use of SND_PURGE when silencing sounds to the more modern setting of a NULL sound.