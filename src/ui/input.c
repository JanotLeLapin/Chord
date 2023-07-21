#include "colors.h"
#include "ui.h"

#include <string.h>

void ui_draw_input(struct ncplane *n, char *message, ui_box *box) {
  chord_bg_alt(n);
  if (strlen(message) == 0) {
    chord_fg_dim(n);
    ncplane_printf_yx(n, box->begy, box->begx, "Type a message...");
  } else {
    chord_fg_default(n);
    ncplane_printf_yx(n, box->begy, box->begx, "%s", message);
  }
}
