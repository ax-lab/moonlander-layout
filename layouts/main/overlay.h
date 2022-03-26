#pragma once

typedef void (*overlay_rgb_fn)(void);
typedef bool (*overlay_process_fn)(uint16_t keycode, keyrecord_t *record);

/**
 * Overlays provide a complete set of features that take over the keyboard
 * processing and/or led effects.
 *
 * The goal of overlays is to encapsulate complex behavior without affecting,
 * or being affected by, other parts of the normal keyboard functionality.
 */
typedef struct overlay_t {
	overlay_process_fn process;
	overlay_rgb_fn rgb;
} overlay_t;

static overlay_t current_overlay = { 0 };
static bool current_overlay_skip_not_pressed = false;

void open_overlay(overlay_t overlay)
{
	current_overlay = overlay;
	current_overlay_skip_not_pressed = true;
}

void close_overlay(void)
{
	current_overlay.rgb = NULL;
	current_overlay.process = NULL;
}
