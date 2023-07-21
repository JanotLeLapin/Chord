#include "api.h"

#include <stdlib.h>
#include <string.h>

CURLcode api_request(CURL *curl, char *auth, char *path, curl_write_callback callback) {
  char *url = malloc(128 * sizeof(char));
  strcpy(url, "https://discord.com/api/v10");
  strcat(url, path);

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, auth);
  headers = curl_slist_append(headers, "Content-Type: application/json");

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  if (NULL != callback) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  }

  CURLcode res = curl_easy_perform(curl);

  free(url);
  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  return res;
}
