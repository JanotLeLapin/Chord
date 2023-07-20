#pragma once

#include "structures.h"

#include <notcurses/notcurses.h>

typedef struct ui_box {
  unsigned int begx;
  unsigned int begy;
  unsigned int endx;
  unsigned int endy;
} ui_box;

void ui_draw_rect(struct ncplane *n, int begx, int begy, int endx, int endy);
void ui_clear(struct ncplane *n);

void ui_clear(struct ncplane *n);
void ui_draw_userlist(struct ncplane *n, user *users, int user_count, ui_box *box);
void ui_draw_messages(struct ncplane *n, message *messages, int message_count, ui_box *box);
void ui_draw_input(struct ncplane *n, char *message, ui_box *box);
