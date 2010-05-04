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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "./" /I "../../src/common" /I "../../src/windows/common" /I "../../src/windows/native" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "./" /I "../../src/common" /I "../../src/windows/common" /I "../../src/windows/native" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
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

SOURCE=..\..\src\windows\native\CXBitmap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXDeviceContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXExactTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\CXGPSDClient.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXMainWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXMutex.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXRWLock.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXSemaphore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\CXSerial.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXWorkRequestThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\OSSpecific.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\TargetIncludes.hpp
# End Source File
# End Group
# Begin Group "Windows specific CPP"

# PROP Default_Filter "CPP"
# Begin Source File

SOURCE=..\..\src\windows\native\CXBitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXDeviceContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXExactTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\CXGPSDClient.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXMainWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXMutex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXRWLock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXSemaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\CXSerial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\CXWorkRequestThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\Main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\common\OSSpecific.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\windows\native\TargetIncludes.cpp
# End Source File
# End Group
# Begin Group "Common HPP"

# PROP Default_Filter "HPP"
# Begin Source File

SOURCE=..\..\src\common\CoordConstants.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CoordConversion.h
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXArea.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXAreaColorHolder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXArray.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXBuffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXCache.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXCoor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXDebugInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXDirection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXFile.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXFileIni.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSCourseInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannel.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelFile.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelGPSD.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelSerial.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSPosInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocol.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocolGPSD.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocolNMEA.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSQualityInfo.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSRecvThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXHysterezis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBar.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarBottom.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarCommon.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarRouting.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarSpeed.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarTop.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXKeyVal.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXLocatorThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXLoopThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapContainer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapHashSimple.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapLoaderThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapMovingDetails.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainter2D.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterDoubleBuffered.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterTest.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapSection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapSimple.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapSort.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMutexLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNaviData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNaviPOWM.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNMEA.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNode.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXOptions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPen.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPenHolder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPOIVisibilityDescriptor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPOWMMap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXReadLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXRect.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXRGB.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSatelliteData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaver.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaverGPX.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaverRaw.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSmartPtr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSpeedCalculator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXStringASCII.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXStringUTF8.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXTimeStampData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXTrackLog.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXTransformationMatrix.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTCTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTMCoor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTMSpeed.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWatchdogThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWay.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWriteLocker.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IBitmap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IDeviceContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IExactTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IGPSDClient.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IMainWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IMutex.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IRWLock.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISemaphore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISerial.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IWindow.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IWorkRequestThread.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Utils.hpp
# End Source File
# End Group
# Begin Group "Common CPP"

# PROP Default_Filter "CPP"
# Begin Source File

SOURCE=..\..\src\common\CoordConversion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXArea.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXAreaColorHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXCoor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXDebugInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXDirection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXFileIni.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSCourseInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelGPSD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSInputChannelSerial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSPosInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocolGPSD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSProtocolNMEA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSQualityInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXGPSRecvThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarBottom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarCommon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarRouting.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarSpeed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXInfoBarTop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXLocatorThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXLoopThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapLoaderThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapMovingDetails.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainter2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterDoubleBuffered.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapPainterThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMapSection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXMutexLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNaviData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNaviPOWM.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNMEA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXOptions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPenHolder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPOIVisibilityDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXPOWMMap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXReadLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXRGB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSatelliteData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaver.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaverGPX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSaverRaw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXSpeedCalculator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXStringASCII.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXStringUTF8.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXTrackLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXTransformationMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTCTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTMCoor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXUTMSpeed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWatchdogThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWay.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\CXWriteLocker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IBitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IMainWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISemaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\ISerial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\IWorkRequestThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\common\Utils.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\common\Images\MainIcon.ico
# End Source File
# Begin Source File

SOURCE=.\NaviPOWM.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Target
# End Project
