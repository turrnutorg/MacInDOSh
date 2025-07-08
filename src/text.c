#include "video.h"
#include "gui.h"
#include "string.h"
#include "tiles.h"
#include "text.h"
#include "stdlib.h"

typedef struct {
    const unsigned char *bmp;
    unsigned char x0;
    unsigned char x1;
    unsigned char adv;
} Glyph;

static Glyph glyphs[256];
static unsigned char decompressed_tiles[256][144];

// decompress signed RLE to 12x12 bitmap (144 bytes)
static void decompressTile(unsigned char *dst, const int8_t *rle) {
    int idx = 0;
    for (int i = 0; rle[i] != 0 && idx < 144; ++i) {
        int count = rle[i];
        unsigned char val = count > 0 ? 17 : 0;
        count = count > 0 ? count : -count;

        for (int j = 0; j < count && idx < 144; ++j)
            dst[idx++] = val;
    }

    while (idx < 144)
        dst[idx++] = 17;
}

static void analyseGlyph(Glyph *g) {
    if (!g->bmp) { g->x0 = 0; g->x1 = 11; g->adv = 13; return; }

    int l = 0, r = 11;
    for (; l < 12; ++l) {
        int solid = 0;
        for (int row = 0; row < 12; ++row)
            if (g->bmp[row*12 + l] != 17) { solid = 1; break; }
        if (solid) break;
    }
    for (; r >= l; --r) {
        int solid = 0;
        for (int row = 0; row < 12; ++row)
            if (g->bmp[row*12 + r] != 17) { solid = 1; break; }
        if (solid) break;
    }
    g->x0  = (unsigned char)l;
    g->x1  = (unsigned char)r;
    g->adv = (unsigned char)((r - l + 1) + 1);
}

static inline void blitGlyphTight(const Glyph *g, int x, int y) {
    if (!g->bmp) return;

    for (int col = g->x0; col <= g->x1; ++col)
        for (int row = 0; row < 12; ++row)
            if (g->bmp[row*12 + col] != 17)
                setPixel(x + (col - g->x0), y + row, 0);
}

static inline void blitGlyphTightNoFB(const Glyph *g, int x, int y) {
    if (!g->bmp) return;

    for (int col = g->x0; col <= g->x1; ++col)
        for (int row = 0; row < 12; ++row)
            if (g->bmp[row*12 + col] != 17)
                plotPixel(x + (col - g->x0), y + row, 0);
}

#define LOAD_GLYPH(ch, name) \
    decompressTile(decompressed_tiles[(unsigned char)(ch)], name##_rle); \
    glyphs[(unsigned char)(ch)].bmp = decompressed_tiles[(unsigned char)(ch)]

void loadText(void) {
    for (int i = 0; i < 256; ++i) {
        glyphs[i].bmp = NULL;
        glyphs[i].adv = 13;
        glyphs[i].x0  = 0;
        glyphs[i].x1  = 11;
    }
 
    LOAD_GLYPH(' ', tile_space);
    LOAD_GLYPH('.', tile_sym_period);

    LOAD_GLYPH('!', tile_sym_excl);
    LOAD_GLYPH('"', tile_sym_quote);
    LOAD_GLYPH('#', tile_sym_hash);
    LOAD_GLYPH('$', tile_sym_dollar);
    LOAD_GLYPH('%', tile_sym_percent);
    LOAD_GLYPH('&', tile_sym_amp);
    LOAD_GLYPH('\'', tile_sym_apos);
    LOAD_GLYPH('(', tile_sym_lparen);
    LOAD_GLYPH(')', tile_sym_rparen);
    LOAD_GLYPH('*', tile_sym_aster);
    LOAD_GLYPH('+', tile_sym_plus);
    LOAD_GLYPH(',', tile_sym_comma);
    LOAD_GLYPH('-', tile_sym_minus);
    LOAD_GLYPH('/', tile_sym_slash);
    LOAD_GLYPH(':', tile_sym_colon);
    LOAD_GLYPH(';', tile_sym_semicolon);
    LOAD_GLYPH('<', tile_sym_lt);
    LOAD_GLYPH('=', tile_sym_equals);
    LOAD_GLYPH('>', tile_sym_gt);
    LOAD_GLYPH('?', tile_sym_qmark);
    LOAD_GLYPH('@', tile_sym_at);
    LOAD_GLYPH('[', tile_sym_lbrack);
    LOAD_GLYPH('\\', tile_sym_bslash);
    LOAD_GLYPH(']', tile_sym_rbrack);
    LOAD_GLYPH('^', tile_sym_caret);
    LOAD_GLYPH('_', tile_sym_underscore);
    LOAD_GLYPH('`', tile_sym_backtick);
    LOAD_GLYPH('{', tile_sym_lbrace);
    LOAD_GLYPH('|', tile_sym_pipe);
    LOAD_GLYPH('}', tile_sym_rbrace);
    LOAD_GLYPH('~', tile_sym_tilde);

    LOAD_GLYPH('0', tile_num_0);
    LOAD_GLYPH('1', tile_num_1);
    LOAD_GLYPH('2', tile_num_2);
    LOAD_GLYPH('3', tile_num_3);
    LOAD_GLYPH('4', tile_num_4);
    LOAD_GLYPH('5', tile_num_5);
    LOAD_GLYPH('6', tile_num_6);
    LOAD_GLYPH('7', tile_num_7);
    LOAD_GLYPH('8', tile_num_8);
    LOAD_GLYPH('9', tile_num_9);

    LOAD_GLYPH('A', tile_cap_a);
    LOAD_GLYPH('B', tile_cap_b);
    LOAD_GLYPH('C', tile_cap_c);
    LOAD_GLYPH('D', tile_cap_d);
    LOAD_GLYPH('E', tile_cap_e);
    LOAD_GLYPH('F', tile_cap_f);
    LOAD_GLYPH('G', tile_cap_g);
    LOAD_GLYPH('H', tile_cap_h);
    LOAD_GLYPH('I', tile_cap_i);
    LOAD_GLYPH('J', tile_cap_j);
    LOAD_GLYPH('K', tile_cap_k);
    LOAD_GLYPH('L', tile_cap_l);
    LOAD_GLYPH('M', tile_cap_m);
    LOAD_GLYPH('N', tile_cap_n);
    LOAD_GLYPH('O', tile_cap_o);
    LOAD_GLYPH('P', tile_cap_p);
    LOAD_GLYPH('Q', tile_cap_q);
    LOAD_GLYPH('R', tile_cap_r);
    LOAD_GLYPH('S', tile_cap_s);
    LOAD_GLYPH('T', tile_capt);
    LOAD_GLYPH('U', tile_cap_u);
    LOAD_GLYPH('V', tile_cap_v);
    LOAD_GLYPH('W', tile_cap_w);
    LOAD_GLYPH('X', tile_cap_x);
    LOAD_GLYPH('Y', tile_cap_y);
    LOAD_GLYPH('Z', tile_cap_z);

    LOAD_GLYPH('a', tile_low_a);
    LOAD_GLYPH('b', tile_low_b);
    LOAD_GLYPH('c', tile_low_c);
    LOAD_GLYPH('d', tile_low_d);
    LOAD_GLYPH('e', tile_low_e);
    LOAD_GLYPH('f', tile_low_f);
    LOAD_GLYPH('g', tile_low_g);
    LOAD_GLYPH('h', tile_low_h);
    LOAD_GLYPH('i', tile_low_i);
    LOAD_GLYPH('j', tile_low_j);
    LOAD_GLYPH('k', tile_low_k);
    LOAD_GLYPH('l', tile_low_l);
    LOAD_GLYPH('m', tile_low_m);
    LOAD_GLYPH('n', tile_low_n);
    LOAD_GLYPH('o', tile_low_o);
    LOAD_GLYPH('p', tile_low_p);
    LOAD_GLYPH('q', tile_low_q);
    LOAD_GLYPH('r', tile_low_r);
    LOAD_GLYPH('s', tile_low_s);
    LOAD_GLYPH('t', tile_lowt);
    LOAD_GLYPH('u', tile_low_u);
    LOAD_GLYPH('v', tile_low_v);
    LOAD_GLYPH('w', tile_low_w);
    LOAD_GLYPH('x', tile_low_x);
    LOAD_GLYPH('y', tile_low_y);
    LOAD_GLYPH('z', tile_low_z);

    for (int i = 0; i < 256; ++i) analyseGlyph(&glyphs[i]);
}

void print(const unsigned char *s, int x, int y) {
    const int baseX = x;

    while (*s) {
        unsigned char c = *s++;

        if (c == '\n') { y += 12; x = baseX; continue; }
        if (c == ' ')  { x += 4;  continue; }

        const Glyph *g = &glyphs[c];
        if (!g->bmp)   { x += 13; continue; }

        if (x > WIDTH - 12) { y += 12; x = baseX; }

        blitGlyphTight(g, x, y);
        x += g->adv;
    }
    drawBuffer();
}

void printNoFramebuf(const unsigned char *s, int x, int y) {
    const int baseX = x;

    while (*s) {
        unsigned char c = *s++;

        if (c == '\n') { y += 12; x = baseX; continue; }
        if (c == ' ')  { x += 4;  continue; }

        const Glyph *g = &glyphs[c];
        if (!g->bmp)   { x += 13; continue; }

        if (x > WIDTH - 12) { y += 12; x = baseX; }

        blitGlyphTightNoFB(g, x, y);
        x += g->adv;
    }
}
