# ToBeContinued

Does what it says on the tin. You know these "to be continued" freeze-frame videos? Now, on a desktop near you!

## Requirements

 - SDL2 for all targets

<details>
<summary> `x11` backend </summary>

 - `libX11` for taking the screenshot

</details>

<details>
<summary> `win32` backend </summary>

 - Windows GDI headers for screenshot

</details>

<details>
<summary> `quartz` backend </summary>

 - _(WIP, not yet implemented)_

</details>

On build machine, `gcc` and `objcopy` are also required.
 
## Build:

The provided Makefile supports a couple extra options which should help target
other platforms:

 - The usual `CC` and `LD` to specify a cross-compiler. You shouldn't need to redefine
   them.
 - Like in the Linux kernel, `O` designates an alternate output directory.
 - `BACKEND` selects a specific method to take a screenshot. Individual backends
   can be found as subdirectories of `src`.

If you have `nix` installed (or use [`nix-portable`](https://github.com/DavHau/nix-portable)),
you can use the provided `win.nix` file to cross-compile to Windows. The
generated `SDL2.dll` file will need to be provided alongside the executable
in order for it to work.
