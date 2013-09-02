/* definitions for interface routintes */

#define MAXBUF  255

/* angle modes */
#define MODE_RAD        0
#define MODE_DEG        1
#define MODE_GRAD       2

/* display modes */
#define MODE_FIX        0
#define MODE_ENG        1
#define MODE_SCI        2
#define MODE_STO        3
#define MODE_RCL        4
#define MODE_MIN        5
#define MODE_PLU        6
#define MODE_MUL        7
#define MODE_DIV        8
#define MODE_FEX        9

/* dec oct hex modes */
#define MODE_DEC        0
#define MODE_OCT        1
#define MODE_HEX        2
#define MODE_BIN        3

/* define decimal states */
#define HAVEDOT         1
#define NODOT           0
#define DATAERROR       "DATA ERROR"

/* Global Variables */
#ifdef INTERFACE
BOOL    bShiftMode = FALSE, bGetNumMode = FALSE;
BOOL        fXyzt=FALSE, fHexOct = FALSE;
BOOL    fComma=FALSE;
USHORT  uNumMode = MODE_ENG, uGetNum;
USHORT  uAngleMode = MODE_DEG;
USHORT  uBinMode = MODE_DEC;
USHORT  uDispDigs = 4;
USHORT  bDot = 0;
USHORT  numdigits=0, numeex=0;
BOOL    bEexMode=FALSE, bEntryMode=FALSE, bLift=TRUE, bError=FALSE;
BOOL        fVgaSize=FALSE;
UCHAR   szDigits[]="              ";
UCHAR   szEex[] = "   ";
double  stack[]={0.0, 0.0, 0.0, 0.0}, lastx=0.0, memory[10];
double  summation[6];   /* sx, sx2, sy, sy2, sxy, n */
#else
extern BOOL    bShiftMode , bGetNumMode;
extern BOOL        fXyzt, fHexOct ;
extern BOOL    fComma;
extern USHORT  uNumMode, uGetNum;
extern USHORT  uAngleMode;
extern USHORT  uBinMode;
extern USHORT  uDispDigs;
extern USHORT  bDot;
extern USHORT  numdigits, numeex;
extern BOOL    bEexMode, bEntryMode, bLift, bError;
extern BOOL        fVgaSize;
extern UCHAR   szDigits[];
extern UCHAR   szEex[];
extern double  stack[], lastx, memory[];
extern double  summation[];   /* sx, sx2, sy, sy2, sxy, n */
#endif


/* Function prototypes */
void UpdateDisplay(double);
void LiftStack(void);
void DoChs(void);
void EntryToStack(void);
void RollDown(void);
void RollUp(void);
void DropStack(void);
void UpdateYZT(void);
void WaitGetNum(USHORT);
void ResetEntry(void);
void SetDisplay(double);

