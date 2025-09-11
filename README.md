# VTFLib - A Valve VTF and VMT image format programming library.

VTFLib is a LGPL open source programming library that provides a C and C++ API that, with a few simple functions, can open and save .vtf and .vmt files, providing access to all known features. The library functions independent of Steam, allowing third party applications to use the library without Steam present or running on the target system.

VTFLib includes two GPL example applications, VTFCmd and VTFEdit. VTFCmd is a C command line frontend for VTFLib that can create .vtf and .vmt files from various source formats. It is similar in functionality to Valve's vtex Source SDK utility, but offers a lot more control. VTFEdit is a C++ .NET graphical frontend for VTFLib with viewing and creation capabilities. Both VTFCmd and VTFEdit support several source image formats, including, but not limited to .bmp, .dds, .gif, .jpg, .png and .tga.

## Library/Author Information

* **Title**: VTFLib
* **Written In**: C/C++
* **Date**: July 25th, 2011
* **Authors**: [IAmKnotMax](https://github.com/WereTech), [Skyrym](https://github.com/Sky-rym), [misyltoad](https://github.com/misyltoad), [Neil 'Jed' Jedrzejewski](https://github.com/NeilJed) & [Ryan Gregg](http://nemesis.thewavelength.net/)

## Project Structure

The library contains five folders:

* **Bin** - Contains library and example program binaries.
* **Lib** - Contains library C and C++ Header and Inline Files.
* **Sln** - Contains Visual Studio solutions.
* **VTFCmd** - Contains C example program source code.
* **VTFEdit** - Contains C++ .NET example program source code.
* **VTFLib** - Contains C++ library source code.

The project files are for Visual Studio .NET 2003 and 2005; no .NET extensions are used except in VTFEdit. Visual Studio 6.0 project files have also been
included.

## How to Build

### Prerequisites
Visual Studio 2019 or Visual Studio 2022

"Desktop development with C++" workload
#

Open the solution in /VTFEdit-Reloaded/sln/ with Visual Studio 2019 or 2022. Set the build from Debug to Release, then right-click on VTFEdit in the Solution Explorer and click Set as startup project, then right-click VTFEdit again and click Build.

After the Build is finished, the executable will be in /VTFEdit-Reloaded/sln/vs2019/Build/

Move the executable and all dll files to any folder you want VTFEdit-Reloaded to be in, it does not matter.

#
HLLib can be obtained from here, with the dll and the source code if you want to build it yourself. [>>Link](https://web.archive.org/web/20171114194253/http://nemesis.thewavelength.net/files/files/hllib246.zip) 

DevIL.dll from this zip (This may be changed if the project has a working 32 bit compile) [>>Link](https://sourceforge.net/projects/openil/files/DevIL%20Win32%20and%20Win64/DevIL-EndUser-x64-1.8.0.zip/download?use_mirror=phoenixnap)
#

## VTFCmd Usage
Parameters:
```
 -file <path>             (Input file path.)
 -folder <path>           (Input directory search string.)
 -output <path>           (Output directory.)
 -prefix <string>         (Output file prefix.)
 -postfix <string>        (Output file postfix.)
 -version <string>         (Output version.)
 -format <string>          (Output format to use on non-alpha textures.)
 -alphaformat <string>     (Output format to use on alpha textures.)
 -flag <string>           (Output flags to set.)
 -resize                  (Resize the input to a power of 2.)
 -rmethod <string>        (Resize method to use.)
 -rfilter <string>        (Resize filter to use.)
 -rwidth <integer>        (Resize to specific width.)
 -rheight <integer>       (Resize to specific height.)
 -rclampwidth <integer>   (Maximum width to resize to.)
 -rclampheight <integer>  (Maximum height to resize to.)
 -alphathreshold <integer> (Alpha threshold for One Bit Alpha. Pixel alpha below this value is set to 0)
 -gamma                   (Gamma correct image.)
 -gcorrection <single>    (Gamma correction to use.)
 -nomipmaps               (Don't generate mipmaps.)
 -mfilter <string>        (Mipmap filter to use.)
 -nwrap                   (Wrap the normal map for tiled textures.)
 -bumpscale <single>      (Engine bump mapping scale to use.)
 -nothumbnail             (Don't generate thumbnail image.)
 -noreflectivity          (Don't calculate reflectivity.)
 -shader <string>         (Create a material for the texture.)
 -param <string> <string> (Add a parameter to the material.)
 -recurse                 (Process directories recursively.)
 -exportformat <string>   (Convert VTF files to the format of this extension.)
 -silent                  (Silent mode.)
 -pause                   (Pause when done.)
 -help                    (Display vtfcmd help.)
```
Example vtfcmd usage:
```
vtfcmd.exe -file "C:\texture1.bmp" -file "C:\texture2.bmp" -format "dxt1"
vtfcmd.exe -folder "C:\input\*.tga" -output "C:\output" -recurse -pause
vtfcmd.exe -folder "C:\output\*.vtf" -output "C:\input" -exportformat "jpg"
```
## VTFEdit Reloaded Changelog
<details>

  v2.0.4
  - Changed the UI to use a better version of the tool bar and added more buttons for ease of access.
  - Adjusted several UI elements to stop text wrapping, causing the rest of the text to not be visible at all.
  - Adjusted some windows to now use a minimum window size, as this was not set before and you were able to resize these windows to be extremely small which also hid controls.
  - Added a Close option to both the File dropdown, and the new tool bar. The shortcut for this is Ctrl + Q. This will close the current file, which has a confirmation prompt so you don't close your file accidentally.
  - Changed the right-click context menu for VTFs to additionally show when clicking within the image window instead of needing to right-click on the image itself.
  - Changed the functionality of the Frame, Face, Slice, and Mipmap numeric bars to only be interactable if any of these properties have more than one to them. (in this case 0 = 1 because C++ starts at 0)
  - Adjusted some VTF flag names.

  v2.0.3
  - Updated the Shaders and Surface Properties list in VMT Create in accordance to the Valve Developer Wiki's current list
  - Added Drag and Drop functionality for images that can be imported normally through the File > Import dialog
	  - Note that if any window is above VTFEdit-Reloaded, or any part of the window is outside monitor bounds, the Import settings will default to the top-left of the screen. I do not have the knowledge to change this behavior myself unfortunately.
  - Changed the ReadOnly property in the Convert Folder and Convert WAD dialog, so you can manually insert or change the path to your folder instead of needing to use the Folder Selector button on the right.
  - Changed the resource files to use "winres.h" and "winver.h" instead of "afxres.h". Supposedly afxres.h is outdated, and has been replaced with the two other headers. So far I haven't noticed any issues with this.

  v2.0.2
  - Updated Compressonator to latest version as of 8/8/22.
  - Added 32-bit version.

  v2.0.1
  - Updated to HLLib v2.4.6.
  
  v2.0.0
  - Migrated to using AMD Compressonator for DXT compression.
  - Fix the green tinge when exporting textures
  - Respect sRGB-ness when generating mipmaps and resizing.
  - Ported to using the latest CLR and VS 2019.
  - Removed crufty sharpening filters (no longer needed with proper sRGB)
  - Use monospace font for VMT editor
  - High DPI support
  - Syntax highlighting support for VMTs
  - Fixed cubemap previews
    - Previously they were doing integer maths on what should be floats
    - Replaced overly complex controls with a simple exposure slider
    - Very simple Reinhard tonemapper for previewing exposure
</details>

## Program Copyright-Permissions

See the lgpl.txt (VTFLib) and gpl.txt (VTFCmd & VTFEdit) files contained in the distribution.
