@echo off
set OLDPATH=%PATH%

rem ============================================= CONFIG PATS:
set PSP_BIN=C:\PSP\PSPSDK\bin;c:\windows\system32
set PSP_SDK=C:\PSP\PSPSDK\psp\sdk


rem ============================================= CONFIG BUILD
set BUILD_WII=1
set BUILD_PSP=1
set BUILD_NDS=0
set BUILD_WIN=0

rem ============================================= END CONFIG.
IF EXIST release GOTO NODIRS
@echo Building output structure...
@mkdir release
@cd release
@mkdir psp
@mkdir wii
@cd ..
:NODIRS


IF %BUILD_WII%==0 GOTO NOWII
	@echo ========== WII ===========
	@echo = Clean
	
	set root=%cd%
	set build=%root%\release
	make clean
	@echo = Build
	make
	@echo = Grab release
	copy uxcode.dol release\wii\boot.dol
	make clean
	rm *.dol
	rm *.elf
	rm build/*.*
	rmdir build
:NOWII

IF %BUILD_PSP%==0 GOTO NOPSP
	@echo ========== PSP ===========
	@echo = Setting paths...
	set path=%PSP_BIN%
	set PSPSDK=%PSP_SDK%
	@echo = Clean
	make -f Makefile.psp clean
	make -f Makefile.psp
	copy EBOOT.PBP release\psp
	make -f Makefile.psp clean
	@echo = Build
	@echo ....
	@echo ==========================
:NOPSP

pause
exit




@echo off
@echo --- Compilando ... mmm ... PSP? ---
set path=C:\PSP\PSPSDK\bin;c:\windows\system32
set PSPSDK=C:\PSP\PSPSDK\psp\sdk
make -f Makefile.psp clean
make -f Makefile.psp
cd PSPLINK
rm luadev.elf
rm luadev.prx
cd ..
copy luadev.elf PSPLINK\luadev.elf
copy luadev.prx PSPLINK\luadev.prx
copy EBOOT.PBP release\PSP\EBOOT.PBP
pause



rem call buildcount.bat
rem set path=C:\PSP\PSPSDK\bin;c:\windows\system32
rem set PSPSDK=C:\PSP\PSPSDK\psp\sdk
rem pause
rem @echo --- Compilando OSLIB  ---
rem cd oslib
rem make lib
rem copy "libosl.a" "../libosl.a"
rem cd ..
rem pause
rem @echo --- Compilando DRIVER ---
rem cd driver
rem psp-build-exports -s support.exp
rem make rebuild
rem copy syslib.prx ..\syslib.prx
rem cd ..
rem del sysl.h
rem bin2h syslib.prx sysl.h sysl
rem del syslib.prx
rem bin2h mpeg_vsh330.prx mpg330.h mpg330
rem bin2h mpeg_vsh350.prx mpg350.h mpg350
rem bin2h mpeg_vsh370.prx mpg370.h mpg370
rem pause
rem @echo --- Compilar recursos ---
rem bin2h res\lua.png lualogo.h lualogoimage
rem bin2h res\gear.png gear.h gearimage
rem bin2h res\logo.png logo.h logoimage
rem bin2h res\chipmunk.png chip.h chipimage
rem bin2h res\init.lua init.h luainitor
rem pause
rem @echo --- Compilando LuaDEV ---
rem rem make rebuild
rem make rebuild
rem del lualogo.h
rem del gear.h
rem del logo.h
rem del chip.h
rem del init.h
rem rem rename EBOOT.PBP EBOOT.PSP
rem rem make clean
rem rem rename EBOOT.PSP EBOOT.PBP
rem pause
rem 
rem @echo --- Comprimiendo ---
rem call comp.bat
rem del comp.bat
rem 
rem @echo --- Copiando archivos ---
rem copy EBOOT.PBP F:\PSP\GAME\CAT_LuaDEV\GDP\EBOOT.PBP
rem copy EBOOT.PBP F:\PSP\GAME\CAT_LuaDEV\NetCrawler\EBOOT.PBP
rem rem pause
rem 
rem 
rem @echo ##################    F I N I S H E D   #####################