#include "include/structures.h"
#include "include/ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <notcurses/direct.h>
#include <notcurses/notcurses.h>
#include <curl/curl.h>
#include <json-c/json_tokener.h>
#include <json-c/json_object.h>

void middle_print(struct ncplane *n, char *text) {
  unsigned int y;
  unsigned int x;
  ncplane_dim_yx(n, &y, &x);

  ncplane_printf_yx(n, y / 2, (x / 2) - (strlen(text) / 2), text);
}

static size_t callback(void *contents, size_t size, size_t nmemb, void *data) {
  struct ncplane *n = (struct ncplane *) data;

  char* txt = malloc(64);
  strcpy(txt, "Welcome: ");
  struct json_object *obj = json_tokener_parse(contents);
  for (int i = 0; i < json_object_array_length(obj); i++) {
    json_object *elem = json_object_array_get_idx(obj, i);
    strcat(txt, json_object_get_string(elem));
    strcat(txt, " ");
  }

  middle_print(n, txt);
  return size * nmemb;
}

int main() {
  notcurses_options opts = {};
  struct notcurses *nc = notcurses_core_init(&opts, stdout);
  if (NULL == nc) {
    printf("Whoops\n");
    return -1;
  }

  CURL *curl = curl_easy_init();
  if (!curl) {
    printf("Whoops\n");
    return -1;
  }

  notcurses_enter_alternate_screen(nc);

  struct ncplane *n = notcurses_stdplane(nc);
  middle_print(n, "Loading...");
  ncpile_render(n);
  notcurses_render(nc);

  curl_easy_setopt(curl, CURLOPT_URL, "https://random-word-api.herokuapp.com/word?number=3");
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, n);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    printf("Whoops\n");
  }

  user user_1 = {
    .name = "Foo",
    .status = 0,
  };

  user user_2 = {
    .name = "Bar",
    .status = 0,
  };

  user user_3 = {
    .name = "Baz",
    .status = 0,
  };

  user *users = malloc(3);
  *users = user_1;
  *(users + (sizeof(user))) = user_2;
  *(users + (sizeof(user) * 2)) = user_3;

  while (true) {
    ui_clear(n);
    ui_draw_userlist(n, users, 3, 32);

    ncpile_render(n);
    notcurses_render(nc);
  }

  notcurses_leave_alternate_screen(nc);
  notcurses_stop(nc);

  curl_easy_cleanup(curl);

  return 0;
}
