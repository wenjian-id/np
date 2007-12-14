TEMPLATE = app 
TARGET = bin/NaviPOWM
CONFIG += warn_on \
          qt \
          thread \
          rtti \
 debug
QMAKE_CXXFLAGS_DEBUG += -Wall
INCLUDEPATH += src \
 ../../common/src/ \
 ../src/
CONFIG -= release

SOURCES += src/CXSerial.cpp \
 ../src/CXBitmap.cpp \
 ../src/CXDeviceContext.cpp \
 ../src/CXExactTime.cpp \
 ../src/CXMainWindow.cpp \
 ../src/CXMutex.cpp \
 ../src/CXRWLock.cpp \
 ../src/CXSemaphore.cpp \
 ../src/CXThread.cpp \
 ../src/CXWindow.cpp \
 ../src/CXWorkRequestThread.cpp \
 ../src/Main.cpp \
 ../src/TargetIncludes.cpp \
 ../../common/src/CoordConversion.cpp \
 ../../common/src/CXFile.cpp \
 ../../common/src/CXFileIni.cpp \
 ../../common/src/CXGPSRecvThread.cpp \
 ../../common/src/CXInfoBarBottom.cpp \
 ../../common/src/CXInfoBar.cpp \
 ../../common/src/CXInfoBarTop.cpp \
 ../../common/src/CXLocatorThread.cpp \
 ../../common/src/CXLoopThread.cpp \
 ../../common/src/CXMapPainter2D.cpp \
 ../../common/src/CXMapPainter.cpp \
 ../../common/src/CXMapPainterDoubleBuffered.cpp \
 ../../common/src/CXMapPainterTest.cpp \
 ../../common/src/CXMapThread.cpp \
 ../../common/src/CXMutexLocker.cpp \
 ../../common/src/CXNaviData.cpp \
 ../../common/src/CXNaviPOWM.cpp \
 ../../common/src/CXOptions.cpp \
 ../../common/src/CXPen.cpp \
 ../../common/src/CXPenHolder.cpp \
 ../../common/src/CXPOWMMap.cpp \
 ../../common/src/CXReadLocker.cpp \
 ../../common/src/CXRGB.cpp \
 ../../common/src/CXSpeedCalculator.cpp \
 ../../common/src/CXStringASCII.cpp \
 ../../common/src/CXStringUTF8.cpp \
 ../../common/src/CXTransformationMatrix.cpp \
 ../../common/src/CXUTMCoor.cpp \
 ../../common/src/CXCoor.cpp \
 ../../common/src/CXUTMSpeed.cpp \
 ../../common/src/CXWriteLocker.cpp \
 ../../common/src/IBitmap.cpp \
 ../../common/src/IMainWindow.cpp \
 ../../common/src/ISemaphore.cpp \
 ../../common/src/IThread.cpp \
 ../../common/src/IWorkRequestThread.cpp \
 ../../common/src/Utils.cpp \
 ../../common/src/ISerial.cpp \
 ../../common/src/CXInfoBarCommon.cpp \
 ../../common/src/CXInfoBarSpeed.cpp \
 ../../common/src/CXtrackLog.cpp

HEADERS += src/CXSerial.hpp \
src/OSSpecific.hpp \
 ../src/CXBitmap.hpp \
 ../src/CXDeviceContext.hpp \
 ../src/CXExactTime.hpp \
 ../src/CXMainWindow.hpp \
 ../src/CXMutex.hpp \
 ../src/CXRWLock.hpp \
 ../src/CXSemaphore.hpp \
 ../src/CXThread.hpp \
 ../src/CXWindow.hpp \
 ../src/CXWorkRequestThread.hpp \
 ../src/TargetIncludes.hpp \
 ../../common/src/CoordConstants.h \
 ../../common/src/CoordConversion.h \
 ../../common/src/CXBuffer.hpp \
 ../../common/src/CXFile.hpp \
 ../../common/src/CXFileIni.hpp \
 ../../common/src/CXGPSRecvThread.hpp \
 ../../common/src/CXInfoBarBottom.hpp \
 ../../common/src/CXInfoBar.hpp \
 ../../common/src/CXInfoBarTop.hpp \
 ../../common/src/CXKeyVal.hpp \
 ../../common/src/CXLocatorThread.hpp \
 ../../common/src/CXLoopThread.hpp \
 ../../common/src/CXMapHashSimple.hpp \
 ../../common/src/CXMapPainter2D.hpp \
 ../../common/src/CXMapPainterDoubleBuffered.hpp \
 ../../common/src/CXMapPainter.hpp \
 ../../common/src/CXMapPainterTest.hpp \
 ../../common/src/CXMapSimple.hpp \
 ../../common/src/CXMapThread.hpp \
 ../../common/src/CXMutexLocker.hpp \
 ../../common/src/CXNaviData.hpp \
 ../../common/src/CXNaviPOWM.hpp \
 ../../common/src/CXOptions.hpp \
 ../../common/src/CXPen.hpp \
 ../../common/src/CXPenHolder.hpp \
 ../../common/src/CXPOWMMap.hpp \
 ../../common/src/CXReadLocker.hpp \
 ../../common/src/CXRect.hpp \
 ../../common/src/CXRGB.hpp \
 ../../common/src/CXSpeedCalculator.hpp \
 ../../common/src/CXStringASCII.hpp \
 ../../common/src/CXStringUTF8.hpp \
 ../../common/src/CXTransformationMatrix.hpp \
 ../../common/src/CXUTMCoor.hpp \
 ../../common/src/CXUTMSpeed.hpp \
 ../../common/src/CXWriteLocker.hpp \
 ../../common/src/IBitmap.hpp \
 ../../common/src/IDeviceContext.hpp \
 ../../common/src/IExactTime.hpp \
 ../../common/src/IMainWindow.hpp \
 ../../common/src/IMutex.hpp \
 ../../common/src/IRWLock.hpp \
 ../../common/src/ISemaphore.hpp \
 ../../common/src/ISerial.hpp \
 ../../common/src/IThread.hpp \
 ../../common/src/IWindow.hpp \
 ../../common/src/IWorkRequestThread.hpp \
 ../../common/src/Utils.hpp \
 ../../common/src/CXInfoBarCommon.hpp \
 ../../common/src/CXInfoBarSpeed.hpp
