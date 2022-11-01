#########################################################################################
# helper functions

function MakeModule($ModuleSource, $ModuleOut) {
    $MakeModuleCommand = [scriptblock]::Create($Env:CmakeExe + " -S " + $ModuleSource + " -B "  + $ModuleOut)
    Write-Output $MakeModuleCommand
    Invoke-Command -script $MakeModuleCommand
}

function BuildModule($ModuleOut) {
    $BuildModuleCommand = [scriptblock]::Create($Env:CmakeExe + " --build " + $ModuleOut + " --target all")
    Write-Output $BuildModuleCommand
    Invoke-Command -script $BuildModuleCommand
}

function CleanBuildModule($ModuleName, $OutputDirName) {
    $ModuleSource = $Env:SOURCES_DIR + $ModuleName; $ModuleOut = $Env:OUTPUT_DIR + $OutputDirName
    MakeModule $ModuleSource $ModuleOut
    BuildModule $ModuleOut
}

#########################################################################################
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
        $Env:INSTALL_PREFIX = $Env:SOURCES_DIR + "/Install"
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
        $Env:Qt6Test_DIR = $QtPath + "/mingw_64/lib/cmake/Qt6Test"
        $Env:WINDEPLOYQT_EXECUTABLE = $QtPath + "/mingw_64/bin/windeployqt.exe"
        Write-Output "---Setting environment for build---"
    }
    else {
        Write-Output "Please provide path to your qt installation folder as second parameter"
        exit 1
    }
}

function CleanBuild() {
    Write-Output "+++Clean build+++"

    try {

        if(Test-Path $Env:OUTPUT_DIR) {
            Remove-Item $Env:OUTPUT_DIR -Recurse
        }

        $Env:Path = $Env:Path + ";" + $Env:CMAKE_PREFIX_PATH + "/../../Tools/mingw1120_64/bin"
        $Env:CmakeExe = $Env:CMAKE_PREFIX_PATH + "/../../Tools/Cmake_64/bin/cmake.exe"
        
        CleanBuildModule "/AlgorithmsModule" "/libs"
        CleanBuildModule "/MainWindow" "/exe"
        CleanBuildModule "/TestsModule" "/tests"
    }
    catch {
        Write-Output $_Exception.Message
        exit 1
    }

    Write-Output "---Clean build---"
    exit $LASTEXITCODE
}

function Run($OutputExePath) {
    try {
        $Env:PATH = $Env:PATH + ";" + $Env:CMAKE_PREFIX_PATH + "/bin"
        $RunExe = [scriptblock]::Create($Env:OUTPUT_DIR + $OutputExePath)
        Invoke-Command -script $RunExe
    }
    catch {
        Write-Output $_Exception.Message
        exit 1
    }

    exit $LASTEXITCODE
}

#########################################################################################

# params
Switch($Args[0]) {
    "SetEnvironment" { SetEnvironment $Args[1] }
    "CleanBuild" { CleanBuild }
    "RunApp" { Run "/exe/MainWindow.exe" }
    "RunTests" { Run "/tests/TestsModule.exe" }
    Default {
        Write-Output("Please provide any option, available options are:
            SetEnvironment
            CleanBuild 
            RunApp
            RunTests")
        exit 1
    }
}