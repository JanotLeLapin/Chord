#include "api.h"

#include <stdlib.h>
#include <string.h>

discord *api_init(CURL *curl, char *token) {
  char *header = malloc(100 * sizeof(char));

  strcpy(header, "Authorization: ");
  strcat(header, token);

  discord *d = malloc(sizeof(discord));
  d->curl = curl;
  d->auth_header = header;

  return d;
}

CURLcode api_request(discord *d, char *path, curl_write_callback callback) {
  char *url = malloc(128 * sizeof(char));
  strcpy(url, "https://discord.com/api/v10");
  strcat(url, path);

  struct curl_slist *lst = NULL;
  lst = curl_slist_append(lst, d->auth_header);

  curl_easy_setopt(d->curl, CURLOPT_URL, url);
  curl_easy_setopt(d->curl, CURLOPT_HTTPHEADER, lst);
  curl_easy_setopt(d->curl, CURLOPT_WRITEFUNCTION, callback);

  return curl_easy_perform(d->curl);
}
