
@copy Obj\mcu.hex ..\output\
@del Obj\mcu.hex
@cd ..\output

@del *.bin
::@del *.i

@set y=%date:~0,4%
@set m=%date:~5,2%
@set d=%date:~8,2%


HEX.exe
::------------------------------------------------------------------
::binMerg 名称 

@set  binMerge=bin_merge8836_v1.9


@HEX2BIN.EXE  _orc.hex


@%binMerge%.exe _orc.bin  FT8836_Pramboot_%y%%m%%d%_app.bin  FT8836_Pramboot_%y%%m%%d%_all.bin


@del _orc.bin
@del _orc.hex
copy .\*.bin .\bin\



