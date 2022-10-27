# services
function SetEnvironment($QtPath) {
    if($QtPath) {
        echo "---Setting environment for build---"
        $Env:QtPath = $QtPath
        echo "$Env:CI_PROJECT_DIR"
        $Env:SourcesDir = $PSScriptRoot + "/.."
        $Env:OutputDir = $Env:SourcesDir + "/out"
        $Env:ALGORITHMS_MODULE= $Env:OutputDir + "/libs/libAlgorithmsModule.a"
        $Env:CMAKE_BUILD_TYPE = "Release"
        $Env:Path = $Env:Path + ";" + $QtPath + "/Tools/mingw1120_64/bin"
        $Env:CMAKE_GENERATOR = "Ninja"
        $Env:CMAKE_GNUtoMS = "OFF"
        $Env:INSTALL_PREFIX = $Env:SourcesDir + "Install"
        $Env:CMAKE_PREFIX_PATH = $QtPath + "/6.3.1/mingw_64"
        $Env:CMAKE_PROJECT_INCLUDE_BEFORE = $QtPath + "/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake"
        $Env:QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP = "OFF"
        $Env:QT_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6"
        $Env:QT_QMAKE_EXECUTABLE = $QtPath + "/6.3.1/mingw_64/bin/qmake.exe"
        $Env:Qt6CoreTools_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6CoreTools"
        $Env:Qt6Core_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6Core"
        $Env:Qt6EntryPointPrivate_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6EntryPointPrivate"
        $Env:Qt6GuiTools_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6GuiTools"
        $Env:Qt6Gui_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6Gui"
        $Env:Qt6WidgetsTools_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6WidgetsTools"
        $Env:Qt6Widgets_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6Widgets"
        $Env:Qt6ZlibPrivate_DIR = $QtPath + "/6.3.1/mingw_64/lib/cmake/Qt6ZlibPrivate"
        $Env:WINDEPLOYQT_EXECUTABLE = $QtPath + "/6.3.1/mingw_64/bin/windeployqt.exe"
    }
    else {
        Write-host("Please provide path to your qt installation folder as second parameter")
    }
}

function CleanBuild() {
    Write-Host("---Clean build---")
    if(Test-Path $Env:OutputDir) {
        Remove-Item $Env:OutputDir -Recurse
    }
    New-Item -Force -Path ($Env:OutputDir) -ItemType Directory
    New-Item -Force -Path ($Env:OutputDir + "/libs") -ItemType Directory
    New-Item -Force -Path ($Env:OutputDir + "/exe") -ItemType Directory

    $AlgorithmsSource = $Env:SourcesDir + "/AlgorithmsModule"; $AlgorithmsOut = $Env:OutputDir + "/libs"
    $MakeAlgorithmsModule = [scriptblock]::Create($Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe -S $AlgorithmsSource -B $AlgorithmsOut")
    Write-Host ($MakeAlgorithmsModule)
    Invoke-Command -script $MakeAlgorithmsModule
    $BuildAlgorithmsModule = [scriptblock]::Create($Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe --build $AlgorithmsOut --target all")
    Write-Host ($BuildAlgorithmsModule)
    Invoke-Command -script $BuildAlgorithmsModule

    $MainWindowSource = $Env:SourcesDir + "/MainWindow"; $MainWindowOut = $Env:OutputDir + "/exe"
    $MakeMainWindow = [scriptblock]::Create($Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe -S $MainWindowSource -B $MainWindowOut")
    Write-Host ($MakeMainWindow)
    Invoke-Command -script $MakeMainWindow
    $BuildMainWindow = [scriptblock]::Create($Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe --build $MainWindowOut --target all")
    Write-Host ($BuildMainWindow)
    Invoke-Command -script $BuildMainWindow

    Write-Host("---Clean build---")
}

function RunApplication() {
    $Env:PATH = $Env:PATH + ";" + $QtPath + "/6.3.1/mingw_64/bin"
    Invoke-Item ($Env:SourcesDir + "/out/exe/MainWindow.exe")
}

# params
Switch($Args[0]) {
    "SetEnvironment" { SetEnvironment($Args[1]) }
    "CleanBuild" { CleanBuild }
    "Run" { RunApplication }
}