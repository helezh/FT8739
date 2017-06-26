@echo on
color 0a
"D:\program files\AStyle\bin\AStyle.exe" .\src/*.c .\src/*.h  --style=ansi -s4 -S -H -N -L -m0 -M40 -Z -R -c -n %f
