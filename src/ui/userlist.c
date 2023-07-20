#include "include/colors.h"
#include "include/ui.h"
#include <notcurses/notcurses.h>

void ui_draw_userlist(struct ncplane *n, user *users, int user_count, ui_box *box) {
  chord_bg_alt(n);
  ui_draw_rect(n, box->begx, box->begy, box->endx, box->endy);
  for (int i = 0; i < user_count; i++) {
    user u = *(users + (i * sizeof(user)));

    switch (u.status) {
      case 0:
        ncplane_set_fg_rgb8(n, CHORD_COLOR_EMERALD);
        break;
      case 1:
        ncplane_set_fg_rgb8(n, CHORD_COLOR_AMBER);
        break;
      case 2:
        ncplane_set_fg_rgb8(n, CHORD_COLOR_RED);
        break;
    }

    ncplane_set_styles(n, NCSTYLE_BOLD);
    ncplane_putstr_yx(n, i+1, box->begx+1, "•");
    ncplane_set_styles(n, 0);

    chord_fg_alt(n);
    ncplane_printf_yx(n, i+1, box->begx+3, "%s", u.name);
  }
}
