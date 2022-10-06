{ pkgs ? import <nixpkgs> {}
, depsAreStatic ? true
}:

let
  pkgsCross = pkgs.pkgsCross.mingwW64;
  pkgsHost = if depsAreStatic then pkgsCross.pkgsStatic
                              else pkgsCross;
  sdl2Static = pkgsHost.SDL2.override { withStatic = true; };
in
pkgsCross.stdenv.mkDerivation {
  name = "tobecont";
  src = ./.;

  nativeBuildInputs = with pkgs;
    [ pkgconfig ];
  
  depsBuildHost = with pkgs;
    [ gcc binutils ];
  
  buildInputs = with pkgsHost; 
    [ sdl2Static ];

  buildPhase = ''
    make BACKEND=win32 OUTPUT=tobecont.exe CC=x86_64-w64-mingw32-gcc LD=x86_64-w64-mingw32-gcc OBJCOPY=x86_64-w64-mingw32-objcopy
  '';
  installPhase = ''
    mkdir -p $out
    cp tobecont.exe $out/tobecont.exe
    cp ${sdl2Static}/bin/SDL2.dll $out/SDL2.dll
  '';
}
