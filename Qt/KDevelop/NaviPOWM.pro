TEMPLATE = app 
TARGET = bin/NaviPOWM
CONFIG += warn_on \
          qt \
          thread \
          rtti \
QMAKE_CXXFLAGS += -Wall
INCLUDEPATH += src \
               ../../common/src/ \
               ../src/
CONFIG += release
CONFIG -= debug

SOURCES += ../../common/src/IBitmap.cpp \
../../common/src/CXMapSection.cpp \
../../common/src/CXWatchdogThread.cpp \
../../common/src/CXTrackLog.cpp \
../../common/src/CXSatelliteData.cpp \
../../common/src/IWorkRequestThread.cpp \
../../common/src/CXStringUTF8.cpp \
../../common/src/Utils.cpp \
../../common/src/CXPOWMMap.cpp \
../../common/src/CXInfoBarSpeed.cpp \
../../common/src/ISemaphore.cpp \
../../common/src/CXMapPainter.cpp \
../../common/src/CXMapContainer.cpp \
../../common/src/CXFileIni.cpp \
../../common/src/CoordConversion.cpp \
../../common/src/CXFile.cpp \
../../common/src/CXNode.cpp \
../../common/src/CXMapPainter2D.cpp \
../../common/src/CXMutexLocker.cpp \
../../common/src/CXInfoBar.cpp \
../../common/src/IThread.cpp \
../../common/src/CXSpeedCalculator.cpp \
../../common/src/CXInfoBarTop.cpp \
../../common/src/CXLoopThread.cpp \
../../common/src/CXPen.cpp \
../../common/src/CXOptions.cpp \
../../common/src/CXWay.cpp \
../../common/src/CXArea.cpp \
../../common/src/CXMapLoaderThread.cpp \
../../common/src/CXMapPainterThread.cpp \
../../common/src/CXInfoBarCommon.cpp \
../../common/src/CXNMEA.cpp \
../../common/src/CXLocatorThread.cpp \
../../common/src/CXNaviPOWM.cpp \
../../common/src/CXPenHolder.cpp \
../../common/src/CXAreaColorHolder.cpp \
../../common/src/CXGPSRecvThread.cpp \
../../common/src/CXRGB.cpp \
../../common/src/IMainWindow.cpp \
../../common/src/CXInfoBarBottom.cpp \
../../common/src/CXMapPainterTest.cpp \
../../common/src/CXDebugInfo.cpp \
../../common/src/CXUTMCoor.cpp \
../../common/src/CXWriteLocker.cpp \
../../common/src/CXUTMSpeed.cpp \
../../common/src/CXNaviData.cpp \
../../common/src/CXCoor.cpp \
../../common/src/CXReadLocker.cpp \
../../common/src/CXStringASCII.cpp \
../../common/src/CXMapPainterDoubleBuffered.cpp \
../../common/src/CXTransformationMatrix.cpp \
../../common/src/ISerial.cpp \
../../common/src/CXMapMovingDetails.cpp \
../../common/src/CXUTCTime.cpp \
../../common/src/CXPOIVisibilityDescriptor.cpp \
../../common/src/CXDirection.cpp \
../../common/src/CXGPSProtocol.cpp \
../../common/src/CXGPSProtocolNMEA.cpp \
../../common/src/CXGPSProtocolGPSD.cpp \
../../common/src/CXGPSInputChannel.cpp \
../../common/src/CXGPSInputChannelSerial.cpp \
../../common/src/CXGPSInputChannelFile.cpp \
../../common/src/CXGPSInputChannelGPSD.cpp \
../../common/src/CXGPSPosInfo.cpp \
../../common/src/CXGPSCourseInfo.cpp \
../../common/src/CXGPSQualityInfo.cpp \
../../common/src/CXSaver.cpp \
../../common/src/CXSaverRaw.cpp \
../../common/src/CXSaverGPX.cpp \
../../common/src/CXInfoBarRouting.cpp \
../../Qt/src/CXMutex.cpp \
../../Qt/src/TargetIncludes.cpp \
../../Qt/src/CXDeviceContext.cpp \
../../Qt/src/Main.cpp \
../../Qt/src/CXSemaphore.cpp \
../../Qt/src/CXWindow.cpp \
../../Qt/src/CXWorkRequestThread.cpp \
../../Qt/src/CXBitmap.cpp \
../../Qt/src/CXRWLock.cpp \
../../Qt/src/CXThread.cpp \
../../Qt/src/CXExactTime.cpp \
../../Qt/src/CXMainWindow.cpp \
../../Qt/KDevelop/src/CXSerial.cpp \
../../Qt/KDevelop/src/OSSpecific.cpp

HEADERS += ../../common/src/CoordConstants.h \
../../common/src/CoordConversion.h \
../../common/src/CXWatchdogThread.hpp \
../../common/src/CXWriteLocker.hpp \
../../common/src/CXPen.hpp \
../../common/src/CXMapSort.hpp \
../../common/src/CXMapPainterDoubleBuffered.hpp \
../../common/src/CXTimeStampData.hpp \
../../common/src/CXMapPainterTest.hpp \
../../common/src/CXStringASCII.hpp \
../../common/src/CXMapSection.hpp \
../../common/src/CXKeyVal.hpp \
../../common/src/CXNode.hpp \
../../common/src/CXPOWMMap.hpp \
../../common/src/IBitmap.hpp \
../../common/src/CXCoor.hpp \
../../common/src/CXStringUTF8.hpp \
../../common/src/IDeviceContext.hpp \
../../common/src/CXLoopThread.hpp \
../../common/src/CXReadLocker.hpp \
../../common/src/CXInfoBar.hpp \
../../common/src/CXBuffer.hpp \
../../common/src/ISerial.hpp \
../../common/src/CXMapLoaderThread.hpp \
../../common/src/CXMapPainter2D.hpp \
../../common/src/CXMapPainterThread.hpp \
../../common/src/CXNMEA.hpp \
../../common/src/CXNaviData.hpp \
../../common/src/IThread.hpp \
../../common/src/IWorkRequestThread.hpp \
../../common/src/CXInfoBarSpeed.hpp \
../../common/src/CXDebugInfo.hpp \
../../common/src/CXUTMSpeed.hpp \
../../common/src/CXOptions.hpp \
../../common/src/CXInfoBarTop.hpp \
../../common/src/CXNaviPOWM.hpp \
../../common/src/CXMapContainer.hpp \
../../common/src/CXSpeedCalculator.hpp \
../../common/src/IMutex.hpp \
../../common/src/CXTransformationMatrix.hpp \
../../common/src/IWindow.hpp \
../../common/src/CXMapHashSimple.hpp \
../../common/src/CXInfoBarCommon.hpp \
../../common/src/CXLocatorThread.hpp \
../../common/src/CXTrackLog.hpp \
../../common/src/CXSatelliteData.hpp \
../../common/src/CXRect.hpp \
../../common/src/CXFile.hpp \
../../common/src/CXWay.hpp \
../../common/src/CXArea.hpp \
../../common/src/CXPenHolder.hpp \
../../common/src/CXAreaColorHolder.hpp \
../../common/src/ISemaphore.hpp \
../../common/src/CXCache.hpp \
../../common/src/CXSmartPtr.hpp \
../../common/src/IMainWindow.hpp \
../../common/src/CXGPSRecvThread.hpp \
../../common/src/CXFileIni.hpp \
../../common/src/CXMapPainter.hpp \
../../common/src/CXInfoBarBottom.hpp \
../../common/src/CXArray.hpp \
../../common/src/IExactTime.hpp \
../../common/src/CXUTMCoor.hpp \
../../common/src/IRWLock.hpp \
../../common/src/Utils.hpp \
../../common/src/CXMutexLocker.hpp \
../../common/src/CXRGB.hpp \
../../common/src/CXMapSimple.hpp \
../../common/src/CXHysterezis.hpp \
../../common/src/CXMapMovingDetails.hpp \
../../common/src/CXUTCTime.hpp \
../../common/src/CXPOIVisibilityDescriptor.hpp \
../../common/src/CXDirection.hpp \
../../common/src/CXGPSProtocol.hpp \
../../common/src/CXGPSProtocolNMEA.hpp \
../../common/src/CXGPSProtocolGPSD.hpp \
../../common/src/CXGPSInputChannel.hpp \
../../common/src/CXGPSInputChannelSerial.hpp \
../../common/src/CXGPSInputChannelFile.hpp \
../../common/src/CXGPSInputChannelGPSD.hpp \
../../common/src/CXGPSPosInfo.hpp \
../../common/src/CXGPSCourseInfo.hpp \
../../common/src/CXGPSQualityInfo.hpp \
../../common/src/CXSaver.hpp \
../../common/src/CXSaverRaw.hpp \
../../common/src/CXSaverGPX.hpp \
../../common/src/CXInfoBarRouting.hpp \
../../Qt/src/CXRWLock.hpp \
../../Qt/src/CXMainWindow.hpp \
../../Qt/src/TargetIncludes.hpp \
../../Qt/src/CXThread.hpp \
../../Qt/src/CXBitmap.hpp \
../../Qt/src/CXMutex.hpp \
../../Qt/src/CXSemaphore.hpp \
../../Qt/src/CXExactTime.hpp \
../../Qt/src/CXWindow.hpp \
../../Qt/src/CXWorkRequestThread.hpp \
../../Qt/src/CXDeviceContext.hpp \
../../Qt/KDevelop/src/OSSpecific.hpp \
../../Qt/KDevelop/src/CXSerial.hpp
