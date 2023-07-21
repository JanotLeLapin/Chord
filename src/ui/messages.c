#include "colors.h"
#include "ui.h"
#include "structures.h"

#include <math.h>
#include <stdlib.h>

void ui_draw_messages(struct ncplane *n, message *messages, int message_count, ui_box *box) {
  chord_bg_default(n);
  ui_draw_rect(n, box->begx, box->begy, box->endx, box->endy);

  int row = box->endy;

  for (int i = 0; i < message_count; i++) {
    message msg = *(messages + sizeof(message) * i);

    chord_fg_default(n);
    ncplane_printf_yx(n, row, box->begx, "%s", msg.content);

    chord_fg_alt(n);
    ncplane_set_styles(n, NCSTYLE_BOLD);
    ncplane_printf_yx(n, row-1, box->begx, "%s:", msg.author->username);

    ncplane_set_styles(n, 0);
    row -= 3;
  }
}
