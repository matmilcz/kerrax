# KrxImpExp multiplatform

Attempt to make [KrxImpExp plugin] cross-platform.

## Index

* KrxImpExp - [KrxImpExp plugin] source
* wxWidgets-2.8.12 - [wxWidgets framework] in 2.8.12 version source and custom build script


## Backstory

While working on [History of Khorinis] some of our 3d graphics guys were using different than Windows operating system.
But the [Gothic] game and all modding related tools are designed to work only on Windows.
Those tools are also quite old.

[KrxImpExp plugin] allows to import/export models from game and supports multiple 3d modeling programs.
Some of them (e.g. [Blender]) runs on Linux and Mac but [KrxImpExp plugin] does not supports those operating systems.

This repository is an attempt to configure and compile almost 10 years old [KrxImpExp plugin] on Linux/Mac.
We hope that by doing this we will allow more people to join the [Gothic] modding community.


### About KrxImpExp plugin

[KrxImpExp plugin] is almost a 10 years old project therefore it is difficult to compile event on today Windows.
_(How to do that is explained in [windows compilation section].)_

It is a C++ console application written using [wxWidgets framework] in 2.8.12 version.
This framework is cross-platform and that's why we decided to try compile whole project on Linux/Mac.

Beside the C++ core there are multiple plugins and script for 3d modeling programs.
The [Blender] plugin is written in Python but some aspects of those scripts will had to be cross-platformed.


## Windows compilation

_Original and more detailed build instruction can be found in:_ `KrxImpExp\devdoc\how_to_build.txt`

Here is shorter version:

1. Compilation requires Visual Studio 2010 Express.

2. Before opening the solution a few environmental variables are required.
   All of them can be found in: `KrxImpExp\build\config_pathes.reg` file.
   But only three of them are required for compilation:
   * WX - Path to [wxWidgets framework] source folder.
          Should contain compiled binaries.
          To compile see next step.
   * KRXIMPEXP - Path to [KrxImpExp plugin] source.
   * KRXIMPEXP_INTERMEDIATE - Path for build results.

3. After creating required environmental variables you need to compile [wxWidgets framework] in `UNICODE DEBUG` configuration.
   To do this the `wxWidgets-2.8.12\build.bat` script was created.
   Just set the path to Visual Studio 2010 Express bin tools and run in from `wxWidgets-2.8.12\` location.

4. Now you can open `KrxImpExp\build\vc2010express\wxImpExpUI.sln` solution and build [KrxImpExp plugin]


## Linux compilation

_Work In Progress_

Required packages:
* build-essential
* pkg-config
* libgtk2.0-dev

To install execute:
```bash
sudo apt-get install build-essential
sudo apt-get install pkg-config
sudo apt-get install libgtk2.0-dev
```

To compile [wxWidgets framework] run `wxWidgets-2.8.12\build.sh` script with root:
```bash
cd wxWidgets-2.8.12
sudo build.sh
```

To compile [KrxImpExp plugin] run `KrxImpExp\build\linux\build.sh` script.


## Mac compilation

_Work In Progress_


[KrxImpExp plugin]: http://krximpexp.sourceforge.net/
[History of Khorinis]: https://historyofkhorinis.org/
[Gothic]: https://en.wikipedia.org/wiki/Gothic_(video_game)
[Blender]: https://www.blender.org/
[wxWidgets framework]: https://www.wxwidgets.org/
[Python]: https://pl.python.org/

[windows compilation section]: #windows-compilation
