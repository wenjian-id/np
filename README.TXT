======================
      NaviPOWM
======================

todo: brief description

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
