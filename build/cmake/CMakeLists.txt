# Name of the project
project( OSM2POWM )

cmake_minimum_required( VERSION 2.4.8)

# This project requires Qt4
find_package( Qt4 REQUIRED )

# make a release
SET ( CMAKE_BUILD_TYPE release )

# Enable all compiler warnings
add_definitions( -Wall )

# include directories
include_directories( 
  ../../src/common
  ../../src/qt
  ../../src/linux
)

# All header files go here
set (HDR_FILES
  ../../src/common/CoordConstants.h
  ../../src/common/CoordConversion.h
  ../../src/common/CXWatchdogThread.hpp
  ../../src/common/CXWriteLocker.hpp
  ../../src/common/CXPen.hpp
  ../../src/common/CXMapSort.hpp
  ../../src/common/CXMapPainterDoubleBuffered.hpp
  ../../src/common/CXTimeStampData.hpp
  ../../src/common/CXMapPainterTest.hpp
  ../../src/common/CXStringASCII.hpp
  ../../src/common/CXMapSection.hpp
  ../../src/common/CXKeyVal.hpp
  ../../src/common/CXNode.hpp
  ../../src/common/CXPOWMMap.hpp
  ../../src/common/IBitmap.hpp
  ../../src/common/CXCoor.hpp
  ../../src/common/CXStringUTF8.hpp
  ../../src/common/IDeviceContext.hpp
  ../../src/common/CXLoopThread.hpp
  ../../src/common/CXReadLocker.hpp
  ../../src/common/CXInfoBar.hpp
  ../../src/common/CXBuffer.hpp
  ../../src/common/ISerial.hpp
  ../../src/common/CXMapLoaderThread.hpp
  ../../src/common/CXMapPainter2D.hpp
  ../../src/common/CXMapPainterThread.hpp
  ../../src/common/CXNMEA.hpp
  ../../src/common/CXNaviData.hpp
  ../../src/common/IThread.hpp
  ../../src/common/IWorkRequestThread.hpp
  ../../src/common/CXInfoBarSpeed.hpp
  ../../src/common/CXDebugInfo.hpp
  ../../src/common/CXUTMSpeed.hpp
  ../../src/common/CXOptions.hpp
  ../../src/common/CXInfoBarTop.hpp
  ../../src/common/CXNaviPOWM.hpp
  ../../src/common/CXMapContainer.hpp
  ../../src/common/CXSpeedCalculator.hpp
  ../../src/common/IMutex.hpp
  ../../src/common/CXTransformationMatrix.hpp
  ../../src/common/IWindow.hpp
  ../../src/common/CXMapHashSimple.hpp
  ../../src/common/CXInfoBarCommon.hpp
  ../../src/common/CXLocatorThread.hpp
  ../../src/common/CXTrackLog.hpp
  ../../src/common/CXSatelliteData.hpp
  ../../src/common/CXRect.hpp
  ../../src/common/CXFile.hpp
  ../../src/common/CXWay.hpp
  ../../src/common/CXArea.hpp
  ../../src/common/CXPenHolder.hpp
  ../../src/common/CXAreaColorHolder.hpp
  ../../src/common/ISemaphore.hpp
  ../../src/common/CXCache.hpp
  ../../src/common/CXSmartPtr.hpp
  ../../src/common/IMainWindow.hpp
  ../../src/common/CXGPSRecvThread.hpp
  ../../src/common/CXFileIni.hpp
  ../../src/common/CXMapPainter.hpp
  ../../src/common/CXInfoBarBottom.hpp
  ../../src/common/CXArray.hpp
  ../../src/common/IExactTime.hpp
  ../../src/common/CXUTMCoor.hpp
  ../../src/common/IRWLock.hpp
  ../../src/common/Utils.hpp
  ../../src/common/CXMutexLocker.hpp
  ../../src/common/CXRGB.hpp
  ../../src/common/CXMapSimple.hpp
  ../../src/common/CXHysterezis.hpp
  ../../src/common/CXMapMovingDetails.hpp
  ../../src/common/CXUTCTime.hpp
  ../../src/common/CXPOIVisibilityDescriptor.hpp
  ../../src/common/CXDirection.hpp
  ../../src/common/CXGPSProtocol.hpp
  ../../src/common/CXGPSProtocolNMEA.hpp
  ../../src/common/CXGPSProtocolGPSD.hpp
  ../../src/common/CXGPSInputChannel.hpp
  ../../src/common/CXGPSInputChannelSerial.hpp
  ../../src/common/CXGPSInputChannelFile.hpp
  ../../src/common/CXGPSInputChannelGPSD.hpp
  ../../src/common/CXGPSPosInfo.hpp
  ../../src/common/CXGPSCourseInfo.hpp
  ../../src/common/CXGPSQualityInfo.hpp
  ../../src/common/CXSaver.hpp
  ../../src/common/CXSaverRaw.hpp
  ../../src/common/CXSaverGPX.hpp
  ../../src/common/CXInfoBarRouting.hpp
  ../../src/common/IGPSDClient.hpp
  ../../src/qt/CXRWLock.hpp
  ../../src/qt/CXMainWindow.hpp
  ../../src/qt/TargetIncludes.hpp
  ../../src/qt/CXThread.hpp
  ../../src/qt/CXBitmap.hpp
  ../../src/qt/CXMutex.hpp
  ../../src/qt/CXSemaphore.hpp
  ../../src/qt/CXExactTime.hpp
  ../../src/qt/CXWindow.hpp
  ../../src/qt/CXWorkRequestThread.hpp
  ../../src/qt/CXDeviceContext.hpp
  ../../src/linux/OSSpecific.hpp
  ../../src/linux/CXSerial.hpp
  ../../src/linux/CXGPSDClient.hpp
  ../../src/linux/CXGPSDClientBase.hpp
  ../../src/linux/CXGPSDClientNoVersion.hpp
  ../../src/linux/CXGPSDClient3.hpp
  ../../src/linux/CXGPSDClient4.hpp
)

# All cpp files go here
set(SRC_FILES
  ../../src/common/IBitmap.cpp
  ../../src/common/CXMapSection.cpp
  ../../src/common/CXWatchdogThread.cpp
  ../../src/common/CXTrackLog.cpp
  ../../src/common/CXSatelliteData.cpp
  ../../src/common/IWorkRequestThread.cpp
  ../../src/common/CXStringUTF8.cpp
  ../../src/common/Utils.cpp
  ../../src/common/CXPOWMMap.cpp
  ../../src/common/CXInfoBarSpeed.cpp
  ../../src/common/ISemaphore.cpp
  ../../src/common/CXMapPainter.cpp
  ../../src/common/CXMapContainer.cpp
  ../../src/common/CXFileIni.cpp
  ../../src/common/CoordConversion.cpp
  ../../src/common/CXFile.cpp
  ../../src/common/CXNode.cpp
  ../../src/common/CXMapPainter2D.cpp
  ../../src/common/CXMutexLocker.cpp
  ../../src/common/CXInfoBar.cpp
  ../../src/common/IThread.cpp
  ../../src/common/CXSpeedCalculator.cpp
  ../../src/common/CXInfoBarTop.cpp
  ../../src/common/CXLoopThread.cpp
  ../../src/common/CXPen.cpp
  ../../src/common/CXOptions.cpp
  ../../src/common/CXWay.cpp
  ../../src/common/CXArea.cpp
  ../../src/common/CXMapLoaderThread.cpp
  ../../src/common/CXMapPainterThread.cpp
  ../../src/common/CXInfoBarCommon.cpp
  ../../src/common/CXNMEA.cpp
  ../../src/common/CXLocatorThread.cpp
  ../../src/common/CXNaviPOWM.cpp
  ../../src/common/CXPenHolder.cpp
  ../../src/common/CXAreaColorHolder.cpp
  ../../src/common/CXGPSRecvThread.cpp
  ../../src/common/CXRGB.cpp
  ../../src/common/IMainWindow.cpp
  ../../src/common/CXInfoBarBottom.cpp
  ../../src/common/CXMapPainterTest.cpp
  ../../src/common/CXDebugInfo.cpp
  ../../src/common/CXUTMCoor.cpp
  ../../src/common/CXWriteLocker.cpp
  ../../src/common/CXUTMSpeed.cpp
  ../../src/common/CXNaviData.cpp
  ../../src/common/CXCoor.cpp
  ../../src/common/CXReadLocker.cpp
  ../../src/common/CXStringASCII.cpp
  ../../src/common/CXMapPainterDoubleBuffered.cpp
  ../../src/common/CXTransformationMatrix.cpp
  ../../src/common/ISerial.cpp
  ../../src/common/CXMapMovingDetails.cpp
  ../../src/common/CXUTCTime.cpp
  ../../src/common/CXPOIVisibilityDescriptor.cpp
  ../../src/common/CXDirection.cpp
  ../../src/common/CXGPSProtocol.cpp
  ../../src/common/CXGPSProtocolNMEA.cpp
  ../../src/common/CXGPSProtocolGPSD.cpp
  ../../src/common/CXGPSInputChannel.cpp
  ../../src/common/CXGPSInputChannelSerial.cpp
  ../../src/common/CXGPSInputChannelFile.cpp
  ../../src/common/CXGPSInputChannelGPSD.cpp
  ../../src/common/CXGPSPosInfo.cpp
  ../../src/common/CXGPSCourseInfo.cpp
  ../../src/common/CXGPSQualityInfo.cpp
  ../../src/common/CXSaver.cpp
  ../../src/common/CXSaverRaw.cpp
  ../../src/common/CXSaverGPX.cpp
  ../../src/common/CXInfoBarRouting.cpp
  ../../src/common/IGPSDClient.cpp
  ../../src/qt/CXMutex.cpp
  ../../src/qt/TargetIncludes.cpp
  ../../src/qt/CXDeviceContext.cpp
  ../../src/qt/Main.cpp
  ../../src/qt/CXSemaphore.cpp
  ../../src/qt/CXWindow.cpp
  ../../src/qt/CXWorkRequestThread.cpp
  ../../src/qt/CXBitmap.cpp
  ../../src/qt/CXRWLock.cpp
  ../../src/qt/CXThread.cpp
  ../../src/qt/CXExactTime.cpp
  ../../src/qt/CXMainWindow.cpp
  ../../src/linux/CXSerial.cpp
  ../../src/linux/OSSpecific.cpp
  ../../src/linux/CXGPSDClientBase.cpp
  ../../src/linux/CXGPSDClientNoVersion.cpp
  ../../src/linux/CXGPSDClient3.cpp
  ../../src/linux/CXGPSDClient4.cpp
)

# Includes the standard Qt libraries
include( ${QT_USE_FILE} )

add_executable( NaviPOWM ${SRC_FILES} ${HDR_FILES})

# Link Qt to the executable
target_link_libraries( NaviPOWM ${QT_LIBRARIES} gps) 
