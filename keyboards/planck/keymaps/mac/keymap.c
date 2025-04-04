#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_ortho_4x12(
//------------------------------------------------------------------------------------------------------------------------------------------
KC_TAB, KC_Q, KC_W, KC_C, KC_P, KC_Z, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_RGUI,
//------------------------------------------------------------------------------------------------------------------------------------------
KC_LGUI, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O), KC_ENT,
//------------------------------------------------------------------------------------------------------------------------------------------
MO(3), KC_X, KC_V, KC_F, KC_D, KC_B, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
//------------------------------------------------------------------------------------------------------------------------------------------
KC_ESC, MO(4), KC_LCTL, KC_LALT, MO(2), KC_LSFT, MEH_T(KC_SPC), MO(1), KC_RALT, KC_RCTL, MO(5), KC_ESC,
//------------------------------------------------------------------------------------------------------------------------------------------
),

[1] = LAYOUT_ortho_4x12(
//------------------------------------------------------------------------------------------------------------------------------------------
KC_NO, KC_F10, KC_F7, KC_F8, KC_F9, KC_NO, KC_NO, KC_END, KC_HOME, KC_NO, KC_NO, KC_DEL,
//------------------------------------------------------------------------------------------------------------------------------------------
KC_TRNS, KC_F11, KC_F4, KC_F5, KC_F6, KC_NO, KC_PGDN, KC_DOWN, KC_UP, KC_RGHT, KC_PGUP, KC_NO,
//------------------------------------------------------------------------------------------------------------------------------------------
KC_NO, KC_F12, KC_F1, KC_F2, KC_F3, KC_NO, KC_NO, KC_LEFT, KC_NO, KC_NO, KC_NO, KC_NO,
//------------------------------------------------------------------------------------------------------------------------------------------
KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS
//------------------------------------------------------------------------------------------------------------------------------------------
),

[2] = LAYOUT_ortho_4x12(KC_NO, KC_NO, KC_EQL, KC_DLR, KC_TILD, KC_AT, KC_PLUS, KC_LCBR, KC_RCBR, KC_MINS, KC_UNDS, KC_GRV, KC_TRNS, KC_EXLM, KC_HASH, KC_LT, KC_GT, KC_PERC, KC_ASTR, KC_LPRN, KC_RPRN, KC_AMPR, KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO),
[3] = LAYOUT_ortho_4x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_PSCR, KC_NUM, KC_SCRL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, TO(7), KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
[4] = LAYOUT_ortho_4x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PAST, KC_PEQL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_P0, KC_NO, KC_NO, KC_PDOT, KC_PSLS, KC_NO),
[5] = LAYOUT_ortho_4x12(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(6), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO),
};

// TODO: weird bit at end of json2c output. needed?
// #if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

// };
// #endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
