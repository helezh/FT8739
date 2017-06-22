@cd ..\output

@del *.bin
@del *.i

@copy .\obj\mcu.hex mcu.hex 1>>nul
@copy .\list\mcu.map mcu.map 1>>nul


@set y=%date:~0,4%
@set m=%date:~5,2%
@set d=%date:~8,2%


HEX.exe
::------------------------------------------------------------------
::binMerg 名称 

@set  binMerge=bin_merge8836_v1.8

@HEX2BIN.EXE  _orc.hex

@%binMerge%.exe _orc.bin  module_%y%%m%%d%_app.bin  module_%y%%m%%d%_all.bin

@del _orc.bin
@del _orc.hex
copy .\*.bin .\bin\



