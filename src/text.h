#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>

typedef struct {
    unsigned char *bmp;
    unsigned char x0, x1, adv;
} Glyph;

extern Glyph glyphs_geneva[256];
extern Glyph glyphs_chicago[256];

void loadGenevaFont(void);
void loadChicagoFont(void);

void print(const unsigned char *s, int x, int y);
void printNoFramebuf(const unsigned char *s, int x, int y);

void printChicago(const unsigned char *s, int x, int y);
void printChicagoNoFB(const unsigned char *s, int x, int y);

void printChicagoGreyed(const unsigned char *s, int x, int y);
void printChicagoGreyedNoFB(const unsigned char *s, int x, int y);

void printFont(Glyph *font, const unsigned char *s, int x, int y, int spacing);
void printFontNoFB(Glyph *font, const unsigned char *s, int x, int y, int spacing);

void printFontGreyed(Glyph *font, const unsigned char *s, int x, int y, int spacing);
void printFontGreyedNoFB(Glyph *font, const unsigned char *s, int x, int y, int spacing);

#endif
