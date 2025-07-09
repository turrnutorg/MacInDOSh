#include "video.h"
#include "gui.h"
#include "string.h"
#include "tiles.h"
#include "text.h"
#include "stdlib.h"
#include "fonts.h"

Glyph glyphs_geneva[256];
Glyph glyphs_chicago[256];
static unsigned char decompressed_tiles_geneva[256][144];
static unsigned char decompressed_tiles_chicago[256][144];

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

#define LOAD_GLYPH(ch, name, fontset, buffer) \
    decompressTile(buffer[(unsigned char)(ch)], name); \
    fontset[(unsigned char)(ch)].bmp = buffer[(unsigned char)(ch)]

void loadGenevaFont(void) {
    for (int i = 0; i < 256; ++i) {
        glyphs_geneva[i].bmp = NULL;
        glyphs_geneva[i].adv = 13;
        glyphs_geneva[i].x0  = 0;
        glyphs_geneva[i].x1  = 11;
    }

    // LOAD_GLYPH('\b', geneva_sym_command, glyphs_geneva, decompressed_tiles_geneva);

    LOAD_GLYPH(' ', geneva_space, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('.', geneva_sym_period, glyphs_geneva, decompressed_tiles_geneva);

    LOAD_GLYPH('!', geneva_sym_excl, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('"', geneva_sym_quote, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('#', geneva_sym_hash, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('$', geneva_sym_dollar, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('%', geneva_sym_percent, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('&', geneva_sym_amp, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('\'', geneva_sym_apos, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('(', geneva_sym_lparen, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH(')', geneva_sym_rparen, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('*', geneva_sym_aster, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('+', geneva_sym_plus, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH(',', geneva_sym_comma, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('-', geneva_sym_minus, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('/', geneva_sym_slash, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH(':', geneva_sym_colon, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH(';', geneva_sym_semicolon, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('<', geneva_sym_lt, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('=', geneva_sym_equals, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('>', geneva_sym_gt, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('?', geneva_sym_qmark, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('@', geneva_sym_at, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('[', geneva_sym_lbrack, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('\\', geneva_sym_bslash, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH(']', geneva_sym_rbrack, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('^', geneva_sym_caret, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('_', geneva_sym_underscore, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('`', geneva_sym_backtick, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('{', geneva_sym_lbrace, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('|', geneva_sym_pipe, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('}', geneva_sym_rbrace, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('~', geneva_sym_tilde, glyphs_geneva, decompressed_tiles_geneva);

    LOAD_GLYPH('0', geneva_num_0, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('1', geneva_num_1, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('2', geneva_num_2, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('3', geneva_num_3, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('4', geneva_num_4, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('5', geneva_num_5, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('6', geneva_num_6, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('7', geneva_num_7, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('8', geneva_num_8, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('9', geneva_num_9, glyphs_geneva, decompressed_tiles_geneva);

    LOAD_GLYPH('A', geneva_cap_a, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('B', geneva_cap_b, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('C', geneva_cap_c, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('D', geneva_cap_d, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('E', geneva_cap_e, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('F', geneva_cap_f, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('G', geneva_cap_g, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('H', geneva_cap_h, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('I', geneva_cap_i, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('J', geneva_cap_j, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('K', geneva_cap_k, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('L', geneva_cap_l, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('M', geneva_cap_m, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('N', geneva_cap_n, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('O', geneva_cap_o, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('P', geneva_cap_p, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('Q', geneva_cap_q, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('R', geneva_cap_r, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('S', geneva_cap_s, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('T', geneva_capt, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('U', geneva_cap_u, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('V', geneva_cap_v, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('W', geneva_cap_w, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('X', geneva_cap_x, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('Y', geneva_cap_y, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('Z', geneva_cap_z, glyphs_geneva, decompressed_tiles_geneva);

    LOAD_GLYPH('a', geneva_low_a, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('b', geneva_low_b, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('c', geneva_low_c, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('d', geneva_low_d, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('e', geneva_low_e, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('f', geneva_low_f, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('g', geneva_low_g, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('h', geneva_low_h, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('i', geneva_low_i, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('j', geneva_low_j, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('k', geneva_low_k, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('l', geneva_low_l, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('m', geneva_low_m, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('n', geneva_low_n, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('o', geneva_low_o, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('p', geneva_low_p, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('q', geneva_low_q, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('r', geneva_low_r, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('s', geneva_low_s, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('t', geneva_lowt, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('u', geneva_low_u, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('v', geneva_low_v, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('w', geneva_low_w, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('x', geneva_low_x, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('y', geneva_low_y, glyphs_geneva, decompressed_tiles_geneva);
    LOAD_GLYPH('z', geneva_low_z, glyphs_geneva, decompressed_tiles_geneva);

    for (int i = 0; i < 128; ++i)
        glyphs_geneva[i].adv = font_width_geneva[i];

    for (int i = 0; i < 256; ++i)
        analyseGlyph(&glyphs_geneva[i]);
}

void loadChicagoFont(void) {
    for (int i = 0; i < 256; ++i) {
        glyphs_chicago[i].bmp = NULL;
        glyphs_chicago[i].adv = 13;
        glyphs_chicago[i].x0  = 0;
        glyphs_chicago[i].x1  = 11;
    }
    LOAD_GLYPH('\b', chicago_sym_command, glyphs_chicago, decompressed_tiles_chicago);

    LOAD_GLYPH(' ', chicago_space, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('.', chicago_sym_period, glyphs_chicago, decompressed_tiles_chicago);

    LOAD_GLYPH('!', chicago_sym_excl, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('"', chicago_sym_quote, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('#', chicago_sym_hash, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('$', chicago_sym_dollar, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('%', chicago_sym_percent, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('&', chicago_sym_amp, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('\'', chicago_sym_apos, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('(', chicago_sym_lparen, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH(')', chicago_sym_rparen, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('*', chicago_sym_aster, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('+', chicago_sym_plus, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH(',', chicago_sym_comma, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('-', chicago_sym_minus, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('/', chicago_sym_slash, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH(':', chicago_sym_colon, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH(';', chicago_sym_semicolon, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('<', chicago_sym_lt, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('=', chicago_sym_equals, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('>', chicago_sym_gt, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('?', chicago_sym_qmark, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('@', chicago_sym_at, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('[', chicago_sym_lbrack, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('\\', chicago_sym_bslash, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH(']', chicago_sym_rbrack, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('^', chicago_sym_caret, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('_', chicago_sym_underscore, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('`', chicago_sym_backtick, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('{', chicago_sym_lbrace, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('|', chicago_sym_pipe, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('}', chicago_sym_rbrace, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('~', chicago_sym_tilde, glyphs_chicago, decompressed_tiles_chicago);

    LOAD_GLYPH('0', chicago_num_0, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('1', chicago_num_1, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('2', chicago_num_2, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('3', chicago_num_3, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('4', chicago_num_4, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('5', chicago_num_5, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('6', chicago_num_6, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('7', chicago_num_7, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('8', chicago_num_8, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('9', chicago_num_9, glyphs_chicago, decompressed_tiles_chicago);

    LOAD_GLYPH('A', chicago_cap_a, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('B', chicago_cap_b, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('C', chicago_cap_c, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('D', chicago_cap_d, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('E', chicago_cap_e, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('F', chicago_cap_f, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('G', chicago_cap_g, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('H', chicago_cap_h, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('I', chicago_cap_i, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('J', chicago_cap_j, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('K', chicago_cap_k, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('L', chicago_cap_l, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('M', chicago_cap_m, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('N', chicago_cap_n, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('O', chicago_cap_o, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('P', chicago_cap_p, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('Q', chicago_cap_q, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('R', chicago_cap_r, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('S', chicago_cap_s, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('T', chicago_capt, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('U', chicago_cap_u, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('V', chicago_cap_v, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('W', chicago_cap_w, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('X', chicago_cap_x, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('Y', chicago_cap_y, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('Z', chicago_cap_z, glyphs_chicago, decompressed_tiles_chicago);

    LOAD_GLYPH('a', chicago_low_a, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('b', chicago_low_b, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('c', chicago_low_c, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('d', chicago_low_d, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('e', chicago_low_e, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('f', chicago_low_f, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('g', chicago_low_g, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('h', chicago_low_h, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('i', chicago_low_i, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('j', chicago_low_j, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('k', chicago_low_k, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('l', chicago_low_l, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('m', chicago_low_m, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('n', chicago_low_n, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('o', chicago_low_o, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('p', chicago_low_p, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('q', chicago_low_q, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('r', chicago_low_r, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('s', chicago_low_s, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('t', chicago_lowt, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('u', chicago_low_u, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('v', chicago_low_v, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('w', chicago_low_w, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('x', chicago_low_x, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('y', chicago_low_y, glyphs_chicago, decompressed_tiles_chicago);
    LOAD_GLYPH('z', chicago_low_z, glyphs_chicago, decompressed_tiles_chicago);

    for (int i = 0; i < 128; ++i)
        glyphs_chicago[i].adv = font_width_chicago[i];

    for (int i = 0; i < 256; ++i)
        analyseGlyph(&glyphs_chicago[i]);
}

void printFont(Glyph *font, const unsigned char *s, int x, int y, int spacing) {
    const int baseX = x;

    while (*s) {
        unsigned char c = *s++;

        if (c == '\n') { y += 12; x = baseX; continue; }
        if (c == ' ')  { x += 4; continue; }

        const Glyph *g = &font[c];
        if (!g->bmp)   { x += 13; continue; }

        if (x > WIDTH - 12) { y += 12; x = baseX; }

        blitGlyphTight(g, x, y);
        x += g->adv + spacing;
    }
    drawBuffer();
}

void printFontNoFB(Glyph *font, const unsigned char *s, int x, int y, int spacing) {
    const int baseX = x;

    while (*s) {
        unsigned char c = *s++;

        if (c == '\n') { y += 12; x = baseX; continue; }
        if (c == ' ')  { x += 4; continue; }

        const Glyph *g = &font[c];
        if (!g->bmp)   { x += 13; continue; }

        if (x > WIDTH - 12) { y += 12; x = baseX; }

        blitGlyphTightNoFB(g, x, y);
        x += g->adv + spacing;
    }
}

void print(const unsigned char *s, int x, int y) {
    printFont(glyphs_geneva, s, x, y, 0);
}

void printNoFramebuf(const unsigned char *s, int x, int y) {
    printFontNoFB(glyphs_geneva, s, x, y, 0);
}

void printChicago(const unsigned char *s, int x, int y) {
    printFont(glyphs_chicago, s, x, y, 1);
}

void printChicagoNoFB(const unsigned char *s, int x, int y) {
    printFontNoFB(glyphs_chicago, s, x, y, 1);
}
