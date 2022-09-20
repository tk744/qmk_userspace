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

#pragma once

/* tk definitions */

#define KVM_TAP_DELAY 100       // delay between macro keys for KVM hotkeys

/* qmk definitions */

#define ENCODER_RESOLUTION 4    // dependent on rotary encoder

#define TAP_CODE_DELAY 10       // delay between key press and release on `tapcode(kc)`

#define TAPPING_TERM 200        // mod tap tap-window

// oneshot keys --

#define ONESHOT_TAP_TOGGLE 25   // taps to toggle a one-shot layer/key persistence
#define ONESHOT_TIMEOUT 500     // one-shot layer/key timeout

// dynamic macros --

#define DYNAMIC_MACRO_NO_NESTING

// you can store HALF of this number of keypresses in both macros together
#define DYNAMIC_MACRO_SIZE 256

// mouse/scroll keys and speeds --

#define MK_3_SPEED

// cursor offset per movement
#define MK_C_OFFSET_1 8
#define MK_C_OFFSET_2 16

// time between cursor movements (ms)
#define MK_C_INTERVAL_1 16  // 16 ms = 60 Hz refresh rate
#define MK_C_INTERVAL_2 16

// scroll steps per scroll action
#define MK_W_OFFSET_1 1
#define MK_W_OFFSET_2 1

// time between scroll steps (ms)
#define MK_W_INTERVAL_1 64  // 64 ms = 15 Hz refresh rate
#define MK_W_INTERVAL_2 16


// audio --

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1

#include "music.h"