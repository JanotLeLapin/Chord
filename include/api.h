#pragma once

#include "structures.h"

#include <curl/curl.h>

typedef struct discord {
  CURL *curl;
  char *auth_header;
} discord;

discord *api_init(CURL *curl, char *token);
CURLcode api_request(discord *d, char *path, curl_write_callback callback);

// USER
CURLcode api_get_current_user(discord *d, curl_write_callback callback);
