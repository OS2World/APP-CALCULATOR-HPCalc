/* HP Calculator */

/* Definitions */
#define INCL_PM
#define INCL_DOS
#define INCL_WINHELP

#define MYAPPCLASS           "HPcalc"

 
/* Includes */
#include <stdio.h>
#include <string.h>
#include <io.h>  /*used by emx instead of unistd.h */
/* #include <unistd.h> */
#include <os2.h>
#include "HPcalc.h"
#include "interface.h"
#include "ini.h"
#include "change.h"

/* Local Prototypes */
MRESULT EXPENTRY ClientWinProc (HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY SubclassFrame (HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY HexOctWinProc (HWND, ULONG, MPARAM, MPARAM);
void GetIniFilename(int argc, char *argv[], PSZ buf);
void GetFullPathToExe(PSZ buf);
BOOL ConvertExeToIni(PSZ buf);
 
/* Local Global Variables */
PFNWP   pfnFrame;
HINI       hini;
PSZ        szIniFile="HPcalc.ini";

/* main function */
 
void main (int argc, char *argv[], char *envp[])
{
     HWND         hwndMenu;
     HMQ     hmq;
     QMSG    qmsg;
     SWP     swp, swpm;
     ULONG   flCreate;
     FRAMECDATA  fcdata;
     USHORT     usWinSize=SIZE_NORM;
     BOOL       fIniRead=FALSE, fXyztMode=FALSE;
     CHAR       buf[256];
     APIRET     rc;

     SetPositions(SIZE_NORM);

     if ( !(hab = WinInitialize (0)) )
         return;
     
     GetIniFilename(argc, argv, buf);

     if ((hini = PrfOpenProfile(hab, buf))) {
        ReadIniFile(hini, &fIniRead, &usWinSize, &fXyztMode, &swp);
     }

 
     hmq = WinCreateMsgQueue (hab, 0);
     WinRegisterClass(
         hab,
         MYAPPCLASS,
         (PFNWP) ClientWinProc,
         CS_SIZEREDRAW,
         0);

     flCreate =  FCF_TITLEBAR | FCF_DLGBORDER  | FCF_MINBUTTON |
                FCF_SYSMENU     | FCF_TASKLIST  | FCF_MENU      |
                FCF_ACCELTABLE  | FCF_ICON ;

     fcdata.cb = sizeof(FRAMECDATA);
     fcdata.flCreateFlags = flCreate;
     fcdata.hmodResources = (HMODULE) NULL;
     fcdata.idResources = ID_HPCALC;

     hwndFrame = WinCreateWindow(HWND_DESKTOP, WC_FRAME, "HPcalc 41C",
                        0, 0, 0, 0,
                        0, (int)NULL, HWND_TOP,
                        ID_HPCALC, &fcdata, NULL);
     if (hwndFrame == NULL) {
        exit(-1);
     } /* endif */

     WinSetWindowPos(hwndFrame, HWND_TOP, swp.x,
                swp.y, 0, 0, SWP_MOVE);

     hwndClient = WinCreateWindow(hwndFrame, MYAPPCLASS, NULL,
                        WS_VISIBLE, 0, 0, 0,
                        0, hwndFrame, HWND_BOTTOM,
                        FID_CLIENT, NULL, NULL);

     hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);
     WinQueryWindowPos(hwndMenu, &swpm);

     WinSetWindowPos(hwndClient, HWND_BOTTOM, swpm.x,
                swpm.x, swpm.cx,
                swpm.y-swpm.x,
                SWP_MOVE | SWP_SIZE);

     CreateButtons(hwndClient);
     ChangeSize(usWinSize, fXyztMode);

/*
     hwndHexOct = WinLoadDlg(HWND_DESKTOP, hwndFrame, HexOctWinProc, (HMODULE) 0, ID_HEX_OCT, NULL);
     WinQueryWindowPos(hwndFrame, &swp);
     WinSetWindowPos(hwndHexOct, NULL, swp.x + swp.cx + 1, swp.y, 0, 0, SWP_MOVE);
*/

     WinShowWindow(hwndFrame, TRUE);

     while (WinGetMsg (hab,&qmsg,(HWND)NULL,0,0))
         WinDispatchMsg (hab,&qmsg);
 
     WinDestroyWindow(hwndFrame);
     WinDestroyMsgQueue(hmq);
     WinTerminate(hab);
}

 
/* our window procedure */
MRESULT EXPENTRY ClientWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   RECTL        rcl;
   HPS          hps;
   static       BOOL   start=TRUE;

   switch (msg) {
   case WM_CREATE:
/* printf("ClientWinProc WM_CREATE\n"); */
       InitializeDisplay();
       break;
   case WM_PAINT:
/* printf("ClientWinProc WM_PAINT\n"); */
       hps = WinBeginPaint(hwnd, (HPS) NULL, &rcl);
       WinFillRect(hps, &rcl, CLR_NEUTRAL);
       GpiSetColor(hps, CLR_YELLOW);
       DrawShiftText(hps);
       WinEndPaint(hps);
       if (start) {
          WinSetFocus(HWND_DESKTOP, hwndClient);
          start = FALSE;
       } /* endif */
       InitializeDisplay();

       return 0;
       break;
    case WM_CLOSE:
       WriteIni(hini);
       PrfCloseProfile(hini);
       /* don't return allow default stuff to work */
       WinPostMsg(hwnd,WM_QUIT,0L,0L);
       return (MRESULT) 0;
       break;

    case WM_CHAR:
       return ProcessKeyboardChar(hwnd, msg, mp1, mp2);
       break;

    case WM_COMMAND:
       return ProcessCommand(hwnd, msg, mp1, mp2);
       break;
    case WM_PRESPARAMCHANGED:
       WinInvalidateRect(hwnd, NULL, TRUE);
       return 0;
       break;

       break;

    default:
        return WinDefWindowProc (hwnd, msg, mp1, mp2);
    }
    return WinDefWindowProc (hwnd, msg, mp1, mp2);
}


MRESULT EXPENTRY SubclassFrame (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   RECTL        rcl;
   HPS          hps;

   switch (msg) {
   case WM_PAINT:
       hps = WinBeginPaint(hwnd, (HPS) NULL, &rcl);
       WinDrawBorder(hps, &rcl, 1, 1, 0, 0, DB_DLGBORDER);
       WinEndPaint(hps);
       return 0;
       break;
   default:
   } /* endswitch */

   /* Pass all other messages to original procedure */
   return (MRESULT) pfnFrame(hwnd, msg, mp1, mp2);
}


/* our HEX - OCT window procedure */
MRESULT EXPENTRY HexOctWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   SHORT        mparam;

   switch (msg) {
   case WM_COMMAND:
      mparam = SHORT1FROMMP(mp1);
      switch (mparam) {
      case ID_BUT_HEX:
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(mparam), 0);
         WinSetFocus(HWND_DESKTOP, hwndClient);
         return (0);
         break;
      default:
        break;
      } /* endswitch */
      break;
   case WM_CONTROL:
      mparam = SHORT1FROMMP(mp1);
      switch (mparam) {
      case ID_RADIO_DEC:
      case ID_RADIO_HEX:
      case ID_RADIO_OCT:
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(mparam), 0);
         WinSetFocus(HWND_DESKTOP, hwndFrame);
         break;
      default:
        break;
      } /* endswitch */
      break;
   default:
     break;
   } /* endswitch */

   return WinDefDlgProc (hwnd, msg, mp1, mp2);
}


/*
  order of search for .INI
  1) filename in argument
  2) HPcalc.INI in current Directory
  3) HPcalc.INI in directory where HPcalc.EXE resides
*/
void GetIniFilename(int argc, char *argv[], PSZ buf)
{
   if (argc >= 2) {
      strcpy(buf, argv[1]);
   } else {
      strcpy(buf, szIniFile);
      if (access(buf, 0)) {
         GetFullPathToExe(buf);
         if ( !ConvertExeToIni(buf)) {
            strcpy(buf, szIniFile);
         } /* endif */
      } /* endif */
   } /* endif */
}


/* large enough buffer must passed as argument */
void GetFullPathToExe(PSZ buf)
{
    PTIB ptib;
    PPIB ppib;
    char *p;
    int len;

    DosGetInfoBlocks(&ptib, &ppib);
    p = ppib->pib_pchenv;
    while ((len = strlen(p)) != 0) {
        p += len + 1;
    }
    p++;
    strcpy(buf, p);
}


/* return true if change is  okay */
BOOL ConvertExeToIni(PSZ buf)
{
   char *p;

   /* assume format is "xxx...xxx.EXE" */
   p = buf + strlen(buf) - 4;

   if (!strcmp(p, ".EXE")) {
      strcpy(p, ".INI");
      return(TRUE);
   } /* endif */
   return(FALSE);
}
