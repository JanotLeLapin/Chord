#include <stdio.h>
#include <string.h>
#include <notcurses/direct.h>
#include <notcurses/notcurses.h>

void middle_print(struct ncplane *n, char *text) {
  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);

  ncplane_printf_yx(n, y / 2, (x / 2) - (strlen(text) / 2), text);
}

int main() {
  notcurses_options opts = {};
  struct notcurses *nc = notcurses_core_init(&opts, stdout);
  if (NULL == nc) {
    printf("Whoops\n");
    return -1;
  }

  notcurses_enter_alternate_screen(nc);


  struct ncplane *n = notcurses_stdplane(nc);
  middle_print(n, "Welcome to Chord!");

  while (true) {
    ncpile_render(n);
    // ncpile_rasterize(n);
    notcurses_render(nc);
  }

  notcurses_leave_alternate_screen(nc);
  notcurses_stop(nc);

  return 0;
}
