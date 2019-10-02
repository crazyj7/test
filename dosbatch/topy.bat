@echo off
:: ipynb-py-convert package required.
:: pip install ipynb-py-convert
::

:: check extension
set filepath=%~1
if "%~1"=="" (
echo no parameter
goto :eof
)

set ext=%filepath:~-5%
:: echo extension=%ext%

if "%ext%"=="ipynb" (
rem nop
) else (
echo no ipynb file!
goto :eof
)

:: echo change to py(script)
set filename=%filepath:~0,-6%

:: echo filename=%filename%
echo from:"%filename%.ipynb"
echo to:"%filename%.py"
ipynb-py-convert "%filename%.ipynb" "%filename%.py"

