{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "tobecont";
  src = ./.;

  nativeBuildInputs = with pkgs;
    [ emscripten
      binaryen
      llvmPackages.bintools
    ];

  buildPhase = ''
    make BACKEND=wasm CC=emcc LD=wasm-ld AS=wasm-as
  '';

  #TODO: determine how emscripten outputs things
  installPhase = ''
    touch $out
  '';
}
