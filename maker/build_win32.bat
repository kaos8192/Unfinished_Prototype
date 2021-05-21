@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
set OUT_DIR=Debug
set OUT_EXE=gui_test_proto
set INCLUDES=/I..\src\gui-fe /I..\src\gui-fe\wrappers /I%SDL2_DIR%\include /I..\src\gui-fe\libs\gl3w /I..\src\imgui-master
set SOURCES=..\src\gui-fe\gui_main.cpp ..\src\gui-fe\wrappers\imgui_impl_sdl.cpp ..\src\gui-fe\wrappers\imgui_impl_opengl3.cpp ..\src\imgui-master\imgui*.cpp ..\src\gui-fe\libs\gl3w\GL\gl3w.c
set LIBS=/libpath:%SDL2_DIR%\lib\x86 SDL2.lib SDL2main.lib opengl32.lib
mkdir %OUT_DIR%
cl /nologo /Zi /MD %INCLUDES% %SOURCES% /Fe%OUT_DIR%/%OUT_EXE%.exe /Fo%OUT_DIR%/ /link %LIBS% /subsystem:console
