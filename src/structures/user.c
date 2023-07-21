#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

user *discord_parse_user(char *json) {
  json_t *obj = json_loads(json, 0, NULL);

  user *u = malloc(sizeof(user));
  u->username = malloc(32 * sizeof(char));
  u->global_name = malloc(32 * sizeof(char));
  u->discriminator = malloc(5 * sizeof(char));

  strcpy(u->username, json_string_value(json_object_get(obj, "username")));
  strcpy(u->global_name, json_string_value(json_object_get(obj, "global_name")));
  strcpy(u->discriminator, json_string_value(json_object_get(obj, "discriminator")));

  free(obj);

  return u;
}
