======================
      NaviPOWM
======================
NaviPOWM is a car navigation system capable of running on a variety of operating 
systems. At the time, only OSM based map data is supported. Realtime routing engine
is planned in a later version. Geocaching and city guide functionality are also
planned.

======================
Compiling NaviPOWM
======================
NaviPOWM can be compiled under Windows (with or without Qt) and Linux (with Qt)

----------------------------------------------
Compiling under Windows using Visual Studio 6:
----------------------------------------------
1. A workspace and project file can be found in directory 
   NaviPOWM\Windows\VisualStudio6
2. Open workspace and compile. Qt is not needed.

-------------------------------------------
Compiling under Windows using MinGW Studio:
-------------------------------------------
1. A workspace and project file can be found in directory 
   NaviPOWM\Windows\MinGW
2. Open workspace and compile. Qt is not needed.

---------------------------------------------------
Compiling under Windows using MinGW Studio with Qt:
---------------------------------------------------
1. A workspace and project file can be found in directory 
   NaviPOWM\Qt\MinGW
2. Make sure includes and libraries are accesible from MinGWStudio
3. Open workspace and compile. Qt (at least 4.3.2) is needed.

------------------------------------------------------------
Compiling for Windows Mobile using embedded Visual Studio 4:
------------------------------------------------------------
1. A workspace and project file can be found in directory 
   NaviPOWM\WindowsMobile\eVC4
2. Open workspace and compile. Qt is not needed.

------------------------------
Compiling under Linux with Qt:
------------------------------
1. Go to directory Qt\KDevelop
2. run qmake
3. run make clean
4. run make 




======================
Running NaviPOWM
======================
If NaviPOWM is not installed by a installer software, you have to ensure some
directories are created manually and some file copied into them. When using an
installer this steps are done automatically.

--------------------
Directory structure:
--------------------
Let's consider "your/path/to/NaviPOWM" as the directory you want NaviPOWM to reside.
To work properly, NaviPOWM needs the following subdirectories (case sensitive!):
1. Icons
2. Maps
3. Save

The following files must be copied:
1. common/Images/info.bmp to Icons/info.bmp
2. common/Images/quit.bmp to Icons/quit.bmp
3. common/Images/saveon.bmp to Icons/saveon.bmp
4. common/Images/saveoff.bmp to Icons/saveoff.bmp
5. common/Images/logo.bmp to Icons/logo.bmp
6. common/Config/navipowm.ini to navipowm.ini
7. and finally the executable itself


---------
INI file:
---------
[directories]
DirectoryIcons -> Subdirectory with icons
DirectoryMaps -> Subdirectory from which maps are loaded
DirectorySave -> Subdirectory in which GPS data is saved

[icons]
LogoName -> icon for start logo
InfoName -> icon for info button
QuitName -> icon for quit button
SaveOnName -> icon for save active state
SaveOffName -> icon for save inactive state

[config]
LogoTime -> time in ms for displaying logo when starting
FullScreen ->If on, a frameless maximized window is used, when off a normal window is used [on/off]
Northing -> If on, north is alway on top, else heading is on top [on/off]
InfoBarBottomHeight -> please don't touch [20]
InfoBarTopHeight -> please don't touch [20]

[Serial port for GPS input]
SerialPort -> serial port from which NMEA data is read.
Here some examples:
Windows: SerialPort = COM1
Windows Mobile (with trailing ':'): SerialPort = COM5:
Linux: SerialPort = /dev/ttyS1
DEMO mode: SerialPort = DEMO;2005042301.txt;1
When using DEMO mode, th first part is DEMO, followed by the filename and the
timeout (in seconds) between two GGA packets. Please take a closer look at the
used file.


-------------------
Operating NaviPOWM:
-------------------
1. Zooming is done by keys "<-" (left) and "->" (right) on Windows and Linux and 
   with the corresponding hard keys on PDFAs
2. An info screen is displayed when typing on the NaviPOWM icon in the top left
   corner of the screen.
3. A red floppy disk indicates "NO SAVING", a green one indicates that NaviPOWM 
   is saving all received NMEA data.
4. The exit button terminates NaviPOWM.
 
