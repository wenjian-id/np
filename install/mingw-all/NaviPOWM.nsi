;--------------------------------

!include "MUI.nsh"
CRCCheck force                                                      ; force CRC check

; uncomment for Qt version
;!define USE_QT

; The name of the installer
Name "NaviPOWM"

!define Version "0.2.5"                                             ; version string
!ifdef USE_QT
    !define QtVersion "4.6.2"                                       ; version of Qt
    !define QtDLLPath "C:\Qt\${QtVersion}\bin\"                     ; path for Qt DLLs
!endif

!define MainPath "..\..\"                                           ; main path 
!ifdef USE_QT
    !define ExePath "${MainPath}\build\mingw\Release\"                 ; path where the executable lies
!else
    !define ExePath "${MainPath}\build\mingw-qt\Release\"            ; path where the executable lies
!endif
!define ImagePath "${MainPath}\common\Images\"                      ; path with images
!define ConfigPath "${MainPath}\common\Config\"                     ; path with config files
!define DemoPath "${MainPath}\common\Demo\"                         ; path with demo files
!define MinGWPath "C:\MinGWStudio\MinGW\bin\"                       ; path with MinGW stuff


!ifdef USE_QT
    ; file names
    !define QtCore4FileName "QtCore4.dll"                           ; QtCore4.dll 
    !define QtGui4FileName "QtGui4.dll"                             ; QtGui4.dll
    !define mingwm10FileName "mingwm10.dll"                         ; mingwm10.dll

    ; now create complete file names
    !define QtCore4File "${QtDLLPath}\${QtCore4FileName}" 
    !define QtGui4File "${QtDLLPath}\${QtGui4FileName}"
    !define mingwm10File "${QtDLLPath}\${mingwm10FileName}"
!endif

!define LIBGCC_S_DW2-1FileName "LIBGCC_S_DW2-1.DLL"                  ; LIBGCC_S_DW2-1.DLL
!define LIBGCC_S_DW2-1File "${MinGWPath}\${LIBGCC_S_DW2-1FileName}"


; Result of compiler
!ifdef USE_QT
    OutFile "Install\NaviPOWM-Qt-MinGW-${Version}-Setup.exe"
!else
    OutFile "Install\NaviPOWM-MinGW-${Version}-Setup.exe"
!endif

; default install directory
InstallDir C:\NaviPOWM

!define LicenseFile "${MainPath}\LICENSE.TXT"
LicenseData ${LicenseFile}

;--------------------------------
; Pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${LicenseFile}"
!ifdef USE_QT
    !insertmacro MUI_PAGE_COMPONENTS
!endif
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

;--------------------------------
; installation stuff
Section "NaviPOWM (required)" SECT_NaviPOWM     ;
    ; Can not be disabled
    SectionIn RO

    ; Set output path to the installation directory.
    SetOutPath $INSTDIR
  
    ; Main path
    File "${ExePath}\NaviPOWM.exe"
    File "${ConfigPath}\NaviPOWM.INI"
    File "${DemoPath}\demo01.txt"
    File "${MainPath}\LICENSE.TXT"
    File "${MainPath}\README.TXT"
    File "${MainPath}\CHANGELOG.TXT"
    File ${LIBGCC_S_DW2-1File}

    ; Icons
    CreateDirectory $INSTDIR\Icons
    SetOutPath $INSTDIR\Icons 
    File "${ImagePath}\currentpos.bmp"
    File "${ImagePath}\info.bmp"
    File "${ImagePath}\logo.bmp"
    File "${ImagePath}\minimize.bmp"
    File "${ImagePath}\move.bmp"
    File "${ImagePath}\poi00.bmp"
    File "${ImagePath}\quit.bmp"
    File "${ImagePath}\saveoff.bmp"
    File "${ImagePath}\saveon.bmp"
    File "${ImagePath}\zoomin.bmp"
    File "${ImagePath}\zoomout.bmp"
    File "${ImagePath}\places.bmp"


    ; Maps
    CreateDirectory $INSTDIR\Maps
    SetOutPath $INSTDIR\Maps 
    File "${DemoPath}\E007N50.map"

    ; Save
    CreateDirectory $INSTDIR\Save

    ; Uninstaller
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NaviPOWM" "DisplayName" "NaviPOWM (remove only)"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NaviPOWM" "UninstallString" '"$INSTDIR\NaviPOWM-uninst.exe"'
    WriteUninstaller "$INSTDIR\NaviPOWM-uninst.exe"

SectionEnd ; end the section

!ifdef USE_QT
    LangString DESC_NaviPOWM ${LANG_ENGLISH} "NaviPOWM core files."
!endif

!ifdef USE_QT
    ;--------------------------------
    ; section for Qt DLLs
    Section "Qt ${QtVersion} DLLs (optional)" SECT_Qt
        ; Set output path to the installation directory.
        SetOutPath $INSTDIR
      
        ; Qt DLLs
        File ${QtCore4File} 
        File ${QtGui4File}
        File ${mingwm10File}
    SectionEnd ; end the section
    
    LangString DESC_Qt ${LANG_ENGLISH} "Needed Qt ${QtVersion} DLLs. Will be installed in the same directory as NaviPOWM."

    ;--------------------------------
    ; descriptions for mouseover
    !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
      !insertmacro MUI_DESCRIPTION_TEXT ${SECT_NaviPOWM} $(DESC_NaviPOWM)
      !insertmacro MUI_DESCRIPTION_TEXT ${SECT_Qt} $(DESC_Qt)
    !insertmacro MUI_FUNCTION_DESCRIPTION_END
!endif

;--------------------------------
; Uninstaller

UninstallText "This will uninstall NaviPOWM. Hit next to continue."

Section "Uninstall"

    ; uninstaller
    Delete "$INSTDIR\NaviPOWM-uninst.exe"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NaviPOWM"

    ; Save
    RmDir $INSTDIR\Save ; will be deleted only if empty

    ; Maps
    Delete "$INSTDIR\Maps\E007N50.map"
    RmDir $INSTDIR\Maps ; will be deleted only if empty

    ; Icons
    Delete "$INSTDIR\Icons\currentpos.bmp"
    Delete "$INSTDIR\Icons\info.bmp"
    Delete "$INSTDIR\Icons\logo.bmp"
    Delete "$INSTDIR\Icons\minimize.bmp"
    Delete "$INSTDIR\Icons\move.bmp"
    Delete "$INSTDIR\Icons\poi00.bmp"
    Delete "$INSTDIR\Icons\quit.bmp"
    Delete "$INSTDIR\Icons\saveoff.bmp"
    Delete "$INSTDIR\Icons\saveon.bmp"
    Delete "$INSTDIR\Icons\zoomin.bmp"
    Delete "$INSTDIR\Icons\zoomout.bmp"
    Delete "$INSTDIR\Icons\places.bmp"
    RmDir $INSTDIR\Icons ; will be deleted only if empty

    !ifdef USE_QT
        ; Qt DLLs
        Delete "$INSTDIR\${QtCore4FileName}"
        Delete "$INSTDIR\${QtGui4FileName}"
        Delete "$INSTDIR\${mingwm10Filename}"
    !endif

    ; Main path
    Delete "$INSTDIR\NaviPOWM.exe"
    Delete "$INSTDIR\NaviPOWM.INI"
    Delete "$INSTDIR\demo01.txt"
    Delete "$INSTDIR\LICENSE.TXT"
    Delete "$INSTDIR\README.TXT"
    Delete "$INSTDIR\CHANGELOG.TXT"
    Delete "$INSTDIR\last.gps"
    Delete "$INSTDIR\Save\last.gps"
    Delete "$INSTDIR\${LIBGCC_S_DW2-1FileName}"
    RmDir $INSTDIR ; will be deleted only if empty

SectionEnd
