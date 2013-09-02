=======================================================================
HPcalc        for OS/2 2.x, 3.x
-----------------------------------------------------------------------
version 0.97


Copyright (c) Les Chan, 1993-1995

email (internet): ae151@freenet.carleton.ca
=======================================================================

 ********
* NOTICE * <----------------------------------------------------------<
 ********
    If you have access to email and if you have not already done so, you are
required to send me a brief message stating the version of HPcalc you are
using and where you onbtained it. You only need to do this for the first
version you use. This is only so that I personally have some idea of the
number of users of this program. This is not to gauge the market for
shareware, this and future versions HPcalc for OS/2 will remain a free program.
Also, the more people that send email the more likely I will update the program.


Table of Contents
=================
Notice
Description
Installation
Numlock Information
Keyboard shortcuts
Keyboard shortcuts for DEC-HEX-OCT mode
Statistical Functions
Customization
Contents of Archive
Licensing
Planned features for future versions
History of changes


Description
===========
    This program is an Free RPN calculator with a layout similar to that of
the HP 41c.  HPcalc is meant to be a simple scientific calculator and does not
have programmability unlike the real HP 41c calculator.  Thus all the functions
which pertain to programming are absent.  Although there are additional 
functions/modes not on the real 41.   The keyboard and mouse may be 
used to operate this calculator.

    The startup size of HPcalc is set up for 1024x768. For those who prefer 
a smaller window size, there is a configuration submenu
under the File menu item.  Also configurable is the option to display
the full XYZT stack.

    To use Decimal to Hexadecimal to Octal calculation and conversion modes,
select it from the Functions menu.  When in the HEX-DEC-OCT mode all
operations are performed on signed 32 bit numbers.

    An ini file is used for constant memory. The size and location of the
window is saved on exit.  All data registers are saved as well as the
display and angle modes. 


Installation
============
HPcalc.exe can reside in any directory.

    A constant memory file called HPcalc.INI is created in the same directory
where HPcalc.EXE is located.  If an HPcalc.INI is found in the current directory,
it will be used instead.  As a third alternate, the INI file may be used by
specifying it as a parameter on the command line or with program objects. eg.

[C:\SOMEDIR] HPcalc d:\location\HPcalc.ini

This allows you to setup a normal calculator program object and
a Hexadecimal calculator, etc.
    
Note: you may use the os2 defined file C:\NOWHERE  as a valid ini file
if you do not want to have constant memory operation.

Note: 1
If you use some code page other than 437(US) as the default, some symbols such
as the Sigma may not appear correctly. The solution is to change the code page
before you start HPcalc, you may set up a command file to start HPcalc,
an example command file is:

CHCP 437
START C:\pathtocalculator\HPcalc.exe
CHCP 850

Note: 2
The following abstract from the OS/2 help applies:

 If you try to start a program from the program-name 
 choice of the pop-up menu of a folder and the 
 program does not start or displays an error message, 
 you can stop the name of the folder from being sent 
 to the program by doing the following: 

    1. Point to the program object whose name was 
       added as a choice on the pop-up menu. 
    2. Click mouse button 2. 
    3. Select Settings. 
    4. Select the Program tab. 
    5. Type the following in the Parameters field: 

          %
       
    6. Close the Settings notebook. 
  
Numlock Information
===================
I have had some request to turn numlock on when HPcalc starts up. I had
intended to inplement this feature when I found out how to do it. But
upon further thought I have decided that this is a global issue for
the desktop. There are people that want the numlock on all the time like
me but there also those who do not want it on.

For those who want numlock on I think the optimal solution would have
been for IBM to place such a option in the desktop settings. But next
best thing is to run a program from the startup folder or in startup.cmd
file to turn it on. I have found a nice small and free program written by 
a team os/2 member which does this and more called keybset.zip at
ftp-os2.nmsu.edu(128.123.35.151):/os2/xxxx


Keyboard shortcuts
==================
HPcalc is not case sensitive.
p - pi                        Down arrow - Roll down     
q - square root               Up arrow - Roll Up         
g - LOG                       Shift-Insert - paste       
n - LN                        Insert - paste             
s - SIN                       Shift-Delete - copy        
c - COS                       Delete - paste             
t - TAN                       Enter - enter              
o - STO                       Backspace - backspace      
r - RCL                       Left arrow - backspace     
h - CHS                       Ctrl - shift               
e - EEX                       - - minus                  
l - Lastx                     + - plus                   
k - Cls (Clear Stack)         * - multiply               
v - 1/x (1 oVer x)            / - divide                 
u - ä+                        % - %                      
m - MOD                       ^ - y^x                    
a - toggle angle modes        . and , - decimal separator

Keyboard shortcuts for DEC-HEX-OCT mode
=======================================
a-f - Hexadecimal digits
m - change between DEC-HEX-OCT modes
n, & - and
| - or
^ - xor
< - shift left
> - shift right


Statistical Functions
=====================
Slope - slope of linear regression line
Intercept - intercept of linear regression line
Correlation - Correlation factor
X' - estimated X given Y from linear regression
Y' - estimated Y given X from linear regression
pop.SDEV - population Standard deviation
yPx - permutations : y!/(y-x)!
yCx - combinations : y!/(x!(y-x)!)


Customization
=============
-> Size of the HPcalc Window
There are two sizes that is available for HPcalc a large and a small size.
The size is changed by toggling the Menu item File->Configuration->Small Window.

-> Display of XYZT
HPcalc can display the standard X stack register or the complete XYZT stack.
This is changed by toggling the Menu item File->Configuration->XYZT Mode.

-> Thousands Separator
HPcalc can separate thousands by using a ",".
This is changed by toggling the Menu item File->Configuration->1000s Separator.

-> Some Customization of Fonts
There are five separate fonts that can be save for each of the large and small
displays. The procedure to change the fonts is by the use of drag and drop.
Step 1 has to be performed first in order for the fonts to be saved correctly,
although it may be omitted if you wish to only change fonts in steps 2-4.
Step 0 can be done at any time before step 5)

0) drop the font onto the menu bar to change the menu font.
1) drop the font onto the background to change all the gold text as well as all
the functions(sin, cos, etc.)
2) drop the font onto the <- key to change the back space as well as the
four arithmetic operators +, -, *, /
3) drop the font onto the 0 button to change the font for all 10 digits
4) drop the font onto the X display register to change the font for
all four stack registers.
5) Exit the program from the Menu File->Exit or F3 to save the changes
abort the changes by alt-F4 or chose close from the command menu.

The program must be exited and restarted for the font changes to be properly
displayed. 

-> Restoring to the Initial State
If things are really messed up (eg. you chose some really horrible fonts and
can't get back to something reasonable) just delete the ini file and
the program will use built in defaults to start HPcalc.


Contents of Archive
===================
HPcalc.exe              The executable
ReadMe                  This file
file_id.diz             Short description for BBS systems

Verification information from Infozip's zip/unzip:
 Length  Method   Size  Ratio   Date    Time   CRC-32     Name ("^" ==> case
 ------  ------   ----  -----   ----    ----   ------     ----   conversion)
  74752  Defl:X   31774  58%  10-06-95  23:30  2586a7d5   HPcalc.exe

Licensing
=========
This program is Provided free of charge.
Although this program is free, donations are welcome and should
speed up bug fixes and addition of features by enabling purchase of
better tools and documentation.  They can be sent to the author at:

        Les Chan
        710 Melbourne Ave. Unit 3
        Ottawa, ON, Canada
        K2A 4C8

If you send a donation and have an email address, I will
notify and/or email you new versions as they become available.
Bug reports and suggestions are welcome regardless.

email(internet):  ae151@freenet.carleton.ca


NO WARRANTY
===========
   BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.
   IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.



Planned features for future versions
====================================
Listed in no specific order of priorities

- saving of drag and drop colors
  Note: I am having trouble with this, if you know about the difference
  between palette and RGB colors for use with Presentation Parameters, 
  please contact me if you want to see this feature.
- user configurable constants


History of changes
==================
- = bug fix
+ = added feature
# = operational change

version 0.97 - 1995 October (Released)
------------
- disable menu functions in DEC-HEX_OCT mode

version 0.96 - 1995 October
------------
- copying to clipboard has been fixed
# the top left corner now stays put when changing configurations which
  affect the size of the window


version 0.95 - 1995 March (Released)
------------
- icon for the program was not displayed in program object, now works
- miles-km conversions were out by a factor of 1000
- going from 2.5 (etc.) to HMS and back to HR gave incorrect results due
  to LSB behaviour in division.
- invalid menu items now disabled in HEX-OCT mode
+ you can now use the comma for entering the decimal separator
+ Linear regression and estimation
+ factorial, Population sDev, clear stack
+ combinations and permutations
+ labels for XYZT registers

version 0.94 - 1995 February (Released)
------------
- Menu Title "Functions" Shortened to "Funcs" to fix display problem with
  small windows at 1280x1024
+ saving of Fonts
+ as the default, HPcalc.ini is now created in the directory where HPcalc.exe
  is located but it still will use the HPcalc.INI if it exist in the current 
  directory
+ Hyperbolic functions
+ Some Constants
+ some metric conversions

version 0.93 - 1994 May 23 (Released)
------------
- keys that require shift not working are fixed (the keys that did on work
  vary with the keyboard used, ie. on the US keyboard <shift><=+>)
+ add instructions for people not using the 437(US) code page

Version 0.92 1994 March 10 (Released)
---------------------------
+ thousands separators
+ ->HMS and ->HR
+ add FEX mode (same as FIX mode except that overflows and underflows into
  ENG instead of SCI)
+ add Roll Up function to up arrow.
+ add MOD(ulus) function
- fixed bug with large number of digits copyed to clipboard in FIX mode
- fixed cut and paste problems in DEC-HEX-OCT modes
- fixed cut and paste menu displaying the wrong accelerator keys

Version 0.9  1993 August 8 (Released)
---------------------------
- Hexadecimal <-> Octal <-> Decimal conversion modes
  and associated functions
- summation functions

Version 0.8  1993 April 17 (Released)
---------------------------
- Constant memory mode operation
- Large and Small Window mode with appropriate fonts
- FIX mode works again
- no longer requires emx.dll
- xyzt display option
- yellow shift key
- eng mode displays properly

Version 0.7a  1993 March 25 (Released)
---------------------------
-window location fixed, so that whole window is displayed on VGA
-pressing EEX by itself and then performing an operation gave 
 incorrect results, now fixed.
-double keys fixed, work under xfeel.
-change to nonsizable border since, sizing is not valid for now
-better looking icons:   
    The sysmenu icon is now a more legible black
 and background color icon, like the standard os2 windows.
    Drop shadow for main icon (if you created
 a program object for previous versions; to get the new main icon,
 Go to settings, delete last 'E' from filename, click on parameters,
 add 'E' back to filename.)
-Add a few additional keybaord accelerators

Version 0.7   1993 March (Released)
------------------------
-Initial beta release

