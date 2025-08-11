# texinfo-amiga

This is Texinfo makeinfo, compiled for classic Amiga, without ixemul or other POSIX dependencies.

## [amigazen project](http://www.amigazen.com)

*A web, suddenly*

*Forty years meditation*

*Minds awaken, free*

**amigazen project** uses modern software development tools and methods to update and rerelease classic Amiga open source software. Our upcoming releases include a new AWeb, and a new Amiga Python 2.

Key to our approach is ensuring every project can be built with the same common set of development tools and configurations, so we created the ToolKit project to provide a standard configuration for Amiga development. All *amigazen project* releases will be guaranteed to build against the ToolKit standard so that anyone can download and begin contributing straightaway without having to tailor the toolchain for their own setup.

The original authors of the *Texinfo* software are not affiliated with the amigazen project. This software is redistributed on terms described in the documentation, particularly the files COPYING or LICENSE.md

Our philosophy is based on openness:

*Open* to anyone and everyone	- *Open* source and free for all	- *Open* your mind and create!

PRs for all of our projects are gratefully received at [GitHub](https://github.com/amigazen/). While our focus now is on classic 68k software, we do intend that all amigazen project releases can be ported to other Amiga-like systems including AROS and MorphOS where feasible.

## About ToolKit

**ToolKit** exists to solve the problem that most Amiga software was written in the 1980s and 90s, by individuals working alone, each with their own preferred setup for where their dev tools are run from, where their include files, static libs and other toolchain artifacts could be found, which versions they used and which custom modifications they made. Open source collaboration did not exist as we know it in 2025. 

**ToolKit** from amigazen project is a work in progress to make a standardised installation of not just the Native Developer Kit, but the compilers, build tools and third party components needed to be able to consistently build projects in collaboration with others, without each contributor having to change build files to work with their particular toolchain configuration. 

All *amigazen project* releases will release in a ready to build configuration according to the ToolKit standard.

Each component of **ToolKit** is open source and like *Texinfo* here will have it's own github repo, while ToolKit itself will eventually be released as an easy to install package containing the redistributable components, as well as scripts to easily install the parts that are not freely redistributable from archive.

## Requirements

- Amiga or Amiga-compatible computer with latest operating system software
- VBCC with PosixLib setup according to the ToolKit standard
- NDK3.2R4

## Installation

- copy SDK/C/makeinfo to SDK:C/ this being the standard location for ToolKit commands
- make sure SDK: exists as an assign to your ToolKit files root, and that SDK:C/ is in your path
- the ToolKit sdk-startup script will do this for you if you have it installed
- makeinfo can also be used standalone, in which case simply place the *makeinfo* binary somewhere in your path

## Changelog

- Refactored code to use available functions from VBCC PosixLib
- Added an Amiga specific alloca implementation
- Implemented new VMakefile to replace legacy makefile to build against NDK3.2 and ToolKit
- Partially implemented SAS/C SMakefile support (not complete)

## To Do

- Evaluate feasibility of updating to newer, but still Amiga-contemporary, versions such as 4.13, mostly for the HTML support
- Permanently fork the code and remove irrelevant files
- Fix SAS/C support
- Add unittests or test files - currently WIP
- Code review and hardening

## Contact 

- At GitHub https://github.com/amigazen/texinfo-amiga
- on the web at http://www.amigazen.com/toolkit/ (Amiga browser compatible)
- or email toolkit@amigazen.com

## [Aminet.readme](https://www.aminet.net/package/text/hyper/texinfo216)

***N.B. this readme contents dates to 1992! contact details may no longer be relevant!***

Short:	Version 2.16 of GNU texinfo
Uploader:	
Type:	text/hyper
Architecture:	m68k-amigaos
Date:	1992-11-16
Download:	text/hyper/texinfo216.lzh - View contents
Readme:	text/hyper/texinfo216.readme
Downloads:	570

This is version 2.16 of GNU texinfo. It contains the documentation,
TeXinfo macros and sources. You need this archive to compile
.texinfo docs.

## Acknowledgements

*Amiga* is a trademark of **Amiga Inc**. 