#include "include/ui.h"

#include <notcurses/notcurses.h>

void draw_rect(struct ncplane *n, int begx, int begy, int endx, int endy) {
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
  ncplane_set_bg_rgb8(n, 40, 44, 52);

  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);
  draw_rect(n, 0, 0, x, y);
}

void ui_draw_userlist(struct ncplane *n, user *users, int user_count, int width) {
  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);

  ncplane_set_bg_rgb8(n, 55, 61, 72);
  draw_rect(n, x - width, 0, x, y);
  for (int i = 0; i < user_count; i++) {
    user u = *(users + (i * sizeof(user)));

    switch (u.status) {
      case 0:
        ncplane_set_fg_rgb8(n, 152, 232, 125);
        break;
      case 1:
        ncplane_set_fg_rgb8(n, 232, 179, 125);
        break;
      case 2:
        ncplane_set_fg_rgb8(n, 232, 125, 125);
        break;
    }
    ncplane_putstr_yx(n, i+1, x-width+1, "•");

    ncplane_set_fg_default(n);
    ncplane_printf_yx(n, i+1, x-width+3, "%s", u.name);
  }
}
