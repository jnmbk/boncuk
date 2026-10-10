[Setup]
AppName=Boncuk
AppVersion=2.0.0
AppPublisher=Boncuk Development Team
DefaultDirName={autopf}\Boncuk
DefaultGroupName=Boncuk
OutputDir=..\dist
OutputBaseFilename=Boncuk_Setup
SetupIconFile=..\resources\boncuk.ico
UninstallDisplayIcon={app}\boncuk.exe
Compression=lzma2
SolidCompression=yes
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\bin\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\Boncuk"; Filename: "{app}\boncuk.exe"
Name: "{autodesktop}\Boncuk"; Filename: "{app}\boncuk.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\boncuk.exe"; Description: "{cm:LaunchProgram,Boncuk}"; Flags: nowait postinstall skipifsilent

