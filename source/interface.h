/* Prototypes */
MRESULT ProcessCommand (HWND, ULONG, MPARAM, MPARAM);
MRESULT ProcessKeyboardChar (HWND, ULONG, MPARAM, MPARAM);
void InitializeDisplay(void);

/* Global Variables */
#ifdef INTERFACE
    HWND    hwndDisplay, hwndAmode, hwndSmode, hwndgol, hwndAbout, hwndHexOct,
            hwnd0, hwndbs,
            hwndDispY, hwndDispZ, hwndDispT, hwndClient, hwndFrame;
    HAB     hab;
#else
    extern HWND    hwndDisplay, hwndAmode, hwndSmode, hwndgol, hwndAbout, hwndHexOct,
            hwnd0, hwndbs,
            hwndDispY, hwndDispZ, hwndDispT, hwndClient, hwndFrame;
    extern HAB     hab;
#endif
