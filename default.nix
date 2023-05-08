{ pkgs ? import <nixpkgs> {}
, backend ? "x11"
, static ? false
}:

let
  pkgsHost = if static then pkgs.pkgsStatic
                       else pkgs;
in
pkgs.stdenv.mkDerivation {
  name = "tobecont";
  src = ./.;

  nativeBuildInputs = with pkgs;
    [ pkgconfig ];

  depsBuildHost = with pkgs;
    [ gcc binutils ];

  buildInputs = with pkgsHost;
    [ SDL2 ];

  buildPhase = ''
    ${ if backend == "quartz" then
    ''
      export CC="$CC -F${pkgs.darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks"
    '' else ""}
    make BACKEND=${backend}
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp tobecont $out/bin/tobecont
  '';
}
