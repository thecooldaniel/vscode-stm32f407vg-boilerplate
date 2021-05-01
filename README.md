# VS Code STM32F407VG Discovery Development Environment

## Goal
To provide a plug-and-play embedded environment and project boilerplate for low-friction startup and continued development using open-source tools on Linux.

![Demo](https://camo.githubusercontent.com/f761c69c3f52ea2c147adf70defbe3602db98fd49aa4912aa763e0dcd8ad61f5/68747470733a2f2f692e696d6775722e636f6d2f55764a4b6677362e676966)

## Features
1. Ready-to-go boilerplate. Get started on C/ASM programming immediately!
2. Breakpoints, watches, and register/DSP inspection via OpenOCD, arm-none-eabi-gdb, and Corext-Debug
3. Quickly and easily compare source C/ASM lines with the compiled output via Disassembly Explorer

## Intended Audience
This project is aimed specifically at individuals programming for the STM32F407VG using a flavor of Linux. It is possible to configure this project to work with other microcontrollers (assuming it is supported by [libopencm3](https://github.com/libopencm3/libopencm3)) and/or under Windows, but it is outside the scope of this project.

## Installation
### I. Dependencies
1. [Visual Studio Code](https://code.visualstudio.com/)
2. [The GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
3. [OpenOCD](http://openocd.org/)
   
### II. Local Setup
1. Ensure all of the above dependencies are met and their binaries added to your PATH.
2. Clone this repository using `--recurse-submodules` i.e. `git clone --recurse-submodules ...`
3. Alternatively after cloning, using the terminal, navigate to the root folder folder and run:
```bash
   git submodule init
   git submodule update
```
4. Navigate to the `project` folder and run:
```bash
   make lib
```
### III. VS Code Plugins
1. You will need to install two plugins: [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) and [Disassembly Explorer](https://marketplace.visualstudio.com/items?itemName=dseight.disasexpl)
(These plugins are also workspace recommendations, so VS Code should prompt you when opening the folder to install)
```bash
   code --install-extension marus25.cortex-debug
   code --install-extension dseight.disasexpl
```
2. Optional, but recommended: [ARM](https://marketplace.visualstudio.com/items?itemName=dan-c-underwood.arm) (ARM ASM syntax highlighting)
```bash
   code --install-extension dan-c-underwood.arm
```

### IV. Usage
1. Open the root folder in VS Code
2. Open `main.c` in-editor
3. Set a breakpoint
4. Hit F5, debugging should begin!
5. Hit F1 and type 'Disassembly explorer' until the 'Show' option is available. Select it to compare source and compilation side-by-side. Note: You will need to execute this command for each source file you wish to compare.

## Notes
* The amount of available memory exposed to the compiler via the linker script is reduced from 128 KiB to 112 KiB to force the stack into SRAM1. Access to SRAM2 is slower and negatively impacts performance. [[1](https://kannwischer.eu/papers/2019_nttm4.pdf)]
* To use the `libopencm3` default, remove `LDSCRIPT = stm32f407vg.ld` from the appropriate `Makefile` entries.
* `-flto` is added to the gcc flags by default to improve performance [[1](https://kannwischer.eu/papers/2019_nttm4.pdf)]. Depending on the version of gcc you are using, [this may or may not have any effect](https://stackoverflow.com/questions/31688069/requirements-to-use-flto). 

## FAQ
**Will this work with the STM32F4xx ?**

Maybe! Change the `DEVICE` variable in the `Makefile`, update the `CFLAGS`, and you will probably need to switch to the libopencm3 generated `ld` script for your device. (see Note #2 above). You will also need to provide a new `.svd` and make sure to add it to the OpenOCD configuration in `launch.json`.

**Can I add source files?**

`main.c` and `main.asm` come pre-configured in the `Makefile`, tasks, and launch settings. If you would like to add more source files, remember to add them to the appropriate entry in the `Makefile`. If you want to change the name `main`, make sure to change all occurences in `tasks.json`, `launch.json`, and the `Makefile`.
   
**Can I use this on Windows?**

If you are on Windows 10 and want to use this project, I recommend using [VS Code Remote](https://code.visualstudio.com/docs/remote/remote-overview) and [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10). There may be extra configuration involved.

## Thanks
* [Marus](https://github.com/Marus) for Cortex-Debug
* [dseight](https://github.com/dseight) for Disassembly Explorer
* [dan-c-underwood](https://github.com/dan-c-underwood) for ARM
* All contributors to the excellent `libopencm3` project

## References
1. Leon Botros, Matthias J. Kannwischer, and Peter Schwabe. _Memory-Efficient High-Speed Implementation of Kyber on Cortex-M4_, 2019, https://kannwischer.eu/papers/2019_nttm4.pdf
