
@rem error
@rem set str1=Hello World
set str1="Hello World"
echo str1=%str1%

IF %str1%=="Hello World" (
echo match!
) else (
echo not match!
)

IF %str1% == "Hello World" (
echo match!
) else (
echo not match!
)



:: test case-insensitive?
IF %str1%=="hello world" (
echo match!
) else (
echo not match! So, case-sensitive matching.
)

:: case-insensitive matching.
IF /I %str1%=="hello world" (
echo match! case in-senstitive
) else (
echo not match.
)

