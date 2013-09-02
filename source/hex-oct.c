/* hex - oct - dec routines */

/* Definitions */
#define INCL_PM
/* Includes */
#include <os2.h>
#include <stdio.h>
#include "HPcalc.h"
#include "interface.h"
#include "interface-vars.h"
#include "hex-oct.h"
#include "change.h"

/* local function prototypes */
void ResetDisplay(USHORT);
void UpdateEntryHex(UCHAR);
void DoEnterHex(void);
void DoBackSpaceHex(void);
void EntryToStackHex(void);




void ProcessHexCommand(SHORT comm)
{
   double       temp;

    if (bShiftMode) {
        bShiftMode = FALSE;
        WinSetWindowText(hwndSmode, "");

        EntryToStackHex();
        bLift = TRUE;

        switch (comm ) {
        case K_BS: /* CLx */
           if (bError) {
              UpdateDisplay(stack[0]);
           } else {
              UpdateDisplay(0.0);
              bLift = FALSE;
           } /* endif */
           break;
        case K_DOT: /* lastx */
           LiftStack();
           UpdateDisplay(lastx);
           break;
        default:
        }
    } else {
       CHAR     ch;
        /* Stack Lift Disable or Neutral command keys */
        switch (comm ) {
        case K_0: case K_1: case K_2: case K_3: case K_4: case K_5:
        case K_6: case K_7:
           ch = '0' + comm - K_0;
           UpdateEntryHex(ch);
           return ;
           break;
        case K_8: case K_9:
           ch = '0' + comm - K_0;
           if (uBinMode != MODE_OCT) {
              UpdateEntryHex(ch);
           } /* endif */
           return;
           break;
        case K_SIG: case K_1X: case K_ROO: case K_LOG: case K_LN:
           ch = 'A' + comm - K_SIG;
           if (uBinMode == MODE_HEX) {
              UpdateEntryHex(ch);
           } /* endif */
           return;
           break;
        case K_TAN:
           ch = 'F';
           if (uBinMode == MODE_HEX) {
              UpdateEntryHex(ch);
           } /* endif */
           return;
           break;
        case K_ENT:
           DoEnterHex();
           return ;
           break;
        case K_BS:
           if (bError) {
              UpdateDisplay(stack[0]);
           } else {
              DoBackSpaceHex();
           } /* endif */
           return ;
           break;
        case K_CHS:
           DoChs();
           return ;
           break;
        }

        /* the following function end entry mode and enable stack lift */
        EntryToStackHex();
        bLift = TRUE;

        switch (comm ) {
        case K_AMODE:
           switch (uBinMode) {
           case MODE_OCT:
              uBinMode = MODE_DEC;
              WinSetWindowText(hwndAmode, "DEC");
              ResetDisplay(uBinMode);
              break;
           case MODE_DEC:
              uBinMode = MODE_HEX;
              WinSetWindowText(hwndAmode, "HEX");
              ResetDisplay(uBinMode);
              break;
           case MODE_HEX:
              uBinMode = MODE_OCT;
              WinSetWindowText(hwndAmode, "OCT");
              ResetDisplay(uBinMode);
              break;
           default:
           } /* endswitch */
           UpdateDisplay(stack[0]);
           ShowHexOct(uBinMode);
/*           WinInvalidateRect(hwndClient, NULL, TRUE);   force redraw */
           break;
        case K_RD:
           RollDown();
           break;
        case K_RU:
           RollUp();
           break;
        case K_MIN:
           lastx = stack[0];
           temp = (int)(stack[1]) - (int)(stack[0]);
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_PLU:
           lastx = stack[0];
           temp = (int)stack[1] + (int)stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_MUL:
           lastx = stack[0];
           temp = (int)stack[1] * (int)stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_DIV:
           if (stack[0] == 0.0) {
              WinSetWindowText(hwndDisplay, DATAERROR);
              bError = TRUE;
           } else {
              lastx = stack[0];
              temp = (int)stack[1] / (int)stack[0];
              DropStack();
              UpdateDisplay(temp);
           }
           break;
        case K_SIN:
           temp = (int)stack[1] & (int)stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_COS:
           temp = (int)stack[1] | (int)stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_EEX:
           temp = (int)stack[1] ^ (int)stack[0];
           DropStack();
           UpdateDisplay(temp);
           break;
        case K_XY:
           temp = stack[1];
           stack[1] = stack[0];
           UpdateDisplay(temp);
           UpdateYZT();
           break;
        case K_XEQ: /* left shift */
           lastx = stack[0];
           UpdateDisplay(((int)stack[0]) << 1);
           ResetEntry();
           break;
        case K_SST: /* right shift */
           lastx = stack[0];
           UpdateDisplay(((int)stack[0]) >> 1);
           ResetEntry();
           break;
        case K_DOT: /* one's complement */
           lastx = stack[0];
           UpdateDisplay(~((int)stack[0]));
           ResetEntry();
           break;
        case K_STO:
           WaitGetNum(MODE_STO);
           break;
        case K_RCL:
           WaitGetNum(MODE_RCL);
           break;
        default:
        }
    } /* endif */
}


void ProcessKeyBoardHex(UCHAR ch, USHORT fs, USHORT vkey)
{

      switch (ch) {
      case '0':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_0), 0);
         break;
      case '1':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_1), 0);
         break;
      case '2':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_2), 0);
         break;
      case '3':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_3), 0);
         break;
      case '4':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_4), 0);
         break;
      case '5':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_5), 0);
         break;
      case '6':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_6), 0);
         break;
      case '7':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_7), 0);
         break;
      case '8':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_8), 0);
         break;
      case '9':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_9), 0);
         break;
      case '+':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_PLU), 0);
         break;
      case '-':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_MIN), 0);
         break;
      case '*':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_MUL), 0);
         break;
      case '/':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_DIV), 0);
         break;
      case '.':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_DOT), 0);
         break;
      case 'a': case 'A':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_SIG), 0);
         break;
      case 'b': case 'B':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_1X), 0);
         break;
      case 'c': case 'C':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_ROO), 0);
         break;
      case 'd': case 'D':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_LOG), 0);
         break;
      case 'e': case 'E':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_LN), 0);
         break;
      case 'f': case 'F':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_TAN), 0);
         break;

      case 'h': case 'H':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_CHS), 0);
         break;
      case 'l': case 'L':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_DOT), 0);
         break;
      case 'm': case 'M':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_AMODE), 0);
         break;
      case 'n': case 'N': case'&':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_SIN), 0);
         break;
      case 'o': case 'O':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_STO), 0);
         break;
      case 'r': case 'R':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_RCL), 0);
         break;
      case 'x': case 'X':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_XY), 0);
         break;
      case '|':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_COS), 0);
         break;
      case '^':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_EEX), 0);
         break;
      case '<':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_XEQ), 0);
         break;
      case '>':
         WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_SST), 0);
         break;
      default: 
         switch (vkey) {
         case VK_CTRL:
            if (fs & KC_PREVDOWN) {        /* key repeat */
               break;      /* early break from switch(vkey) */
            } /* endif */
            WinPostMsg(hwndClient, WM_COMMAND, MPFROMSHORT(K_GOL), 0);
            break;
         default:
            break;
         } /* endswitch */
         break;
      }
}


void ResetDisplay(USHORT mode)
{
   CHAR         buf[MAXBUF];
   SHORT        i;

   for (i=0; i<3; i++) {
      stack[i] = (int)(stack[i]);
   } /* endfor */

   FormatValHex(stack[0], buf);
   WinSetWindowText(hwndDisplay, buf);
   FormatValHex(stack[1], buf);
   WinSetWindowText(hwndDispY, buf);
   FormatValHex(stack[2], buf);
   WinSetWindowText(hwndDispZ, buf);
   FormatValHex(stack[3], buf);
   WinSetWindowText(hwndDispT, buf);
   
}


void FormatValHex(double val, PSZ buf)
{
   int  data;

   data = val;
   switch (uBinMode) {
   case MODE_DEC:
      sprintf(buf, "%13d      %c", data, 0);
      break;
   case MODE_HEX:
      sprintf(buf, "%13x      %c", data, 0);
      while ((*buf)) {
         if (*buf >= 'a') {
            *buf -= 'a' - 'A';
         } /* endif */
         buf++;
      } /* endwhile */
      break;
   case MODE_OCT:
      sprintf(buf, "%13o      %c", data, 0);
      break;
   default:
     break;
   } /* endswitch */

}



void UpdateEntryHex(UCHAR ch)
{
   USHORT        maxDigits=0;

   if (!bEntryMode && bLift) {
      LiftStack();
   } /* endif */

   switch (uBinMode) {
   case MODE_DEC:
      maxDigits = 10;
      if (ch > '9') {
         return;
      } /* endif */
      break;
   case MODE_HEX:
      maxDigits = 8;
      break;
   case MODE_OCT:
      maxDigits = 11;
      if (ch > '7') {
         return;
      } /* endif */
      break;
   default:
     break;
   } /* endswitch */

      if (numdigits < maxDigits -1) {
         (numdigits) ++;
         *(szDigits + numdigits) = ch;
         *(szDigits + numdigits + 1) = '_';
      } else if (numdigits < maxDigits) {
         (numdigits) ++;
         *(szDigits + numdigits) = ch;
      } /* endif */

   bEntryMode = TRUE;
   SetDisplay(0.0);
}


void DoEnterHex(void)
{
   if (bEntryMode) {
      EntryToStackHex();
      if (bLift) {
         LiftStack();
      } /* endif */
      UpdateDisplay(stack[0]);
   } else {
      LiftStack();
   } /* endif */
   bLift = FALSE;
}


void DoBackSpaceHex(void)
{
   double       dispVal=0;
   USHORT        maxDigits=0;

   switch (uBinMode) {
   case MODE_DEC:
      maxDigits = 10;
      break;
   case MODE_HEX:
      maxDigits = 8;
      break;
   case MODE_OCT:
      maxDigits = 11;
      break;
   default:
     break;
   } /* endswitch */

   if (bEntryMode) {
         if (numdigits == 0) {
            ResetEntry();
            dispVal = 0.0;
         } else if (numdigits == 1) {
               ResetEntry();
               dispVal = 0.0;
               bLift = FALSE;
         } else if (numdigits == maxDigits ){
               *(szDigits + numdigits) = '_';
               (numdigits) --;
         } else {
               *(szDigits + numdigits) = '_';
               *(szDigits + numdigits + 1) = ' ';
               (numdigits) --;
         } /* endif */
   } else {
      dispVal = 0.0;
      bLift = FALSE;
   } /* endif */

   SetDisplay(dispVal);
}


void EntryToStackHex(void)
{
   double       temp=0;
   int          itemp=0;

   if (bEntryMode) {
      switch (uBinMode) {
      case MODE_DEC:
         sscanf(szDigits, "%d", &itemp);
         break;
      case MODE_HEX:
         sscanf(szDigits, "%x", &itemp);
         break;
      case MODE_OCT:
         sscanf(szDigits, "%o", &itemp);
         break;
      default:
        break;
      } /* endswitch */
      temp = itemp;

      ResetEntry();
      stack[0] = (int)temp;
   } /* endif */
}


