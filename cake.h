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
float cake_sign(float n);
float cake_abs(float n);
float cake_floor(float n);
float cake_ceil(float n);
float cake_round(float n);
float cake_sqrt(float n);
float cake_clamp(float n, float a, float b);
float cake_wrap(float n, float a, float b);
float cake_stepify(float n, float step);
float cake_move(float a, float b, float delta);
float cake_move_with(float a, float b, float delta, float slowdown);

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

float cake_sign(float n) {
    return n <= 0.0f ? -1.0f : 1.0f;
}

float cake_abs(float n) {
    return n <= 0.0f ? -n : n;
}

float cake_floor(float n) {
    float floored = CAKE_CAST(float) CAKE_CAST(int) n;
    return (n <= 0.0f && floored != n) ? floored - 1.0f : floored;
}

float cake_ceil(float n) {
    float ceiled = CAKE_CAST(float) CAKE_CAST(int) n;
    return (n <= 0.0f || ceiled == n) ? ceiled : ceiled + 1.0f;
}

float cake_round(float n) {
    return n <= 0.0f ? CAKE_CAST(float) CAKE_CAST(int) (n - 0.5f) : CAKE_CAST(float) CAKE_CAST(int) (n + 0.5f);
}

float cake_sqrt(float n) {
    float result = n / 2.0f;
    float temp = 0.0f;
    while (result != temp) {
        temp = result;
        result = (n / temp + temp) / 2.0f;
    }
    return result;
}

float cake_clamp(float n, float a, float b) {
    return n <= a ? a : n >= b ? b : n;
}

float cake_wrap(float n, float a, float b) {
    float result = n;
    float delta = b - a;
    while (result < a) {
        result += delta;
    }
    while (result > b) {
        result -= delta;
    }
    return result;
}

float cake_stepify(float n, float step) {
    return step * cake_round(n / step);
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
        result.y = y + w;
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
