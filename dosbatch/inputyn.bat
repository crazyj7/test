@echo off
:: init var for empty string.
set "result="
set /p result=are you ok(y/n)?
if "%result%" == "" (
echo no input
goto :eof
)

echo your input is %result%
