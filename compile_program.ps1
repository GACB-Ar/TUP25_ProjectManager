# Define the output executable name
$outputExecutable = "project_manager.exe"

# Define the source files
$sourceFiles = @("main.c", "project_methods.c", "task_methods.c", "file.c")

# Check if gcc is available
$gccPath = Get-Command gcc -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "gcc is not installed or not found in PATH. Please install it and ensure it's in your PATH."
    exit 1
}

# Compile the project
$compileCommand = "gcc -o $outputExecutable $sourceFiles"

# Execute the compile command
Invoke-Expression $compileCommand

# Check if the compilation was successful
if (Test-Path $outputExecutable) {
    Write-Host "Compilation successful! Executable created: $outputExecutable"
} else {
    Write-Host "Compilation failed."
}
