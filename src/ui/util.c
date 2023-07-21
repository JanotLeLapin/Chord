#include "colors.h"
#include "ui.h"

void ui_draw_rect(struct ncplane *n, int begx, int begy, int endx, int endy) {
  int w = endx - begx;
  char *str = malloc((w + 1) * sizeof(char));

  for (int i = 0; i < w; i++) {
    *(str+i) = ' ';
  }

  int h = endy - begy;
  for (int i = 0; i < h; i++) {
    ncplane_printf_yx(n, i, begx, "%s", str);
  }

  free(str);
}

void ui_clear(struct ncplane *n, int x, int y) {
  chord_bg_default(n);
  ui_draw_rect(n, 0, 0, x, y);
}
