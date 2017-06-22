@echo on

set datetime=%date%
set yy=%datetime:~0,4%
set mm=%datetime:~5,2%
set dd=%datetime:~8,2%

del /f /s /q .\%yy%%mm%%dd% 
rd /s /q .\%yy%%mm%%dd%
MD .\%yy%%mm%%dd%
XCOPY  .\src  .\%yy%%mm%%dd%/S

del -f -s -q .\back\%yy%%mm%%dd% 
rd /s /q .\back\%yy%%mm%%dd%
MD .\back\%yy%%mm%%dd%
XCOPY .\%yy%%mm%%dd%  .\back\%yy%%mm%%dd% /s /q

del /f /s /q .\%yy%%mm%%dd% 
rd /s /q .\%yy%%mm%%dd% 
