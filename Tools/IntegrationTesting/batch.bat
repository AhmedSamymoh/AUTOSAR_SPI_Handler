@echo off
setlocal

:: Define the path to your GDB script
set GDB_SCRIPT=O:\Jenkins\workspace\_SPIH-CI_Brightskies_main\Tools\IntegrationTesting\script.gdb

:: Define the output file
set OUTPUT_FILE=O:\Jenkins\workspace\_SPIH-CI_Brightskies_main\Tools\IntegrationTesting\out.txt

:: Define the timeout in seconds (e.g., 30 seconds)
set TIMEOUT=3

:: Start GDB and run the script, redirecting output to the file
arm-none-eabi-gdb -x "%GDB_SCRIPT%" > "%OUTPUT_FILE%" 2>&1

:: Wait for the specified timeout period
timeout /t %TIMEOUT%

:: Check if GDB is still running and kill it if necessary
tasklist /FI "IMAGENAME eq arm-none-eabi-gdb.exe" | find /I "arm-none-eabi-gdb.exe" >nul
if %ERRORLEVEL% equ 0 (
    taskkill /F /IM arm-none-eabi-gdb.exe >nul 2>&1
)

:: Check if GDB ran successfully
if %ERRORLEVEL% neq 0 (
    echo Error: GDB execution failed or was terminated.
    exit /b 1
)

:: Display the output file path
echo GDB output saved to %OUTPUT_FILE%

endlocal
