#include "VIDEO.H"
#include "GUI.h"
#include <string.h>

unsigned char *fontTiles[256];

void loadText(void) {
    fontTiles['A'] = (unsigned char*)loadTileFile("text\\cap_a.til", 8, 8);
    fontTiles['B'] = (unsigned char*)loadTileFile("text\\cap_b.til", 8, 8);
    fontTiles['C'] = (unsigned char*)loadTileFile("text\\cap_c.til", 8, 8);
    fontTiles['D'] = (unsigned char*)loadTileFile("text\\cap_d.til", 8, 8);
    fontTiles['E'] = (unsigned char*)loadTileFile("text\\cap_e.til", 8, 8);
    fontTiles['F'] = (unsigned char*)loadTileFile("text\\cap_f.til", 8, 8);
    fontTiles['G'] = (unsigned char*)loadTileFile("text\\cap_g.til", 8, 8);
    fontTiles['H'] = (unsigned char*)loadTileFile("text\\cap_h.til", 8, 8);
    fontTiles['I'] = (unsigned char*)loadTileFile("text\\cap_i.til", 8, 8);
    fontTiles['J'] = (unsigned char*)loadTileFile("text\\cap_j.til", 8, 8);
    fontTiles['K'] = (unsigned char*)loadTileFile("text\\cap_k.til", 8, 8);
    fontTiles['L'] = (unsigned char*)loadTileFile("text\\cap_l.til", 8, 8);
    fontTiles['M'] = (unsigned char*)loadTileFile("text\\cap_m.til", 8, 8);
    fontTiles['N'] = (unsigned char*)loadTileFile("text\\cap_n.til", 8, 8);
    fontTiles['O'] = (unsigned char*)loadTileFile("text\\cap_o.til", 8, 8);
    fontTiles['P'] = (unsigned char*)loadTileFile("text\\cap_p.til", 8, 8);
    fontTiles['Q'] = (unsigned char*)loadTileFile("text\\cap_q.til", 8, 8);
    fontTiles['R'] = (unsigned char*)loadTileFile("text\\cap_r.til", 8, 8);
    fontTiles['S'] = (unsigned char*)loadTileFile("text\\cap_s.til", 8, 8);
    fontTiles['T'] = (unsigned char*)loadTileFile("text\\cap_t.til", 8, 8);
    fontTiles['U'] = (unsigned char*)loadTileFile("text\\cap_u.til", 8, 8);
    fontTiles['V'] = (unsigned char*)loadTileFile("text\\cap_v.til", 8, 8);
    fontTiles['W'] = (unsigned char*)loadTileFile("text\\cap_w.til", 8, 8);
    fontTiles['X'] = (unsigned char*)loadTileFile("text\\cap_x.til", 8, 8);
    fontTiles['Y'] = (unsigned char*)loadTileFile("text\\cap_y.til", 8, 8);
    fontTiles['Z'] = (unsigned char*)loadTileFile("text\\cap_z.til", 8, 8);

    fontTiles['a'] = (unsigned char*)loadTileFile("text\\lower_a.til", 8, 8);
    fontTiles['b'] = (unsigned char*)loadTileFile("text\\lower_b.til", 8, 8);
    fontTiles['c'] = (unsigned char*)loadTileFile("text\\lower_c.til", 8, 8);
    fontTiles['d'] = (unsigned char*)loadTileFile("text\\lower_d.til", 8, 8);
    fontTiles['e'] = (unsigned char*)loadTileFile("text\\lower_e.til", 8, 8);
    fontTiles['f'] = (unsigned char*)loadTileFile("text\\lower_f.til", 8, 8);
    fontTiles['g'] = (unsigned char*)loadTileFile("text\\lower_g.til", 8, 8);
    fontTiles['h'] = (unsigned char*)loadTileFile("text\\lower_h.til", 8, 8);
    fontTiles['i'] = (unsigned char*)loadTileFile("text\\lower_i.til", 8, 8);
    fontTiles['j'] = (unsigned char*)loadTileFile("text\\lower_j.til", 8, 8);
    fontTiles['k'] = (unsigned char*)loadTileFile("text\\lower_k.til", 8, 8);
    fontTiles['l'] = (unsigned char*)loadTileFile("text\\lower_l.til", 8, 8);
    fontTiles['m'] = (unsigned char*)loadTileFile("text\\lower_m.til", 8, 8);
    fontTiles['n'] = (unsigned char*)loadTileFile("text\\lower_n.til", 8, 8);
    fontTiles['o'] = (unsigned char*)loadTileFile("text\\lower_o.til", 8, 8);
    fontTiles['p'] = (unsigned char*)loadTileFile("text\\lower_p.til", 8, 8);
    fontTiles['q'] = (unsigned char*)loadTileFile("text\\lower_q.til", 8, 8);
    fontTiles['r'] = (unsigned char*)loadTileFile("text\\lower_r.til", 8, 8);
    fontTiles['s'] = (unsigned char*)loadTileFile("text\\lower_s.til", 8, 8);
    fontTiles['t'] = (unsigned char*)loadTileFile("text\\lower_t.til", 8, 8);
    fontTiles['u'] = (unsigned char*)loadTileFile("text\\lower_u.til", 8, 8);
    fontTiles['v'] = (unsigned char*)loadTileFile("text\\lower_v.til", 8, 8);
    fontTiles['w'] = (unsigned char*)loadTileFile("text\\lower_w.til", 8, 8);
    fontTiles['x'] = (unsigned char*)loadTileFile("text\\lower_x.til", 8, 8);
    fontTiles['y'] = (unsigned char*)loadTileFile("text\\lower_y.til", 8, 8);
    fontTiles['z'] = (unsigned char*)loadTileFile("text\\lower_z.til", 8, 8);

    fontTiles['0'] = (unsigned char*)loadTileFile("text\\zero.til", 8, 8);
    fontTiles['1'] = (unsigned char*)loadTileFile("text\\one.til", 8, 8);
    fontTiles['2'] = (unsigned char*)loadTileFile("text\\two.til", 8, 8);
    fontTiles['3'] = (unsigned char*)loadTileFile("text\\three.til", 8, 8);
    fontTiles['4'] = (unsigned char*)loadTileFile("text\\four.til", 8, 8);
    fontTiles['5'] = (unsigned char*)loadTileFile("text\\five.til", 8, 8);
    fontTiles['6'] = (unsigned char*)loadTileFile("text\\six.til", 8, 8);
    fontTiles['7'] = (unsigned char*)loadTileFile("text\\seven.til", 8, 8);
    fontTiles['8'] = (unsigned char*)loadTileFile("text\\eight.til", 8, 8);
    fontTiles['9'] = (unsigned char*)loadTileFile("text\\nine.til", 8, 8);

    fontTiles['&'] = (unsigned char*)loadTileFile("text\\and.til", 8, 8);
    fontTiles['\''] = (unsigned char*)loadTileFile("text\\apost.til", 8, 8);
    fontTiles['*'] = (unsigned char*)loadTileFile("text\\asterisk.til", 8, 8);
    fontTiles[':'] = (unsigned char*)loadTileFile("text\\col.til", 8, 8);
    fontTiles[','] = (unsigned char*)loadTileFile("text\\comma.til", 8, 8);
    fontTiles['-'] = (unsigned char*)loadTileFile("text\\dash.til", 8, 8);
    fontTiles['='] = (unsigned char*)loadTileFile("text\\equals.til", 8, 8);
    fontTiles['!'] = (unsigned char*)loadTileFile("text\\exclaim.til", 8, 8);
    fontTiles['/'] = (unsigned char*)loadTileFile("text\\forward.til", 8, 8);
    fontTiles['.'] = (unsigned char*)loadTileFile("text\\fullstop.til", 8, 8);
    fontTiles['['] = (unsigned char*)loadTileFile("text\\l_brack.til", 8, 8);
    fontTiles['('] = (unsigned char*)loadTileFile("text\\r_paren.til", 8, 8);
    fontTiles['%'] = (unsigned char*)loadTileFile("text\\percent.til", 8, 8);
    fontTiles['+'] = (unsigned char*)loadTileFile("text\\plus.til", 8, 8);
    fontTiles['?'] = (unsigned char*)loadTileFile("text\\question.til", 8, 8);
    fontTiles['"'] = (unsigned char*)loadTileFile("text\\quotes.til", 8, 8);
    fontTiles[']'] = (unsigned char*)loadTileFile("text\\r_brack.til", 8, 8);
    fontTiles[')'] = (unsigned char*)loadTileFile("text\\l_paren.til", 8, 8);
    fontTiles[';'] = (unsigned char*)loadTileFile("text\\semicol.til", 8, 8);
    fontTiles['~'] = (unsigned char*)loadTileFile("text\\tilde.til", 8, 8);
}

void print(unsigned char input[101], int printX, int printY) {
    int i;
    int originalPrintX = printX;
    int len = strlen(input);
    for (i = 0; i < len; i++) {
        if (printX > WIDTH - 8 && originalPrintX <= WIDTH - 8) {
            printY += 8;
            printX = originalPrintX;
        } else if (originalPrintX > WIDTH - 8) {
	    originalPrintX = 1;
	}
	if (input[i] == ' ') { printX += 4; continue; }
	if (input[i] == '\n') { printY += 8; printX = originalPrintX; continue;}
    if (input[i] == '\x10') { drawTileBackBuffer(logo, printX, printY, 10, 12, 1); continue; }
	setTile(fontTiles[input[i]], printX, printY, 8, 8, 1);
        printX += 8;
    }
    drawBuffer(0);
}

void printBackBuffer(unsigned char input[101], int printX, int printY) {
    int i;
    int originalPrintX = printX;
    int len = strlen(input);
    for (i = 0; i < len; i++) {
        if (printX > WIDTH - 8 && originalPrintX <= WIDTH - 8) {
            printY += 8;
            printX = originalPrintX;
        } else if (originalPrintX > WIDTH - 8) {
	    originalPrintX = 1;
        }
        if (input[i] == ' ') { printX += 4; continue; }
        if (input[i] == '\n') { printY += 8; printX = originalPrintX; continue;}
        if (420.69 == atof(input[i])) { drawTileBackBuffer(logo, printX, printY, 10, 12, 1); continue; }
        setTileBackBuffer(fontTiles[input[i]], printX, printY, 8, 8, 1);
        printX += 8;
    }
    drawBuffer(1);
}

void printNoFramebuf(unsigned char input[101], int printX, int printY) {
    int i;
    int originalPrintX = printX;
    int len = strlen(input);
    for (i = 0; i < len; i++) {
        if (printX > WIDTH - 8 && originalPrintX <= WIDTH - 8) {
            printY += 8;
            printX = originalPrintX;
        } else if (originalPrintX > WIDTH - 8) {
	    originalPrintX = 1;
	}
	if (input[i] == ' ') { printX += 4; continue; }
	if (input[i] == '\n') { printY += 8; printX = originalPrintX; continue;}
    if (input[i] == '\x10') { drawTileBackBuffer(logo, printX, printY, 10, 12, 1); continue; }
	drawTileNoFramebuf(fontTiles[input[i]], printX, printY, 8, 8, 1);
        printX += 8;
    }
}