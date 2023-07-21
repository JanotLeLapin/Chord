#include "api.h"
#include "structures.h"
#include "ui.h"

#include <stdlib.h>
#include <string.h>

static size_t callback(char *contents, size_t size, size_t nmemb, void *data) {
  user *u = (user *) data;
  *u = *discord_parse_user(contents);
  
  return size * nmemb;
}

static size_t default_callback(char *contents, size_t size, size_t nmemb, void *data) {
  return size * nmemb;
}

int main() {
  // Discord API
  CURL *curl;
  char *token = malloc(71);
  FILE *f = fopen("token", "r");

  if (NULL == f) {
    printf("Could not access token. Be sure to have a token file in the current directory containing your Discord token.\n");
    return -1;
  }

  fgets(token, 71, f);

  char *auth = malloc(100 * sizeof(char));
  snprintf(auth, 100 * sizeof(char), "Authorization: %s", token);

  free(token);
  fclose(f);

  curl = curl_easy_init();
  api_create_message(curl, auth, "1132018104734580767", "Nez", default_callback);
  curl_easy_cleanup(curl);

  curl = curl_easy_init();
  api_create_message(curl, auth, "1132018104734580767", "Lesieur", default_callback);
  curl_easy_cleanup(curl);
  
  // notcurses
  notcurses_options opts = {};
  struct notcurses *nc = notcurses_core_init(&opts, stdout);
  if (NULL == nc) {
    printf("Could not initialize notcurses.\n");
    return -1;
  }

  notcurses_linesigs_disable(nc);
  notcurses_enter_alternate_screen(nc);

  struct ncplane *n = notcurses_stdplane(nc);

  user u;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &u);
  api_get_current_user(curl, auth, callback);
  curl_easy_cleanup(curl);

  char *message = malloc(3001 * sizeof(char));
  short message_len = 0;
  *message = '\0';

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

    ui_box input_box = {
      .begx = 32,
      .begy = y - 2,
      .endx = x - 32,
      .endy = y - 2,
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
    ui_draw_input(n, message, &input_box);
    ui_draw_profile(n, &u, &profile_box);

    ncinput in;
    int id = notcurses_get_nblock(nc, &in);

    if (in.evtype == NCTYPE_PRESS || in.evtype == NCTYPE_REPEAT) {
      if (1115008 == id && message_len > 0) {
        message_len -= sizeof(char);
        *(message+message_len) = '\0';
      }

      if (1115121 == id && message_len > 0) {
        curl = curl_easy_init();
        api_create_message(curl, auth, "1132018104734580767", message, default_callback);
        curl_easy_cleanup(curl);

        *message = '\0';
        message_len = 0;
      }

      if (id >= 32 && id <= 126) {
        if (in.evtype) {
          *(message+message_len) = (char) id;
          *(message+message_len+sizeof(char)) = '\0';
          message_len+=sizeof(char);
        }
      }
    }

    ncpile_render(n);
    notcurses_render(nc);

    if (27 == id) {
      break;
    }
  }

  notcurses_leave_alternate_screen(nc);
  notcurses_stop(nc);

  return 0;
}
