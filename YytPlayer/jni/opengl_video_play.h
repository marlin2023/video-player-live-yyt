#ifndef __OPENGL_VIDEO_PLAY_H
#define __OPENGL_VIDEO_PLAY_H


#define TEXTURE_WIDTH 512
#define TEXTURE_HEIGHT 256

/*
 *
 * return : return -1 mean failed
 * */
int init_opengl_variable(int handle);

void opengl_resize(int screen_w ,int screen_h ,int display_w ,int display_h);

#endif
