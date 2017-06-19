::del List\*.lst
::del List\*.map
::del Obj\*.obj
del ..\output\obj\*.crf
del ..\output\obj\*.lnp
::del Obj\*.plg
::del *.m51
::del *.bak
::Obj\mcu

copy ..\output\list\mcu.map ..\output\
copy ..\output\obj\mcu.hex ..\output\
del ..\output\Obj\mcu.hex
cd ..\output

del *.bin
::del *.i

set y=%date:~0,4%
set m=%date:~5,2%
set d=%date:~8,2%


HEX2BIN.EXE   mcu.hex  rom_%y%%m%%d%.bin 


copy .\*.bin .\bin\




