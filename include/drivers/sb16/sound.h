#ifndef SOUND_H
#define SOUND_H

#include <types.h>

#define IOCTL_SOUND_ACQUIRE         1
#define IOCTL_SOUND_RELEASE         2
#define IOCTL_SOUND_SETUP           3
#define IOCTL_SOUND_PAUSE           4
#define IOCTL_SOUND_RESUME          5
#define IOCTL_SOUND_GET_INFO        6
#define IOCTL_SOUND_WAIT_COMPLETION 7

struct sound_card_info
{
    char        name[32];
    uint32_t    max_sample_rate;
    uint32_t    max_bits;
    uint32_t    max_channels;
};

struct sound_params
{
    uint16_t    sample_rate;    // 441000..22050 etc.
    uint8_t     bits;           // 8..16
    uint8_t     channels;       // 1..2
    uint8_t     sign;           // 0 = unsigned, 1 = signed
};

#endif // SOUND_H