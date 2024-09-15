#include <stdio.h>
#include <stdlib.h>

#include <nds.h>
#include <filesystem.h>
#include <nf_lib.h>
#include <maxmod9.h>

// Sound.
#include "soundbank.h"

// Objects.
#include "objects/objects.h"

// Wrappers.
#include "wrappers/wrappers_text.h"
#include "wrappers/level_loading.h"
#include "wrappers/wrappers_audio.h"

// Effects.
#include "effects/effects.h"

//keys held right now.
extern int kheld;
//keys pressed right now.
extern int kdown;
//keys released right now.
extern int kreleased;
