;--------------------------------

!include "MUI.nsh"


; The name of the installer
Name "NaviPOWM"

!define Version "0.1.2"             ; version string

; Result of compiler
OutFile "Install\NaviPOWM-MinGW-${Version}-Setup.exe"
; OutFile "Install\NaviPOWM-Qt-MinGW-${Version}-Setup.exe"

; default install directory
InstallDir C:\NaviPOWM

LicenseData "..\..\LICENSE.TXT"
;--------------------------------
; Pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\..\LICENSE.TXT"
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
Section "" ;start with this

    ; Set output path to the installation directory.
    SetOutPath $INSTDIR
  
    ; Main path
    File "Common\NaviPOWM.exe"
    File "Common\NaviPOWM.INI"
    File "Common\demo01.txt"
    File "Common\E0071N509.map"
    File "..\..\LICENSE.TXT"
    File "..\..\README.TXT"
    File "..\..\CHANGELOG.TXT"

    ; Icons
    CreateDirectory $INSTDIR\Icons
    SetOutPath $INSTDIR\Icons 
    File "Icons\info.bmp"
    File "Icons\logo.bmp"
    File "Icons\quit.bmp"
    File "Icons\saveoff.bmp"
    File "Icons\saveon.bmp"
    File "Icons\zoomin.bmp"
    File "Icons\zoomout.bmp"
    SetOutPath Icons 

    ; Maps
    CreateDirectory $INSTDIR\Maps

    ; Save
    CreateDirectory $INSTDIR\Save

    ; Uninstaller
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NaviPOWM" "DisplayName" "NaviPOWM (remove only)"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\NaviPOWM" "UninstallString" '"$INSTDIR\NaviPOWM-uninst.exe"'
    WriteUninstaller "$INSTDIR\NaviPOWM-uninst.exe"

SectionEnd ; end the section


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
    RmDir $INSTDIR\Maps ; will be deleted only if empty

    ; Icons
    Delete "$INSTDIR\Icons\info.bmp"
    Delete "$INSTDIR\Icons\logo.bmp"
    Delete "$INSTDIR\Icons\quit.bmp"
    Delete "$INSTDIR\Icons\saveoff.bmp"
    Delete "$INSTDIR\Icons\saveon.bmp"
    Delete "$INSTDIR\Icons\zoomin.bmp"
    Delete "$INSTDIR\Icons\zoomout.bmp"
    RmDir $INSTDIR\Icons ; will be deleted only if empty

    ; Main path
    Delete "$INSTDIR\NaviPOWM.exe"
    Delete "$INSTDIR\NaviPOWM.INI"
    Delete "$INSTDIR\demo01.txt"
    Delete "$INSTDIR\E0071N509.map"
    Delete "$INSTDIR\LICENSE.TXT"
    Delete "$INSTDIR\README.TXT"
    Delete "$INSTDIR\CHANGELOG.TXT"
    RmDir $INSTDIR ; will be deleted only if empty

SectionEnd
