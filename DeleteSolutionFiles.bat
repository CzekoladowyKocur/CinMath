@echo off
rem Pop a directory to enter project's root directory
echo Recursive file scan for root directory:
CD

rem Start at the root node of the tree and loop though each directory
for /r %%a in (.) do (
    rem Enter the directory
    pushd %%a
    rem Loop through all the files with given extension in the current directory
    rem Delete solution files
    for %%f in (*.sln) do (
        if "%%~xf" == ".filters" echo Found file %%f
        DEL %%f
    )

    rem Delete project files
    for %%f in (*.vcxproj) do (
        if "%%~xf" == ".vcxproj" echo Found file %%f
        DEL %%f
    )

    rem Delete C# project files
    for %%f in (*.csproj) do (
        if "%%~xf" == ".csproj" echo Found file %%f
        DEL %%f
    )

    rem Delete filter files
    for %%f in (*.filters) do (
        if "%%~xf" == ".filters" echo Found file %%f
        DEL %%f
    )

    rem delete user files
    for %%f in (*.user) do (
        if "%%~xf" == ".user" echo Found file %%f
        DEL %%f
    )

    rem delete cache files
    for %%f in (*.vs) do (
        if "%%~xf" == ".vs" echo Found file %%f
	rem Setting the /AH flags turn on deleting hidden files
        DEL /AH %%f
    )

    rem Pop the directory
    popd
)
echo All the project files should have been successfully deleted.