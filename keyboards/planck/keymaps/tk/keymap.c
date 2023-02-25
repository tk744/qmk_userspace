/* Copyright 2022 Tushar Khan
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include QMK_KEYBOARD_H
#include "muse.h"


/*
    ██████╗ ███████╗███████╗██╗███╗   ██╗██╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
    ██╔══██╗██╔════╝██╔════╝██║████╗  ██║██║╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
    ██║  ██║█████╗  █████╗  ██║██╔██╗ ██║██║   ██║   ██║██║   ██║██╔██╗ ██║███████╗
    ██║  ██║██╔══╝  ██╔══╝  ██║██║╚██╗██║██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║
    ██████╔╝███████╗██║     ██║██║ ╚████║██║   ██║   ██║╚██████╔╝██║ ╚████║███████║
    ╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/

// Secret macros

#if !defined(NAME) || !defined(EMAIL) || !defined(PHONE)
#define NAME ""
#define EMAIL ""
#define PHONE ""
#endif

// Mod masks

#define LCTL_MASK (get_mods() & MOD_BIT(KC_LCTL))
#define RCTL_MASK (get_mods() & MOD_BIT(KC_RCTL))
#define CTL_MASK  (LCTL_MASK || RCTL_MASK)
#define LSFT_MASK (get_mods() & MOD_BIT(KC_LSFT))
#define RSFT_MASK (get_mods() & MOD_BIT(KC_RSFT))
#define SFT_MASK  (LSFT_MASK || RSFT_MASK)
#define LALT_MASK (get_mods() & MOD_BIT(KC_LALT))
#define RALT_MASK (get_mods() & MOD_BIT(KC_RALT))
#define ALT_MASK  (LALT_MASK || RALT_MASK)

// Layers

enum planck_layers {
    _BASE,
    _L1,
    _R1,
    _L2,
    _R2,
    _I3,
    _KB,
    _F,
};

// Rotary encoder states

enum encoder_states {
    E_VOLUME,     // volume up/down, toggle mute
    E_MEDIA,      // media next/previous, play/pause
    E_BRIGHTNESS, // brightness up/down
    E_SCROLL_V,   // scroll up/down, middle click
    E_SCROLL_H,   // scroll right/left, middle click
    E_ARROW_V,    // arrow up/down
    E_ARROW_H,    // arrow left/right
};

enum encoder_states rotary_state = E_VOLUME;

// Custom keycodes

enum keycodes {
    ENCODER = SAFE_RANGE,
    CTRL_SH,    // CTRL + SH
    
    // rotary state selection
    R_VOL, R_MEDIA, R_BRI, R_SC_V, R_SC_H, R_AR_V, R_AR_H,

    // kvm macros
    KVM_PC1,    // show PC 1 on both monitors 
    KVM_PC2,    // show PC 2 on both monitors
    KVM_IN,     // if showing both PCs then toggle focus for input
    KVM_OUT,    // let monitor 1 be the sink: 
                //      if showing both PCs then swap monitors and focus input on the sink
                //      if showing one PC then show other PC on the sink and focus input on it

    // static macros
    M_CLEAR,    // [delete line]
    M_NAME,     // [full name]
    M_EMAIL,    // [email address]
    M_PHONE,    // [phone number]
    M_CMT,      // git commit -m ''
    M_SHBNG,    // #!/usr/bin/env 
    M_CHMOD,    // chmod 744
    M_VENV,     // source *env*/bin/activate

    // olkb emulator keys
    OLKB_00, OLKB_01, OLKB_02, OLKB_03, OLKB_04, OLKB_05, OLKB_06, OLKB_07, OLKB_08, OLKB_09,
    OLKB_10, OLKB_11, OLKB_12, OLKB_13, OLKB_14, OLKB_15, OLKB_16, OLKB_17, OLKB_18, OLKB_19,
    OLKB_20, OLKB_21, OLKB_22, OLKB_23, OLKB_24, OLKB_25, OLKB_26, OLKB_27, OLKB_28, OLKB_29,
    OLKB_35,
};

#define BASE   TO(_BASE)
#define HYPER  MO(_KB)
#define ADJUST MO(_F)

// these keys need to bee OSL so that xxx2 can be activated
#define LOWER1  OSL(_L1)
#define LOWER2  OSL(_L2)
#define RAISE1  OSL(_R1)
#define RAISE2  OSL(_R2)

// mod taps
#define CTL_TAB MT(MOD_LCTL, KC_TAB)
#define SH_ESC  MT(MOD_LSFT, KC_ESC)

// Songs

#ifdef AUDIO_ENABLE
// feedback songs
float confirm_song[][2]         = SONG(MARIO_COIN);
float reject_song[][2]          = SONG(MARIO_BUMP);

// dynamic macro songs
float dmacro_recs_song[][2]     = SONG(MARIO_CAVE_1);
float dmacro_rece_song[][2]     = SONG(MARIO_CAVE_2);
float dmacro_play_song[][2]     = SONG(MARIO_PIPE);

// layer toggle songs
float base_song[][2]            = SONG(MARIO_BUMP);
float hyper_song[][2]           = SONG(MARIO_POWERUP_BLOCK);
float adjust_song[][2]          = SONG(MARIO_PIPE);
float raise1_song[][2]          = SONG(MARIO_POWERUP_BLOCK);
float raise2_song[][2]          = SONG(MARIO_POWERUP);
float lower1_song[][2]          = SONG(MARIO_POWERUP_BLOCK);
float lower2_song[][2]          = SONG(MARIO_POWERUP);

// shortcut songs
float caps_on_song[][2]         = SONG(MARIO_ONEUP);
float caps_off_song[][2]        = SONG(MARIO_ONEUP);
float save_song[][2]            = SONG(MARIO_COIN);
float cut_song[][2]             = SONG(MARIO_STOMP);
float copy_song[][2]            = SONG(MARIO_STOMP);
float paste_song[][2]           = SONG(MARIO_FIREBALL);
float undo_song[][2]            = SONG(MARIO_KICK);
float redo_song[][2]            = SONG(MARIO_KICK);
#endif


/*
██╗  ██╗███████╗██╗   ██╗███╗   ███╗ █████╗ ██████╗ ███████╗
██║ ██╔╝██╔════╝╚██╗ ██╔╝████╗ ████║██╔══██╗██╔══██╗██╔════╝
█████╔╝ █████╗   ╚████╔╝ ██╔████╔██║███████║██████╔╝███████╗
██╔═██╗ ██╔══╝    ╚██╔╝  ██║╚██╔╝██║██╔══██║██╔═══╝ ╚════██║
██║  ██╗███████╗   ██║   ██║ ╚═╝ ██║██║  ██║██║     ███████║
╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝     ╚══════╝
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base

        |-------------------------------------------------------------------------------------------------|
        |[encoder]|   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | <[bk]>|
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |<ct>[tab]|   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   |[enter]|
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |<sh>[esc]|   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   '   |
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |   <KB>  | [dm1] | <meta>|<ct+sh>|  <L1> |  <os> |  [_]  | <R1>  |<[del]>| [caps]| [dm2] | <KB>  |
        |-------------------------------------------------------------------------------------------------|

        * Tab:      CTRL on hold
        * Esc:      SHIFT on hold

    */
    [_BASE] = LAYOUT_planck_grid(
        ENCODER, KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,     KC_Y,     KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPACE,
        CTL_TAB, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,     KC_H,     KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SH_ESC,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,     KC_N,     KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
        HYPER,   DM_PLY1, KC_LALT, CTRL_SH, LOWER1, KC_LGUI,  KC_SPACE, RAISE1, KC_DEL,  KC_CAPS, DM_PLY2, HYPER
    ),

    /* L1 - numbers and brackets

        |-----------------------------------------------------------------------------------------------|
        |       |   1   |   2   |   3   |   $   |   *   |   /   |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   4   |   5   |   6   |   .   |   +   |   =   |   [   |   ]   |   {   |   }   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   7   |   8   |   9   |   0   |   -   |   _   |   (   |   )   |   <   |   >   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |  <L2> |       |       |  <F>  |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|   

        * The following symbols are found on other layers: $ * /
        * It is recommended to not primarily use this layer for those symbols
        * They are merely on this layer for numerical-typing convenience

    */
    [_L1] = LAYOUT_planck_grid(
        _______, KC_1,    KC_2,    KC_3,    KC_DLR, KC_ASTR, KC_SLSH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, KC_4,    KC_5,    KC_6,    KC_DOT, KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
        _______, KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS, KC_UNDS, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, _______,
        _______, _______, _______, _______, LOWER2, _______, _______, ADJUST,  _______, _______, _______, _______
    ),

    /* R1 - symbols and movement

        |-----------------------------------------------------------------------------------------------|
        |       |   !   |   @   |   #   |       |   *   |   /   | [home]|[pg dn]|[pg up]| [end] |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   $   |   %   |   ^   |       |   +   |   =   | [left]| [down]| [up]  |[right]|       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   &   |   *   |   (   |   )   |   -   |   _   |   ~   |   `   |   |   |   \   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |  <F>  |       |       | <R2>  |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        * It is not recomended to use the (  ) symbols on this layer
        * They are merely here for uniformity

    */
    [_R1] = LAYOUT_planck_grid(
        _______, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, KC_ASTR, KC_SLSH, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   _______,
        _______, KC_DLR,  KC_PERC, KC_CIRC, XXXXXXX, KC_PLUS, KC_EQL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
        _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_UNDS, KC_TILD, KC_GRV,  KC_PIPE, KC_BSLS,  _______,
        _______, _______, _______, _______, ADJUST,  _______, _______, RAISE2,  _______, _______, _______,  _______
    ),

    /* L2 - static macros

        |-----------------------------------------------------------------------------------------------|
        |       |       |       |[email]|       |       |       |       |       |       |[phone]|[clear]|
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |[shbng]|       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |[ch744]|       | [gcmt]| [venv]|       | [name]|       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | [BASE]|       |       | xxxxx |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        * DO NOT INCLUDE DESTRUCTIVE MACROS

    */
    [_L2] = LAYOUT_planck_grid(
        _______, XXXXXXX, XXXXXXX, M_EMAIL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_PHONE, M_CLEAR,
        _______, XXXXXXX, M_SHBNG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, M_CHMOD, XXXXXXX, M_CMT,   M_VENV,  XXXXXXX, M_NAME,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, BASE,    _______, _______, XXXXXXX, _______, _______, _______, _______
    ),

    /* R2 - mouse navigation

        |-----------------------------------------------------------------------------------------------|
        |       |       |       |       |       |       |       | S lt  | S up  | S dn  | S rt  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       | M lt  | M dn  | M up  | M rt  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       | L Ck  | R ck  | Slow  | Fast  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | xxxxx |       |       |[BASE] |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

    */
    [_R2] = LAYOUT_planck_grid(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_ACL1, KC_ACL2, _______,
        _______, _______, _______, _______, XXXXXXX, _______, _______, BASE,    _______, _______, _______, _______
    ),

    /* I3 - emulate Linux i3 config using Windows PowerToys

        |-----------------------------------------------------------------------------------------------|
        |       |olkb_00|olkb_01|olkb_02|olkb_03|olkb_04|olkb_05|olkb_06|olkb_07|olkb_08|olkb_09|       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |olkb_10|olkb_11|olkb_12|olkb_13|olkb_14|olkb_15|olkb_16|olkb_17|olkb_18|olkb_19|      |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        | [run] |olkb_20|olkb_21|olkb_22|olkb_23|olkb_24|olkb_25|olkb_26|olkb_27|olkb_28|olkb_29| [kill]|
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       | xxxxx |olkb_35|       |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

    */
    [_I3] = LAYOUT_planck_grid(
        _______, OLKB_00, OLKB_01, OLKB_02, OLKB_03, OLKB_04, OLKB_05, OLKB_06, OLKB_07, OLKB_08, OLKB_09, _______,
        _______, OLKB_10, OLKB_11, OLKB_12, OLKB_13, OLKB_14, OLKB_15, OLKB_16, OLKB_17, OLKB_18, OLKB_19, _______,
        _______, OLKB_20, OLKB_21, OLKB_22, OLKB_23, OLKB_24, OLKB_25, OLKB_26, OLKB_27, OLKB_28, OLKB_29, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OLKB_35, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* F - function keys, system keys (sleep, wake, power down), KVM switch hotkeys, print screen

        |-----------------------------------------------------------------------------------------------|
        |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |[sleep]|
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |[pr_sc]|  F11  |  F12  |  F13  |  F14  |  F15  |  F16  |  F17  |  F18  |  F19  |  F20  | [wake]|
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |  F21  |  F22  |  F23  |  F24  |       |       |KVM PC1|KVM PC2|KVM OUT| KVM IN|[power]|
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | xxxxx | [BASE]|[BASE] | xxxxx |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

    */
    [_F] = LAYOUT_planck_grid(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_SLEP,
        KC_PSCR, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_WAKE,
        _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  XXXXXXX, XXXXXXX, KVM_PC1, KVM_PC2, KVM_OUT, KVM_IN  , KC_PWR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BASE,    BASE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* KB - modify keyboard in terms of dynamic macros, rotary select, audio settings, and reboot

        |--------------------------------------------------------------------------------------------------|
        |         |       |       |       |       |       |       |scrll h|scrll v|scrll v|scrll h|        |
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------|
        |[aud_tog]|       |       |       |       |       |       |arrow h|arrow v|arrow v|arrow h|[pio_tg]|
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------|
        |[clk_tog]|       |       |       |  vol  | bright|       | media |       |       |       |[mod_tg]|
        |---------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------|
        | [reboot]|[dm1 r]|       |       |       | [BASE]|[BASE] |       |       |       |[dm2 r]|[reboot]|
        |--------------------------------------------------------------------------------------------------|

    */
    [_KB] = LAYOUT_planck_grid(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, R_SC_H,  R_SC_V,  R_SC_V,  R_SC_H,  _______,
        AU_TOG,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, R_AR_H,  R_AR_V,  R_AR_V,  R_AR_H,  MU_TOG,
        CK_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, R_VOL,   R_BRI,   XXXXXXX, R_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, MU_MOD,
        RESET,   DM_REC1, _______, _______, _______,   BASE,    BASE,  _______, _______, _______, DM_REC2, RESET
    ),

};


/*
 ██████╗██╗   ██╗███████╗████████╗ ██████╗ ███╗   ███╗    ██╗      ██████╗  ██████╗ ██╗ ██████╗
██╔════╝██║   ██║██╔════╝╚══██╔══╝██╔═══██╗████╗ ████║    ██║     ██╔═══██╗██╔════╝ ██║██╔════╝
██║     ██║   ██║███████╗   ██║   ██║   ██║██╔████╔██║    ██║     ██║   ██║██║  ███╗██║██║
██║     ██║   ██║╚════██║   ██║   ██║   ██║██║╚██╔╝██║    ██║     ██║   ██║██║   ██║██║██║
╚██████╗╚██████╔╝███████║   ██║   ╚██████╔╝██║ ╚═╝ ██║    ███████╗╚██████╔╝╚██████╔╝██║╚██████╗
 ╚═════╝ ╚═════╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝     ╚═╝    ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝ ╚═════╝
*/


// Keyboard initialization

void keyboard_post_init_user(void) {
    clicky_off();
}

// Dynamic macros

static bool prerecord_clicky = false;

void dynamic_macro_record_start_user(void) {
    prerecord_clicky = is_clicky_on();
    if (!prerecord_clicky) {
        clicky_on();
    }

    #ifdef AUDIO_ENABLE
    PLAY_SONG(dmacro_recs_song);
    #endif
}

void dynamic_macro_record_end_user(int8_t direction) {
    if (!prerecord_clicky) {
        clicky_off();
    }

    #ifdef AUDIO_ENABLE
    PLAY_SONG(dmacro_rece_song);
    #endif
}

void dynamic_macro_play_user(int8_t direction) {
    #ifdef AUDIO_ENABLE
    PLAY_SONG(dmacro_play_song);
    #endif
}

// Layers

layer_state_t layer_state_set_user(layer_state_t state) {
    // layer music should not go in here
    // possibly add LED effects here
    return state;
}

// Keycode events

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool caps_active = false;
    static int kvm_pc = 1;

    switch (keycode) {

        /*
        ██   ██ ███████ ██    ██  ██████  ██████  ██████  ███████ ███████ 
        ██  ██  ██       ██  ██  ██      ██    ██ ██   ██ ██      ██      
        █████   █████     ████   ██      ██    ██ ██   ██ █████   ███████ 
        ██  ██  ██         ██    ██      ██    ██ ██   ██ ██           ██ 
        ██   ██ ███████    ██     ██████  ██████  ██████  ███████ ███████
        */

        // kvm switch
        case KVM_PC1:
            if(record->event.pressed) {
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_1);
                kvm_pc = 1;
            }
            break;
        case KVM_PC2:
            if(record->event.pressed) {
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_2);
                kvm_pc = 2;
            }
            break;
        case KVM_IN:
            if(record->event.pressed) {
                tap_code(KC_RALT); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_RALT);
            }
            break;
        case KVM_OUT:
            if(record->event.pressed) {
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                tap_code(KC_SLCK); wait_ms(KVM_TAP_DELAY);
                if (kvm_pc == 1) {
                    tap_code(KC_4);
                    kvm_pc = 2;
                }
                else {
                    tap_code(KC_3);
                    kvm_pc = 1;
                }
            }
            break;

        // contrl+shift
        case CTRL_SH:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
            }
            else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            break;

        // caps lock
        case KC_CAPS:
            if (record->event.pressed) {
                caps_active = !caps_active;
            }
            break;

        // rotary encoder state selection
        case R_VOL:
            if (record->event.pressed) {
                rotary_state = E_VOLUME;
            }
            break;
        case R_MEDIA:
            if (record->event.pressed) {
                rotary_state = E_MEDIA;
            }
            break;
        case R_BRI:
            if (record->event.pressed) {
                rotary_state = E_BRIGHTNESS;
            }
            break;
        case R_SC_V:
            if (record->event.pressed) {
                rotary_state = E_SCROLL_V;
            }
            break;
        case R_SC_H:
            if (record->event.pressed) {
                rotary_state = E_SCROLL_H;
            }
            break;
        case R_AR_V:
            if (record->event.pressed) {
                rotary_state = E_ARROW_V;
            }
            break;
        case R_AR_H:
            if (record->event.pressed) {
                rotary_state = E_ARROW_H;
            }
            break;
        case ENCODER:
            if (record->event.pressed) {
                if (rotary_state == E_VOLUME) {
                    tap_code(KC_MUTE);  // toggle mute
                }
                else if (rotary_state == E_MEDIA) {
                    tap_code(KC_MPLY);  // play/pause media
                }
                else if (rotary_state == E_SCROLL_V || rotary_state == E_SCROLL_H) {
                    tap_code(KC_BTN3);  // middle mouse button
                }
            }
            return false;

        /*
        ███    ███  █████   ██████ ██████   ██████  ███████ 
        ████  ████ ██   ██ ██      ██   ██ ██    ██ ██      
        ██ ████ ██ ███████ ██      ██████  ██    ██ ███████ 
        ██  ██  ██ ██   ██ ██      ██   ██ ██    ██      ██ 
        ██      ██ ██   ██  ██████ ██   ██  ██████  ███████
        */

        case M_CLEAR:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_E)); // go to start of line
                tap_code16(LCTL(KC_U)); // clear to beginning of line
            }
            break;
        case M_NAME:
            if (record->event.pressed) {
                SEND_STRING(NAME);
            }
            break;
        case M_EMAIL:
            if (record->event.pressed) {
                SEND_STRING(EMAIL);
            }
            break;
        case M_PHONE:
            if (record->event.pressed) {
                SEND_STRING(PHONE);
            }
            break;
        case M_SHBNG:
            if (record->event.pressed) {
                SEND_STRING("#!/usr/bin/env ");
            }
            break;
        case M_CHMOD:
            if (record->event.pressed) {
                SEND_STRING("chmod 744 ");
            }
            break;
        case M_CMT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m ''");
                tap_code(KC_LEFT);
            }
            break;
        case M_VENV:
            if (record->event.pressed) {
                SEND_STRING("source *env*/bin/activate");
            }
            break;
    };

    /*
         █████  ██    ██ ██████  ██  ██████ 
        ██   ██ ██    ██ ██   ██ ██ ██    ██ 
        ███████ ██    ██ ██   ██ ██ ██    ██ 
        ██   ██ ██    ██ ██   ██ ██ ██    ██ 
        ██   ██  ██████  ██████  ██  ██████
    */

    #ifdef AUDIO_ENABLE
    if (record->event.pressed) {
        switch (keycode) {
            case KC_CAPS:
                if (caps_active) {
                    PLAY_SONG(caps_on_song);
                }
                else {
                    PLAY_SONG(caps_off_song);
                }
                break;

            // layer keys

            case BASE:
                PLAY_SONG(base_song);
                break;
            case HYPER:
                PLAY_SONG(hyper_song);
                break;
            case ADJUST:
                PLAY_SONG(adjust_song);
                break;
            case LOWER1:
                PLAY_SONG(lower1_song);
                break;
            case LOWER2:
                PLAY_SONG(lower2_song);
                break;
            case RAISE1:
                PLAY_SONG(raise1_song);
                break;
            case RAISE2:
                PLAY_SONG(raise2_song);
                break;

            // shortcuts

            case KC_S: // CTRL+S
                if (CTL_MASK) {
                    PLAY_SONG(save_song);
                }
                break;
            case KC_C: // CTRL+C
                if (CTL_MASK) {
                    PLAY_SONG(copy_song);
                }
                break;
            case KC_V: // CTRL+V
                if (CTL_MASK) {
                    PLAY_SONG(paste_song);
                }
                break;
            case KC_X: // CTRL+X
                if (CTL_MASK) {
                    PLAY_SONG(cut_song);
                }
                break;
            case KC_Z: // CTRL+Z
                if (CTL_MASK) {
                    PLAY_SONG(undo_song);
                }
                break;
            case KC_Y: // CTRL+Y
                if (CTL_MASK) {
                    PLAY_SONG(redo_song);
                }
                break;

            // kb layer

            case R_VOL:
            case R_MEDIA:
            case R_BRI:
            case R_SC_V:
            case R_SC_H:
            case R_AR_V:
            case R_AR_H:
                PLAY_SONG(confirm_song);
                break;

            case DM_REC1:
            case DM_REC2:
            case AU_TOG:
            case CK_TOGG:
            case MU_TOG:
            case MU_MOD:
            case RESET:
                break;

            default:
                if (IS_LAYER_ON(_KB)) {
                    PLAY_SONG(reject_song);
                }
        };
    }
    #endif

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    
}


/*
██████╗  ██████╗ ████████╗ █████╗ ██████╗ ██╗   ██╗    ███████╗███╗   ██╗ ██████╗ ██████╗ ██████╗ ███████╗██████╗
██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗
██████╔╝██║   ██║   ██║   ███████║██████╔╝ ╚████╔╝     █████╗  ██╔██╗ ██║██║     ██║   ██║██║  ██║█████╗  ██████╔╝
██╔══██╗██║   ██║   ██║   ██╔══██║██╔══██╗  ╚██╔╝      ██╔══╝  ██║╚██╗██║██║     ██║   ██║██║  ██║██╔══╝  ██╔══██╗
██║  ██║╚██████╔╝   ██║   ██║  ██║██║  ██║   ██║       ███████╗██║ ╚████║╚██████╗╚██████╔╝██████╔╝███████╗██║  ██║
╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
*/

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (rotary_state) {
        case E_VOLUME:
            if (clockwise) {
                tap_code(KC_VOLU);
            }
            else {
                tap_code(KC_VOLD);
            }
            break;
        case E_MEDIA:
            if (clockwise) {
                tap_code(KC_MNXT);
            }
            else {
                tap_code(KC_MPRV);
            }
            break;
        case E_BRIGHTNESS:
            if (clockwise) {
                tap_code(KC_BRIU);
            }
            else {
                tap_code(KC_BRID);
            }
            break;
        case E_SCROLL_V:
            if (clockwise) {
                // tap_code(KC_PGDN);
                for (int i=0; i<SCROLL_INTERVAL; i++) {
                    tap_code(KC_WH_D);
                }
            }
            else {
                // tap_code(KC_PGUP);
                for (int i=0; i<SCROLL_INTERVAL; i++) {
                    tap_code(KC_WH_U);
                }
            }
            break;
        case E_SCROLL_H:
            if (clockwise) {
                for (int i=0; i<SCROLL_INTERVAL; i++) {
                    tap_code(KC_WH_R);
                }
            }
            else {
                for (int i=0; i<SCROLL_INTERVAL; i++) {
                    tap_code(KC_WH_L);
                }
            }
            break;
        case E_ARROW_V:
            if (clockwise) {
                tap_code(KC_DOWN);
            }
            else {
                tap_code(KC_UP);
            }
            break;
        case E_ARROW_H:
            if (clockwise) {
                tap_code(KC_RIGHT);
            }
            else {
                tap_code(KC_LEFT);
            }
            break;
    }
}
#endif
