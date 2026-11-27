[Setup]
AppName=Lee Go!
AppVersion=0.1.0
DefaultDirName={autopf}\Lee Go!
DefaultGroupName=Lee Go!
DisableProgramGroupPage=yes
OutputDir=..\dist
OutputBaseFilename=LeeGoSetup
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
UninstallDisplayIcon={app}\CMSC11-Machine-Problem.exe

[Files]
Source: "..\release\CMSC11-Machine-Problem.exe"; DestDir: "{app}"
Source: "..\release\Assets\*"; DestDir: "{app}\Assets"; Flags: recursesubdirs createallsubdirs
Source: "..\release\levels\*"; DestDir: "{app}\levels"; Flags: recursesubdirs createallsubdirs

[Icons]
Name: "{group}\Lee Go!"; Filename: "{app}\CMSC11-Machine-Problem.exe"; WorkingDir: "{app}"
Name: "{autodesktop}\Lee Go!"; Filename: "{app}\CMSC11-Machine-Problem.exe"; WorkingDir: "{app}"

[Run]
Filename: "{app}\CMSC11-Machine-Problem.exe"; WorkingDir: "{app}"; Description: "Launch Lee Go!"; Flags: nowait postinstall skipifsilent