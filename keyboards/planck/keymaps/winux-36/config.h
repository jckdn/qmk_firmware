#pragma once

#define TAPPING_TERM 300 // was 200. unclear why I made 300...
#define TAPPING_TERM_PER_KEY

#define COMBO_TERM 30
#define COMBO_TERM_PER_COMBO
#define COMBO_STRICT_TIMER // added to see if helps with accidental enter fires, but maybe just tweaking the timeout is good enough.
// #define COMBO_TERM 1000 // useful to test that new fw was flashed

#define PERMISSIVE_HOLD // I added this when I made TAPPING_TERM 300. Maybe having permissive hold means tterm can be higher for some reason?
// #define HOLD_ON_OTHER_KEY_PRESS

#define CHORDAL_HOLD
