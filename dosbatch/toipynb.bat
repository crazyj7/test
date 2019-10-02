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

set ext=%filepath:~-2%
:: echo extension=%ext%

if "%ext%"=="py" (
rem nop
) else (
echo no py file!
goto :eof
)

:: echo change to ipynb(notebook)
set filename=%filepath:~0,-3%

:: echo filename=%filename%
echo from:"%filename%.py"
echo to:"%filename%.ipynb"
ipynb-py-convert "%filename%.py" "%filename%.ipynb"

