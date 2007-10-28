;--------------------------------

!include "MUI.nsh"


; The name of the installer
Name "NaviPOWM"

; Result of compiler
OutFile "Install\InstPOWM.exe"

; default install directory
InstallDir C:\NaviPOWM

LicenseData "..\..\LICENCE.TXT"
;--------------------------------
; Pages

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\..\LICENCE.TXT"
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

    ; Icons
    CreateDirectory $INSTDIR\Icons
    SetOutPath $INSTDIR\Icons 
    File "Icons\Info.bmp"
    File "Icons\Logo.bmp"
    File "Icons\Quit.bmp"
    File "Icons\SaveOff.bmp"
    File "Icons\SaveOn.bmp"
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
    Delete "$INSTDIR\Icons\Info.bmp"
    Delete "$INSTDIR\Icons\Logo.bmp"
    Delete "$INSTDIR\Icons\Quit.bmp"
    Delete "$INSTDIR\Icons\SaveOff.bmp"
    Delete "$INSTDIR\Icons\SaveOn.bmp"
    RmDir $INSTDIR\Icons ; will be deleted only if empty

    ; Main path
    Delete "$INSTDIR\NaviPOWM.exe"
    Delete "$INSTDIR\NaviPOWM.INI"
    RmDir $INSTDIR ; will be deleted only if empty

SectionEnd
