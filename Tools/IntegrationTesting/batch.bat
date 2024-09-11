@echo off
setlocal

:: Define the path to your GDB script
set GDB_SCRIPT=C:\Users\ahmed\Desktop\AUTOSAR\SPIHandler\AUTOSAR_SPI_Handler\Tools\IntegrationTesting\script.gdb

:: Define the output file
set OUTPUT_FILE=C:\Users\ahmed\Desktop\AUTOSAR\SPIHandler\AUTOSAR_SPI_Handler\Tools\IntegrationTesting\out.txt

:: Define the timeout in seconds (e.g., 30 seconds)
set TIMEOUT=5

:: Start GDB in a new window and run the script, redirecting output to the file
start "" /B arm-none-eabi-gdb -x "%GDB_SCRIPT%" > "%OUTPUT_FILE%" 2>&1

:: Wait for the specified timeout period
timeout /t %TIMEOUT%

:: Check if GDB is still running and kill it if necessary
taskkill /F /IM arm-none-eabi-gdb.exe >nul 2>&1

:: Check if GDB ran successfully
if %ERRORLEVEL% neq 0 (
    echo Error: GDB execution failed or was terminated.
    exit /b 1
)
:: Check if GDB is still running and kill it if necessary
tasklist /FI "IMAGENAME eq arm-none-eabi-gdb.exe" | find /I "arm-none-eabi-gdb.exe" >nul
if %ERRORLEVEL% equ 0 (
    taskkill /F /IM arm-none-eabi-gdb.exe >nul 2>&1
)

:: Display the output file path
echo GDB output saved to %OUTPUT_FILE%

endlocal
