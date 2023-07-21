#pragma once

#include "structures.h"

#include <curl/curl.h>

char *api_url(char *path);

// USER
CURLcode api_get_current_user(CURL *curl, curl_write_callback callback);
