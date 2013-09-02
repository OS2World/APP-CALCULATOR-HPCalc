/* Definitions */
#define INCL_PM

/* allow global vars to be allocated */
#define CHANGE

/* Includes */
#include <string.h>
#include <stdio.h>
#include <os2.h>
#include "HPcalc.h"
#include "interface.h"
#include "interface-vars.h"
#include "change.h"


/* Local Prototypes */
void SwitchFonts(USHORT);
void SwitchSizes(BOOL);


/* local defines */
#define NORMPROP        "10.System Monospaced"
#define NORMMONO        "12.Courier"
#define SMALLPROP       "8.Helv"
#define SMALLMONO       "10.Courier"

/* Local Global Variables */
HWND       hwnd1, hwnd2, hwnd3, hwnd4, hwnd5, hwnd6,
           hwnd7, hwnd8, hwnd9, hwnddot,
           hwndmin, hwndplu, hwndmul, hwnddiv,
           hwndent, hwndxy, hwndsig,
           hwndxeq, hwndrd, hwnd1x,
           hwndchs, hwndsto, hwndsin, hwndroo,
           hwndeex, hwndrcl, hwndcos, hwndlog,
           hwndsst, hwndtan, hwndln,
           hwndpi, hwndtest;

int  KEYHEIGHT, ROWSEP, ROWSTEP,
        ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8, ROW9,
        FUNCWIDTH, FUNCSEP, FUNCSTEP,
        COL1, COL2, COL3, COL4, COL5, COL6,
        ENTWIDTH, DISPLAYWIDTH, NUMWIDTH, NUMSTEP, NUMSEP,
        NUMCOL1, NUMCOL2, NUMCOL3, ROWDISPLAY;


void ChangeSize(USHORT usSize, BOOL fXYZT)
{
   SetPositions(usSize);
   SwitchFonts(usSize);
   SwitchSizes(fXYZT);
}


void SetPositions(USHORT pos)
{
   switch (pos) {
   case SIZE_NORM:
      KEYHEIGHT       =25;
      ROWSEP          =18;
      ROW1            =10;
      FUNCWIDTH       =35;
      FUNCSEP         =15;
      COL1            =10;
      NUMWIDTH        =40;
      NUMSEP          =24;
      break;
   case SIZE_SMALL:
      KEYHEIGHT       =20;
      ROWSEP          =14;
      ROW1            =7;
      FUNCWIDTH       =28;
      FUNCSEP         =12;
      COL1            =7;
      NUMWIDTH        =34;
      NUMSEP          =18;
      break;
   default:
   } /* endswitch */

 ROWSTEP         =(KEYHEIGHT + ROWSEP);
 ROW2            =(ROW1 + ROWSTEP);
 ROW3            =(ROW2 + ROWSTEP);
 ROW4            =(ROW3 + ROWSTEP);
 ROW5            =(ROW4 + ROWSTEP);
 ROW6            =(ROW5 + ROWSTEP);
 ROW7            =(ROW6 + ROWSTEP);
 ROW8            =(ROW7 + ROWSTEP);
 ROW9            =(ROW8 + ROWSTEP);
 FUNCSTEP        =(FUNCWIDTH + FUNCSEP);
 COL2            =(COL1 + FUNCSTEP);
 COL3            =(COL2 + FUNCSTEP);
 COL4            =(COL3 + FUNCSTEP);
 COL5            =(COL4 + FUNCSTEP);
 COL6            =(COL5 + FUNCSTEP);
 ENTWIDTH        =(FUNCWIDTH + FUNCSEP + FUNCWIDTH);
 DISPLAYWIDTH    =(FUNCWIDTH * 5 + FUNCSEP * 4);
 NUMSTEP         =(NUMWIDTH + NUMSEP);
 NUMCOL1         =(COL1 + (DISPLAYWIDTH - 3 * NUMWIDTH - 2 * NUMSEP));
 NUMCOL2         =(NUMCOL1 + NUMSTEP);
 NUMCOL3         =(NUMCOL2 + NUMSTEP);
 ROWDISPLAY      =(ROW9 + 2 * ROWSEP);
}

void SwitchFonts(USHORT  usType)
{
   PSZ       szDisp, szBS, szFunc, szDigit, szMenu;
   HWND         hwndMenu;

   switch (usType) {
   case SIZE_NORM:
      szDisp = szLargeDispFont;
      szBS = szLargeBSFont;
      szFunc = szLargeFuncFont;
      szDigit = szLargeDigitFont;
      szMenu = szLargeMenuFont;
      break;
   case SIZE_SMALL:
      szDisp = szSmallDispFont;
      szBS = szSmallBSFont;
      szFunc = szSmallFuncFont;
      szDigit = szSmallDigitFont;
      szMenu = szSmallMenuFont;
      break;
   default:
      szDisp = szLargeDispFont;
      szBS = szLargeBSFont;
      szFunc = szLargeFuncFont;
      szDigit = szLargeDigitFont;
      szMenu = szLargeMenuFont;
      break;
   } /* endswitch */

   hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);

   WinSetPresParam(hwndMenu, PP_FONTNAMESIZE, (ULONG)strlen(szMenu)+1, (PVOID)szMenu);
   WinSetPresParam(hwndClient, PP_FONTNAMESIZE, (ULONG)strlen(szFunc)+1, (PVOID)szFunc);
   WinSetPresParam(hwndDisplay, PP_FONTNAMESIZE, (ULONG)strlen(szDisp)+1, (PVOID)szDisp);
   WinSetPresParam(hwndDispY, PP_FONTNAMESIZE, (ULONG)strlen(szDisp)+1, (PVOID)szDisp);
   WinSetPresParam(hwndDispZ, PP_FONTNAMESIZE, (ULONG)strlen(szDisp)+1, (PVOID)szDisp);
   WinSetPresParam(hwndDispT, PP_FONTNAMESIZE, (ULONG)strlen(szDisp)+1, (PVOID)szDisp);
   WinSetPresParam(hwndbs, PP_FONTNAMESIZE, (ULONG)strlen(szBS)+1, (PVOID)szBS);
   WinSetPresParam(hwndmin, PP_FONTNAMESIZE, (ULONG)strlen(szBS)+1, (PVOID)szBS);
   WinSetPresParam(hwndplu, PP_FONTNAMESIZE, (ULONG)strlen(szBS)+1, (PVOID)szBS);
   WinSetPresParam(hwndmul, PP_FONTNAMESIZE, (ULONG)strlen(szBS)+1, (PVOID)szBS);
   WinSetPresParam(hwnddiv, PP_FONTNAMESIZE, (ULONG)strlen(szBS)+1, (PVOID)szBS);
   WinSetPresParam(hwnd0, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd1, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd2, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd3, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd4, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd5, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd6, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd7, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd8, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnd9, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
   WinSetPresParam(hwnddot, PP_FONTNAMESIZE, (ULONG)strlen(szDigit)+1, (PVOID)szDigit);
/*
   if (fDispBG) idAttrType=PP_BACKGROUNDCOLORINDEX; else idAttrType=PP_BACKGROUNDCOLOR;
   WinSetPresParam(hwndDisplay, idAttrType, sizeof(int), &lDispBG);
   WinSetPresParam(hwndDispY, idAttrType, sizeof(int), &lDispBG);
   WinSetPresParam(hwndDispZ, idAttrType, sizeof(int), &lDispBG);
   WinSetPresParam(hwndDispT, idAttrType, sizeof(int), &lDispBG);
*/
}


void CreateButtons(HWND hwndClient)
{
     LONG       lRGB;

     hwnd0 = WinCreateWindow(hwndClient, WC_BUTTON, "0", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL1, ROW1, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_0, NULL, NULL);
     hwnd1 = WinCreateWindow(hwndClient, WC_BUTTON, "1", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL1, ROW2, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_1, NULL, NULL);
     hwnd4 = WinCreateWindow(hwndClient, WC_BUTTON, "4", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL1, ROW3, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_4, NULL, NULL);
     hwnd7 = WinCreateWindow(hwndClient, WC_BUTTON, "7", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL1, ROW4, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_7, NULL, NULL);

     hwnddot = WinCreateWindow(hwndClient, WC_BUTTON, "\371", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL2, ROW1, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DOT, NULL, NULL);
     hwnd2 = WinCreateWindow(hwndClient, WC_BUTTON, "2", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL2, ROW2, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_2, NULL, NULL);
     hwnd5 = WinCreateWindow(hwndClient, WC_BUTTON, "5", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL2, ROW3, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_5, NULL, NULL);
     hwnd8 = WinCreateWindow(hwndClient, WC_BUTTON, "8", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL2, ROW4, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_8, NULL, NULL);

     hwnd3 = WinCreateWindow(hwndClient, WC_BUTTON, "3", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL3, ROW2, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_3, NULL, NULL);
     hwnd6 = WinCreateWindow(hwndClient, WC_BUTTON, "6", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL3, ROW3, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_6, NULL, NULL);
     hwnd9 = WinCreateWindow(hwndClient, WC_BUTTON, "9", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, NUMCOL3, ROW4, NUMWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_9, NULL, NULL);

     hwndmin = WinCreateWindow(hwndClient, WC_BUTTON, "-", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW4, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_MIN, NULL, NULL);
     hwndplu = WinCreateWindow(hwndClient, WC_BUTTON, "+", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW3, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_PLU, NULL, NULL);
     hwndmul = WinCreateWindow(hwndClient, WC_BUTTON, "X", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW2, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_MUL, NULL, NULL);
     hwnddiv = WinCreateWindow(hwndClient, WC_BUTTON, "\366", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW1, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DIV, NULL, NULL);

     hwndent = WinCreateWindow(hwndClient, WC_BUTTON, "Enter \030", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW5, ENTWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_ENT, NULL, NULL);
     hwndgol = WinCreateWindow(hwndClient, WC_BUTTON, "", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW6, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_GOL, NULL, NULL);
     hwndxy = WinCreateWindow(hwndClient, WC_BUTTON, "~x\035y", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW7, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_XY, NULL, NULL);
     hwndsig = WinCreateWindow(hwndClient, WC_BUTTON, "\344+", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL1, ROW8, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_SIG, NULL, NULL); 

     hwndxeq = WinCreateWindow(hwndClient, WC_BUTTON, "<",  BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL2, ROW6, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_XEQ, NULL, NULL);
     hwndrd = WinCreateWindow(hwndClient, WC_BUTTON, "R\31", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL2, ROW7, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_RD, NULL, NULL);
     hwnd1x = WinCreateWindow(hwndClient, WC_BUTTON, "1/x", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL2, ROW8, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_1X, NULL, NULL);

     hwndchs = WinCreateWindow(hwndClient, WC_BUTTON, "C~hs", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL3, ROW5, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_CHS, NULL, NULL);
     hwndsto = WinCreateWindow(hwndClient, WC_BUTTON, "St~o", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL3, ROW6, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_STO, NULL, NULL);
     hwndsin = WinCreateWindow(hwndClient, WC_BUTTON, "~Sin", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL3, ROW7, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_SIN, NULL, NULL);
     hwndroo = WinCreateWindow(hwndClient, WC_BUTTON, "\373x", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL3, ROW8, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_ROO, NULL, NULL);

     hwndeex = WinCreateWindow(hwndClient, WC_BUTTON, "~EEx", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL4, ROW5, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_EEX, NULL, NULL);
     hwndrcl = WinCreateWindow(hwndClient, WC_BUTTON, "~Rcl", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL4, ROW6, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_RCL, NULL, NULL);
     hwndcos = WinCreateWindow(hwndClient, WC_BUTTON, "~Cos", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL4, ROW7, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_COS, NULL, NULL);
     hwndlog = WinCreateWindow(hwndClient, WC_BUTTON, "Lo~g", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL4, ROW8, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_LOG, NULL, NULL);

     hwndbs = WinCreateWindow(hwndClient, WC_BUTTON, "\33", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL5, ROW5, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_BS, NULL, NULL);
     hwndsst = WinCreateWindow(hwndClient, WC_BUTTON, "Cls", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL5, ROW6, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_SST, NULL, NULL);
     hwndtan = WinCreateWindow(hwndClient, WC_BUTTON, "~Tan", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL5, ROW7, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_TAN, NULL, NULL);
     hwndln = WinCreateWindow(hwndClient, WC_BUTTON, "L~N", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL5, ROW8, FUNCWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_LN, NULL, NULL);

     hwndDisplay = WinCreateWindow(hwndClient, WC_ENTRYFIELD, " 0.0000    00", WS_VISIBLE | ES_MARGIN | ES_READONLY | ES_LEFT, COL1, ROWDISPLAY, DISPLAYWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DISPLAY, NULL, NULL);
     hwndDispY = WinCreateWindow(hwndClient, WC_ENTRYFIELD, " 0.0000    00", ES_MARGIN | ES_READONLY | ES_LEFT, COL1, ROWDISPLAY+KEYHEIGHT*4/3, DISPLAYWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DISPY, NULL, NULL);
     hwndDispZ = WinCreateWindow(hwndClient, WC_ENTRYFIELD, " 0.0000    00", ES_MARGIN | ES_READONLY | ES_LEFT, COL1, ROWDISPLAY+KEYHEIGHT*8/3, DISPLAYWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DISPZ, NULL, NULL);
     hwndDispT = WinCreateWindow(hwndClient, WC_ENTRYFIELD, " 0.0000    00", ES_MARGIN | ES_READONLY | ES_LEFT, COL1, ROWDISPLAY+KEYHEIGHT*12/3, DISPLAYWIDTH, KEYHEIGHT, hwndClient, HWND_TOP, K_DISPT, NULL, NULL);
     hwndAmode = WinCreateWindow(hwndClient, WC_BUTTON, "RAD", WS_VISIBLE | BS_PUSHBUTTON | BS_NOPOINTERFOCUS, COL2, ROW9+ROWSEP/2, FUNCWIDTH+FUNCSEP, KEYHEIGHT-2, hwndClient, HWND_TOP, K_AMODE, NULL, NULL);
     hwndSmode = WinCreateWindow(hwndClient, WC_STATIC, "", WS_VISIBLE | SS_TEXT | DT_VCENTER | DT_CENTER, NUMCOL2, ROW9+ROWSEP/2, FUNCWIDTH+FUNCSEP, KEYHEIGHT-2, hwndClient, HWND_BOTTOM, K_SMODE, NULL, NULL);
/*     hwndtest = WinCreateWindow(hwndClient, WC_BUTTON, "#1", WS_VISIBLE | BS_ICON | BS_PUSHBUTTON | BS_AUTOSIZE, COL1, ROW8, 0, 0, hwndClient, HWND_BOTTOM, K_XEQ, NULL, NULL); */

     lRGB=CLR_YELLOW;
     WinSetPresParam(hwndgol, PP_BACKGROUNDCOLORINDEX, (ULONG)sizeof(LONG), (PVOID)&lRGB);
     lRGB=CLR_WHITE;
     WinSetPresParam(hwndAmode, PP_BACKGROUNDCOLORINDEX, (ULONG)sizeof(LONG), (PVOID)&lRGB);
/*     lRGB=CLR_PALEGRAY;
     WinSetPresParam(hwndClient, PP_BACKGROUNDCOLORINDEX, (ULONG)sizeof(LONG), (PVOID)&lRGB);
*/
     SwitchFonts(SIZE_NORM);
}


void SwitchSizes(BOOL fMode)
{
   WinSetWindowPos(hwnd0, HWND_TOP, NUMCOL1, ROW1, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd1, HWND_TOP, NUMCOL1, ROW2, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd4, HWND_TOP, NUMCOL1, ROW3, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd7, HWND_TOP, NUMCOL1, ROW4, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwnddot, HWND_TOP, NUMCOL2, ROW1, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd2, HWND_TOP, NUMCOL2, ROW2, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd5, HWND_TOP, NUMCOL2, ROW3, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd8, HWND_TOP, NUMCOL2, ROW4, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwnd3, HWND_TOP, NUMCOL3, ROW2, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd6, HWND_TOP, NUMCOL3, ROW3, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd9, HWND_TOP, NUMCOL3, ROW4, NUMWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndmin, HWND_TOP, COL1, ROW4, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndplu, HWND_TOP, COL1, ROW3, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndmul, HWND_TOP, COL1, ROW2, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnddiv, HWND_TOP, COL1, ROW1, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndent, HWND_TOP, COL1, ROW5, ENTWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndgol, HWND_TOP, COL1, ROW6, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndxy, HWND_TOP, COL1, ROW7, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndsig, HWND_TOP, COL1, ROW8, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndxeq, HWND_TOP, COL2, ROW6, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndrd, HWND_TOP, COL2, ROW7, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwnd1x, HWND_TOP, COL2, ROW8, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndchs, HWND_TOP, COL3, ROW5, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndsto, HWND_TOP, COL3, ROW6, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndsin, HWND_TOP, COL3, ROW7, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndroo, HWND_TOP, COL3, ROW8, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndeex, HWND_TOP, COL4, ROW5, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndrcl, HWND_TOP, COL4, ROW6, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndcos, HWND_TOP, COL4, ROW7, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndlog, HWND_TOP, COL4, ROW8, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndbs, HWND_TOP, COL5, ROW5, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndsst, HWND_TOP, COL5, ROW6, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndtan, HWND_TOP, COL5, ROW7, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndln, HWND_TOP, COL5, ROW8, FUNCWIDTH, KEYHEIGHT, SWP_MOVE | SWP_SIZE);

   WinSetWindowPos(hwndDisplay, HWND_TOP, COL1, ROWDISPLAY, DISPLAYWIDTH-FUNCWIDTH/2, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndDispY, HWND_TOP, COL1, ROWDISPLAY+KEYHEIGHT*4/3, DISPLAYWIDTH-FUNCWIDTH/2, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndDispZ, HWND_TOP, COL1, ROWDISPLAY+KEYHEIGHT*8/3, DISPLAYWIDTH-FUNCWIDTH/2, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndDispT, HWND_TOP, COL1, ROWDISPLAY+KEYHEIGHT*12/3, DISPLAYWIDTH-FUNCWIDTH/2, KEYHEIGHT, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndAmode, HWND_TOP, COL2, ROW9+ROWSEP/2, FUNCWIDTH+FUNCSEP, KEYHEIGHT-2, SWP_MOVE | SWP_SIZE);
   WinSetWindowPos(hwndSmode, HWND_TOP, NUMCOL2, ROW9+ROWSEP/2, FUNCWIDTH+FUNCSEP, KEYHEIGHT-2, SWP_MOVE | SWP_SIZE);

   ShowXYZT(fMode);
}


void DrawShiftText(HPS hps)
{
   RECTL        rcl;

#define CORRECTION      2

 if (!fHexOct) {
   rcl.xLeft = NUMCOL1; rcl.yBottom = ROW1 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL1 + NUMWIDTH; rcl.yTop = ROW2;
   WinDrawText(hps, -1, "\343", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
 } /* endif */
   rcl.xLeft = NUMCOL2; rcl.yBottom = ROW1 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL2 + NUMWIDTH; rcl.yTop = ROW2;
   WinDrawText(hps, -1, "lstX", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

 if (!fHexOct) {
   rcl.xLeft = NUMCOL1; rcl.yBottom = ROW2 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL1 + NUMWIDTH; rcl.yTop = ROW3;
   WinDrawText(hps, -1, "Fix", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL2; rcl.yBottom = ROW2 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL2 + NUMWIDTH; rcl.yTop = ROW3;
   WinDrawText(hps, -1, "Sci", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL3; rcl.yBottom = ROW2 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL3 + NUMWIDTH; rcl.yTop = ROW3;
   WinDrawText(hps, -1, "Eng", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = NUMCOL1; rcl.yBottom = ROW3 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL1 + NUMWIDTH; rcl.yTop = ROW4;
   WinDrawText(hps, -1, "\344y\375", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL2; rcl.yBottom = ROW3 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL2 + NUMWIDTH; rcl.yTop = ROW4;
   WinDrawText(hps, -1, "P\032R", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL3; rcl.yBottom = ROW3 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL3 + NUMWIDTH; rcl.yTop = ROW4;
   WinDrawText(hps, -1, "R\032P", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = NUMCOL1; rcl.yBottom = ROW4 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL1 + NUMWIDTH; rcl.yTop = ROW5;
   WinDrawText(hps, -1, "\344x\375", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL2; rcl.yBottom = ROW4 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL2 + NUMWIDTH; rcl.yTop = ROW5;
   WinDrawText(hps, -1, "Mean", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = NUMCOL3; rcl.yBottom = ROW4 + KEYHEIGHT - CORRECTION;
   rcl.xRight = NUMCOL3 + NUMWIDTH; rcl.yTop = ROW5;
   WinDrawText(hps, -1, "SDev", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = COL1; rcl.yBottom = ROW4 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = ROW5;
   WinDrawText(hps, -1, "\344x", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL1; rcl.yBottom = ROW3 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = ROW4;
   WinDrawText(hps, -1, "\344y", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL1; rcl.yBottom = ROW2 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = ROW3;
   WinDrawText(hps, -1, "\344xy", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL1; rcl.yBottom = ROW1 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = ROW2;
   WinDrawText(hps, -1, "n", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = COL3; rcl.yBottom = ROW5 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL3 + NUMWIDTH; rcl.yTop = ROW6;
   WinDrawText(hps, -1, "Mod", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL4; rcl.yBottom = ROW5 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL4 + NUMWIDTH; rcl.yTop = ROW6;
   WinDrawText(hps, -1, "FEx", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
 } /* endif */

   rcl.xLeft = COL5; rcl.yBottom = ROW5 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL5 + NUMWIDTH; rcl.yTop = ROW6;
   WinDrawText(hps, -1, "CLx", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

 if (!fHexOct) {
/*
   rcl.xLeft = COL2; rcl.yBottom = ROW6 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL2 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "Asn", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
*/
   rcl.xLeft = COL3; rcl.yBottom = ROW6 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL3 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "\032Hr", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL4; rcl.yBottom = ROW6 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL4 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "Hms", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = COL5; rcl.yBottom = ROW6 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL5 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "n!", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = COL1; rcl.yBottom = ROW7 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "CL\344", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL2; rcl.yBottom = ROW7 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL2 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "%", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL3 - CORRECTION; rcl.yBottom = ROW7 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL3 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "aSin", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL4 - CORRECTION; rcl.yBottom = ROW7 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL4 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "aCos", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL5 - CORRECTION; rcl.yBottom = ROW7 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL5 + NUMWIDTH; rcl.yTop = ROW8;
   WinDrawText(hps, -1, "aTan", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );

   rcl.xLeft = COL1; rcl.yBottom = ROW8 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL1 + NUMWIDTH; rcl.yTop = rcl.yBottom + FUNCWIDTH;
   WinDrawText(hps, -1, "\344-", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL2; rcl.yBottom = ROW8 + KEYHEIGHT;
   rcl.xRight = COL2 + NUMWIDTH; rcl.yTop = rcl.yBottom + FUNCWIDTH;
   WinDrawText(hps, -1, "y^x", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL3; rcl.yBottom = ROW8 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL3 + NUMWIDTH; rcl.yTop = rcl.yBottom + FUNCWIDTH;
   WinDrawText(hps, -1, "x\375", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL4; rcl.yBottom = ROW8 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL4 + NUMWIDTH; rcl.yTop = rcl.yBottom + FUNCWIDTH;
   WinDrawText(hps, -1, "10^x", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
   rcl.xLeft = COL5; rcl.yBottom = ROW8 + KEYHEIGHT - CORRECTION;
   rcl.xRight = COL5 + NUMWIDTH; rcl.yTop = rcl.yBottom + FUNCWIDTH;
   WinDrawText(hps, -1, "e^x", &rcl, 0, 0,
                DT_TEXTATTRS | DT_CENTER | DT_BOTTOM );
 } /* endif */
   rcl.xLeft = COL5 + FUNCWIDTH*2/3; rcl.yBottom = ROWDISPLAY;
   rcl.xRight = rcl.xLeft + FUNCWIDTH; rcl.yTop = rcl.yBottom + KEYHEIGHT;
   WinDrawText(hps, -1, ":X", &rcl, 0, 0,
                DT_TEXTATTRS | DT_LEFT | DT_VCENTER );
   rcl.xLeft = COL5 + FUNCWIDTH*2/3; rcl.yBottom = ROWDISPLAY+KEYHEIGHT*4/3;
   rcl.xRight = rcl.xLeft + FUNCWIDTH; rcl.yTop = rcl.yBottom + KEYHEIGHT;
   WinDrawText(hps, -1, ":Y", &rcl, 0, 0,
                DT_TEXTATTRS | DT_LEFT | DT_VCENTER );
   rcl.xLeft = COL5 + FUNCWIDTH*2/3; rcl.yBottom = ROWDISPLAY+KEYHEIGHT*8/3;
   rcl.xRight = rcl.xLeft + FUNCWIDTH; rcl.yTop = rcl.yBottom + KEYHEIGHT;
   WinDrawText(hps, -1, ":Z", &rcl, 0, 0,
                DT_TEXTATTRS | DT_LEFT | DT_VCENTER );
   rcl.xLeft = COL5 + FUNCWIDTH*2/3; rcl.yBottom = ROWDISPLAY+KEYHEIGHT*12/3;
   rcl.xRight = rcl.xLeft + FUNCWIDTH; rcl.yTop = rcl.yBottom + KEYHEIGHT;
   WinDrawText(hps, -1, ":T", &rcl, 0, 0,
                DT_TEXTATTRS | DT_LEFT | DT_VCENTER );
}


void ShowXYZT(BOOL fXyzt)
{
   SWP  swp;
   int  mv=0;

   WinQueryWindowPos(hwndFrame, &swp);
       if (!fXyzt) {
          if (swp.cy!=0) { /* occurs at startup */
             mv = swp.cy-(ROWDISPLAY + ROWSTEP*9/4);
          } /* endif */
          WinSetWindowPos(hwndFrame, HWND_TOP, swp.x,
                swp.y + mv,
                (DISPLAYWIDTH+3*COL1),
                (ROWDISPLAY + ROWSTEP*9/4),
                SWP_SIZE | SWP_MOVE);
       } else {
          if (swp.cy!=0) { /* occurs at startup */
             mv = swp.cy-(ROWDISPLAY + ROWSTEP*9/4 + KEYHEIGHT*12/3);
          } /* endif */
          WinSetWindowPos(hwndFrame, HWND_TOP, swp.x,
                swp.y + mv,
                (DISPLAYWIDTH+3*COL1),
                (ROWDISPLAY + ROWSTEP*9/4 + KEYHEIGHT*12/3),
                SWP_SIZE | SWP_MOVE);
       }
}


void ShowKeyboard(BOOL fHexOct, USHORT uBinMode)
{
   if (fHexOct) {
      WinSetWindowText(hwndsig, "A");
      WinSetWindowText(hwnd1x, "B");
      WinSetWindowText(hwndroo, "C");
      WinSetWindowText(hwndlog, "D");
      WinSetWindowText(hwndln, "E");
      WinSetWindowText(hwndsin, "And");
      WinSetWindowText(hwndcos, "Or");
      WinSetWindowText(hwndtan, "F");
      WinSetWindowText(hwndeex, "Xor");
      WinSetWindowText(hwnddot, "ONEs");
      WinSetWindowText(hwndsst, ">");
      WinShowWindow(hwndxeq, TRUE);
      ShowHexOct(uBinMode);
   } else {
      WinSetWindowText(hwndsig, "\344+");
      WinSetWindowText(hwnd1x, "1/x");
      WinSetWindowText(hwndroo, "\373x");
      WinSetWindowText(hwndlog, "Lo~g");
      WinSetWindowText(hwndln, "L~N");
      WinSetWindowText(hwndsin, "~Sin");
      WinSetWindowText(hwndcos, "~Cos");
      WinSetWindowText(hwndtan, "~Tan");
      WinSetWindowText(hwndeex, "~EEx");
      WinSetWindowText(hwnddot, "\371");
      WinSetWindowText(hwndsst, "Cls");
      WinShowWindow(hwndxeq, FALSE);
      ShowHexOct(MODE_HEX);
   } /* endif */
}


void ShowHexOct(USHORT uBinMode)
{
   switch (uBinMode) {
   case MODE_DEC:
      WinEnableWindow(hwnd8, TRUE);
      WinEnableWindow(hwnd9, TRUE);
      WinEnableWindow(hwndsig, FALSE);
      WinEnableWindow(hwnd1x, FALSE);
      WinEnableWindow(hwndroo, FALSE);
      WinEnableWindow(hwndlog, FALSE);
      WinEnableWindow(hwndln, FALSE);
      WinEnableWindow(hwndtan, FALSE);
      break;
   case MODE_HEX:
      WinEnableWindow(hwnd8, TRUE);
      WinEnableWindow(hwnd9, TRUE);
      WinEnableWindow(hwndsig, TRUE);
      WinEnableWindow(hwnd1x, TRUE);
      WinEnableWindow(hwndroo, TRUE);
      WinEnableWindow(hwndlog, TRUE);
      WinEnableWindow(hwndln, TRUE);
      WinEnableWindow(hwndtan, TRUE);
      break;
   case MODE_OCT:
      WinEnableWindow(hwnd8, FALSE);
      WinEnableWindow(hwnd9, FALSE);
      WinEnableWindow(hwndsig, FALSE);
      WinEnableWindow(hwnd1x, FALSE);
      WinEnableWindow(hwndroo, FALSE);
      WinEnableWindow(hwndlog, FALSE);
      WinEnableWindow(hwndln, FALSE);
      WinEnableWindow(hwndtan, FALSE);
      break;
   default:
     break;
   } /* endswitch */
}

