/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdio.h>
#include <string.h>

// #include "ch32v003fun.h"
//  #include "ssd1306.h"
#include "Sine16bit.h"
// #include "ssd1306_i2c.h"

#define I2C_ADDR 0x74

void i2c_write_register(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    i2c_write_blocking(i2c_default, I2C_ADDR, buf, 2, false);
    // ssd1306_i2c_send(I2C_ADDR, buf, 2);
}

void i2c_send_buffer(uint8_t *buf, uint16_t len)
{
    i2c_write_blocking(i2c_default, I2C_ADDR, buf, len, false);
    // ssd1306_i2c_send(I2C_ADDR, buf, len);
}

void Delay_Ms(uint32_t ms)
{
    sleep_ms(ms / 4);
}

uint8_t purples[] = {10, 13, 19, 38, 43, 52, 65, 88, 107, 115};

struct Letters
{
    uint8_t PI[21];
    uint8_t O[14];
    uint8_t RHO1[16];
    uint8_t PHI[17];
    uint8_t Y[12];
    uint8_t RHO2[10];
    uint8_t ALPHA[14];
    uint8_t SIGMA[10];
    uint8_t PHI_DOTS[3];
    uint8_t VOLCANO[9];
    uint8_t EMBERS_LEFT[4];
    uint8_t EMBERS_RIGHT[6];
    uint8_t STARS[8];
};

union LEDS
{
    struct Letters letters;
    uint8_t all[144];
};

const union LEDS leds = {
    .letters.PI = {49, 65, 81, 97, 113, 129, 34, 50, 66, 82, 98, 114, 130, 1, 17, 33, 2, 18, 3, 19, 35},
    .letters.O = {20, 4, 51, 67, 83, 99, 115, 131, 116, 100, 84, 68, 52, 36},
    .letters.RHO1 = {86, 70, 54, 38, 22, 6, 5, 21, 37, 53, 69, 85, 101, 117, 133, 132},
    .letters.PHI = {87, 71, 55, 8, 24, 40, 103, 119, 135, 102, 118, 134, 56, 72, 88, 104, 120},
    .letters.Y = {9, 25, 41, 57, 89, 105, 121, 137, 136, 73, 10, 26},
    .letters.RHO2 = {43, 27, 11, 58, 42, 74, 90, 106, 122, 138},
    .letters.ALPHA = {12, 28, 76, 92, 108, 124, 44, 60, 59, 75, 91, 107, 123, 139},
    .letters.SIGMA = {13, 29, 45, 61, 140, 77, 93, 109, 125, 141},
    .letters.PHI_DOTS = {39, 23, 7},
    .letters.VOLCANO = {143, 127, 111, 95, 15, 31, 47, 63, 79},
    .letters.EMBERS_LEFT = {32, 48, 80, 128},
    .letters.EMBERS_RIGHT = {16, 14, 30, 142, 46, 78},
    .letters.STARS = {144, 96, 64, 112, 126, 110, 94, 62},
};

struct Letter
{
    uint8_t *leds;
    uint8_t len;
};
struct Letter LETTERS[] = {
    {.leds = leds.letters.PI, .len = sizeof(leds.letters.PI)},
    {.leds = leds.letters.O, .len = sizeof(leds.letters.O)},
    {.leds = leds.letters.RHO1, .len = sizeof(leds.letters.RHO1)},
    {.leds = leds.letters.PHI, .len = sizeof(leds.letters.PHI)},
    {.leds = leds.letters.Y, .len = sizeof(leds.letters.Y)},
    {.leds = leds.letters.RHO2, .len = sizeof(leds.letters.RHO2)},
    {.leds = leds.letters.ALPHA, .len = sizeof(leds.letters.ALPHA)},
    {.leds = leds.letters.SIGMA, .len = sizeof(leds.letters.SIGMA)},
    {.leds = leds.letters.PHI_DOTS, .len = sizeof(leds.letters.PHI_DOTS)},
};

uint8_t ASH_LAYER[] = {1, 17, 33, 2, 18, 3, 35, 51, 4, 20, 36, 5, 6, 22, 55, 8, 24, 56, 72, 9, 25, 41, 57, 73, 26, 42,
                       58, 11, 27, 44, 76, 29};

struct pos
{
    uint16_t x, y;
};
// LED positions as converted from the assembly production position file
struct pos POSITIONS[] = {
    {0, 0},        // 0
    {1055, 3925},  // 1
    {1880, 3875},  // 2
    {2355, 3850},  // 3
    {3553, 3825},  // 4
    {4630, 3750},  // 5
    {4830, 3650},  // 6
    {6279, 2975},  // 7
    {6130, 3900},  // 8
    {7155, 3900},  // 9
    {8275, 3815},  // 10
    {9355, 3725},  // 11
    {10205, 3400}, // 12
    {11682, 3650}, // 13
    {7740, 915},   // 14
    {8004, 3400},  // 15
    {6797, 1255},  // 16
    {1355, 3875},  // 17
    {2130, 3875},  // 18
    {2600, 3840},  // 19
    {3807, 3775},  // 20
    {4605, 3975},  // 21
    {5079, 3650},  // 22
    {6555, 3050},  // 23
    {6357, 4000},  // 24
    {7379, 3800},  // 25
    {8505, 3750},  // 26
    {9582, 3850},  // 27
    {10480, 3675}, // 28
    {11529, 3825}, // 29
    {8685, 995},   // 30
    {7579, 3250},  // 31
    {6105, 1775},  // 32
    {1628, 3900},  // 33
    {2230, 4050},  // 34
    {2828, 3850},  // 35
    {4030, 3900},  // 36
    {4679, 4225},  // 37
    {5225, 3790},  // 38
    {6380, 3225},  // 39
    {6380, 4325},  // 40
    {7630, 3850},  // 41
    {8855, 3800},  // 42
    {9330, 4350},  // 43
    {10480, 3875}, // 44
    {11505, 4025}, // 45
    {10555, 425},  // 46
    {7279, 2850},  // 47
    {5372, 1235},  // 48
    {1456, 4100},  // 49
    {2255, 4200},  // 50
    {3330, 3900},  // 51
    {4057, 4065},  // 52
    {4679, 4475},  // 53
    {5355, 4025},  // 54
    {5855, 3975},  // 55
    {6579, 3925},  // 56
    {7879, 3875},  // 57
    {9130, 3800},  // 58
    {10405, 4325}, // 59
    {10507, 4125}, // 60
    {11530, 4225}, // 61
    {12204, 0},    // 62
    {7080, 2400},  // 63
    {2145, 1535},  // 64
    {1406, 4300},  // 65
    {2278, 4375},  // 66
    {3280, 4075},  // 67
    {4105, 4215},  // 68
    {4680, 4700},  // 69
    {5205, 4175},  // 70
    {5729, 4175},  // 71
    {6855, 3900},  // 72
    {8082, 3975},  // 73
    {9080, 4050},  // 74
    {10304, 4575}, // 75
    {10680, 3950}, // 76
    {11657, 4425}, // 77
    {12130, 1450}, // 78
    {6855, 1875},  // 79
    {4737, 765},   // 80
    {1380, 4475},  // 81
    {2280, 4550},  // 82
    {3280, 4300},  // 83
    {4129, 4450},  // 84
    {4682, 4900},  // 85
    {5005, 4325},  // 86
    {6030, 4450},  // 87
    {6955, 4175},  // 88
    {7879, 4100},  // 89
    {9030, 4450},  // 90
    {10205, 4725}, // 91
    {10804, 4100}, // 92
    {11857, 4550}, // 93
    {12957, 425},  // 94
    {5880, 2200},  // 95
    {1825, 795},   // 96
    {1305, 4650},  // 97
    {2380, 4700},  // 98
    {3355, 4450},  // 99
    {4105, 4625},  // 100
    {4682, 5100},  // 101
    {6355, 5300},  // 102
    {6282, 4525},  // 103
    {6832, 4350},  // 104
    {7904, 4300},  // 105
    {9004, 4850},  // 106
    {9950, 4640},  // 107
    {10907, 4225}, // 108
    {12130, 4700}, // 109
    {10980, 1500}, // 110
    {5654, 2600},  // 111
    {1000, 1920},  // 112
    {1255, 4850},  // 113
    {2580, 4750},  // 114
    {3450, 4590},  // 115
    {3910, 4690},  // 116
    {4679, 5325},  // 117
    {6354, 5500},  // 118
    {6382, 4750},  // 119
    {6630, 4525},  // 120
    {7905, 4675},  // 121
    {8955, 5150},  // 122
    {10029, 4875}, // 123
    {11005, 4350}, // 124
    {12380, 4725}, // 125
    {11307, 2700}, // 126
    {5279, 3000},  // 127
    {575, 165},    // 128
    {955, 4800},   // 129
    {2780, 4775},  // 130
    {3705, 4690},  // 131
    {4382, 5550},  // 132
    {4630, 5525},  // 133
    {6130, 5600},  // 134
    {6407, 5050},  // 135
    {7755, 5050},  // 136
    {7805, 4850},  // 137
    {8729, 5350},  // 138
    {10080, 5050}, // 139
    {11405, 4475}, // 140
    {12480, 5025}, // 141
    {9462, 1720},  // 142
    {4830, 3275},  // 143
    {0, 915},      // 144
};

uint32_t r_state = 1;

// from https://en.wikipedia.org/wiki/Xorshift
/* The state must be initialized to non-zero */
uint32_t xorshift32(uint32_t *state)
{
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return *state = x;
}

uint32_t rand(uint32_t mask)
{
    return xorshift32(&r_state) & mask;
}

const int FPS = 64;
const int WAIT_MS = 1000 / FPS;

void clear_screen(uint8_t *screenbuf)
{
    memset(screenbuf + 1, 0, 144);
}
void fade_screenbuf_purple(uint8_t *screenbuf, uint8_t fade_to, uint8_t fade_purple_to, int speed)
{
    for (int i = 1; i < 145; i++)
    {
        uint8_t t = fade_to;
        for (int j = 0; j < sizeof(purples); j++)
        {
            if (i == purples[j])
            {
                t = fade_purple_to;
                break;
            }
        }
        if (screenbuf[i] > t)
        {
            uint8_t delta = (screenbuf[i] - t) >> speed;
            if (delta == 0)
                delta = 1;
            screenbuf[i] -= delta;
        }
    }
}
void fade_screenbuf(uint8_t *screenbuf, uint8_t fade_to, int speed)
{
    fade_screenbuf_purple(screenbuf, fade_to, 8, speed);
}

void volcano_eruption(uint8_t *screenbuf)
{
    int f;

    // show volcano
    int v = 0;
    for (f = 0; f < FPS * 2; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 8, 3);
        if (f % 8 == 0 && v < sizeof(leds.letters.VOLCANO))
        {
            screenbuf[leds.letters.VOLCANO[v]] = 0x80;
            v++;
        }
        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }

    int last = 3;
    v = 0;
    // sparkle phi dot
    for (f = 0; f < FPS * 30; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 8, 3);
        if (f % 8 == 0)
        {
            int i;

            while ((i = rand(3)) >= sizeof(leds.letters.PHI_DOTS) || i == last)
                ;

            int magma_strength = 0x50;
            if (f < FPS * 4)
            {
                // blend up to 0x80 in 4 seconds
                magma_strength = f * 0x50 / (FPS * 4);
            }

            screenbuf[leds.letters.PHI_DOTS[i]] = magma_strength;
            last = i;
        }

        if (f > FPS * 4)
            if (f % 8 == 0)
                for (int j = 0; j < sizeof(leds.letters.VOLCANO); j++)
                    screenbuf[leds.letters.VOLCANO[j]] = 0xa0;

        if (f > FPS * 6)
        {
            int ef = f - FPS * 6;
            if (ef % 8 == 0)
            {
                uint8_t ember_strength = 0x80;
                // fade out embers starting at 27 seconds
                if (f > FPS * 25)
                {
                    int delta = (FPS * 30 - f) * 0x80 / (FPS * 5);
                    ember_strength = delta;
                }

                screenbuf[leds.letters.EMBERS_LEFT[v % sizeof(leds.letters.EMBERS_LEFT)]] = ember_strength;
                screenbuf[leds.letters.EMBERS_RIGHT[v % sizeof(leds.letters.EMBERS_RIGHT)]] = ember_strength;

                if (ef % 8 == 0)
                    for (int j = 0; j < sizeof(leds.letters.VOLCANO); j++)
                        screenbuf[leds.letters.VOLCANO[j]] = 0xa0;

                v++;
            }

            if (f > FPS * 8)
            {
                if (f % 16 == 0)
                {
                    int i = rand(31);
                    screenbuf[ASH_LAYER[i]] = 0xc0;
                }
            }
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }
}

void stars_and_background(uint8_t *screenbuf)
{
    int j;
    for (j = 0; j < sizeof(leds.letters.EMBERS_RIGHT); j++)
    {
        if (j < sizeof(leds.letters.EMBERS_LEFT))
            screenbuf[leds.letters.EMBERS_LEFT[j]] = 0;
        if (j < sizeof(leds.letters.PHI_DOTS))
            screenbuf[leds.letters.PHI_DOTS[j]] = 0;
        screenbuf[leds.letters.EMBERS_RIGHT[j]] = 0;
    }

    int f;
    int last = 8;
    for (f = 0; f < FPS * 25; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 4, 3);
        if (rand(31) == 0)
        {
            int i;
            while (((i = rand(15)) >= sizeof(leds.letters.STARS)) || i == last)
                ;
            screenbuf[leds.letters.STARS[i]] = 0xff;
            last = i;
        }

        if (f > FPS * 10)
        {
            // twinkle purples
            if (rand(31) == 0)
            {
                int i;

                while ((i = (rand(15))) >= sizeof(purples))
                    ;
                screenbuf[purples[i]] = 0xff;
            }
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }
}

const int middleX = 6380;
const int swipe_speed = 7000 / FPS / 2;

void reveal_letters(uint8_t *screenbuf)
{
    int f;
    int i;
    uint8_t screenbuf2[145];
    uint8_t screenbuf3[145];
    memcpy(screenbuf2, screenbuf, 145);
    memset(screenbuf3, 0, 145);
    screenbuf3[0] = screenbuf[0];
    memset(screenbuf + 1, 0, 144);

    for (f = 0; f < FPS * 20; f++)
    {
        fade_screenbuf(screenbuf3, 3, 3);
        if ((rand(3)) == 0)
        {
            while ((i = rand(127)) >= 114)
                ;
            int l = leds.all[i];
            int x = POSITIONS[l].x;
            screenbuf3[l] = 0xff;
        }

        if (f < FPS * 2)
        {
            // swipe away from the middle, middle x == 6380
            int leftClip = middleX - f * swipe_speed;
            int rightClip = middleX + f * swipe_speed;

            for (i = 1; i < 145; i++)
            {
                int x = POSITIONS[i].x;
                if (x < leftClip || x > rightClip)
                    screenbuf[i] = screenbuf2[i];
                else if (x > leftClip + 1000 && x < rightClip - 1000)
                    screenbuf[i] = screenbuf3[i];
                else
                    screenbuf[i] = 0;
            }
            i2c_send_buffer(screenbuf, 145);
        }
        else
            i2c_send_buffer(screenbuf3, 145);

        Delay_Ms(WAIT_MS);
    }
}
void strike_letters(uint8_t *screenbuf)
{
    int f;
    int i = 0;
    for (f = 0; i < 114; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 0x10, 3);
        if (f % 2 == 0)
        {
            screenbuf[leds.all[i % 114]] = 0x80;
            i++;
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }

    i = 0;
    for (f = 0; i < 9; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 0x20, 3);
        if (f % 16 == 0)
        {
            struct Letter *l = &LETTERS[i];
            for (int j = 0; j < l->len; j++)
            {
                screenbuf[l->leds[j]] = 0x80;
            }
            i++;
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }

    for (f = 0; f < FPS * 5; f++)
    {
        if (f % 2 == 0)
            fade_screenbuf(screenbuf, 0x10, 4);
        if (f % 64 == 0)
        {
            for (int j = 0; j < 117; j++)
            {
                screenbuf[leds.all[j]] = 0x80;
            }
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }
}

void letter_waves(uint8_t *screenbuf)
{
    int f, i;
    int d = 15000 / FPS / 2;
    int centerX = POSITIONS[39].x;
    int centerY = POSITIONS[39].y;
    const int transition_start = 18;

    for (f = 0; f < FPS * 20; f++)
    {
        int separator = (f - FPS * transition_start) * d;
        for (int j = 0; j < 117; j++)
        {
            int l = leds.all[j];
            struct pos *p = &POSITIONS[l];
            int x = p->x;
            int y = p->y;
            int dx = x - centerX;
            int dy = y - centerY;
            int d = (dx * dx + dy * dy) / 70000 + f * 4; // missing the sqrt since we don't have proper math support
            uint8_t s = (Sine16bit[d & 0xff] + 32768) >> 9;

            // transition to swipe in volcano starting at t = 18s
            if (f < FPS * transition_start || x >= separator)
                screenbuf[l] = s;
            else
                screenbuf[l] = 0;
        }
        if (f >= FPS * transition_start)
        {
            for (i = 0; i < sizeof(leds.letters.VOLCANO); i++)
            {
                int l = leds.letters.VOLCANO[i];
                int x = POSITIONS[l].x;
                if (x < separator)
                    screenbuf[l] = 8;
            }
        }

        i2c_send_buffer(screenbuf, 145);
        Delay_Ms(WAIT_MS);
    }
}

int main()
{
    // 48MHz internal clock
    // SystemInit();

    // init i2c
    Delay_Ms(100);
    i2c_init(i2c_default, 100000);
    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_set_function(17, GPIO_FUNC_I2C);
    gpio_pull_up(16);
    gpio_pull_up(17);

    // ssd1306_i2c_init();

    i2c_write_register(0xfd, 0x0b);
    i2c_write_register(0x0a, 0x00); // turn off until we're ready

    // initialize screen buffer
    uint8_t screenbuf[145];
    screenbuf[0] = 0x24;
    for (int i = 1; i < 145; i++)
        screenbuf[i] = 0x00;

    i2c_write_register(0xfd, 0x00);
    // enable all LEDs
    for (int i = 0; i < 18; i++)
        i2c_write_register(i, 0xff);
    // set intensity (PWM) of all LEDs to the zero screenbuffer (off)
    i2c_send_buffer(screenbuf, 145);

    i2c_write_register(0xfd, 0x0b);
    i2c_write_register(0xc2, 0x10); // try to turn on ghosting reduction as described in the application notes (but
                                    // does it have any effect?)
    i2c_write_register(0x0a, 0x01); // turn driver on

    // select bank 0
    i2c_write_register(0xfd, 0x00);
    while (1)
    {
        volcano_eruption(screenbuf);
        stars_and_background(screenbuf);
        reveal_letters(screenbuf);
        strike_letters(screenbuf);
        letter_waves(screenbuf);
    }
}
