/* ini file maniplulation routines 
   Part of HPcalc
*/

/* Definitions */
#define INCL_PM

/* Includes */
#include <stdio.h>
#include <os2.h>
#include <string.h>
#include "HPcalc.h"
#include "interface.h"
#include "interface-vars.h"
#include "ini.h"
#include "change.h"

/* Local Global Variables */
PSZ     szSection="HPcalc",
        szVersion="Version",
        szPosition="Position",
        szWinSize="MainWindowSize",
        szXyzt="XYZTmode",
        szAngle="AngleMode",
        szDisp="DisplayMode",
        szDispDigs="Digits",
        szStack="Stack",
        szLastx="Lastx",
        szMemory="Memory",
        szBGcolor="BackgroundColor",
        szFGcolor="Foregroundcolor",
        szSummation="Summation",
        szHexMode="HexDecOct",
        szFlagHex="FlagHex",
        szFlagComma="FlagComma",
        szLDispFont="LargeDispFont",
        szSDispFont="SmallDispFont",
        szLDigitFont="LargeDigitFont",
        szSDigitFont="SmallDigitFont",
        szLBSFont="LargeBSFont",
        szSBSFont="SmallBSFont",
        szLFuncFont="LargeFuncFont",
        szSFuncFont="SmallFuncFont",
        szLMenuFont="LargeMenuFont",
        szSMenuFont="SmallMenuFont",
        szDispBG="DispBGColor",
        szDispFG="DispFGColor",
        szButFG="ButtonFGColor",
        szButBG="ButtonBGColor",
        szDialogBG="DialogBGColor",
        szShiftFG="iShiftFGColor",
        szDispBGi="iDispBGColor",
        szDispFGi="iDispFGColor",
        szButFGi="iButtonFGColor",
        szButBGi="iButtonBGColor",
        szDialogBGi="iDialogBGColor",
        szShiftFGi="iShiftFGColor";


void ReadIniFile(HINI hini, PBOOL pfReadSize, PUSHORT pusWinSize, PBOOL pfX,
                PSWP pswp)
{
   ULONG        cb;
   SWP          swp;

   /* get desktop size, used to determine defaultswhen there is no ini file */
   WinQueryWindowPos(HWND_DESKTOP, &swp);

   PrfQueryProfileSize(hini, szSection, szPosition, &cb);
   if (cb == sizeof(SWP)) {
      PrfQueryProfileData(hini, szSection, szPosition, pswp, &cb);
      *pfReadSize = TRUE;
   } else {
      *pfReadSize = FALSE;
      if (swp.cy <=480) {
           pswp->x = 10; pswp->y = 10;
      } else {
           pswp->x = swp.cx / 9; pswp->y = swp.cy / 9;
      } /* endif */
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szWinSize, &cb);
   if (cb == sizeof(BOOL)) {
      PrfQueryProfileData(hini, szSection, szWinSize, &fVgaSize, &cb);
   } else {
      if (swp.cy <=480) {
           fVgaSize = TRUE;
      } else {
           fVgaSize = FALSE;
      } /* endif */
   } /* endif */
   if (fVgaSize) {
      *pusWinSize = SIZE_SMALL;
   } else {
      *pusWinSize = SIZE_NORM;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szXyzt, &cb);
   if (cb == sizeof(BOOL)) {
      PrfQueryProfileData(hini, szSection, szXyzt, pfX, &cb);
   } else {
      *pfX = FALSE;
   } /* endif */
   fXyzt = *pfX;

   PrfQueryProfileSize(hini, szSection, szAngle, &cb);
   if (cb == sizeof(USHORT)) {
      PrfQueryProfileData(hini, szSection, szAngle, &uAngleMode, &cb);
   } else {
      uAngleMode = MODE_DEG;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDisp, &cb);
   if (cb == sizeof(USHORT)) {
      PrfQueryProfileData(hini, szSection, szDisp, &uNumMode, &cb);
   } else {
      uNumMode = MODE_ENG;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDispDigs, &cb);
   if (cb == sizeof(USHORT)) {
      PrfQueryProfileData(hini, szSection, szDispDigs, &uDispDigs, &cb);
   } else {
      uDispDigs = 4;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szStack, &cb);
   if (cb == (sizeof(double)*4)) {
      PrfQueryProfileData(hini, szSection, szStack, stack, &cb);
   } else {
      stack[0] = 0.0; stack[1] = 0.0; stack[2] = 0.0; stack[3] = 0.0;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLastx, &cb);
   if (cb == sizeof(double)) {
      PrfQueryProfileData(hini, szSection, szLastx, &lastx, &cb);
   } else {
      lastx = 0.0;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szMemory, &cb);
   if (cb == (sizeof(double)*10)) {
      PrfQueryProfileData(hini, szSection, szMemory, memory, &cb);
   } else {
      int       i;
      for (i=0; i<10; i++) {
         memory[i] = 0.0;
      } /* endfor */
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSummation, &cb);
   if (cb == (sizeof(double)*6)) {
      PrfQueryProfileData(hini, szSection, szSummation, summation, &cb);
   } else {
      int       i;
      for (i=0; i<6; i++) {
         summation[i] = 0;
      } /* endfor */
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szHexMode, &cb);
   if (cb == sizeof(USHORT)) {
      PrfQueryProfileData(hini, szSection, szHexMode, &uBinMode, &cb);
   } else {
      uBinMode = MODE_DEC;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szFlagHex, &cb);
   if (cb == sizeof(BOOL)) {
      PrfQueryProfileData(hini, szSection, szFlagHex, &fHexOct, &cb);
   } else {
      fHexOct = FALSE;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szFlagComma, &cb);
   if (cb == sizeof(BOOL)) {
      PrfQueryProfileData(hini, szSection, szFlagComma, &fComma, &cb);
   } else {
      fComma = FALSE;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLDispFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szLDispFont, szLargeDispFont, &cb);
   } else {
      strcpy(szLargeDispFont, "12.Courier");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSDispFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szSDispFont, szSmallDispFont, &cb);
   } else {
      strcpy(szSmallDispFont, "10.Courier");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLDigitFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szLDigitFont, szLargeDigitFont, &cb);
   } else {
      strcpy(szLargeDigitFont, "10.System Monospaced");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSDigitFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szSDigitFont, szSmallDigitFont, &cb);
   } else {
      strcpy(szSmallDigitFont, "8.Helv");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLBSFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szLBSFont, szLargeBSFont, &cb);
   } else {
      strcpy(szLargeBSFont, "12.Courier");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSBSFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szSBSFont, szSmallBSFont, &cb);
   } else {
      strcpy(szSmallBSFont, "10.Courier");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLFuncFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szLFuncFont, szLargeFuncFont, &cb);
   } else {
      strcpy(szLargeFuncFont, "10.System Monospaced");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSFuncFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szSFuncFont, szSmallFuncFont, &cb);
   } else {
      strcpy(szSmallFuncFont, "8.Helv");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szLMenuFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szLMenuFont, szLargeMenuFont, &cb);
   } else {
      strcpy(szLargeMenuFont, "");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szSMenuFont, &cb);
   if (cb == (sizeof(UCHAR)*MAX_FONT)) {
      PrfQueryProfileData(hini, szSection, szSMenuFont, szSmallMenuFont, &cb);
   } else {
      strcpy(szSmallMenuFont, "");
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDispBG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szDispBG, &lDispBG, &cb);
   } else {
      lDispBG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDispFG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szDispFG, &lDispFG, &cb);
   } else {
      lDispFG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szButBG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szButBG, &lButBG, &cb);
   } else {
      lButBG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szButFG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szButFG, &lButFG, &cb);
   } else {
      lButFG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDialogBG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szDialogBG, &lDialogBG, &cb);
   } else {
      lDialogBG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szShiftFG, &cb);
   if (cb == (sizeof(LONG))) {
      PrfQueryProfileData(hini, szSection, szShiftFG, &lShiftFG, &cb);
   } else {
      lShiftFG = CLR_DEFAULT;
   } /* endif */

   PrfQueryProfileSize(hini, szSection, szDispFGi, &cb);
   if (cb == (sizeof(int))) 
      PrfQueryProfileData(hini, szSection, szDispFGi, &fDispFG, &cb);
   else fDispFG = TRUE;

   PrfQueryProfileSize(hini, szSection, szDispBGi, &cb);
   if (cb == (sizeof(int)))
      PrfQueryProfileData(hini, szSection, szDispBGi, &fDispBG, &cb);
   else fDispBG = TRUE;

   PrfQueryProfileSize(hini, szSection, szButFGi, &cb);
   if (cb == (sizeof(int)))
      PrfQueryProfileData(hini, szSection, szButFGi, &fButFG, &cb);
   else fButFG = TRUE;

   PrfQueryProfileSize(hini, szSection, szButBGi, &cb);
   if (cb == (sizeof(int)))
      PrfQueryProfileData(hini, szSection, szButBGi, &fButBG, &cb);
   else fButBG = TRUE;

   PrfQueryProfileSize(hini, szSection, szShiftFGi, &cb);
   if (cb == (sizeof(int)))
      PrfQueryProfileData(hini, szSection, szShiftFGi, &fShiftFG, &cb);
   else fShiftFG = TRUE;

   PrfQueryProfileSize(hini, szSection, szDialogBGi, &cb);
   if (cb == (sizeof(int)))
      PrfQueryProfileData(hini, szSection, szDialogBGi, &fDialogBG, &cb);
   else fDialogBG = TRUE;
}


void WriteIni(HINI hini)
{
   SWP          swp;
   double       version=0.94;

   ReadUpdatedPresParam();
 
   PrfWriteProfileData(hini, szSection, szVersion, &version, sizeof(double));
   PrfWriteProfileData(hini, szSection, szWinSize, &fVgaSize, sizeof(BOOL));
   PrfWriteProfileData(hini, szSection, szXyzt, &fXyzt, sizeof(BOOL));
   PrfWriteProfileData(hini, szSection, szAngle, &uAngleMode, sizeof(USHORT));
   PrfWriteProfileData(hini, szSection, szDisp, &uNumMode, sizeof(USHORT));
   PrfWriteProfileData(hini, szSection, szDispDigs, &uDispDigs, sizeof(USHORT));
   PrfWriteProfileData(hini, szSection, szStack, stack, (sizeof(double)*4));
   PrfWriteProfileData(hini, szSection, szLastx, &lastx, sizeof(double));
   PrfWriteProfileData(hini, szSection, szMemory, memory, (sizeof(double)*10));
   PrfWriteProfileData(hini, szSection, szSummation, summation, (sizeof(double)*6));
   PrfWriteProfileData(hini, szSection, szHexMode, &uBinMode, sizeof(USHORT));
   PrfWriteProfileData(hini, szSection, szFlagHex, &fHexOct, sizeof(BOOL));
   PrfWriteProfileData(hini, szSection, szFlagComma, &fComma, sizeof(BOOL));

   PrfWriteProfileData(hini, szSection, szDispBG, &lDispBG, sizeof(LONG));
   PrfWriteProfileData(hini, szSection, szDispFG, &lDispFG, sizeof(LONG));
   PrfWriteProfileData(hini, szSection, szButBG, &lButBG, sizeof(LONG));
   PrfWriteProfileData(hini, szSection, szButFG, &lButFG, sizeof(LONG));
   PrfWriteProfileData(hini, szSection, szDialogBG, &lDialogBG, sizeof(LONG));
   PrfWriteProfileData(hini, szSection, szShiftFG, &lShiftFG, sizeof(LONG));

   PrfWriteProfileData(hini, szSection, szDispBGi, &fDispBG, sizeof(int));
   PrfWriteProfileData(hini, szSection, szDispFGi, &fDispFG, sizeof(int));
   PrfWriteProfileData(hini, szSection, szButBGi, &fButBG, sizeof(int));
   PrfWriteProfileData(hini, szSection, szButFGi, &fButFG, sizeof(int));
   PrfWriteProfileData(hini, szSection, szDialogBGi, &fDialogBG, sizeof(int));
   PrfWriteProfileData(hini, szSection, szShiftFGi, &fShiftFG, sizeof(int));

   PrfWriteProfileData(hini, szSection, szLDispFont, szLargeDispFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szLDigitFont, szLargeDigitFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szLBSFont, szLargeBSFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szLFuncFont, szLargeFuncFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szLMenuFont, szLargeMenuFont, (sizeof(UCHAR)*MAX_FONT));
 
   PrfWriteProfileData(hini, szSection, szSDispFont, szSmallDispFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szSDigitFont, szSmallDigitFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szSBSFont, szSmallBSFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szSFuncFont, szSmallFuncFont, (sizeof(UCHAR)*MAX_FONT));
   PrfWriteProfileData(hini, szSection, szSMenuFont, szSmallMenuFont, (sizeof(UCHAR)*MAX_FONT));

   WinQueryWindowPos(hwndFrame, &swp);
   PrfWriteProfileData(hini, szSection, szPosition, &swp, sizeof(SWP));

}

void ReadUpdatedPresParam(void)
{
   ULONG        cb;
   HWND         hwndbs, hwnd0, hwndgol, hwndMenu;
/*   FILE         *fp;

   fp = fopen("junk", "w");
*/
   hwndbs = WinWindowFromID(hwndClient, K_BS);
   hwnd0 = WinWindowFromID(hwndClient, K_0);
   hwndgol = WinWindowFromID(hwndClient, K_GOL);
   hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);

   if(fVgaSize) {
      cb = WinQueryPresParam(hwndDisplay, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szSmallDispFont, 0);
      cb = WinQueryPresParam(hwndClient, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szSmallFuncFont, 0);
      cb = WinQueryPresParam(hwnd0, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szSmallDigitFont, 0);
      cb = WinQueryPresParam(hwndbs, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szSmallBSFont, 0);
      cb = WinQueryPresParam(hwndMenu, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szSmallMenuFont, 0);
   } else {
      cb = WinQueryPresParam(hwndDisplay, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szLargeDispFont, 0);
      cb = WinQueryPresParam(hwndClient, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szLargeFuncFont, 0);
      cb = WinQueryPresParam(hwnd0, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szLargeDigitFont, 0);
      cb = WinQueryPresParam(hwndbs, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szLargeBSFont, 0);
      cb = WinQueryPresParam(hwndMenu, PP_FONTNAMESIZE, 0, NULL, sizeof(UCHAR)*MAX_FONT, szLargeMenuFont, 0);
   }

   cb = WinQueryPresParam(hwndDisplay, PP_BACKGROUNDCOLORINDEX, 0, NULL, (ULONG)sizeof(LONG), (PVOID)&lDispBG, 0);
/*   fprintf(fp, "%x fdisp = %d %x\n", hwndDisplay, cb, lDispBG); */
   cb = WinQueryPresParam(hwndDisplay, PP_BACKGROUNDCOLOR, 0, NULL, (ULONG)sizeof(LONG), (PVOID)&lDispBG, 0);
/*   fprintf(fp, "cb = %d\n", cb);*/

   fDispFG = WinQueryPresParam(hwndDisplay, PP_FOREGROUNDCOLORINDEX, 0, NULL, sizeof(LONG), &lDispFG, 0);
   if (!fDispFG) cb = WinQueryPresParam(hwndDisplay, PP_FOREGROUNDCOLOR, 0, NULL, sizeof(LONG), &lDispFG, 0);

   fButBG = WinQueryPresParam(hwnd0, PP_BACKGROUNDCOLORINDEX, 0, NULL, sizeof(LONG), &lButBG, 0);
   if (!fButBG) cb = WinQueryPresParam(hwnd0, PP_BACKGROUNDCOLOR, 0, NULL, sizeof(LONG), &lButBG, 0);

   fButFG = WinQueryPresParam(hwnd0, PP_FOREGROUNDCOLORINDEX, 0, NULL, sizeof(LONG), &lButFG, 0);
   if (!fButFG) cb = WinQueryPresParam(hwnd0, PP_FOREGROUNDCOLOR, 0, NULL, sizeof(LONG), &lButFG, 0);

   fShiftFG = WinQueryPresParam(hwndgol, PP_BACKGROUNDCOLORINDEX, 0, NULL, sizeof(LONG), &lShiftFG, 0);
   if (!fShiftFG) cb = WinQueryPresParam(hwndgol, PP_BACKGROUNDCOLOR, 0, NULL, sizeof(LONG), &lShiftFG, 0);
/*
   fprintf(fp, "disp BG %x %x\n", fDispBG, lDispBG);
   fprintf(fp, "Dialog BG %x %x\n", fDialogBG, lDialogBG);
   fprintf(fp, "shift %x %x\n", fShiftFG, lShiftFG);
   fclose(fp);
*/
}

