# If you are on command prompt:
# powershell -NoLogo -NoProfile -NonInteractive -File .\install_sdl2_windows.ps1
#
# If you are on powershell:
# .\install_sdl2_windows.ps1

function Install-SDL {
  [CmdletBinding()]
  param (
    [string]$repo_name
  )

  if ([Environment]::Is64BitOperatingSystem) {
    $arch = "x64"
  } else {
    $arch = "x86"
  }
  
  $module_name = $repo_name.Replace("SDL", "SDL2")
  $response = Invoke-WebRequest -Uri "https://github.com/libsdl-org/$repo_name/releases/latest" -MaximumRedirection 0 -ErrorAction Ignore
  $latest_version = $response.Headers.Location -Split "release-" | Select-Object -Index 1
  
  Invoke-WebRequest -Uri "https://github.com/libsdl-org/$repo_name/releases/download/release-$latest_version/$module_name-devel-$latest_version-VC.zip" -OutFile _downloaded_temp.zip
  Expand-Archive -Path .\_downloaded_temp.zip -DestinationPath .\_downloaded_temp

  New-Item .\include\SDL2 -ItemType Directory -ErrorAction SilentlyContinue

  $header_directory = ".\_downloaded_temp\$module_name-$latest_version\include"
  $header_files = Get-ChildItem -Path $header_directory -Name

  foreach ($header_file in $header_files) {
    if ($header_file -notlike "SDL_test*") {
      Move-Item -Path "$header_directory\$header_file" -Destination .\include\SDL2 -Force
    }
  }
  
  $library_directory = ".\_downloaded_temp\$module_name-$latest_version\lib\$arch"
  $library_files = Get-ChildItem -Path $library_directory -Name -Include *.lib,*.dll

  foreach ($library_file in $library_files) {
    if ($library_file -notlike "*test*") {
      Move-Item -Path "$library_directory\$library_file" -Destination . -Force
    }
  }
  
  Remove-Item -Path .\_downloaded_temp -Recurse -Force
  Remove-Item .\_downloaded_temp.zip -Force
}

Install-SDL -repo_name SDL
Install-SDL -repo_name SDL_image
Install-SDL -repo_name SDL_ttf
