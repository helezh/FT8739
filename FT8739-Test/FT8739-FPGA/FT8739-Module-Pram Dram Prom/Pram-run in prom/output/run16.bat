set y=%date:~0,4%
set m=%date:~5,2%
set d=%date:~8,2%

cd ..\output

b2e 16 eb rom_%y%%m%%d%.bin