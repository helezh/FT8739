@echo on
set backName=%date:~0,4%-%date:~5,2%-%date:~8,2%
del /f /s /q .\%backName% 
rd /s /q .\%backName%
MD .\%backName%
XCOPY  .\src\*.*  .\%backName%\

del /f /s /q .\back\%backName% 
rd /s /q .\back\%backName%
MD .\back\%backName%
XCOPY .\%backName%  .\back\%backName% /s /q

del /f /s /q .\%backName% 
rd /s /q .\%backName% 

