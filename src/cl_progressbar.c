#include "cl_progressbar.h"
#define SGETTER(t, p) \
	t progressbar_layer_get_ ## p(ProgressBarLayer *layer) { \
		return layer-> p; \
	} \
	void progressbar_layer_set_ ## p(ProgressBarLayer *layer, t value) { \
		layer-> p = value; \
		layer_mark_dirty(layer->layer); \
	}

SGETTER(int, progress);
SGETTER(int, max);
SGETTER(GColor, foreground);
SGETTER(GColor, background);

static void update_proc(Layer *layer, GContext *ctx)
{
	ProgressBarLayer *prop = layer_get_data(layer);

  //Draw border
  GRect outer = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, prop->foreground);
  graphics_fill_rect(ctx, outer, 0, GCornerNone);

  //Fill background of bar
  GRect inner = GRect(
    outer.origin.x + 1,
    outer.origin.y + 1,
    outer.size.w - 2,
    outer.size.h - 2
  );
  graphics_context_set_fill_color(ctx, prop->background);
  graphics_fill_rect(ctx, inner, 0, GCornerNone);

  //Draw progress as bar
	int max = prop->max > 0 ? prop->max : 1;
	int progress = prop->progress < prop->max ? prop->progress : prop->max;
  GRect bar = GRect(
    outer.origin.x + 1,
    outer.origin.y + 1,
    (progress * inner.size.w) / max,
    outer.size.h - 2
  );
  graphics_context_set_fill_color(ctx, prop->foreground);
  graphics_fill_rect(ctx, bar, 0, GCornerNone);
}

ProgressBarLayer* progressbar_layer_create(GRect bounds)
{
  Layer *layer = layer_create_with_data(bounds, sizeof(ProgressBarLayer));
  layer_set_update_proc((Layer *)layer, update_proc);

	ProgressBarLayer *progressbar_layer = (ProgressBarLayer *)layer_get_data(layer);

	progressbar_layer->progress = 0;
	progressbar_layer->max = 100;
	progressbar_layer->foreground = GColorBlack;
	progressbar_layer->background = GColorWhite;
	progressbar_layer->layer = layer;

  return progressbar_layer;
}

Layer* progressbar_layer_get_layer(ProgressBarLayer *layer)
{
	return layer->layer;
}

void progressbar_layer_destroy(ProgressBarLayer *layer)
{
  layer_destroy(layer->layer);
}
