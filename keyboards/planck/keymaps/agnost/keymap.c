/**
 * NOTES:
 * - uses home row mods and home row combos.
 * - uses the Chordal Hold feature to reduce accidental home row mod triggers when rolling on one hand.
 */

/**
 * TODO:
 * - using permissive hold with chordal hold might be worth doing:
 *   - https://www.reddit.com/r/zsaVoyager/comments/1jqronl/comment/ml96ysv/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
 *   - https://precondition.github.io/home-row-mods#permissive-hold
 * - put win key tap somewhere? a combo?
 * - thumb key combos? thumb combo hold layers? thumb combo OSMs?
 */

#include QMK_KEYBOARD_H

enum custom_keycodes {
    MAC_TOG = SAFE_RANGE,
    SS_PW = SAFE_RANGE + 1
};

// allows toggling between stuff that depends on mac vs win mod key behaviour, like ctrl vs cmd (gui)
bool mac_mode = true;

// gets the appropriate mod key for OS behaviours like ctr-c/cmd-c
uint16_t mod_key(uint16_t kc) {
    return mac_mode ? LGUI(kc) : LCTL(kc);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(
        KC_Q,            LT(0,KC_W),      LT(0,KC_C),    KC_P,          KC_Z,    KC_NO, KC_NO, KC_J,          KC_L,          LT(0,KC_U),   KC_Y,         KC_QUOT,
        LCTL_T(KC_A),    LSFT_T(KC_R),    LALT_T(KC_S),  LGUI_T(KC_T),  KC_G,    KC_NO, KC_NO, KC_M,          RGUI_T(KC_N),  LALT_T(KC_E), RSFT_T(KC_I), RCTL_T(KC_O),
        LT(0,KC_X),      KC_V,            KC_F,          LT(3,KC_D),    KC_B,    KC_NO, KC_NO, KC_K,          KC_H,          KC_COMM,      KC_DOT,       KC_SLSH,
        KC_NO,           KC_NO,           KC_NO,         MO(2),         KC_LSFT, KC_NO, KC_NO, MEH_T(KC_SPC), LT(1,KC_BSPC), KC_NO,        KC_NO,        KC_NO
    ),
	[1] = LAYOUT_ortho_4x12(
        KC_F1,           KC_F2,           KC_F3,         KC_F4,         KC_NO,   KC_NO, KC_NO, KC_NO,         KC_END,        KC_HOME,      KC_PGDN,      KC_PGUP,
        LCTL_T(KC_F5),   LSFT_T(KC_F6),   LALT_T(KC_F7), LGUI_T(KC_F8), KC_NO,   KC_NO, KC_NO, KC_NO,         KC_DOWN,       KC_UP,        KC_RGHT,      MAC_TOG,
        KC_F9,           KC_F10,          KC_F11,        KC_F12,        KC_NO,   KC_NO, KC_NO, KC_NO,         KC_LEFT,       SS_PW,        RGB_TOG,      QK_BOOT,
        KC_NO,           KC_NO,           KC_NO,         KC_NO,         KC_TRNS, KC_NO, KC_NO, KC_NO,         KC_TRNS,       KC_NO,        KC_NO,        KC_NO
    ),
    /* DT_PRNT, DT_UP, DT_DOWN are for printing and adjusting tap term. */
	[2] = LAYOUT_ortho_4x12(
        KC_NO,           KC_EQL,          KC_DLR,        KC_TILD,       KC_AT,   KC_NO, KC_NO, KC_PLUS,       KC_LCBR,       KC_RCBR,      KC_MINS,      KC_UNDS,
        LCTL_T(KC_EXLM), LSFT_T(KC_HASH), LALT_T(KC_LT), LGUI_T(KC_GT), KC_PERC, KC_NO, KC_NO, KC_ASTR,       KC_LPRN,       KC_RPRN,      KC_AMPR,      KC_GRV,
        KC_NO,           KC_NO,           KC_NO,         KC_NO,         KC_NO,   KC_NO, KC_NO, KC_CIRC,       KC_LBRC,       KC_RBRC,      KC_PIPE,      KC_BSLS,
        KC_NO,           KC_NO,           KC_NO,         KC_TRNS,       KC_TRNS, KC_NO, KC_NO, KC_SPC,        KC_DEL,        DT_PRNT,      DT_UP,        DT_DOWN
    ),
	[3] = LAYOUT_ortho_4x12(
        KC_CAPS,         KC_SCRL,         KC_NUM,        KC_PSCR,       KC_NO,   KC_NO, KC_NO, KC_NO,         KC_P7,         KC_P8,        KC_P9,        KC_NO,
        KC_LCTL,         KC_LSFT,         KC_LALT,       KC_LGUI,       KC_NO,   KC_NO, KC_NO, KC_NO,         KC_P4,         KC_P5,        KC_P6,        KC_NO,
        KC_NO,           KC_NO,           KC_NO,         KC_NO,         KC_NO,   KC_NO, KC_NO, KC_NO,         KC_P1,         KC_P2,        KC_P3,        KC_NO,
        KC_NO,           KC_NO,           KC_NO,         KC_NO,         KC_TRNS, KC_NO, KC_NO, KC_P0,         KC_NO,         KC_NO,        KC_NO,        KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // toggle mac mode
        case MAC_TOG:
            if (record->event.pressed) {
                mac_mode = !mac_mode;
            }
            return false;

        // mod-tap workaround: !
        case LCTL_T(KC_EXLM):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_EXLM);
                return false;
            }
            return true;

        // mod-tap workaround: #
        case LSFT_T(KC_HASH):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_HASH);
                return false;
            }
            return true;

        // mod-tap workaround: <
        case LALT_T(KC_LT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LT);
                return false;
            }
            return true;

        // mod-tap workaround: >
        case LGUI_T(KC_GT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_GT);
                return false;
            }
            return true;

        // hold u - undo
        case LT(0, KC_U):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(mod_key(KC_Z));
                return false;
            }
            return true;

        // hold x - cut
        case LT(0, KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(mod_key(KC_X));
                return false;
            }
            return true;

        // hold c - copy
        case LT(0, KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(mod_key(KC_C));
                return false;
            }
            return true;

        // hold w - paste
        case LT(0, KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(mod_key(KC_V));
                return false;
            }
            return true;

        case SS_PW:
            if (record->event.pressed) {
                SEND_STRING("cordial1!");
            }
            return false;

        default:
            return true;
    }
}

// combos
const uint16_t PROGMEM tab_combo[] = { LSFT_T(KC_R), LALT_T(KC_S), COMBO_END };
const uint16_t PROGMEM esc_combo[] = { LALT_T(KC_S), LGUI_T(KC_T), COMBO_END };
const uint16_t PROGMEM enter_combo[] = { RGUI_T(KC_N), LALT_T(KC_E), COMBO_END };
// const uint16_t PROGMEM win_combo[] = { LALT_T(KC_E), RSFT_T(KC_I), COMBO_END };
const uint16_t PROGMEM semi_combo[] = { KC_COMM, KC_DOT, COMBO_END };
combo_t key_combos[] = {
    COMBO(tab_combo, KC_TAB),
    COMBO(esc_combo, KC_ESC),
    COMBO(enter_combo, KC_ENT),
    // COMBO(win_combo, KC_LGUI),
    COMBO(semi_combo, KC_SCLN)
};

// combo timeouts per combo
#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    // decide by combo->keycode
    switch (combo->keycode) {
        case KC_ENT:
            return 20;
    }

    return COMBO_TERM;
}
#endif

// generally useful but kind of required if using high tapping term and permissive hold
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // faster tapping term for hold key actions for easier repeats
        case LT(0, KC_W):
        case LT(0, KC_C):
        case LT(0, KC_X): // used to be 130. why?
        case LT(0, KC_U): // used to be 150. why?
            return 200;
        case LT(1, KC_BSPC):
            return 150; // why?
        default:
            return TAPPING_TERM;
    }
}

// Define the handedness of keys for Chordal Hold, excluding thumb keys.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', '*',  '*', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', '*',  '*', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', '*',  '*', 'R', 'R', 'R', 'R', 'R',
        '*', '*', '*', '*', '*', '*',  '*', '*', '*', '*', '*', '*'
    );
