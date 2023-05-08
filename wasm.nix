{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "tobecont";
  src = ./.;

  nativeBuildInputs = with pkgs;
    [ emscripten
      llvmPackages.bintools
    ];

  buildPhase = ''
    make BACKEND=wasm CC=emcc LD=wasm-ld
  '';

  #TODO: determine how emscripten outputs things
  installPhase = ''
    touch $out
  '';
}
