@echo off

set "BeefcakePath=%~dp0"
pushd "%BeefcakePath%.."

if exist "lua51a.dll" (
    move "lua51.dll" "%~dp0\Beefcake+.dll"
    ren "lua51a.dll" "lua51.dll"
)

popd

echo Beefcake successfully removed!

pause