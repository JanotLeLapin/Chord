#include "api.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CURLcode api_get_current_user(discord *d, curl_write_callback callback) {
  return api_request(d, "/users/@me", callback);
}
