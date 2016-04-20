// include Fake lib
#r @"packages/FAKE/tools/FakeLib.dll"
open Fake


// Properties
let buildDir = "./build/"

// Targets
Target "Clean" (fun _ ->
trace "--- Cleaning build and test dirs --- "
CleanDirs [buildDir]
)

Target "BuildApp" (fun _ ->
trace "--- Building app --- "
!! "Helbreath.LoginServerConsole/*.vcxproj"
 |> MSBuild buildDir "Build" ["Configuration", "Debug"; "PlatformToolset", "v120"; "Platform", "x86"]
 |> Log "AppBuild-Output: "
)

Target "Default" (fun _ ->
trace "--- Starting... --- "
)

// start build
"Clean" ==> "BuildApp" ==> "Default"

RunTargetOrDefault "Default"
