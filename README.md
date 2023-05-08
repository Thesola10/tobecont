# ToBeContinued

Does what it says on the tin. You know these "to be continued" freeze-frame videos? Now, on a desktop near you!

## Requirements

 - SDL2 for all targets

### `x11` backend

 - An X11 server which implements a root window. This means rootless XWayland (as used in Wayland desktop environments) **will not work**.
 - `libX11` for taking the screenshot


On build machine, `gcc` and `pkg-config` are also required.

## Building

<details>
<summary>

### Linux and other GNU-compatible platforms

</summary>

Clone the repository and run `make`. If you have a system-wide installation of SDL2
and X11, this should work out of the box.

The provided Makefile supports a couple extra options which should help target
other platforms:

 - The usual `CC` and `LD` to specify a cross-compiler. You shouldn't need to redefine
   them.
 - Like in the Linux kernel, `O` designates an alternate output directory.
 - `BACKEND` selects a specific method to take a screenshot. Individual backends
   can be found as subdirectories of `src`.

</details>

<details>
<summary>

### Microsoft Windows

</summary>

Building the executable on Windows has only been tested on [MSys2](https://msys2.org), with the `mingw32` toolchain. The `pc-msys2` toolchain may work provided that you have the SDL2 library available.

The `x11` backend can be made to work, but `libX11` is not available on the MSys2 repositories, and an X server like `vcXsrv` is required on the target machine.

If you are running on macOS or Linux, you can run `./nix build .#forWindows` to cross-compile the Windows executable.
The generated `SDL2.dll` file will need to be provided alongside the executable in order for it to work.

</details>

<details>
<summary>

### macOS

</summary>

Ensure that you have installed the macOS SDK (which can be found in Xcode), and
build using the provided Makefile.
The preferred backend is `quartz`, as it can be made to work without installing an
X server.

Building the `x11` backend requires an X server such as [XQuartz](https://xquartz.org),
as well as `libX11` and its development headers. An X server will be required on the
target machine as well.

It is currently not possible to cross-compile to macOS from Linux using Nix, due to
the lack of Darwin's `libSystem`. [`osxcross`](https://github.com/tpoechtrager/osxcross)
might work, you are free to try.

</details>
