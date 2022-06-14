@ECHO OFF
SetLocal EnableDelayedExpansion

SET cppFilenames=
FOR /R %%f in (*.cpp) do (
    SET cppFilenames=!cppFilenames! %%f
)

SET assembly=main

SET compilerFlags=-Wall 

SET includeFlags=-Isrc -Icore -I..\dependencies\GLFW\include -I..\dependencies\GLM -I..\dependencies\GLAD\include

SET linkerFlags=-L..\dependencies\GLFW\lib -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 

ECHO "Building %assembly%..."
g++ %cppFilenames% glad.c -o %assembly% %compilerFlags% %includeFlags% %linkerFlags% 
