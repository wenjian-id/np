# Microsoft Developer Studio Project File - Name="NaviPOWM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NaviPOWM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NaviPOWM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NaviPOWM.mak" CFG="NaviPOWM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NaviPOWM - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NaviPOWM - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NaviPOWM - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../common/src" /I "./" /I "../common/src" /I "../native/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msimg32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NaviPOWM - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../common/src" /I "./" /I "../common/src" /I "../native/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msimg32.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "NaviPOWM - Win32 Release"
# Name "NaviPOWM - Win32 Debug"
# Begin Group "Windows specific HPP"

# PROP Default_Filter "HPP"
# Begin Source File

SOURCE=..\native\src\CXBitmap.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXDeviceContext.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXExactTime.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXMainWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXMutex.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXRWLock.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXSemaphore.hpp
# End Source File
# Begin Source File

SOURCE=..\common\src\CXSerial.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXThread.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\CXWorkRequestThread.hpp
# End Source File
# Begin Source File

SOURCE=..\common\src\OSSpecific.hpp
# End Source File
# Begin Source File

SOURCE=..\native\src\TargetIncludes.hpp
# End Source File
# End Group
# Begin Group "Windows specific CPP"

# PROP Default_Filter "CPP"
# Begin Source File

SOURCE=..\native\src\CXBitmap.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXDeviceContext.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXExactTime.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXMainWindow.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXMutex.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXRWLock.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXSemaphore.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\common\src\CXSerial.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXThread.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXWindow.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\CXWorkRequestThread.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\Main.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\common\src\OSSpecific.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# Begin Source File

SOURCE=..\native\src\TargetIncludes.cpp
# ADD CPP /I "../common/src" /I "../native/src"
# End Source File
# End Group
# Begin Group "Common HPP"

# PROP Default_Filter "HPP"
# Begin Source File

SOURCE=..\..\common\src\CoordConstants.h
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CoordConversion.h
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXArea.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXAreaColorHolder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXArray.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXBuffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXCache.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXCoor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXDebugInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXDirection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXFile.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXFileIni.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSCourseInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannel.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelFile.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelGPSD.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelSerial.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSPosInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocol.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocolGPSD.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocolNMEA.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSQualityInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSRecvThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXHysterezis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBar.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarBottom.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarCommon.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarRouting.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarSpeed.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarTop.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXKeyVal.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXLocatorThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXLoopThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapContainer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapHashSimple.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapLoaderThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapMovingDetails.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainter2D.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterDoubleBuffered.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterTest.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapSection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapSimple.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapSort.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMutexLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNaviData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNaviPOWM.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNMEA.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNode.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXOptions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPen.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPenHolder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPOIVisibilityDescriptor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPOWMMap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXReadLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXRect.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXRGB.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSatelliteData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaver.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaverGPX.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaverRaw.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSmartPtr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSpeedCalculator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXStringASCII.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXStringUTF8.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXTimeStampData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXTrackLog.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXTransformationMatrix.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTCTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTMCoor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTMSpeed.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWatchdogThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWay.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWriteLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IBitmap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IDeviceContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IExactTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IMainWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IMutex.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IRWLock.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\ISemaphore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\ISerial.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IWorkRequestThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\Utils.hpp
# End Source File
# End Group
# Begin Group "Common CPP"

# PROP Default_Filter "CPP"
# Begin Source File

SOURCE=..\..\common\src\CoordConversion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXArea.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXAreaColorHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXCoor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXDebugInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXDirection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXFileIni.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSCourseInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelGPSD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSInputChannelSerial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSPosInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocolGPSD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSProtocolNMEA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSQualityInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXGPSRecvThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarBottom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarCommon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarRouting.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarSpeed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXInfoBarTop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXLocatorThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXLoopThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapLoaderThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapMovingDetails.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainter2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterDoubleBuffered.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapPainterThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMapSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXMutexLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNaviData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNaviPOWM.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNMEA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPenHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPOIVisibilityDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXPOWMMap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXReadLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXRGB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSatelliteData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaverGPX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSaverRaw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXSpeedCalculator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXStringASCII.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXStringUTF8.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXTrackLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXTransformationMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTCTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTMCoor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXUTMSpeed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWatchdogThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\CXWriteLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IBitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IMainWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\ISemaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\ISerial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\IWorkRequestThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\src\Utils.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\NaviPOWM.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Target
# End Project
