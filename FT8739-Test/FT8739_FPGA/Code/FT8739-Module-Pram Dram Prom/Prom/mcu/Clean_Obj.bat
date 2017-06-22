:: Clean C251 obj
del .\output\list\*.* /s /q
del .\output\obj\*.* /s /q


:: Clean Keil bak
del .\keil\*.bak
del .\keil\*.uvgui.* /s /q
del .\keil\*.uvopt /s /q

:: Clean DOS 
::rd  /S /Q .\Dos\OutLog
::del .\Dos\FT8606_Simulator\*.ncb
::rd  /S /Q .\Dos\FT8606_Simulator\Debug
::rd  /S /Q .\Dos\FT8606_Simulator\Release
::rd  /S /Q .\Dos\FT8606_Simulator\FT8606_Simulator\Debug
::rd  /S /Q .\Dos\FT8606_Simulator\FT8606_Simulator\Release
::del  /S /Q .\Dos\FT8606_Simulator\FT8606_Simulator\*.user

::@pause
