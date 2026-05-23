// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │SW7│
     * ├───┼───┬───┐
     * │SW1│SW2│SW3│
     * ├───┼───┼───┤
     * │SW4│SW5│SW6│
     * └───┴───┴───┘
     */
    [0] = LAYOUT(
        MO(1),
        KC_1,   KC_2,   KC_3,
        KC_4,   KC_5,   KC_6
    ),

    [1] = LAYOUT(
        KC_TRNS,
        UG_TOGG,   UG_NEXT,    UG_VALU,
        RGB_M_T,   UG_PREV,   UG_VALD
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
    [1] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) }
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("0"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("1"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
