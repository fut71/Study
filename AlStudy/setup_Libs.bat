@echo off
setlocal

REM === MSVC 환경 세팅 ===
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo [SETUP] Initializing external libraries...

REM ============================================
REM 1. DirectXTK
REM ============================================
if not exist External\DirectXTK (
    echo [INFO] Cloning DirectXTK...
    git clone https://github.com/microsoft/DirectXTK.git External\DirectXTK
) else (
    echo [INFO] DirectXTK already exists. Updating...
    cd External\DirectXTK
    git pull
    cd ../..
)

echo [BUILD] Building DirectXTK Debug/Release...
msbuild External\DirectXTK\DirectXTK_Desktop_2022.vcxproj /p:Configuration=Debug /p:Platform=x64 > nul
msbuild External\DirectXTK\DirectXTK_Desktop_2022.vcxproj /p:Configuration=Release /p:Platform=x64 > nul

REM ============================================
REM 2. SFML (DLL 빌드 강제)
REM ============================================
if not exist External\SFML (
    echo [INFO] Cloning SFML...
    git clone https://github.com/SFML/SFML.git External\SFML
) else (
    echo [INFO] SFML already exists. Updating...
    cd External\SFML
    git pull
    cd ../..
)

REM 빌드 폴더 생성
if not exist External\SFML\build (
    mkdir External\SFML\build
)
cd External\SFML\build

echo [CMAKE] Configuring SFML (DLL build)...
cmake .. -G "Visual Studio 17 2022" -A x64 ^
    -DSFML_BUILD_EXAMPLES=OFF ^
    -DSFML_BUILD_DOC=OFF ^
    -DBUILD_SHARED_LIBS=ON

echo [BUILD] Building SFML Debug/Release...
cmake --build . --config Debug
cmake --build . --config Release

REM === 빌드 결과 확인 ===
if not exist lib\Debug\sfml-graphics-d.lib (
    echo [ERROR] SFML Debug libraries not found! Build may have failed.
    pause
    exit /b 1
)
if not exist lib\Release\sfml-graphics.lib (
    echo [ERROR] SFML Release libraries not found! Build may have failed.
    pause
    exit /b 1
)

cd ..\..\..

REM ============================================
REM 3. DLL 복사 (Debug/Release)
REM ============================================
set TARGET_DEBUG=%CD%\x64\Debug
set TARGET_RELEASE=%CD%\x64\Release

if not exist %TARGET_DEBUG% (
    mkdir %TARGET_DEBUG%
)
if not exist %TARGET_RELEASE% (
    mkdir %TARGET_RELEASE%
)

echo [COPY] Copying SFML DLLs...
copy /Y External\SFML\build\bin\Debug\*.dll %TARGET_DEBUG%
copy /Y External\SFML\build\bin\Release\*.dll %TARGET_RELEASE%

echo [COPY] Copying DirectXTK DLLs...
copy /Y External\DirectXTK\Bin\Desktop_2022\x64\Debug\*.dll %TARGET_DEBUG%
copy /Y External\DirectXTK\Bin\Desktop_2022\x64\Release\*.dll %TARGET_RELEASE%

REM ============================================
REM 4. External.props 자동 생성 (절대 Debug/Release 경로)
REM ============================================
echo ^<?xml version="1.0" encoding="utf-8"?^> > External.props
echo ^<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003"^> >> External.props

REM 공통 include
echo   ^<ItemDefinitionGroup^> >> External.props
echo     ^<ClCompile^> >> External.props
echo       ^<AdditionalIncludeDirectories^>$(ProjectDir)External\SFML\include;$(ProjectDir)External\DirectXTK\Inc;%%(AdditionalIncludeDirectories)^</AdditionalIncludeDirectories^> >> External.props
echo     ^</ClCompile^> >> External.props
echo   ^</ItemDefinitionGroup^> >> External.props

REM Debug 전용
echo   ^<ItemDefinitionGroup Condition="'$(Configuration)'=='Debug'"^> >> External.props
echo     ^<Link^> >> External.props
echo       ^<AdditionalLibraryDirectories^>$(ProjectDir)External\SFML\build\lib\Debug;$(ProjectDir)External\DirectXTK\Bin\Desktop_2022\x64\Debug;%%(AdditionalLibraryDirectories)^</AdditionalLibraryDirectories^> >> External.props
echo       ^<AdditionalDependencies^>sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;DirectXTK.lib;%%(AdditionalDependencies)^</AdditionalDependencies^> >> External.props
echo     ^</Link^> >> External.props
echo   ^</ItemDefinitionGroup^> >> External.props

REM Release 전용
echo   ^<ItemDefinitionGroup Condition="'$(Configuration)'=='Release'"^> >> External.props
echo     ^<Link^> >> External.props
echo       ^<AdditionalLibraryDirectories^>$(ProjectDir)External\SFML\build\lib\Release;$(ProjectDir)External\DirectXTK\Bin\Desktop_2022\x64\Release;%%(AdditionalLibraryDirectories)^</AdditionalLibraryDirectories^> >> External.props
echo       ^<AdditionalDependencies^>sfml-graphics.lib;sfml-window.lib;sfml-system.lib;DirectXTK.lib;%%(AdditionalDependencies)^</AdditionalDependencies^> >> External.props
echo     ^</Link^> >> External.props
echo   ^</ItemDefinitionGroup^> >> External.props

echo ^</Project^> >> External.props

