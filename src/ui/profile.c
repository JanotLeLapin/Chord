#include "colors.h"
#include "ui.h"
#include <notcurses/notcurses.h>

void ui_draw_profile(struct ncplane *n, user *profile, ui_box *box) {
  chord_bg_default(n);
  ui_draw_rect(n, box->begx, box->begy, box->endx, box->endy);

  chord_fg_alt(n);
  ncplane_set_styles(n, NCSTYLE_BOLD);
  ncplane_printf_yx(n, box->begy+1, 1, "%s", profile->global_name);

  chord_fg_default(n);
  ncplane_set_styles(n, 0);
  ncplane_printf_yx(n, box->begy+2, 1, "%s", profile->username);
}
