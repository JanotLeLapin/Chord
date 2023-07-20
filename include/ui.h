#pragma once

#include "structures.h"

#include <notcurses/notcurses.h>

void ui_clear(struct ncplane *n);
void ui_draw_userlist(struct ncplane *n, user *users, int user_count, int width);
void ui_draw_input(struct ncplane *n, char *message);
