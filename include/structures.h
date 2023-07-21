#pragma once

typedef struct user {
  unsigned long *id;
  char *username;
  char *discriminator;
  char *global_name;
  char *avatar;
} user;

typedef struct message {
  unsigned long *id;
  char *content;
  user *author;
} message;

user *discord_parse_user(char *json);
