/*
 * devour
 * X11 window swallower
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* #define ESACPE "`~!#$^&*()[]{}\\|;\'\"<>/? " */
/* #define ESACPE "`'\"()[]& " */
#define ESACPE "`'\"()[]& "

void run_command(char **argv) {
  char argc;
  char *arg;
  char cmd[1024] = {0};
  int is_unsafe = 0;

  /* while ((arg = *++argv)) { */
  /* if (strchr(ESACPE, *arg)) { */
  /*   printf("exist\n"); */
  /* } else */
  /*   strcat(cmd, *argv); */
  /* strcat(cmd, " "); */
  /* } */
  /* strcat(cmd, ">/dev/null 2>&1"); */
  /* system(cmd); */

  while ((arg = *++argv)) {
    while ((argc = *arg++))
      if (strchr(ESACPE, argc))
        is_unsafe = 1;
    if (is_unsafe) {
      strcat(cmd, "'");
      strcat(cmd, *argv);
      strcat(cmd, "'");
    } else
      strcat(cmd, *argv);
    strcat(cmd, " ");
  }
  printf("%s", cmd);
  /* system(cmd); */
}

int main(int argc, char **argv) {
  int rev;
  Window win;
  Display *dis = XOpenDisplay(0);

  XGetInputFocus(dis, &win, &rev);
  XUnmapWindow(dis, win);
  XFlush(dis);
  run_command(argv);
  XMapWindow(dis, win);
  XCloseDisplay(dis);

  (void)argc;
  return 0;
}
