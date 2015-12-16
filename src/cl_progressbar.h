/*
 * ProgressBarLayer code
 * src: https://github.com/C-D-Lewis/pebble-progressbar-layer
 */

#include <pebble.h>

#ifndef CL_PROGRESSBAR_H
#define CL_PROGRESSBAR_H

typedef struct {
	Layer *layer;
	int progress;
	int max;
	GColor foreground;
	GColor background;
} ProgressBarLayer;

ProgressBarLayer* progressbar_layer_create(GRect bounds);
void progressbar_layer_destroy();
void progressbar_layer_set_progress(ProgressBarLayer *layer, int value);
int progressbar_layer_get_progress(ProgressBarLayer *layer);

void progressbar_layer_set_max(ProgressBarLayer *layer, int value);
int progressbar_layer_get_max(ProgressBarLayer *layer);

void progressbar_layer_set_foreground(ProgressBarLayer *layer, GColor value);
GColor progressbar_layer_get_foreground(ProgressBarLayer *layer);

void progressbar_layer_set_background(ProgressBarLayer *layer, GColor value);
GColor progressbar_layer_get_background(ProgressBarLayer *layer);

Layer *progressbar_layer_get_layer(ProgressBarLayer *layer);
#endif
