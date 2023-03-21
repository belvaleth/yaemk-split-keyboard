#include QMK_KEYBOARD_H
#include "keymap_us_international.h"

enum Layers {
    _BASE = 0,
    _NUM  = 1,
    _FUNC = 2,
    _RGB  = 3
};

enum Encoder {
    _ENCODER_LEFT  = 0,
    _ENCODER_RIGHT = 1,
};

enum my_keycodes
{
    UP_DOWN = SAFE_RANGE,
    LEFT_RIGHT
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_BASE] = LAYOUT( \
     KC_GRAVE       , KC_1          , KC_2          , KC_3          , KC_4          , KC_5          , KC_ESCAPE         ,                                 KC_EQUAL          , KC_6          , KC_7          , KC_8          , KC_9          , KC_0          , KC_MINUS      ,\
     KC_TAB         , KC_Q          , KC_W          , KC_E          , KC_R          , KC_T          , LEFT_RIGHT        ,                                 KC_DELETE         , KC_Y          , KC_U          , KC_I          , KC_O          , KC_P          , KC_BSLASH     ,\
     KC_LALT        , KC_A          , KC_S          , KC_D          , KC_F          , KC_G          , KC_LBRACKET       ,                                 KC_RBRACKET       , KC_H          , KC_J          , KC_K          , KC_L          , KC_SCOLON     , KC_QUOTE      ,\
     KC_LCTL        , KC_Z          , KC_X          , KC_C          , KC_V          , KC_B          , LALT_T(KC_SPACE)  , KC_LSFT       ,  KC_LCTL      , KC_ENT            , KC_N          , KC_M          , KC_COMM       , KC_DOT        , KC_SLASH      , TO(_NUM)      ,\
                                                      KC_MUTE       , KC_LWIN       , MO(_FUNC)     , LALT_T(KC_SPACE)  , KC_LSFT       ,  KC_LCTL      , KC_ENT            , KC_BSPACE     , UP_DOWN       , TO(_RGB) \
  ),
   [_NUM] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 _______           , _______       , KC_KP_7       , KC_KP_8       , KC_KP_9       , KC_KP_SLASH   , KC_NUMLOCK    ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 _______           , _______       , KC_KP_4       , KC_KP_5       , KC_KP_6       , KC_KP_ASTERISK, KC_NO         ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 _______           , _______       , KC_KP_1       , KC_KP_2       , KC_KP_3       , KC_KP_MINUS   , KC_NO         ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , KC_KP_ENTER   , KC_KP_DOT     , KC_KP_0       , KC_KP_PLUS    , TO(_BASE)     ,\
                                                      _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , _______       , _______ \
  ),
   [_FUNC] = LAYOUT( \
    _______         , KC_F1         , KC_F2         , KC_F3         , KC_F4         , KC_F5         , _______           ,                                 _______           , KC_F6         , KC_F7         , KC_F8         , KC_F9         , KC_F10        , KC_F11        ,\
    _______         , _______       , KC_UP         , _______       , KC_PGUP       , _______       , KC_HOME           ,                                 KC_END            , _______       , _______       , _______       , _______       , _______       , KC_F12        ,\
    KC_CAPS         , KC_LEFT       , KC_DOWN       , KC_RIGHT      , KC_PGDN       , _______       , _______           ,                                 _______           , _______       , _______       , _______       , _______       , _______       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , _______       , _______       , _______       , _______       , _______       ,\
                                                      _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , _______       , _______ \
  ),
  [_RGB] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 RGB_TOG           , RGB_HUD       , RGB_HUI       , _______       , RGB_RMOD      , RGB_MOD       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 _______           , RGB_SAD       , RGB_SAI       , _______       , RGB_SPD       , RGB_SPI       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           ,                                 _______           , RGB_VAD       , RGB_VAI       , _______       , _______       , _______       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , _______       , _______       , _______       , _______       , KC_NO         ,\
                                                      _______       , _______       , _______       , _______           , _______       , _______       , _______           , _______       , _______       , TO(_BASE) \
  )
};

// clang-format on

#if defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return false;
        case RSFT_T(KC_SPC):
            return false;
        default:
            return true;
    }
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    layer_state_t current_state = get_highest_layer(layer_state);

    if (index == _ENCODER_LEFT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                    tap_code(KC_RIGHT);
                    break;
                case _NUM:
                    tap_code(KC_AUDIO_VOL_UP);
                    break;
                case _FUNC:
                    tap_code(KC_AUDIO_VOL_UP);
                    break;
                case _RGB:
                    tap_code(KC_AUDIO_VOL_UP);
                    break;
                default:
                    tap_code(KC_RIGHT);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                    tap_code(KC_LEFT);
                    break;
                case _NUM:
                    tap_code(KC_AUDIO_VOL_DOWN);
                    break;
                case _FUNC:
                    tap_code(KC_AUDIO_VOL_DOWN);
                    break;
                case _RGB:
                    tap_code(KC_AUDIO_VOL_DOWN);
                    break;
                default:
                    tap_code(KC_RIGHT);
                    break;
            }
        }
    } else if (index == _ENCODER_RIGHT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _NUM:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _FUNC:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _RGB:
                    rgb_matrix_increase_val();
                    break;
                default:
                    tap_code(KC_MS_WH_DOWN);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _NUM:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _FUNC:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _RGB:
                    rgb_matrix_decrease_val();
                    break;
                default:
                    tap_code(KC_MS_WH_UP);
                    break;
            }
        }
    }

    return false;
}
#endif

#if defined(OLED_ENABLE)

#    define w_val(str, val)                         \
        snprintf(buffer, sizeof(buffer), str, val); \
        oled_write_ln(buffer, false)

void render_display(void) {
    static layer_state_t last_state    = ~0;
    layer_state_t        current_state = get_highest_layer(layer_state);

    if (last_state < _NUM && current_state < _NUM) {
        // Don't do anything if we are on the default layers
        return;
    } else if (last_state != current_state) {
        oled_clear();
        last_state = current_state;
    }

    char buffer[25];
    switch (current_state) {
        case _FUNC:
            oled_write_ln("Function", false);
            w_val("Caps: %s", host_keyboard_led_state().caps_lock ? "On" : "Off" );
            w_val("Num: %s", host_keyboard_led_state().num_lock ? "On" : "Off" );
/*#    if defined(DEBUG_MATRIX_SCAN_RATE)
            oled_write_ln("Scan Freq:", false);
            w_val("%05ld", get_matrix_scan_rate());
#    endif*/
            break;
        case _RGB:
#    if defined(RGB_MATRIX_ENABLE)
            oled_write_ln("RGB\n", false);
            w_val("En:   %03d\n", rgb_matrix_config.enable);
            w_val("Mode: %03d\n", rgb_matrix_config.mode);
            w_val("Hue:  %03d\n", rgb_matrix_config.hsv.h);
            w_val("Sat:  %03d\n", rgb_matrix_config.hsv.s);
            w_val("Bri:  %03d\n", rgb_matrix_config.hsv.v);
            w_val("Spd:  %03d\n", rgb_matrix_config.speed);
            break;
#    endif
        case _NUM:
            oled_write_ln("Numpad", false);
            w_val("Caps: %s", host_keyboard_led_state().caps_lock ? "On" : "Off" );
            w_val("Num: %s", host_keyboard_led_state().num_lock ? "On" : "Off" );
            oled_write_ln("\n", false);
            oled_write_ln("   789/", false);
            oled_write_ln("   456*", false);
            oled_write_ln("   123-", false);
            oled_write_ln("   E.0+", false);
            break;
        default:
            if (is_keyboard_master()) {
                oled_write_ln("\x7QWERTY\x7", false);
                w_val("Caps: %s", host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ? "On" : "Off" );
                w_val("Num: %s", host_keyboard_leds() & (1<<USB_LED_NUM_LOCK) ? "On" : "Off" );
                oled_write_ln("\n", false);
                if (is_keyboard_left())
                {
                    oled_write_ln("Spc(Alt)", false);
                    oled_write_ln("Shift", false);
                }
                else if (!is_keyboard_left())
                {
                    oled_write_ln("Enter", false);
                    oled_write_ln("Control", false);
                }
            } else {
                oled_write_ln("QWERTY", false);
                w_val("Caps: %s", host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ? "On" : "Off" );
                w_val("Num: %s", host_keyboard_leds() & (1<<USB_LED_NUM_LOCK) ? "On" : "Off" );
                oled_write_ln("\n", false);
               if (is_keyboard_left())
                {
                    oled_write_ln("Spc(Alt)", false);
                    oled_write_ln("Shift", false);
                }
                else if (!is_keyboard_left())
                {
                    oled_write_ln("Enter", false);
                    oled_write_ln("Control", false);
                }
            }
            break;
    }
}
#endif

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
        case UP_DOWN:
            if (record->event.pressed)
            {
                if (get_mods() & MOD_MASK_SHIFT)
                {
                    mod_state = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_DOWN);
                    set_mods(mod_state);
                    return false;
                }
                else
                {
                    tap_code(KC_UP);
                    return false;
                }
            }
        case LEFT_RIGHT:
            if (record->event.pressed)
            {
                if (get_mods() & MOD_MASK_SHIFT)
                {
                    mod_state = get_mods();
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_RIGHT);
                    set_mods(mod_state);
                    return false;
                }
                else
                {
                    tap_code(KC_LEFT);
                    return false;
                }
            }
        default:
            return true;
    }
}