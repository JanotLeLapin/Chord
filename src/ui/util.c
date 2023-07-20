#include "colors.h"
#include "ui.h"

void ui_draw_rect(struct ncplane *n, int begx, int begy, int endx, int endy) {
  int w = endx - begx;
  char *str = malloc(w);

  for (int i = 0; i < w; i++) {
    *(str+i) = ' ';
  }

  int h = endy - begy;
  for (int i = 0; i < h; i++) {
    ncplane_printf_yx(n, i, begx, "%s", str);
  }
}

void ui_clear(struct ncplane *n) {
  chord_bg_default(n);
  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);
  ui_draw_rect(n, 0, 0, x, y);
}
