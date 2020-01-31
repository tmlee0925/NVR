@echo off
rem -----------------------------------
rem	 		WIN32 batch file
rem -----------------------------------

echo %0 %1 %2
echo "$$PWD : %1"
echo "$$OUT_PWD : %2"

IF NOT EXIST "%2\include" mkdir "%2\include"

mkdir include
copy /Y "%1\*.h" 		"%2\include\"

rem Copy Library
copy /Y "%1\..\qt-gstreamer\x64\Debug\*.dll" 		"%2"