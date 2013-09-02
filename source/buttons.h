
#define KEYHEIGHT       25
#define ROWSEP          18
#define ROWSTEP         (KEYHEIGHT + ROWSEP)
#define ROW1            10
#define ROW2            (ROW1 + ROWSTEP)
#define ROW3            (ROW2 + ROWSTEP)
#define ROW4            (ROW3 + ROWSTEP)
#define ROW5            (ROW4 + ROWSTEP)
#define ROW6            (ROW5 + ROWSTEP)
#define ROW7            (ROW6 + ROWSTEP)
#define ROW8            (ROW7 + ROWSTEP)
#define ROW9            (ROW8 + ROWSTEP)
#define FUNCWIDTH       35
#define FUNCSEP         15
#define FUNCSTEP        (FUNCWIDTH + FUNCSEP)
#define COL1            10
#define COL2            (COL1 + FUNCSTEP)
#define COL3            (COL2 + FUNCSTEP)
#define COL4            (COL3 + FUNCSTEP)
#define COL5            (COL4 + FUNCSTEP)
#define COL6            (COL5 + FUNCSTEP)
#define ENTWIDTH        (FUNCWIDTH + FUNCSEP + FUNCWIDTH)
#define DISPLAYWIDTH    (FUNCWIDTH * 5 + FUNCSEP * 4)
#define NUMWIDTH        40
#define NUMSEP          24
#define NUMSTEP         (NUMWIDTH + NUMSEP)
#define NUMCOL1         (COL1 + (DISPLAYWIDTH - 3 * NUMWIDTH - 2 * NUMSEP))
#define NUMCOL2         (NUMCOL1 + NUMSTEP)
#define NUMCOL3         (NUMCOL2 + NUMSTEP)
#define ROWDISPLAY      (ROW9 + 2 * ROWSEP)


