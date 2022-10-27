# services
function SetEnvironment($QtPath) {
    if($QtPath) {
        Write-Output "+++Setting environment for build+++"
        $Env:SOURCES_DIR = $PSScriptRoot + "/.."
        $Env:OUTPUT_DIR = $Env:SOURCES_DIR + "/out"
        $Env:ALGORITHMS_MODULE= $Env:OUTPUT_DIR + "/libs/libAlgorithmsModule.a"
        $Env:CMAKE_BUILD_TYPE = "Release"
        $Env:CMAKE_GENERATOR = "Ninja"
        $Env:CMAKE_GNUtoMS = "OFF"
        $Env:INSTALL_PREFIX = $Env:SOURCES_DIR + "Install"
        $Env:CMAKE_PREFIX_PATH = $QtPath + "/mingw_64"
        $Env:CMAKE_PROJECT_INCLUDE_BEFORE = $QtPath + "/../Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake"
        $Env:QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP = "OFF"
        $Env:QT_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6"
        $Env:QT_QMAKE_EXECUTABLE = $QtPath + "/mingw_64/bin/qmake.exe"
        $Env:Qt6CoreTools_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6CoreTools"
        $Env:Qt6Core_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6Core"
        $Env:Qt6EntryPointPrivate_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6EntryPointPrivate"
        $Env:Qt6GuiTools_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6GuiTools"
        $Env:Qt6Gui_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6Gui"
        $Env:Qt6WidgetsTools_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6WidgetsTools"
        $Env:Qt6Widgets_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6Widgets"
        $Env:Qt6ZlibPrivate_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6ZlibPrivate"
        $Env:WINDEPLOYQT_EXECUTABLE = $QtPath + "/mingw_64/bin/windeployqt.exe"
        Write-Output "---Setting environment for build---"
    }
    else {
        Write-Output("Please provide path to your qt installation folder as second parameter")
        exit 1
    }
}

function CleanBuild() {
    Write-Output("+++Clean build+++")

    try {

        if(Test-Path $Env:OUTPUT_DIR) {
            Remove-Item $Env:OUTPUT_DIR -Recurse
        }

        $AlgorithmsModuleSource = $Env:SOURCES_DIR + "/AlgorithmsModule"; $AlgorithmsModuleOut = $Env:OUTPUT_DIR + "/libs"
        $MainWindowModuleSource = $Env:SOURCES_DIR + "/MainWindow"; $MainWindowModuleOut = $Env:OUTPUT_DIR + "/exe"
        $Env:Path = $Env:Path + ";" + $Env:CMAKE_PREFIX_PATH + "/../../Tools/mingw1120_64/bin"
        $CmakeExe = $Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe"

        # Create directories for new build
        New-Item -Force -Path ($Env:OUTPUT_DIR) -ItemType Directory
        New-Item -Force -Path ($AlgorithmsModuleSource) -ItemType Directory
        New-Item -Force -Path ($AlgorithmsModuleOut) -ItemType Directory
        
        # Make and build AlgorithmsModule
        $MakeAlgorithmsModuleCommand = [scriptblock]::Create($CmakeExe + " -S " + $AlgorithmsModuleSource + " -B "  + $AlgorithmsModuleOut)
        Write-Output ($MakeAlgorithmsModuleCommand)
        Invoke-Command -script $MakeAlgorithmsModuleCommand

        $BuildAlgorithmsModuleCommand = [scriptblock]::Create($CmakeExe + " --build " + $AlgorithmsModuleOut + " --target all")
        Write-Output ($BuildAlgorithmsModuleCommand)
        Invoke-Command -script $BuildAlgorithmsModuleCommand

        # Make and build MainWindow module
        $MakeMainWindowModuleCommand = [scriptblock]::Create($CmakeExe + " -S " + $MainWindowModuleSource + " -B " + $MainWindowModuleOut)
        Write-Output ($MakeMainWindowModuleCommand)
        Invoke-Command -script $MakeMainWindowModuleCommand

        $BuildMainWindowModuleCommand = [scriptblock]::Create($CmakeExe + " --build " + $MainWindowModuleOut + " --target all")
        Write-Output ($BuildMainWindowModuleCommand)
        Invoke-Command -script $BuildMainWindowModuleCommand
    }
    catch {
        Write-Output $_Exception.Message
        exit 1
    }

    Write-Output("---Clean build---")
    exit $LASTEXITCODE
}

function RunApplication() {

    try {
        $Env:PATH = $Env:PATH + ";" + $Env:CMAKE_PREFIX_PATH + "/bin"
        Invoke-Item ($Env:SOURCES_DIR + "/out/exe/MainWindow.exe")
    }
    catch {
        Write-Output $_Exception.Message
        exit 1
    }

    exit $LASTEXITCODE
}

# params
Switch($Args[0]) {
    "SetEnvironment" { SetEnvironment($Args[1]) }
    "CleanBuild" { CleanBuild }
    "Run" { RunApplication }
    Default {
        Write-Output("Please provide any option, available options are: SetEnvironment, CleanBuild, Run")
        exit 1
    }
}