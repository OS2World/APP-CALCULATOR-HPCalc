#define SIZE_NORM       1
#define SIZE_SMALL      2
#define MAX_FONT        64

#ifdef CHANGE
UCHAR   szLargeDispFont[MAX_FONT], szSmallDispFont[MAX_FONT];
UCHAR   szLargeDigitFont[MAX_FONT], szSmallDigitFont[MAX_FONT];
UCHAR   szLargeBSFont[MAX_FONT], szSmallBSFont[MAX_FONT];
UCHAR   szLargeFuncFont[MAX_FONT], szSmallFuncFont[MAX_FONT];
UCHAR   szLargeMenuFont[MAX_FONT], szSmallMenuFont[MAX_FONT];
LONG    lDispBG, lDispFG, lButBG, lButFG, lDialogBG, lShiftFG;
int     fDispBG, fDispFG, fButBG, fButFG, fDialogBG, fShiftFG;
#else
extern UCHAR   szLargeDispFont[], szSmallDispFont[];
extern UCHAR   szLargeDigitFont[], szSmallDigitFont[];
extern UCHAR   szLargeBSFont[], szSmallBSFont[];
extern UCHAR   szLargeFuncFont[], szSmallFuncFont[];
extern UCHAR   szLargeMenuFont[], szSmallMenuFont[];
extern LONG    lDispBG, lDispFG, lButBG, lButFG, lDialogBG, lShiftFG;
extern int     fDispBG, fDispFG, fButBG, fButFG, fDialogBG, fShiftFG;
#endif

void DrawShiftText(HPS hps);
void SetPositions(USHORT pos);
void CreateButtons(HWND hwndClient);
void ChangeSize(USHORT, BOOL);
void ShowXYZT(BOOL fMode);
void ShowKeyboard(BOOL, USHORT);
void ShowHexOct(USHORT);

