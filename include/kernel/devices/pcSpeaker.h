/**
 * @file pcSpeaker.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-12
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef PCSPEAKER_H
#define PCSPEAKER_H

#include <types.h>

extern void pcs_tone_on(uint32_t freq);
extern void pcs_tone_off();
extern void pcs_beep();

#endif // PCSPEAKER_H