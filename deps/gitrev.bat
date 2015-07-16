@echo off

IF NOT EXIST lastrev.txt (
    echo Unknown Revision > lastrev.txt
)

FOR /F %%H IN (lastrev.txt) DO SET LASTREVISION=%%H

IF EXIST "C:\Program Files\Git\bin\git.exe" (
    SET FOUNDGIT="C:\Program Files\Git\bin\git.exe"
) ELSE IF EXIST "C:\Program Files (x86)\Git\bin\git.exe" (
    SET FOUNDGIT="C:\Program Files (x86)\Git\bin\git.exe"
) ELSE IF EXIST "%PROGRAMFILES%\Git\bin\git.exe" (
    SET FOUNDGIT="%PROGRAMFILES%\Git\bin\git.exe"
) ELSE IF EXIST "%PROGRAMFILES(x86)%\Git\bin\git.exe" (
    SET FOUNDGIT="%PROGRAMFILES(x86)%\Git\bin\git.exe"
) ELSE (
    goto fail
)

%FOUNDGIT% rev-list HEAD --count > lastrev.txt

FOR /F %%H IN (lastrev.txt) DO SET REVISION=%%H

echo Current revision is %REVISION%
echo Last revision is %LASTREVISION%

IF %REVISION% NEQ %LASTREVISION% (
    echo // generated by gitrev.cmd > ..\t4m\buildnumber.h
	echo #define COMMIT %REVISION% >> ..\t4m\buildnumber.h
    echo #define COMMIT_STR "%REVISION%" >> ..\t4m\buildnumber.h
    echo #define BUILDHOST "%COMPUTERNAME%" >> ..\t4m\buildnumber.h
)

goto exit

:fail
echo Couldn't Update Buildnumber

:exit