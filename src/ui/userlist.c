#include "include/colors.h"
#include "include/ui.h"

void ui_draw_userlist(struct ncplane *n, user *users, int user_count, ui_box *box) {
  chord_bg_alt(n);
  ui_draw_rect(n, box->begx, box->begy, box->endx, box->endy);
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
    ncplane_putstr_yx(n, i+1, box->begx+1, "•");

    chord_fg_alt(n);
    ncplane_printf_yx(n, i+1, box->begx+3, "%s", u.name);
  }
}
