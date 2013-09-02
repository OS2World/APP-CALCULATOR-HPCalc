/* Definitions */
#define INCL_PM
        /* to allocate interface.h global vars */
#define INTERFACE

/* summation definitions */
#define SIGX    summation[0]
#define SIGX2   summation[1]
#define SIGY    summation[2]
#define SIGY2   summation[3]
#define SIGXY   summation[4]
#define SIG_N   ((int)summation[5])

/* Includes */
#include <os2.h>
#include <math.h>
#include <float.h>  /* used in emx/gcc */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HPcalc.h"
#include "interface.h"
#include "interface-vars.h"
#include "ini.h"
#include "change.h"
#include "hex-oct.h"

/* Local Prototypes */
void UpdateEntry(UCHAR);
void UpdateDot(void);
void DoBackSpace(void);
void DoEnter(void);
void DoEex(void);
void Enter(double);
double UseAngle(double);
double ToAngle(double);
void DoGetNum(SHORT);
void CopyData(void);
void PasteData(void);
void FormatVal(double, PSZ);
void DoSigma(double, double, int);
void putComma(PSZ szFormat);
void doHR(double t);
void doHMS(double t);
double slope(void);
double permutation(int, int);
double combination(int, int);
void AcceptValue(void);
MRESULT EXPENTRY DialogWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);



MRESULT ProcessCommand (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    SHORT           comm, i;
    double          temp, t2;
    UCHAR           ch;
    APIRET          rc;
    HWND            hwndMenu;

    comm = SHORT1FROMMP(mp1);
/* printf("ProcessCommand %d\n", comm); */

    switch (comm ) {
    case IDM_EXIT:
       WinPostMsg(hwnd,WM_CLOSE,0L,0L);
       return ((MRESULT)0);
       break;
    case IDM_COPY:
       CopyData();
       return ((MRESULT)0);
       break;
    case IDM_PASTE:
       PasteData();
       return ((MRESULT)0);
       break;
    case IDM_ABOUT:
       rc = WinDlgBox(HWND_DESKTOP, hwnd, DialogWinProc, 0, ID_HPDLG, NULL);
       return ((MRESULT)0);
       break;
    case IDM_XYZT:
       if (fXyzt) {
          WinShowWindow(hwndDispY, FALSE);
          WinShowWindow(hwndDispZ, FALSE);
          WinShowWindow(hwndDispT, FALSE);
       } else {
          WinShowWindow(hwndDispY, TRUE);
          WinShowWindow(hwndDispZ, TRUE);
          WinShowWindow(hwndDispT, TRUE);
       } /* endif */
       fXyzt = !fXyzt;
       ShowXYZT(fXyzt);

       hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);
       rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_XYZT, (USHORT)fXyzt);
       return ((MRESULT)0);
       break;
    case IDM_SIZE:
       {
          if (fVgaSize) {
             ChangeSize(SIZE_NORM, fXyzt);
          } else {
             ChangeSize(SIZE_SMALL, fXyzt);
          } /* endif */
          fVgaSize = !fVgaSize;

          hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);
          rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_SIZE, (USHORT)fVgaSize);

/*          WinInvalidateRect(hwnd,pwrc,); */
       }
       return ((MRESULT)0);
       break;
    case IDM_HEX_OCT:
    case ID_BUT_HEX:
       EntryToStack();
       bLift = TRUE;
       fHexOct = !fHexOct;
       InitializeDisplay();
       WinInvalidateRect(hwndClient, NULL, TRUE);  /* force redraw */
       return ((MRESULT)0);
       break;
    case IDM_COMMA:
       fComma = !fComma;
       UpdateDisplay(stack[0]);
       UpdateYZT();
 
       hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);
       rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_COMMA, (USHORT)fComma);
       return ((MRESULT)0);
       break;
    case K_GOL:
       if ((bShiftMode = (! bShiftMode))) {
           WinSetWindowText(hwndSmode, "shift");
       } else {
           WinSetWindowText(hwndSmode, "");
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_HYP_SIN:
       AcceptValue();
       temp=stack[0];
       Enter((exp(temp)-exp(-temp))*0.5);
       return ((MRESULT)0);
       break;
    case IDM_HYP_COS:
       AcceptValue();
       temp=stack[0];
       Enter((exp(temp)+exp(-temp))*0.5);
       return ((MRESULT)0);
       break;
    case IDM_HYP_TAN:
       AcceptValue();
       temp=stack[0];
       t2 = exp(temp)+exp(-temp);
       if (t2 == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
       } else {
          Enter((exp(temp)-exp(-temp))/t2);
       }
       return ((MRESULT)0);
       break;
    case IDM_HYP_ASIN:
       AcceptValue();
       temp=stack[0];
       t2 = temp + sqrt(temp*temp+1);
       Enter(log(t2));
       return ((MRESULT)0);
       break;
    case IDM_HYP_ACOS:
       AcceptValue();
       temp=stack[0];
       if (temp < 1.0) {
           WinSetWindowText(hwndDisplay, DATAERROR);
           bError = TRUE;
       } else {
           t2 = temp + sqrt(temp*temp-1);
           Enter(log(t2));
       }
       return ((MRESULT)0);
       break;
    case IDM_HYP_ATAN:
       AcceptValue();
       temp=stack[0];
       if (abs(temp) >= 1.0) {
           WinSetWindowText(hwndDisplay, DATAERROR);
           bError = TRUE;
       } else {
           Enter(0.5*log((1+temp)/(1-temp)));
       }
       return ((MRESULT)0);
       break;
    case IDM_CON_C:
       AcceptValue();
       LiftStack();
       UpdateDisplay(2.99792458e8);
       return ((MRESULT)0);
       break;
    case IDM_CON_H:
       AcceptValue();
       LiftStack();
       UpdateDisplay(6.626176e-34);
       return ((MRESULT)0);
       break;
    case IDM_CON_E:
       AcceptValue();
       LiftStack();
       UpdateDisplay(1.6021892e-19);
       return ((MRESULT)0);
       break;
    case IDM_CON_NA:
       AcceptValue();
       LiftStack();
       UpdateDisplay(6.022045e23);
       return ((MRESULT)0);
       break;
    case IDM_CON_U0:
       AcceptValue();
       LiftStack();
       UpdateDisplay(4e-7*M_PI);
       return ((MRESULT)0);
       break;
    case IDM_CON_E0:
       AcceptValue();
       LiftStack();
       UpdateDisplay(8.85418782e-12);
       return ((MRESULT)0);
       break;
    case IDM_CONV_CF:
       AcceptValue();
       Enter(stack[0]*9.0/5.0+32.0);
       return ((MRESULT)0);
       break;
    case IDM_CONV_FC:
       AcceptValue();
       Enter((stack[0]-32.0)*5.0/9.0);
       return ((MRESULT)0);
       break;
    case IDM_CONV_INMM:
       AcceptValue();
       Enter(stack[0]*25.4);
       return ((MRESULT)0);
       break;
    case IDM_CONV_MMIN:
       AcceptValue();
       Enter(stack[0]/25.4);
       return ((MRESULT)0);
       break;
    case IDM_CONV_MIKM:
       AcceptValue();
       Enter(stack[0]*1.609344);
       return ((MRESULT)0);
       break;
    case IDM_CONV_KMMI:
       AcceptValue();
       Enter(stack[0]/1.609344);
       return ((MRESULT)0);
       break;
    case IDM_STAT_SLOPE: /* Slope */
       AcceptValue();
       if (SIG_N <= 0) {
          WinSetWindowText(hwndDisplay, DATAERROR);
          bError = TRUE;
       } else {
          Enter(slope());
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_INT: /* Intercept */
       AcceptValue();
       if (SIG_N <= 0) {
          WinSetWindowText(hwndDisplay, DATAERROR);
          bError = TRUE;
       } else {
          Enter((SIGX - slope()*SIGY)/SIG_N);
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_CORR: /* correlation */
       AcceptValue();
       if (SIG_N <= 0) {
          WinSetWindowText(hwndDisplay, DATAERROR);
          bError = TRUE;
       } else {
          double sxx = SIGX2 -  SIGX*SIGX/SIG_N;
          double syy = SIGY2 -  SIGY*SIGY/SIG_N;
          double sxy = SIGXY -  SIGX*SIGY/SIG_N;

          Enter(sxy/sqrt(sxx*syy));
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_X1: /* x given y */
       AcceptValue();
       if (SIG_N <= 0) {
          WinSetWindowText(hwndDisplay, DATAERROR);
          bError = TRUE;
       } else {
          temp = slope();
          if (temp == 0.0) {
             Enter(1e99);
          } else {
             Enter(((stack[0]-(SIGX - temp*SIGY)/SIG_N))/temp);
          } /* endif */
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_Y1: /* y given x */
       AcceptValue();
       if (SIG_N <= 0) {
          WinSetWindowText(hwndDisplay, DATAERROR);
          bError = TRUE;
       } else {
          temp = slope();
          Enter(((SIGX - temp*SIGY)/SIG_N) + stack[0]*temp);
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_SDEV: /* population Standard Deviation */
       AcceptValue();
       if (SIG_N <= 0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
       } else {
              lastx = stack[0];
              stack[0] = sqrt((SIGX2*SIG_N - SIGX*SIGX) /(SIG_N-1) /(SIG_N-1));
              stack[1] = sqrt((SIGY2*SIG_N - SIGY*SIGY) /(SIG_N-1) /(SIG_N-1));
              UpdateYZT();
              UpdateDisplay(stack[0]);
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_PERM: /* permutation */
       AcceptValue();
       if ((stack[0] >= 0.0) && (stack[1] >= 0.0)) {
          if (stack[1] >= stack[0]) {
             lastx = stack[0];
             temp = permutation((int)stack[0],(int)stack[1]);
             DropStack();
             UpdateDisplay(temp);
          } else {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
          } /* endif */
       } else {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
       } /* endif */
       return ((MRESULT)0);
       break;
    case IDM_STAT_COMB: /* permutation */
       AcceptValue();
       if ((stack[0] >= 0.0) && (stack[1] >= 0.0)) {
          if (stack[1] >= stack[0]) {
             lastx = stack[0];
             temp = combination(stack[0],stack[1]);
             DropStack();
             UpdateDisplay(temp);
          } else {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
          } /* endif */
       } else {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
       } /* endif */
       return ((MRESULT)0);
       break;
    }

    if (bGetNumMode) {
       DoGetNum(comm);
       return ((MRESULT)0);
    } else if (fHexOct) {
       ProcessHexCommand(comm);
       return ((MRESULT)0);
    } /* endif */


    if (bShiftMode) {
        bShiftMode = FALSE;
        WinSetWindowText(hwndSmode, "");

        EntryToStack();
        bLift = TRUE;

        switch (comm ) {
        case K_0: /* pi */
           LiftStack();
           UpdateDisplay(M_PI);
           return ((MRESULT)0);
           break;
        case K_1: /* FIX */
           WaitGetNum(MODE_FIX);
           break;
        case K_2: /* SCI */
           WaitGetNum(MODE_SCI);
           break;
        case K_3: /* ENG */
           WaitGetNum(MODE_ENG);
           break;
        case K_EEX: /* FIX */
           WaitGetNum(MODE_FEX);
           break;
        case K_5: /* Polar to Rectangular */
           lastx = stack[0]; /* Angle */
           temp = stack[1];  /* Magnitude */
           stack[1] = lastx * sin(UseAngle(temp));
           stack[0] = lastx * cos(UseAngle(temp));
           UpdateYZT();
           UpdateDisplay(stack[0]);
           break;
        case K_6: /* Rectanglar to Polar */
           lastx = stack[0]; /* X */
           temp = stack[1];  /* Y */
           stack[1] = ToAngle(atan2(temp, lastx));
           stack[0] = sqrt(lastx*lastx + temp*temp);
           UpdateYZT();
           UpdateDisplay(stack[0]);
           break;
        case K_BS: /* CLx */
           if (bError) {
              UpdateDisplay(stack[0]);
           } else {
              UpdateDisplay(0.0);
              bLift = FALSE;
           } /* endif */
           break;
        case K_CHS: /* MOD */
           if (stack[0] == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              temp = stack[1] - ((int)(stack[1] / stack[0]) * stack[0]);
              DropStack();
              UpdateDisplay(temp);
           }
           break;
        case K_DOT: /* lastx */
           LiftStack();
           UpdateDisplay(lastx);
           break;
        case K_SIN: /* ArcSin */
           if (stack[0] > 1.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              Enter(ToAngle(asin(stack[0])));
           } /* endif */
           break;
        case K_COS: /* ArcCos */
           if (stack[0] > 1.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              Enter(ToAngle(acos(stack[0])));
           } /* endif */
           break;
        case K_TAN: /* ArcTan */
           Enter(ToAngle(atan(stack[0])));
           break;
        case K_1X: /* y^x */
           lastx = stack[0];
           temp = pow(stack[1], stack[0]);
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_ROO: /* Square */
           Enter(stack[0]*stack[0]);
           break;
        case K_LOG: /* 10^x */
           Enter(pow(10.0,stack[0]));
           break;
        case K_LN: /* e^x */
           Enter(exp(stack[0]));
           break;
        case K_RD: /* % */
           Enter(stack[0]*0.01*stack[1]);
           break;
        case K_SIG: /* ä- */
           DoSigma(stack[0], stack[1], -1);
           break;
        case K_XY: /* clä */
           UpdateDisplay(stack[0]);
           for (i=0; i<6; i++) {
              summation[i] = 0.0;
           } /* endfor */
           break;
        case K_STO: /* ->HR */
           doHR(stack[0]);
           break;
        case K_RCL: /* ->HMS */
           doHMS(stack[0]);
           break;
        case K_SST: /* n!, Factorial */
           if (stack[0] < 0.0 || stack[0] >= 70.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              temp = 1.0;
              for (i = (int)stack[0]; i > 1; i--) {
                 temp *= i;
              } /* endfor */
              Enter(temp);
           }
           break;
        case K_MIN: /* äx */
           LiftStack();
           Enter(SIGX);
           break;
        case K_PLU: /* äy */
           LiftStack();
           Enter(SIGY);
           break;
        case K_MUL: /* äxy */
           LiftStack();
           Enter(SIGXY);
           break;
        case K_DIV: /* n */
           LiftStack();
           Enter(SIG_N);
           break;
        case K_7: /* äx2 */
           LiftStack();
           Enter(SIGX2);
           break;
        case K_4: /* äy2 */
           LiftStack();
           Enter(SIGY2);
           break;
        case K_8: /* mean */
           if (SIG_N == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              stack[0] = SIGX / SIG_N;
              stack[1] = SIGY / SIG_N;
              UpdateYZT();
              UpdateDisplay(stack[0]);
           } /* endif */
           break;
        case K_9: /* standard deviation */
           if (SIG_N == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              double    ex;
              lastx = stack[0];
              ex = SIGX * SIGX / SIG_N;
              stack[0] = sqrt((SIGX2 - ex) / (SIG_N-1));
              ex = SIGY * SIGY / SIG_N;
              stack[1] = sqrt((SIGY2 - ex) / (SIG_N-1));
              UpdateYZT();
              UpdateDisplay(stack[0]);
           } /* endif */
           break;
        default: 
        }
    } else {
        /* Stack Lift Disable or Neutral command keys */
        switch (comm ) {
        case K_0: case K_1: case K_2: case K_3: case K_4: case K_5:
        case K_6: case K_7: case K_8: case K_9:
           ch = '0' + comm - K_0;
           UpdateEntry(ch);
           return ((MRESULT)0);
           break;
        case K_DOT:
           UpdateDot();
           return ((MRESULT)0);
           break;
        case K_ENT:
           DoEnter();
           return ((MRESULT)0);
           break;
        case K_BS:
           if (bError) {
              UpdateDisplay(stack[0]);
           } else {
              DoBackSpace();
           } /* endif */
           return ((MRESULT)0);
           break;
        case K_CHS:
           DoChs();
           return ((MRESULT)0);
           break;
        case K_EEX:
           DoEex();
           return ((MRESULT)0);
           break;
        }

        /* the following function end entry mode and enable stack lift */
        EntryToStack();
        bLift = TRUE;

        switch (comm ) {
        case K_AMODE:
           switch (uAngleMode) {
           case MODE_RAD:
              uAngleMode = MODE_DEG;
              WinSetWindowText(hwndAmode, "DEG");
              break;
           case MODE_DEG:
              uAngleMode = MODE_GRAD;
              WinSetWindowText(hwndAmode, "GRAD");
              break;
           case MODE_GRAD:
              uAngleMode = MODE_RAD;
              WinSetWindowText(hwndAmode, "RAD");
              break;
           default:
           } /* endswitch */
           UpdateDisplay(stack[0]);
           break;
        case K_SIN:
           Enter(sin(UseAngle(stack[0])));
           break;
        case K_COS:
           if (fabs(stack[0]) == 90 && uAngleMode == MODE_DEG) {
              Enter(0.0);
           } else {
              Enter(cos(UseAngle(stack[0])));
           } /* endif */
           break;
        case K_TAN:
           if (fabs(stack[0]) == 90 && uAngleMode == MODE_DEG) {
              if (stack[0] >0) {
                 Enter(9.9999999e98);
              } else {
                 Enter(-9.9999999e98);
              } /* endif */
           } else {
              Enter(tan(UseAngle(stack[0])));
           } /* endif */
           break;
        case K_1X:
           if (stack[0] == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              UpdateDisplay(1.0/stack[0]);
           }
           break;
        case K_ROO:
           if (stack[0] < 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              UpdateDisplay(sqrt(stack[0]));
           } /* endif */
           break;
        case K_LOG:
           if (stack[0] <= 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              UpdateDisplay(log10(stack[0]));
           } /* endif */
           break;
        case K_LN:
           if (stack[0] <= 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              UpdateDisplay(log(stack[0]));
           } /* endif */
           break;
        case K_RD:
           RollDown();
           break;
        case K_RU:
           RollUp();
           break;
        case K_MIN:
           lastx = stack[0];
           temp = stack[1] - stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_PLU:
           lastx = stack[0];
           temp = stack[1] + stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_MUL:
           lastx = stack[0];
           temp = stack[1] * stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_DIV:
           if (stack[0] == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              temp = stack[1] / stack[0];
              DropStack();
              UpdateDisplay(temp);
           }
           break;
        case K_XY:
           temp = stack[1];
           stack[1] = stack[0];
           UpdateDisplay(temp);
           UpdateYZT();
           break;
        case K_STO:
           WaitGetNum(MODE_STO);
           break;
        case K_RCL:
           WaitGetNum(MODE_RCL);
           break;
        case K_SST: /* Cls - clear stack */
           stack[1] = 0; stack[2] = 0; stack[3] = 0;
           UpdateYZT();
           UpdateDisplay(0.0);
           break;
        case K_SIG: /* sigma + */
           Enter(stack[0]);
           DoSigma(stack[0], stack[1], 1);
           break;
        default:
        }
    } /* endif */
    return ((MRESULT)0);
}



MRESULT ProcessKeyboardChar (HWND hwnd, ULONG msg, MPARAM mp1 , MPARAM mp2)
{
   UCHAR        ch;
   USHORT       fs, vkey;

   ch = (UCHAR) CHAR1FROMMP(mp2);
   fs = SHORT1FROMMP(mp1);
   vkey = SHORT2FROMMP(mp2);

/* printf("ProcessKeyboardChar mp1=%lx mp2=%lx\n", mp1, mp2);  */
   if (fs & (KC_LONEKEY | KC_KEYUP)) {
      return (MRESULT) 0;
   } /* endif */

   if (!(fs & KC_CHAR) && !(fs & KC_VIRTUALKEY)) {
      return (MRESULT) 0;
   } /* endif */

   if (fHexOct) {
      ProcessKeyBoardHex(ch, fs, vkey);
      return (MRESULT) 0;
   } /* endif */

      switch (ch) {
      case '0':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_0), 0);
         break;
      case '1':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_1), 0);
         break;
      case '2':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_2), 0);
         break;
      case '3':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_3), 0);
         break;
      case '4':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_4), 0);
         break;
      case '5':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_5), 0);
         break;
      case '6':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_6), 0);
         break;
      case '7':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_7), 0);
         break;
      case '8':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_8), 0);
         break;
      case '9':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_9), 0);
         break;
      case '+':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_PLU), 0);
         break;
      case '-':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_MIN), 0);
         break;
      case '*':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_MUL), 0);
         break;
      case '/':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_DIV), 0);
         break;
      case '.': case',':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_DOT), 0);
         break;
      case '%':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_RD), 0);
         break;
      case '^':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_1X), 0);
         break;
      case '!':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_SST), 0);
         break;

      case 'a': case 'A':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_AMODE), 0);
         break;
      case 'c': case 'C':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_COS), 0);
         break;
      case 'e': case 'E':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_EEX), 0);
         break;
      case 'g': case 'G':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_LOG), 0);
         break;
      case 'h': case 'H':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_CHS), 0);
         break;
      case 'k': case 'K':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_SST), 0);
         break;
      case 'l': case 'L':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_DOT), 0);
         break;
      case 'm': case 'M':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_CHS), 0);
         break;
      case 'n': case 'N':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_LN), 0);
         break;
      case 'o': case 'O':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_STO), 0);
         break;
      case 'p': case 'P':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_0), 0);
         break;
      case 'q': case 'Q':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_ROO), 0);
         break;
      case 'r': case 'R':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_RCL), 0);
         break;
      case 's': case 'S':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_SIN), 0);
         break;
      case 't': case 'T':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_TAN), 0);
         break;
      case 'u': case 'U':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_SIG), 0);
         break;
      case 'v': case 'V':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_1X), 0);
         break;
      case 'x': case 'X':
         WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_XY), 0);
         break;
      default: 
         switch (vkey) {
         case VK_CTRL:
            if (fs & KC_PREVDOWN) {        /* key repeat */
               break;      /* early break from switch(vkey) */
            } /* endif */
            WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
            break;
         default: 
            break;
         } /* endswitch */
         break;
      }
   return (MRESULT) 0;
}


void ResetEntry(void)
{
     bEntryMode = FALSE; bEexMode = FALSE; numdigits=0; numeex=0;
     bDot=FALSE;  bError = FALSE;
     bShiftMode = FALSE; bLift = TRUE;
     strcpy(szDigits, "              ");
     strcpy(szEex, "   ");
     WinSetWindowText(hwndSmode, "");
}



void SetDisplay(double dispVal)
{
   UCHAR        szBuf[MAXBUF];

   if (bEntryMode) {
      if (bEexMode) {
         strcpy(szBuf, szDigits);
         strcpy((szBuf+ 9 + bDot), szEex);
         WinSetWindowText(hwndDisplay, szBuf);
      } else {
         WinSetWindowText(hwndDisplay, szDigits);
      } /* endif */
   } else {
      UpdateDisplay(dispVal);
   }
   bError = FALSE;
}


void UpdateDot(void)
{
   if (bDot == 1) {
      return;
   } /* endif */

   if (!bEntryMode && bLift) {
      LiftStack();
   } /* endif */

   if (! bEexMode) {
      bDot = 1;
      bEntryMode = TRUE;
      if (numdigits < 10) {
         *(szDigits + numdigits + bDot) = '.';
         *(szDigits + numdigits + 1 + bDot) = '_';
      } else {
         *(szDigits + numdigits + bDot) = '.';
      } /* endif */
   } /* endif */
   SetDisplay(0.0);
}


void UpdateEntry(UCHAR ch)
{
   if (!bEntryMode && bLift) {
      LiftStack();
   } /* endif */

   if (bEexMode) {
      if (numeex < 1) {
         (numeex) ++;
         *(szEex + numeex) = ch;
         *(szEex + numeex + 1) = '_';
      } else if (numeex < 2) {
         (numeex) ++;
         *(szEex + numeex) = ch;
      } /* endif */
   } else {
      if (numdigits < 9) {
         (numdigits) ++;
         *(szDigits + numdigits + bDot) = ch;
         *(szDigits + numdigits + 1 + bDot) = '_';
      } else if (numdigits < 10) {
         (numdigits) ++;
         *(szDigits + numdigits + bDot) = ch;
      } /* endif */
   } /* endif */

   bEntryMode = TRUE;
   SetDisplay(0.0);
}


void DoEnter(void)
{
   double       temp;
   int          ee;

   if (bEntryMode) {
      temp = atof(szDigits);
      if (bEexMode) {
         ee = atoi(szEex);
      } else {
         ee = 0;
      } /* endif */
/* printf("%s<<%s<<%lf %d\n",szDigits, szEex, temp, ee); */
      temp *= pow(10.0, (double)ee);
      ResetEntry();
      stack[0] = temp;
      if (bLift) {
         LiftStack();
      } /* endif */
      UpdateDisplay(temp);
   } else {
      LiftStack();
   } /* endif */
   bLift = FALSE;
}


void DoBackSpace(void)
{
   double       dispVal=0;

   if (bEntryMode) {
      if (bEexMode) {
         if (numeex == 0) {
            if (*szEex == '-') {
               *szEex = ' ';
            } else {
               bEexMode = FALSE;
               *(szDigits + numdigits + 1 + bDot) = '_';
            } /* endif */
         } else if (numeex == 1) {
            *(szEex + numeex ) = '_';
            *(szEex + numeex + 1) = ' ';
            numeex --;
         } else {
            *(szEex + numeex) = '_';
            (numeex) --;
         }
      } else {
         if (numdigits == 0) {
            ResetEntry();
            dispVal = 0.0;
         } else if (numdigits == 1) {
            if (*(szDigits + numdigits + bDot) == '.') {
               *(szDigits + numdigits + bDot) = '_';
               *(szDigits + numdigits + 1 + bDot) = ' ';
               bDot = 0;
            } else if (bDot) {
               *(szDigits + numdigits + bDot) = '_';
               *(szDigits + numdigits + 1 + bDot) = ' ';
               numdigits --;
            } else {
               ResetEntry();
               dispVal = 0.0;
               bLift = FALSE;
            } /* endif */
         } else if (numdigits == 10 ){
            if (*(szDigits + numdigits + bDot) == '.') {
               *(szDigits + numdigits + bDot) = ' ';
               bDot = 0;
            } else {
               *(szDigits + numdigits + bDot) = '_';
               (numdigits) --;
            } /* endif */
         } else {
            if (*(szDigits + numdigits + bDot) == '.') {
               *(szDigits + numdigits + bDot) = '_';
               *(szDigits + numdigits + 1 + bDot) = ' ';
               bDot = 0;
            } else {
               *(szDigits + numdigits + bDot) = '_';
               *(szDigits + numdigits + 1 + bDot) = ' ';
               (numdigits) --;
            } /* endif */
         } /* endif */
      } /* endif */
   } else {
      dispVal = 0.0;
      bLift = FALSE;
   } /* endif */

   SetDisplay(dispVal);
}


void UpdateDisplay(double value)
{
   UCHAR        szBuf[MAXBUF];

   bError = FALSE;
   if (fHexOct) {
      value = (int)value;
   } /* endif */
   stack[0] = value;
   FormatVal(value, szBuf);
   WinSetWindowText(hwndDisplay, szBuf);
}


void Enter(double val)
{
   lastx = stack[0];
   UpdateDisplay(val);
   ResetEntry();
}


void RollDown(void)
{
   double temp;

   temp = stack[0];
   stack[0] = stack[1];
   stack[1] = stack[2];
   stack[2] = stack[3];
   stack[3] = temp;
   UpdateDisplay(stack[0]);
   UpdateYZT();
}


void RollUp(void)
{
   double temp;

   temp = stack[3];
   stack[3] = stack[2];
   stack[2] = stack[1];
   stack[1] = stack[0];
   stack[0] = temp;
   UpdateDisplay(stack[0]);
   UpdateYZT();
}


void LiftStack(void)
{
   stack[3] = stack[2];
   stack[2] = stack[1];
   stack[1] = stack[0];
   UpdateYZT();
}



void DropStack(void)
{
   stack[1] = stack[2];
   stack[2] = stack[3];
   UpdateYZT();
}


void DoChs(void)
{
   if (bEntryMode) {
      if (bEexMode) {
         *szEex = (*szEex == '-') ? ' ' : '-';
      } else {
         *szDigits = (*szDigits == '-') ? ' ' : '-';
      } /* endif */
      SetDisplay(0.0);
   } else {
      UpdateDisplay(-stack[0]);
      bLift = TRUE;
   } /* endif */
}


void DoEex(void)
{
   if (bEntryMode) {
      if (numdigits < 8) {
         strcpy(szEex, " _ ");
         numeex = 0;
         bEexMode = TRUE;
         *(szDigits + numdigits + 1 + bDot) = ' ';
         SetDisplay(0.0);
      } /* endif */
   } else {
     if (bLift) {
        LiftStack();
     } /* endif */
     strcpy(szDigits, " 1            ");
     strcpy(szEex, " _ ");
     numdigits = 1; numeex = 0;
     bEexMode = TRUE; bEntryMode = TRUE;
     bLift = TRUE;
     SetDisplay(0.0);
   } /* endif */
}


double UseAngle(double ang)
{
   switch (uAngleMode) {
   case MODE_RAD:
      return (ang);
      break;
   case MODE_DEG:
      return (ang * M_PI / 180.0);
      break;
   case MODE_GRAD:
      return (ang * M_PI / 200.0);
      break;
   default:
   } /* endswitch */
   return(0.0); /* to keep compiler from warning only */
}


double ToAngle(double ang)
{
   switch (uAngleMode) {
   case MODE_RAD:
      return (ang);
      break;
   case MODE_DEG:
      return (ang / M_PI * 180.0);
      break;
   case MODE_GRAD:
      return (ang / M_PI * 200.0);
      break;
   default:
   } /* endswitch */
   return(0.0); /* to keep compiler from warning only */
}


void WaitGetNum(USHORT uMode)
{
   UCHAR        buf[MAXBUF];

   switch (uMode) {
   case MODE_FIX:
      strcpy(buf, "FIX _");
      break;
   case MODE_SCI:
      strcpy(buf, "SCI _");
      break;
   case MODE_ENG:
      strcpy(buf, "ENG _");
      break;
   case MODE_FEX:
      strcpy(buf, "FEX _");
      break;
   case MODE_STO:
      strcpy(buf, "STO _");
      break;
   case MODE_RCL:
      strcpy(buf, "RCL _");
      break;
   default: 
      return ;
   } /* endswitch */
   WinSetWindowText(hwndDisplay, buf);
   bGetNumMode = TRUE;
   uGetNum = uMode;
}


void DoGetNum(SHORT comm)
{
   SHORT        num;

   switch (comm) {
   case K_0: case K_1: case K_2: case K_3: case K_4: case K_5:
   case K_6: case K_7: case K_8: case K_9:
      num = comm - K_0;

      switch (uGetNum) {
      case MODE_SCI:    /* these two case fall out into MODE_FIX */
      case MODE_ENG:
         if (num > 7) {
            num = 7;
         } /* endif */
      case MODE_FIX:
      case MODE_FEX:
         uNumMode = uGetNum;
         uDispDigs = num;
         UpdateDisplay(stack[0]);
         UpdateYZT();
         break;
      case MODE_STO:
         memory[num] = stack[0];
         UpdateDisplay(stack[0]);
         break;
      case MODE_RCL:
         if (bLift) LiftStack();
         bLift = TRUE;
         UpdateDisplay(memory[num]);
         break;
      case MODE_MIN: /* STO minus */
         memory[num] -= stack[0];
         UpdateDisplay(stack[0]);
         break;
      case MODE_PLU: /* STO plus */
         memory[num] += stack[0];
         UpdateDisplay(stack[0]);
         break;
      case MODE_MUL: /* STO multiply */
         memory[num] *= stack[0];
         UpdateDisplay(stack[0]);
         break;
      case MODE_DIV: /* STO divide */
         if (stack[0] == 0.0) {
            WinSetWindowText(hwndDisplay, DATAERROR);
            bError = TRUE;
         } else {
            memory[num] /= stack[0];
            UpdateDisplay(stack[0]);
         }
         break;
      } /* endswitch */
      bGetNumMode = FALSE;
      break;
   case K_MIN:
      uGetNum = MODE_MIN;
      WinSetWindowText(hwndDisplay, "ST- _");
      break;
   case K_PLU:
      uGetNum = MODE_PLU;
      WinSetWindowText(hwndDisplay, "ST+ _");
      break;
   case K_MUL:
      uGetNum = MODE_MUL;
      WinSetWindowText(hwndDisplay, "STx _");
      break;
   case K_DIV:
      uGetNum = MODE_DIV;
      WinSetWindowText(hwndDisplay, "ST/ _");
      break;
   case K_BS:
      UpdateDisplay(stack[0]);
      bGetNumMode = FALSE;
      break;
   default:
   } /* endswitch */
}


/* copy data in stack[0]=x to clipboard */
void CopyData(void)
{
   PSZ          pszSrc, pszDest;
   BOOL         fSuccess;
   CHAR         szClipString[MAXBUF];
   PCHAR        pszStart;
   double       logx;
   int          itemp;

   // FILE         *fp = fopen("j","w");
   // fprintf(fp, " in copy data\n");

   EntryToStack();
   bLift = TRUE;
   UpdateDisplay(stack[0]);

   if (stack[0] == 0) {
      logx = 0;
   } else {
      logx = log10(fabs(stack[0]));
   } /* endif */

   if (fHexOct) {
      itemp =stack[0];
      switch (uBinMode) {
      case MODE_DEC:
         sprintf(szClipString, "%d%c", itemp, 0);
         break;
      case MODE_HEX:
         sprintf(szClipString, "%x%c", itemp, 0);
         pszSrc = szClipString;
         while ((*pszSrc)) {
            if (*pszSrc >= 'a') {
               *pszSrc -= 'a' - 'A';
            } /* endif */
            pszSrc++;
         } /* endwhile */
         break;
      case MODE_OCT:
         sprintf(szClipString, "%o%c", itemp, 0);
         break;
      default:
        break;
      } /* endswitch */
      pszStart = szClipString;
   } else {
      sprintf(szClipString, "%15.10g%c", stack[0], 0);
      pszStart = strpbrk(szClipString, "-0123456789");
   } /* endif */


   if (WinOpenClipbrd(hab)) {
/*      fSuccess = WinSetClipbrdOwner(hab,hwndClient); */
      if (!(fSuccess = DosAllocSharedMem(
                (PVOID)&pszDest, NULL, strlen(szClipString)+1,
                PAG_WRITE | PAG_COMMIT | OBJ_GIVEABLE))) {
         strcpy(pszDest, pszStart);
         fSuccess = WinSetClipbrdData(hab, (ULONG)pszDest, 
                        CF_TEXT, CFI_POINTER);
      } /* endif */
      WinCloseClipbrd(hab);
   } /* endif */

  // fclose(fp);
}


void PasteData(void)
{
   double       val=0;
   PSZ          pszClipText;
   int          itemp=0;

   // FILE         *fp = fopen("j","w");
   // fprintf(fp, " in copy data\n");

   if (WinOpenClipbrd(hab)) {
      if ((pszClipText = (PSZ) WinQueryClipbrdData(hab, CF_TEXT))) {
         if ((strlen(pszClipText)) <= MAXBUF) {
            if (fHexOct) {
               switch (uBinMode) {
               case MODE_DEC:
                  sscanf(pszClipText, "%d", &itemp);
                  break;
               case MODE_HEX:
                  sscanf(pszClipText, "%x", &itemp);
                  break;
               case MODE_OCT:
                  sscanf(pszClipText, "%o", &itemp);
                  break;
               default:
                  break;
               } /* endswitch */
               val = itemp;
            } else {
               sscanf(pszClipText, "%lf", &val);
            } /* endif */

            EntryToStack();
            if (bLift) LiftStack();
            bLift = TRUE;
            UpdateDisplay(stack[0]);
            Enter(val);
         } /* endif */
      } /* endif */
      WinCloseClipbrd(hab);
   } /* endif */

  // fclose(fp);
}


void EntryToStack(void)
{
   double       temp;
   int          ee;

        if (bEntryMode) {
           temp = atof(szDigits);
           if (bEexMode) {
              ee = atoi(szEex);
           } else {
              ee = 0;
           } /* endif */
/* printf("EntryToStack #%s#%s# %lf %d\n", szDigits, szEex, temp, ee); */
           temp *= pow(10.0, (double)ee);
           stack[0] = temp;
           ResetEntry();
        } /* endif */
}

void InitializeDisplay(void)
{
   APIRET          rc;
   HWND         hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);


      UpdateDisplay(stack[0]);
      ShowKeyboard(fHexOct, uBinMode);
      if (fHexOct) {
         WinEnableMenuItem(hwndMenu, IDM_HYP, FALSE);
         WinEnableMenuItem(hwndMenu, IDM_CONV, FALSE);
         WinEnableMenuItem(hwndMenu, IDM_CON, FALSE);
         WinEnableMenuItem(hwndMenu, IDM_STAT, FALSE);
         switch (uBinMode) {
         case MODE_HEX:
              WinSetWindowText(hwndAmode, "HEX");
              break;
         case MODE_DEC:
              WinSetWindowText(hwndAmode, "DEC");
              break;
         case MODE_OCT:
              WinSetWindowText(hwndAmode, "OCT");
              break;
         default:
         } /* endswitch */
      } else {
         WinEnableMenuItem(hwndMenu, IDM_HYP, TRUE);
         WinEnableMenuItem(hwndMenu, IDM_CONV, TRUE);
         WinEnableMenuItem(hwndMenu, IDM_CON, TRUE);
         WinEnableMenuItem(hwndMenu, IDM_STAT, TRUE);
         switch (uAngleMode) {
         case MODE_RAD:
              WinSetWindowText(hwndAmode, "RAD");
              break;
         case MODE_DEG:
              WinSetWindowText(hwndAmode, "DEG");
              break;
         case MODE_GRAD:
              WinSetWindowText(hwndAmode, "GRAD");
              break;
         default:
         } /* endswitch */
      } /* endif */

      hwndMenu = WinWindowFromID(hwndFrame, FID_MENU);
      rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_XYZT, (USHORT)fXyzt);
      rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_SIZE, (USHORT)fVgaSize);
      rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_HEX_OCT, (USHORT)fHexOct);
      rc = WinCheckMenuItem(hwndMenu, (SHORT)IDM_COMMA, (USHORT)fComma);

      UpdateYZT();
      WinShowWindow(hwndDispY, fXyzt);
      WinShowWindow(hwndDispZ, fXyzt);
      WinShowWindow(hwndDispT, fXyzt);

}


void UpdateYZT(void)
{
   CHAR         buf[MAXBUF];

   FormatVal(stack[1], buf);
   WinSetWindowText(hwndDispY, buf);
   FormatVal(stack[2], buf);
   WinSetWindowText(hwndDispZ, buf);
   FormatVal(stack[3], buf);
   WinSetWindowText(hwndDispT, buf);
}


void FormatVal(double value, PSZ szFormat)
{
   double       mantissa, logx, temp;
   int          exponent, decs, engexp;
   UCHAR        szBuf[MAXBUF], szB[MAXBUF];
   BOOL         neg;
   SHORT        usDisp;
 
   if (fHexOct) {
      FormatValHex(value, szFormat);
      return;
   } /* endif */

   usDisp = uDispDigs;
   if (value == 0)
     logx = 0;
   else
     logx = log10(fabs(value));
   neg = (value < 0.0);
   temp = fabs(value);

   switch (uNumMode) {
   case MODE_FIX:
      if (((-usDisp+log10(0.5) <= logx) && (logx < 10))|| value==0.0) {
         sprintf(szBuf, "% .*f%c", usDisp, value,0);
         *(szBuf + 12) = '\0';
         putComma(szBuf);
         strcpy(szFormat, szBuf);
         return ;
      } /* endif */
      /* use sci notation oltherwise */
      if (usDisp > 7) {
         usDisp = 7;
      } /* endif */
   case MODE_SCI:
      if (temp == 0.0) {
         exponent = 0; mantissa = 0;
      } else {
         exponent = log10(temp);
         exponent -= (log10(temp) < 0.0) ? 1 : 0;
         mantissa = value / pow(10.0, exponent);
      } /* endif */

      sprintf(szBuf, "% .*f.   %c", usDisp, mantissa, 0);
      if (szBuf[2] != '.') {      /* correct for rounding causes 10. */
         mantissa /= 10.0;
         exponent++;
         sprintf(szBuf, "% .*f.   %c", usDisp, mantissa, 0);
      } /* endif */
      sprintf(szB, "% 03d%c",exponent,0);
      strcpy(szBuf + 3 + usDisp, "         \0");
      strcpy((szBuf + 10), szB);
      strcpy(szFormat, szBuf);
      break;
   case MODE_FEX:
      if (((-usDisp+log10(0.5) <= logx) && (logx < 10))|| value==0.0) {
         sprintf(szBuf, "% .*f%c", usDisp, value, 0);
         *(szBuf + 12) = '\0';
         putComma(szBuf);
         strcpy(szFormat, szBuf);
         return ;
      } /* endif */
      /* use sci notation oltherwise */
      if (usDisp > 7) {
         usDisp = 7;
      } /* endif */
   case MODE_ENG:
      if (temp == 0.0) {
         exponent = 0; mantissa = 0;
      } else {
         exponent = log10(temp);
         exponent -= (log10(temp) < 0.0) ? 1 : 0;
         mantissa = value / pow(10.0, exponent);
      } /* endif */

      sprintf(szBuf, "% .*f.   %c", usDisp, mantissa, 0);
      if (szBuf[2] != '.') {      /* correct for rounding causes 10. */
         mantissa /= 10.0;
         exponent++;
         sprintf(szBuf, "% .*f.   %c", usDisp, mantissa, 0);
      } /* endif */
      strcpy(szBuf + 3 + usDisp, "         \0");
      sscanf(szBuf, "%lf", &mantissa);  /* mantissa is now rounded properly*/
      engexp = exponent / 3;
      engexp *= 3;
      engexp -= (exponent < 0)&&(exponent % 3) ? 3 : 0;
      mantissa *= pow(10.0,exponent-engexp);
      if (mantissa == 0)
         decs = 0;
      else {
        decs = log10(fabs(mantissa));
        if (usDisp-decs < 0)
         decs = usDisp;
      }
      sprintf(szB, "% 03d%c",engexp, 0);
      sprintf(szBuf, "% .*f%c        %c", usDisp-decs, mantissa,
                usDisp-decs?' ':'.', 0);
      strcpy((szBuf + 10), szB);
      strcpy(szFormat, szBuf);
      break;
   default:
   } /* endswitch */
}


void putComma(PSZ szFormat)
{
   char        szBuf[MAXBUF];

   if (fComma) {
      int       i, dot;
      char      *c, *d;

      dot = strcspn(szFormat, ".") - 1;

      strcpy(szBuf, szFormat);
      c = szFormat + (dot % 3) + 1;
      d = szBuf + (dot % 3) + 1;
      if ((dot%3) > 0 && dot > 3) {
         *d = ',';
         d++;
      } /* endif */

      for (i=1; i<(dot/3); i++) {
         strcpy(d, c);
         d += 3;
         *d = ',';
         d++;
         c = c + 3;
      } /* endfor */
      strcpy(d, c);
      strcpy(szFormat, szBuf);
   } /* endif */
}


void DoSigma(double x, double y, int dir)
{
   SIGX += x * dir;
   SIGX2 += x * x * dir;
   SIGY += y * dir;
   SIGY2 += y * y * dir;
   SIGXY += x * y * dir;
   summation[5] += dir;
   UpdateDisplay(SIG_N);
}


void doHMS(double t)
{
   long         H;
   int          m;

   H = (long)t;
   t -= H;
   t *= 60;
   m = (int)t;
   t -= m;
   t *= 60;
         /* add 5e-16 because of rounding error in lsb when input
            fractional part of input is a 2 to the power negative x  ie 2.5
            ie. 2.5, otherwise value stored is 2.299999... which gives an
            invalid seconds field of 99 */
   Enter(H + m/100.0 + t/10000.0 + 5.0e-16);
}


void doHR(double t)
{
   long         H;
   int          m;

   H = (long)t;
   t -= H;
   t *= 100.0;
   m = (int) t;
   t -= m;
   t *= 100.0;
   Enter(H + (m*60 + t)/3600.0);
}

/* Get out of data entry mode and reset statuses */
void AcceptValue(void)
{
       EntryToStack();
       bLift = TRUE;
       bShiftMode = FALSE;
       WinSetWindowText(hwndSmode, "");
}


double slope(void)
{
          double sxy = SIGXY -  SIGX*SIGY/SIG_N;
          double syy = SIGY2 -  SIGY*SIGY/SIG_N;

          if (syy == 0.0) {
             return(1.0e99);
          } else {
             return(sxy/syy);
          } /* endif */
}


/* do permutation assumes n >= r >= 0 */
double permutation(int r, int n)
{
   double temp = 1.0;
   int  i, x;
 
   x= n - r + 1;
   for (i = n; i >= x; i--) {
      temp *= i;
   } /* endfor */
   return(temp);
}


/* do combination assumes n >= r >= 0 */
double combination(int r, int n)
{
   double temp = 1.0, t2 = 1.0;
   int  i, x;
 
   x = n - r;
   if (x < r) r = n - r;
   x = n - r + 1;

   for (i = n; i >= x; i--) {
      temp *= i;
   } /* endfor */

   for (i=2; i <= r; i++) {
      t2 *= i;
   } /* endfor */

   return(temp/t2);
}


MRESULT EXPENTRY DialogWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   ULONG        cb;
   HWND         hwndcolor;

   hwndcolor = WinWindowFromID(hwnd, ID_BG_COLOR);

   switch (msg) {
   case WM_COMMAND:
      fDialogBG = WinQueryPresParam(hwndcolor, PP_BACKGROUNDCOLORINDEX, 0, NULL, sizeof(LONG), &lDialogBG, 0);
      if (!fDialogBG) cb = WinQueryPresParam(hwndcolor, PP_BACKGROUNDCOLOR, 0, NULL, sizeof(LONG), &lDialogBG, 0);
      break;
   default:
     break;
   } /* endswitch */

   return WinDefDlgProc (hwnd, msg, mp1, mp2);
}
