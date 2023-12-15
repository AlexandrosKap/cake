// Copyright 2023 Alexandros F. G. Kapretsos
// SPDX-License-Identifier: Apache-2.0

#ifndef CAKE_HEADER
#define CAKE_HEADER

#include <stdbool.h>

typedef struct Cake_V2 {
    float x;
    float y;
} Cake_V2;

typedef struct Cake_R2 {
    float x;
    float y;
    float w;
    float h;
} Cake_R2;

typedef enum Cake_Anchor {
    CAKE_ANCHOR_TOP_LEFT,
    CAKE_ANCHOR_TOP,
    CAKE_ANCHOR_TOP_RIGHT,
    CAKE_ANCHOR_CENTER_LEFT,
    CAKE_ANCHOR_CENTER,
    CAKE_ANCHOR_CENTER_RIGHT,
    CAKE_ANCHOR_BOTTOM_LEFT,
    CAKE_ANCHOR_BOTTOM,
    CAKE_ANCHOR_BOTTOM_RIGHT,
} Cake_Anchor;

float cake_min(float a, float b);
float cake_max(float a, float b);
float cake_sign(float x);
float cake_abs(float x);
float cake_floor(float x);
float cake_ceil(float x);
float cake_round(float x);
float cake_sqrt(float x);
float cake_factorial(float x);
float cake_exp(float x);
float cake_ln(float x);
float cake_pow(float x, float n);
float cake_clamp(float x, float a, float b);
float cake_wrap(float x, float a, float b);
float cake_stepify(float x, float step);

float cake_lerp(float a, float b, float weight);
float cake_smoothstep(float a, float b, float weight);
float cake_smootherstep(float a, float b, float weight);
float cake_move(float a, float b, float delta);
float cake_move_with(float a, float b, float delta, float slowdown);
float cake_cubic_in(float x);
float cake_cubic_out(float x);
float cake_cubic_in_out(float x);

Cake_V2 cake_v2_new(float x, float y);
Cake_V2 cake_v2_add(Cake_V2 a, Cake_V2 b);
Cake_V2 cake_v2_sub(Cake_V2 a, Cake_V2 b);
Cake_V2 cake_v2_mul(Cake_V2 a, Cake_V2 b);
Cake_V2 cake_v2_div(Cake_V2 a, Cake_V2 b);
float cake_v2_length(Cake_V2 v);
Cake_V2 cake_v2_normalized(Cake_V2 v);
Cake_V2 cake_v2_direction(Cake_V2 a, Cake_V2 b);
Cake_V2 cake_v2_move(Cake_V2 a, Cake_V2 b, Cake_V2 delta);
Cake_V2 cake_v2_move_with(Cake_V2 a, Cake_V2 b, Cake_V2 delta, float slowdown);

Cake_R2 cake_r2_new(float x, float y, float w, float h);
bool cake_r2_has_point(Cake_R2 r, Cake_V2 point);
bool cake_r2_has_intersection(Cake_R2 r, Cake_R2 area);
Cake_R2 cake_r2_intersection(Cake_R2 r, Cake_R2 area);
Cake_R2 cake_r2_merger(Cake_R2 r, Cake_R2 area);
Cake_R2 cake_r2_add_left(Cake_R2 *r, float amount);
Cake_R2 cake_r2_add_right(Cake_R2 *r, float amount);
Cake_R2 cake_r2_add_top(Cake_R2 *r, float amount);
Cake_R2 cake_r2_add_bottom(Cake_R2 *r, float amount);
Cake_R2 cake_r2_sub_left(Cake_R2 *r, float amount);
Cake_R2 cake_r2_sub_right(Cake_R2 *r, float amount);
Cake_R2 cake_r2_sub_top(Cake_R2 *r, float amount);
Cake_R2 cake_r2_sub_bottom(Cake_R2 *r, float amount);
void cake_r2_add_left_right(Cake_R2 *r, float amount);
void cake_r2_add_top_bottom(Cake_R2 *r, float amount);
void cake_r2_add_all(Cake_R2 *r, float amount);
void cake_r2_sub_left_right(Cake_R2 *r, float amount);
void cake_r2_sub_top_bottom(Cake_R2 *r, float amount);
void cake_r2_sub_all(Cake_R2 *r, float amount);
Cake_R2 cake_r2_left(Cake_R2 r, float amount);
Cake_R2 cake_r2_right(Cake_R2 r, float amount);
Cake_R2 cake_r2_top(Cake_R2 r, float amount);
Cake_R2 cake_r2_bottom(Cake_R2 r, float amount);

#define CAKE_CAST(type) (type)

#endif // CAKE_HEADER

#ifdef CAKE_IMPLEMENTATION
#ifndef CAKE_IMPLEMENTATION_ADDED
#define CAKE_IMPLEMENTATION_ADDED

float cake_min(float a, float b) {
    return a <= b ? a : b;
}

float cake_max(float a, float b) {
    return a <= b ? b : a;
}

float cake_sign(float x) {
    return x <= 0.0f ? -1.0f : 1.0f;
}

float cake_abs(float x) {
    return x <= 0.0f ? -x : x;
}

float cake_floor(float x) {
    float floored = CAKE_CAST(float) CAKE_CAST(int) x;
    return (x <= 0.0f && floored != x) ? floored - 1.0f : floored;
}

float cake_ceil(float x) {
    float ceiled = CAKE_CAST(float) CAKE_CAST(int) x;
    return (x <= 0.0f || ceiled == x) ? ceiled : ceiled + 1.0f;
}

float cake_round(float x) {
    return x <= 0.0f ? CAKE_CAST(float) CAKE_CAST(int) (x - 0.5f) : CAKE_CAST(float) CAKE_CAST(int) (x + 0.5f);
}

float cake_sqrt(float x) {
    float result = x / 2.0f;
    float temp = 0.0f;
    while (result != temp) {
        temp = result;
        result = (x / temp + temp) / 2.0f;
    }
    return result;
}

float cake_factorial(float x) {
    float result = 1.0f;
    for (int i = 2; i <= CAKE_CAST(int) x; i += 1) {
        result *= CAKE_CAST(float) i;
    }
    return result;
}

float cake_exp(float x) {
    float result = 0.0f;
    int approximation = 10;
    for (int i = 0; i < approximation; i += 1) {

        float pow;
        float pow_x = x;
        int pow_n = i;
        if (pow_n == 0) {
            pow = 1.0f;
        } else {
            pow = pow_x;
            for (int j = 1; j < pow_n; j += 1) {
                pow *= pow_x;
            }
        }

        result += pow / cake_factorial(CAKE_CAST(float) i);
    }
    return result;
}

float cake_ln(float x) {
    float result = 0.0f;
    int approximation = 10;
    for (int i = 1; i < approximation; i += 1) {

        float pow;
        float pow_x = (x - 1.0f) / (x + 1.0f);
        int pow_n = 2 * i - 1;
        if (pow_n == 0) {
            pow = 1.0f;
        } else {
            pow = pow_x;
            for (int j = 1; j < pow_n; j += 1) {
                pow *= pow_x;
            }
        }

        result += pow / (2.0f * CAKE_CAST(float) i - 1.0f);
    }
    result *= 2.0f;
    return result;
}

float cake_pow(float x, float n) {
    // From: https://gist.github.com/serg06/38760a4b5aceb4c6245d61c56716588c
    
    float pow;
    float pow_x = x;
    int pow_n = CAKE_CAST(int) n;
    if (pow_n == 0) {
        pow = 1.0f;
    } else {
        pow = pow_x;
        for (int j = 1; j < pow_n; j += 1) {
            pow *= pow_x;
        }
    }

    return pow * cake_exp((n - CAKE_CAST(float) pow_n) * cake_ln(x));
}

float cake_clamp(float x, float a, float b) {
    return x <= a ? a : x >= b ? b : x;
}

float cake_wrap(float x, float a, float b) {
    float result = x;
    float delta = b - a;
    while (result < a) {
        result += delta;
    }
    while (result > b) {
        result -= delta;
    }
    return result;
}

float cake_stepify(float x, float step) {
    return step * cake_round(x / step);
}

float cake_lerp(float a, float b, float weight) {
    return a + (b - a) * weight;
}

float cake_smoothstep(float a, float b, float weight) {
    float v = weight * weight * (3.0f - 2.0f * weight);
    return (b * v) + (a * (1.0f - v));
}

float cake_smootherstep(float a, float b, float weight) {
    float v = weight * weight * weight * (weight * (weight * 6.0f - 15.0f) + 10.0f);
    return (b * v) + (a * (1.0f - v));
}

float cake_move(float a, float b, float delta) {
    if (cake_abs(b - a) > cake_abs(delta)) {
        return a + cake_sign(b - a) * delta;
    } else {
        return b;
    }
}

float cake_move_with(float a, float b, float delta, float slowdown) {
    float target = ((a * (slowdown - 1.0f)) + b) / slowdown;
    return a + (target - a) * delta;
}

float cake_cubic_in(float x) {
    return x * x * x;
}

float cake_cubic_out(float x) {
    return 1.0f - cake_pow(1.0f - x, 3.0f);
}

float cake_cubic_in_out(float x) {
    if (x < 0.5f) {
        return 4.0f * x * x * x;
    } else {
        return 1.0f - cake_pow(-2.0f * x + 2.0f, 3.0f) / 2.0f;
    }
}

Cake_V2 cake_v2_new(float x, float y) {
    Cake_V2 result;
    result.x = x;
    result.y = y;
    return result;
}

Cake_V2 cake_v2_add(Cake_V2 a, Cake_V2 b) {
    Cake_V2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Cake_V2 cake_v2_sub(Cake_V2 a, Cake_V2 b) {
    Cake_V2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Cake_V2 cake_v2_mul(Cake_V2 a, Cake_V2 b) {
    Cake_V2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

Cake_V2 cake_v2_div(Cake_V2 a, Cake_V2 b) {
    Cake_V2 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

float cake_v2_length(Cake_V2 v) {
    return cake_sqrt(v.x * v.x + v.y * v.y);
}

Cake_V2 cake_v2_normalized(Cake_V2 v) {
    float length = cake_v2_length(v);
    if (length == 0.0f) {
        return v;
    } else {
        return cake_v2_new(v.x / length, v.y / length);
    }
}

Cake_V2 cake_v2_direction(Cake_V2 a, Cake_V2 b) {
    return cake_v2_normalized(cake_v2_new(b.x - a.x, b.y - a.y));
}

Cake_V2 cake_v2_move(Cake_V2 a, Cake_V2 b, Cake_V2 delta) {
    Cake_V2 direction = cake_v2_direction(a, b);
    Cake_V2 offset = cake_v2_new(direction.x * delta.x, direction.y * delta.y);
    Cake_V2 result;
    if (cake_abs(b.x - a.x) > cake_abs(offset.x)) {
        result.x = a.x + offset.x;
    } else {
        result.x = b.x;
    }
    if (cake_abs(b.y - a.y) > cake_abs(offset.y)) {
        result.y = a.y + offset.y;
    } else {
        result.y = b.y;
    }
    return result;
}

Cake_V2 cake_v2_move_with(Cake_V2 a, Cake_V2 b, Cake_V2 delta, float slowdown) {
    Cake_V2 result;
    result.x = cake_move_with(a.x, b.x, delta.x, slowdown);
    result.y = cake_move_with(a.y, b.y, delta.y, slowdown);
    return result;
}

Cake_R2 cake_r2_new(float x, float y, float w, float h) {
    Cake_R2 result;
    if (w >= 0.0f) {
        result.x = x;
        result.w = w;
    } else {
        result.x = x + w;
        result.w = -w;
    }
    if (h >= 0.0f) {
        result.y = y;
        result.h = h;
    } else {
        result.y = y + h;
        result.h = -h;
    }
    return result;
}

bool cake_r2_has_point(Cake_R2 r, Cake_V2 point) {
    return point.x >= r.x && point.x <= r.x + r.w && point.y >= r.y && point.y <= r.y + r.h;
}

bool cake_r2_has_intersection(Cake_R2 r, Cake_R2 area) {
    return r.x + r.w >= area.x && r.x <= area.x + area.w && r.y + r.h >= area.y && r.y <= area.y + area.h;
}

Cake_R2 cake_r2_intersection(Cake_R2 r, Cake_R2 area) {
    if (!cake_r2_has_intersection(r, area)) {
        return cake_r2_new(0.0f, 0.0f, 0.0f, 0.0f);
    }
    float max_x = cake_max(r.x, area.x);
    float max_y = cake_max(r.y, area.y);
    return cake_r2_new(
        max_x,
        max_y,
        cake_min(r.x + r.w, area.x + area.w) - max_x,
        cake_min(r.y + r.h, area.y + area.h) - max_y
    );
}

Cake_R2 cake_r2_merger(Cake_R2 r, Cake_R2 area) {
    float min_x = cake_min(r.x, area.x);
    float min_y = cake_min(r.y, area.y);
    return cake_r2_new(
        min_x,
        min_y,
        cake_max(r.x + r.w, area.x + area.w) - min_x,
        cake_max(r.y + r.h, area.y + area.h) - min_y
    );
}

Cake_R2 cake_r2_add_left(Cake_R2 *r, float amount) {
    r->x -= amount;
    r->w += amount;
    return cake_r2_new(r->x, r->y, amount, r->h);
}

Cake_R2 cake_r2_add_right(Cake_R2 *r, float amount) {
    float w = r->w;
    r->w += amount;
    return cake_r2_new(w, r->y, amount, r->h);
}

Cake_R2 cake_r2_add_top(Cake_R2 *r, float amount) {
    r->y -= amount;
    r->h += amount;
    return cake_r2_new(r->x, r->y, r->w, amount);
}

Cake_R2 cake_r2_add_bottom(Cake_R2 *r, float amount) {
    float h = r->h;
    r->h += amount;
    return cake_r2_new(r->x, h, r->w, amount);
}

Cake_R2 cake_r2_sub_left(Cake_R2 *r, float amount) {
    float x = r->x;
    r->x = cake_min(r->x + amount, r->x + r->w);
    r->w = cake_max(r->w - amount, 0.0f);
    return cake_r2_new(x, r->y, amount, r->h);
}

Cake_R2 cake_r2_sub_right(Cake_R2 *r, float amount) {
    r->w = cake_max(r->w - amount, 0.0f);
    return cake_r2_new(r->x + r->w, r->y, amount, r->h);
}

Cake_R2 cake_r2_sub_top(Cake_R2 *r, float amount) {
    float y = r->y;
    r->y = cake_min(r->y + amount, r->y + r->h);
    r->h = cake_max(r->h - amount, 0.0f);
    return cake_r2_new(r->x, y, r->w, amount);
}

Cake_R2 cake_r2_sub_bottom(Cake_R2 *r, float amount) {
    r->h = cake_max(r->h - amount, 0.0f);
    return cake_r2_new(r->x, r->y + r->h, r->w, amount);
}

void cake_r2_add_left_right(Cake_R2 *r, float amount) {
    cake_r2_add_left(r, amount);
    cake_r2_add_right(r, amount);
}

void cake_r2_add_top_bottom(Cake_R2 *r, float amount) {
    cake_r2_add_top(r, amount);
    cake_r2_add_bottom(r, amount);
}

void cake_r2_add_all(Cake_R2 *r, float amount) {
    cake_r2_add_left_right(r, amount);
    cake_r2_add_top_bottom(r, amount);
}

void cake_r2_sub_left_right(Cake_R2 *r, float amount) {
    cake_r2_sub_left(r, amount);
    cake_r2_sub_right(r, amount);
}

void cake_r2_sub_top_bottom(Cake_R2 *r, float amount) {
    cake_r2_sub_top(r, amount);
    cake_r2_sub_bottom(r, amount);
}

void cake_r2_sub_all(Cake_R2 *r, float amount) {
    cake_r2_sub_left_right(r, amount);
    cake_r2_sub_top_bottom(r, amount);
}

Cake_R2 cake_r2_left(Cake_R2 r, float amount) {
    return cake_r2_sub_left(&r, amount);
}

Cake_R2 cake_r2_right(Cake_R2 r, float amount) {
    return cake_r2_sub_right(&r, amount);
}

Cake_R2 cake_r2_top(Cake_R2 r, float amount) {
    return cake_r2_sub_top(&r, amount);
}

Cake_R2 cake_r2_bottom(Cake_R2 r, float amount) {
    return cake_r2_sub_bottom(&r, amount);
}

#endif // CAKE_IMPLEMENTATION_ADDED
#endif // CAKE_IMPLEMENTATION
