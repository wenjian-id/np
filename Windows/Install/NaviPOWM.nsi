;--------------------------------

!include "MUI.nsh"


; The name of the installer
Name "NaviPOWM"

; Result of compiler
; OutFile "Install\NaviPOWM-Qt-MinGW-Setup-0.1.0.exe"
OutFile "Install\NaviPOWM-MinGW-Setup-0.1.0.exe"

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
    File "..\..\LICENSE.TXT"
    File "..\..\README.TXT"

    ; Icons
    CreateDirectory $INSTDIR\Icons
    SetOutPath $INSTDIR\Icons 
    File "Icons\info.bmp"
    File "Icons\logo.bmp"
    File "Icons\quit.bmp"
    File "Icons\saveoff.bmp"
    File "Icons\saveon.bmp"
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
    RmDir $INSTDIR\Icons ; will be deleted only if empty

    ; Main path
    Delete "$INSTDIR\NaviPOWM.exe"
    Delete "$INSTDIR\NaviPOWM.INI"
    Delete "$INSTDIR\LICENSE.TXT"
    Delete "$INSTDIR\README.TXT"
    RmDir $INSTDIR ; will be deleted only if empty

SectionEnd
