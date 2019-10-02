
@rem abc includes quote...
set abc="abc de f.gif"
echo %abc%

@rem strip quote.
set abc=%abc:"=%

@rem replace space to empty.
set ret1=%abc: =%

@rem replace .

echo %abc%
echo.
echo %ret1%

@rem string left 0~3 [0,4)
echo %abc:~0,3%

echo %date%
@rem get month. index=[5,7)
echo %date:~5,2%

@rem index 5 to end.
echo %date:~5%

@rem get day. last two char.
echo %date:~-2%

