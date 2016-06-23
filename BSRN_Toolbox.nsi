; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "BSRN Toolbox"
!define PRODUCT_VERSION "2.24"
!define PRODUCT_PUBLISHER "PANGAEA"
!define PRODUCT_WEB_SITE "http://www.pangaea.de"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\BSRN_Toolbox.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\License\License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\BSRN_Toolbox.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox_V2_Win.exe"
InstallDir "$PROGRAMFILES\PANGAEA\BSRN Toolbox"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show
RequestExecutionLevel admin

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\BSRN_Toolbox.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\BSRN_fcheck.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\gzip.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\unzip.exe"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\Qt5Core.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\Qt5Gui.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\Qt5Network.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\Qt5Widgets.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\libgcc_s_dw2-1.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\libstdc++-6.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\libwinpthread-1.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\libeay32.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\ssleay32.dll"

SetOutPath "$INSTDIR\platforms"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\platforms\qminimal.dll"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\platforms\qwindows.dll"

  SetOutPath "$INSTDIR\License"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\License\gpl-3.0.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\License\License.txt"
  File "C:\Users\rsieger\Documents\Development\Distribution\BSRN_Toolbox\License\Readme.txt"
  
  CreateDirectory "$SMPROGRAMS\PANGAEA"
  CreateDirectory "$SMPROGRAMS\PANGAEA\BSRN Toolbox"
  CreateShortCut "$SMPROGRAMS\PANGAEA\BSRN Toolbox\BSRN Toolbox.lnk" "$INSTDIR\BSRN_Toolbox.exe"
  CreateShortCut "$DESKTOP\BSRN Toolbox.lnk" "$INSTDIR\BSRN_Toolbox.exe"
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\PANGAEA\BSRN Toolbox\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\BSRN_Toolbox.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\BSRN Toolbox.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\BSRN_Toolbox.exe"
  Delete "$INSTDIR\BSRN_fcheck.exe"
  Delete "$INSTDIR\gzip.exe"
  Delete "$INSTDIR\unzip.exe"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libeay32.dll"
  Delete "$INSTDIR\ssleay32.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Network.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\platforms\qminimal.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\License\Readme.txt"
  Delete "$INSTDIR\License\License.txt"
  Delete "$INSTDIR\License\gpl-3.0.txt"

  Delete "$SMPROGRAMS\PANGAEA\BSRN Toolbox\Uninstall.lnk"
  Delete "$SMPROGRAMS\PANGAEA\BSRN Toolbox\BSRN Toolbox.lnk"
  Delete "$DESKTOP\BSRN Toolbox.lnk"

  RMDir "$SMPROGRAMS\PANGAEA\BSRN Toolbox"  
  RMDir "$INSTDIR\License"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
