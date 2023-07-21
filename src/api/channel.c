#include "api.h"

#include <jansson.h>
#include <stdlib.h>
#include <string.h>

CURLcode api_create_message(CURL *curl, char *auth, char *channel_id, char *content, curl_write_callback callback) {
  json_t *obj = json_object();
  json_t *content_obj = json_string(content);
  json_object_set(obj, "content", content_obj);

  char *data = json_dumps(obj, 0);

  char *path = malloc(512);
  snprintf(path, 512, "/channels/%s/messages", channel_id);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
  CURLcode res = api_request(curl, auth, path, callback);

  free(obj);
  free(content_obj);
  free(data);
  free(path);
  curl_easy_cleanup(curl);

  return res;
}
