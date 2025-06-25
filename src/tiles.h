#ifndef TILES_H
#define TILES_H

 void drawTile(unsigned char *tile, int x, int y, int width, int height, int multiplier);
 void setTile(unsigned char *tile, int x, int y, int width, int height, int multiplier);
 void drawTileNoFramebuf(unsigned char *tile, int x, int y, int width, int height, int multiplier);
 unsigned char *fetchTile(int x, int y, int width, int height);

#endif