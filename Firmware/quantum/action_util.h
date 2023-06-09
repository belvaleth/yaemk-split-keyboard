/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "report.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(QMK_KEYS_PER_SCAN) && defined(REGISTER_MULTIPLE_KEYEVENTS_ENABLE)
#    pragma message "REGISTER_MULTIPLE_KEYEVENTS_ENABLE needs QMK_KEYS_PER_SCAN defined to have any effect, setting default of 4."
#    define QMK_KEYS_PER_SCAN 4
#endif

#if !defined(QMK_KEYS_PER_SCAN)
#    define UNREGISTER_KEYCODES_BUFFER_SIZE 1
#else
#    define UNREGISTER_KEYCODES_BUFFER_SIZE QMK_KEYS_PER_SCAN * 2  // Should be plenty of space for any occasion
#endif

typedef struct {
    uint8_t  buffer[UNREGISTER_KEYCODES_BUFFER_SIZE];
    size_t   len;
    uint16_t tap_delay;
} unregister_keycodes_t;

extern report_keyboard_t              keyboard_report;
extern bool                           keyboard_report_has_deferred_keycodes;
extern volatile unregister_keycodes_t unregister_keycodes;

void send_keyboard_report_deferred(void);
void send_keyboard_report(void);
void send_keyboard_report_immediate(void);
void send_keyboard_report_buffered_unregister_keys(void);

/* key */
inline void add_key(uint8_t key) { add_key_to_report(&keyboard_report, key); }

inline void del_key(uint8_t key) { del_key_from_report(&keyboard_report, key); }

inline void clear_keys(void) { clear_keys_from_report(&keyboard_report); }

/* modifier */
uint8_t get_mods(void);
void    add_mods(uint8_t mods);
void    del_mods(uint8_t mods);
void    set_mods(uint8_t mods);
void    clear_mods(void);

/* weak modifier */
uint8_t get_weak_mods(void);
void    add_weak_mods(uint8_t mods);
void    del_weak_mods(uint8_t mods);
void    set_weak_mods(uint8_t mods);
void    clear_weak_mods(void);

/* macro modifier */
uint8_t get_macro_mods(void);
void    add_macro_mods(uint8_t mods);
void    del_macro_mods(uint8_t mods);
void    set_macro_mods(uint8_t mods);
void    clear_macro_mods(void);

/* oneshot modifier */
uint8_t get_oneshot_mods(void);
void    add_oneshot_mods(uint8_t mods);
void    del_oneshot_mods(uint8_t mods);
void    set_oneshot_mods(uint8_t mods);
void    clear_oneshot_mods(void);
bool    has_oneshot_mods_timed_out(void);

uint8_t get_oneshot_locked_mods(void);
void    set_oneshot_locked_mods(uint8_t mods);
void    clear_oneshot_locked_mods(void);

typedef enum { ONESHOT_PRESSED = 0b01, ONESHOT_OTHER_KEY_PRESSED = 0b10, ONESHOT_START = 0b11, ONESHOT_TOGGLED = 0b100 } oneshot_fullfillment_t;
void    set_oneshot_layer(uint8_t layer, uint8_t state);
uint8_t get_oneshot_layer(void);
void    clear_oneshot_layer_state(oneshot_fullfillment_t state);
void    reset_oneshot_layer(void);
bool    is_oneshot_layer_active(void);
uint8_t get_oneshot_layer_state(void);
bool    has_oneshot_layer_timed_out(void);
bool    has_oneshot_swaphands_timed_out(void);

void oneshot_locked_mods_changed_user(uint8_t mods);
void oneshot_locked_mods_changed_kb(uint8_t mods);
void oneshot_mods_changed_user(uint8_t mods);
void oneshot_mods_changed_kb(uint8_t mods);
void oneshot_layer_changed_user(uint8_t layer);
void oneshot_layer_changed_kb(uint8_t layer);

void oneshot_toggle(void);
void oneshot_enable(void);
void oneshot_disable(void);
bool is_oneshot_enabled(void);

/* inspect */
uint8_t has_anymod(void);

#ifdef SWAP_HANDS_ENABLE
void set_oneshot_swaphands(void);
void release_oneshot_swaphands(void);
void use_oneshot_swaphands(void);
void clear_oneshot_swaphands(void);
#endif

#ifdef __cplusplus
}
#endif
