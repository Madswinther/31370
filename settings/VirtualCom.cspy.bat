@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM
@REM Read about available command line parameters in the C-SPY Debugging
@REM Guide. Hints about additional command line parameters that may be
@REM useful in specific cases:
@REM   --download_only   Downloads a code image without starting a debug
@REM                     session afterwards.
@REM   --silent          Omits the sign-on message.
@REM   --timeout         Limits the maximum allowed execution time.
@REM 


"F:\Program Files\common\bin\cspybat" "F:\Program Files\arm\bin\armproc.dll" "F:\Program Files\arm\bin\armjlink.dll"  %1 --plugin "F:\Program Files\arm\bin\armbat.dll" --macro "C:\Users\gedemis\Desktop\31370\31370\config\lpc2478.mac" --flash_loader "F:\Program Files\arm\config\flashloader\NXP\FlashNXPLPC512k2.board" --backend -B "--endian=little" "--cpu=ARM7TDMI-S" "--fpu=None" "-p" "F:\Program Files\arm\CONFIG\debugger\NXP\LPC2478.ddf" "--drv_verify_download" "--semihosting" "--device=LPC2478" "--drv_communication=USB0" "--jlink_speed=adaptive" "--jlink_reset_strategy=0,9" 


