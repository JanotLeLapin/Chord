#include "api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CURLcode api_get_current_user(CURL *curl, char *auth, curl_write_callback callback) {
  CURLcode res = api_request(curl, auth, "/users/@me", callback);
  return res;
}
