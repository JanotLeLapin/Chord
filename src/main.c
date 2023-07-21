#include "api.h"
#include "structures.h"
#include "ui.h"

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <notcurses/notcurses.h>

void middle_print(struct ncplane *n, const char *text) {
  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);

  ncplane_printf_yx(n, y / 2, (x / 2) - (strlen(text) / 2), "%s", text);
}

static size_t callback(char *contents, size_t size, size_t nmemb, void *data) {
  user *u = (user *) data;
  *u = *discord_parse_user(contents);
  
  return size * nmemb;
}

int main() {
  // CURL
  CURL *curl = curl_easy_init();
  if (!curl) {
    printf("Could not initialize CURL.\n");
    return -1;
  }

  // Discord API
  char *token = malloc(75);
  FILE *f = fopen("token", "r");

  if (NULL == f) {
    printf("Could not access token. Be sure to have a token file in the current directory containing your Discord token.\n");
    return -1;
  }

  fgets(token, 75, f);
  discord *d = api_init(curl, token);

  free(token);
  fclose(f);

  // notcurses
  notcurses_options opts = {};
  struct notcurses *nc = notcurses_core_init(&opts, stdout);
  if (NULL == nc) {
    printf("Could not initialize notcurses.\n");
    return -1;
  }
  notcurses_enter_alternate_screen(nc);

  struct ncplane *n = notcurses_stdplane(nc);

  user u;
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &u);
  api_get_current_user(d, callback);

  while (true) {
    // Layout
    unsigned int y;
    unsigned int x;
    ncplane_dim_yx(n, &y, &x);

    ui_box userlist_box = {
      .begx = x - 32,
      .begy = 0,
      .endx = x,
      .endy = y,
    };

    ui_box messages_box = {
      .begx = 32,
      .begy = 0,
      .endx = x - 32,
      .endy = y - 3,
    };

    ui_box profile_box = {
      .begx = 0,
      .begy = y - 4,
      .endx = 32,
      .endy = y,
    };

    ui_clear(n, x, y);

    // ui_draw_messages(n, messages, 2, &messages_box);
    // ui_draw_userlist(n, users, 3, &userlist_box);
    ui_draw_profile(n, &u, &profile_box);

    ncinput in;
    notcurses_get(nc, NULL, &in);

    ncpile_render(n);
    notcurses_render(nc);

    if (in.id == 27) {
      break;
    }
  }

  notcurses_leave_alternate_screen(nc);
  notcurses_stop(nc);

  curl_easy_cleanup(curl);

  return 0;
}
