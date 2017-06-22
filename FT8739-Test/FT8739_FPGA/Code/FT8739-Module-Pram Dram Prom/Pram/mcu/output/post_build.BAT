::del List\*.lst
::del List\*.map
::del Obj\*.obj
@del Obj\*.crf
@del Obj\*.lnp
::del Obj\*.plg
::del *.m51
::del *.bak
::Obj\mcu
@copy Obj\mcu.hex ..\output\
@del Obj\mcu.hex
@cd ..\output

@del *.bin
@del *.i

@set y=%date:~0,4%
@set m=%date:~5,2%
@set d=%date:~8,2%


HEX.exe
::------------------------------------------------------------------
::binMerg 名称 

::@set  binMerge=bin_merge8736_v1.7
@set  binMerge=bin_merge8836_v1.8
::HEX2BIN.EXE   mcu.hex  module_%y%%m%%d%.bin 

::@HEX2BIN.EXE  mcu.hex
@HEX2BIN.EXE  _orc.hex
::bin_merge8736_v1.7.exe 	module_%y%%m%%d%.bin 	module_%y%%m%%d%_app.bin  module_%y%%m%%d%_all.bin

@%binMerge%.exe _orc.bin  module_%y%%m%%d%_app.bin  module_%y%%m%%d%_all.bin

::del module_%y%%m%%d%.bin

@del _orc.bin
@del _orc.hex
copy .\*.bin .\bin\



