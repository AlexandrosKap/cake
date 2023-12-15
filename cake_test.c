// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#define CAKE_IMPLEMENTATION

#include "cake.h"
#include <assert.h>
#include <stdio.h>

#define TEST(body) assert(body)
#define TODO(msg) assert(msg && 0)

void test_utils() {
    TEST(cake_min(-1.0f, -1.0f) == -1.0f);
    TEST(cake_min(-1.0f, 1.0f) == -1.0f);
    TEST(cake_min(1.0f, -1.0f) == -1.0f);

    TEST(cake_max(-1.0f, -1.0f) == -1.0f);
    TEST(cake_max(-1.0f, 1.0f) == 1.0f);
    TEST(cake_max(1.0f, -1.0f) == 1.0f);

    TEST(cake_sign(0.0f) == -1.0f);
    TEST(cake_sign(-1.0f) == -1.0f);
    TEST(cake_sign(1.0f) == 1.0f);

    TEST(cake_abs(-1.0f) == 1.0f);
    TEST(cake_abs(1.0f) == 1.0f);

    TEST(cake_floor(0.0f) == 0.0f);
    TEST(cake_floor(-1.0f) == -1.0f);
    TEST(cake_floor(-1.5f) == -2.0f);
    TEST(cake_floor(1.0f) == 1.0f);
    TEST(cake_floor(1.5f) == 1.0f);

    TEST(cake_ceil(0.0f) == 0.0f);
    TEST(cake_ceil(-1.0f) == -1.0f);
    TEST(cake_ceil(-1.5f) == -1.0f);
    TEST(cake_ceil(1.0f) == 1.0f);
    TEST(cake_ceil(1.5f) == 2.0f);

    TEST(cake_round(0.0f) == 0.0f);
    TEST(cake_round(-1.0f) == -1.0f);
    TEST(cake_round(-1.5f) == -2.0f);
    TEST(cake_round(1.0f) == 1.0f);
    TEST(cake_round(1.5f) == 2.0f);

    TEST(cake_sqrt(0.0f) == 0.000f);
    TEST(cake_sqrt(1.0f) == 1.000f);
    TEST(cake_sqrt(2.0f) >= 1.414f - 0.01f && cake_sqrt(2.0f) <= 1.414f + 0.01f);
    TEST(cake_sqrt(3.0f) >= 1.732f - 0.01f && cake_sqrt(3.0f) <= 1.732f + 0.01f);
    TEST(cake_sqrt(4.0f) >= 2.000f - 0.01f && cake_sqrt(4.0f) <= 2.000f + 0.01f);
    TEST(cake_sqrt(5.0f) >= 2.236f - 0.01f && cake_sqrt(5.0f) <= 2.236f + 0.01f);
    TEST(cake_sqrt(6.0f) >= 2.449f - 0.01f && cake_sqrt(6.0f) <= 2.449f + 0.01f);
    TEST(cake_sqrt(7.0f) >= 2.646f - 0.01f && cake_sqrt(7.0f) <= 2.646f + 0.01f);
    TEST(cake_sqrt(8.0f) >= 2.828f - 0.01f && cake_sqrt(8.0f) <= 2.828f + 0.01f);
    TEST(cake_sqrt(9.0f) >= 3.000f - 0.01f && cake_sqrt(9.0f) <= 3.000f + 0.01f);

    TEST(cake_pow(0.0f, 0.0f) == 1.000f);
    TEST(cake_pow(2.0f, 0.0f) == 1.000f);
    TEST(cake_pow(2.0f, 2.2f) >= 4.594f - 0.01f && cake_pow(2.0f, 2.2f) <= 4.594f + 0.01f);
    TEST(cake_pow(2.0f, 2.4f) >= 5.278f - 0.01f && cake_pow(2.0f, 2.4f) <= 5.278f + 0.01f);
    TEST(cake_pow(2.0f, 2.6f) >= 6.062f - 0.01f && cake_pow(2.0f, 2.6f) <= 6.062f + 0.01f);
    TEST(cake_pow(2.0f, 2.8f) >= 6.964f - 0.01f && cake_pow(2.0f, 2.8f) <= 6.964f + 0.01f);
    TEST(cake_pow(2.0f, 3.0f) >= 8.000f - 0.01f && cake_pow(2.0f, 3.0f) <= 8.000f + 0.01f);
    TEST(cake_pow(2.0f, 7.8f) >= 222.860f - 0.01f && cake_pow(2.0f, 7.8f) <= 222.860f + 0.01f);
    TEST(cake_pow(2.0f, 9.6f) >= 776.046f - 0.01f && cake_pow(2.0f, 9.6f) <= 776.046f + 0.01f);
    TEST(cake_pow(2.0f, 14.14f) >= 18053.613f - 0.01f && cake_pow(2.0f, 14.14f) <= 18053.613f + 0.01f);

    TEST(cake_clamp(0.0f, 0.0f, 0.0f) == 0.0f);
    TEST(cake_clamp(-2.0f, -1.0f, 1.0f) == -1.0f);
    TEST(cake_clamp(2.0f, -1.0f, 1.0f) == 1.0f);

    TEST(cake_wrap(0.0f, 0.0f, 0.0f) == 0.0f);
    TEST(cake_wrap(-2.0f, -1.0f, 1.0f) >= 0.0f - 0.001f && cake_wrap(-2.0f, -1.0f, 1.0f) <= 0.0f + 0.001f);
    TEST(cake_wrap(2.0f, -1.0f, 1.0f) >= 0.0f - 0.001f && cake_wrap(2.0f, -1.0f, 1.0f) <= 0.0f + 0.001f);
    TEST(cake_wrap(-5.0f, -4.0f, -2.0f) >= -3.0f - 0.001f && cake_wrap(-5.0f, -4.0f, -2.0f) <= -3.0f + 0.001f);

    TEST(cake_stepify(90.0f, 32.0f) >= 96.0f - 0.001f && cake_stepify(90.0f, 32.0f) <= 96.0f + 0.001f);
    TEST(cake_stepify(96.0f, 32.0f) >= 96.0f - 0.001f && cake_stepify(96.0f, 32.0f) <= 96.0f + 0.001f);
    TEST(cake_stepify(100.0f, 64.0f) >= 128.0f - 0.001f && cake_stepify(100.0f, 64.0f) <= 128.0f + 0.001f);
    TEST(cake_stepify(128.0f, 64.0f) >= 128.0f - 0.001f && cake_stepify(128.0f, 64.0f) <= 128.0f + 0.001f);
}

void test_v2() {
    TEST(cake_v2_length(cake_v2_new(0.0f, 0.0f)) == 0.0f);
    TEST(cake_v2_length(cake_v2_new(0.0f, 1.0f)) == 1.0f);
    TEST(cake_v2_length(cake_v2_new(1.0f, 1.0f)) >= 1.0f);

    TEST(cake_v2_length(cake_v2_normalized(cake_v2_new(0.0f, 0.0f))) == 0.0f);
    TEST(cake_v2_length(cake_v2_normalized(cake_v2_new(0.0f, 1.0f))) == 1.0f);
    TEST(cake_v2_length(cake_v2_normalized(cake_v2_new(1.0f, 1.0f))) == 1.0f);
    TEST(cake_v2_length(cake_v2_normalized(cake_v2_new(0.2f, 0.3f))) == 1.0f);
}

void test_r2() {
    Cake_R2 r = cake_r2_new(1.0f, 1.0f, -3.0f, -3.0f);
    TEST(r.x == -2.0f);
    TEST(r.y == -2.0f);
    TEST(r.w == 3.0f);
    TEST(r.h == 3.0f);

    TEST(cake_r2_has_point(r, cake_v2_new(r.x, r.y)) == true);
    TEST(cake_r2_has_point(r, cake_v2_new(r.x + r.w, r.y + r.h)) == true);

    TEST(cake_r2_has_intersection(r, cake_r2_new(r.x, r.y, 0.0f, 0.0f)) == true);
    TEST(cake_r2_has_intersection(r, cake_r2_new(r.x, r.y, r.w, r.h)) == true);
}

int main() {
    test_utils();
    test_v2();
    test_r2();
    printf("OK!\n");
    return 0;
}
