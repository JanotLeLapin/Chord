#pragma once

typedef struct user {
  char *name;
  char status;
} user;

typedef struct message {
  char *id;
  char *content;
  user *author;
} message;
