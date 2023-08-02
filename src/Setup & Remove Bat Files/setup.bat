@echo off

ren "Beefcake+.dll" "lua51.dll"

set "BeefcakePath=%~dp0"
pushd "%BeefcakePath%.."

if exist "lua51.dll" (
    ren "lua51.dll" "lua51a.dll"
)

popd

move "lua51.dll" "%BeefcakePath%.."

echo Beefcake successfully setup!

pause