RGB_MATRIX_EFFECT(FLASHING)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool FLASHING(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // HSV hsv = rgb_matrix_config.hsv;
    // RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

    // scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8)

    // if (params->time_since_last > 1000) {
    //     for (uint8_t i = led_min; i < led_max; i++) {
    //         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    //     }
    // } else {
    //     for (uint8_t i = led_min; i < led_max; i++) {
    //         rgb_matrix_set_color(i, 0, 0, 0);
    //     }
    // }

    return rgb_matrix_check_finished_leds(led_max);
}

#endif