Timer timer_init() {
    Timer timer = {0};
    timer.ticks = os_get_ticks();
    timer.delta = 16666.6f;
    timer.smooth_delta = 16666.6f;
    timer.very_smooth_delta = 16666.6f;

    return timer;
}

void timer_update(Timer* timer) {
    u64 current_ticks = os_get_ticks();

    u64 elapsed_ticks = (current_ticks > timer->ticks) ? (current_ticks - timer->ticks) : 0;
    double us = (double)elapsed_ticks * os_get_inverse_ticks_per_us();
    if (us > 200000.0) us = 200000.0;

    timer->delta = (float)us;
    timer->ticks = current_ticks;

    float diff = timer->delta - timer->smooth_delta;
    float rel_diff = fabsf(diff) / (timer->smooth_delta + 1.0f);
    float f = rel_diff / (1.0f + rel_diff);

    timer->smooth_delta += diff * clamp_bottom(f, 1.0f / 32.0f);
    timer->very_smooth_delta += (timer->delta - timer->very_smooth_delta) * clamp_bottom(f, 1.0f / 128.0f);
}