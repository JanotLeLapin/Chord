#pragma once

#include "structures.h"

#include <curl/curl.h>

CURLcode api_request(CURL *curl, char *auth, char *path, curl_write_callback callback);

// USER
CURLcode api_get_current_user(CURL *curl, char *auth, curl_write_callback callback);

// CHANNEL
CURLcode api_create_message(CURL *curl, char *auth, char *channel_id, char *content, curl_write_callback callback);
