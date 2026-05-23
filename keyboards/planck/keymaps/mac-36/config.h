#pragma once

#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY

#define COMBO_TERM 30
#define COMBO_TERM_PER_COMBO
#define COMBO_STRICT_TIMER // added to see if helps with accidental enter fires, but maybe just tweaking the timeout is good enough.
// #define COMBO_TERM 1000 // useful to test that new fw was flashed

#define PERMISSIVE_HOLD
// #define HOLD_ON_OTHER_KEY_PRESS

#define CHORDAL_HOLD

#define SENDSTRING_BELL // plays tone when sending string
