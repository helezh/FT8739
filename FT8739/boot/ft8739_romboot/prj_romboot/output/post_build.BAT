
@del obj\*.crf
@del obj\*.lnp


@copy list\mcu.map ..\output\
@copy obj\mcu.hex ..\output\
@del  Obj\mcu.hex
@cd ..\output

@del *.bin
::del *.i

@set y=%date:~0,4%
@set m=%date:~5,2%
@set d=%date:~8,2%


HEX2BIN.EXE   mcu.hex  rom_%y%%m%%d%.bin 


copy .\*.bin .\bin\




