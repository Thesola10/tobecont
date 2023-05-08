{ description = "To Be Continued!";

  inputs.nixpkgs.url = github:nixos/nixpkgs;

  outputs = { self, nixpkgs, ... }:
  let
    emscriptenPackage = pkgs:
      pkgs.callPackage ./wasm.nix {};
    windowsPackage = pkgs:
      pkgs.callPackage ./win.nix {};
    x11Package = pkgs:
      pkgs.callPackage ./default.nix {};
    quartzPackage = pkgs:
      pkgs.callPackage ./default.nix { backend = "quartz"; };

    linuxPkgs = ar: { "${ar}-linux" =
      let pkgs = nixpkgs.legacyPackages."${ar}-linux";
      in
      {
        forWasm = emscriptenPackage pkgs;
        forWindows = windowsPackage pkgs;
        default = x11Package pkgs;
      };
    };
    darwinPkgs = ar: { "${ar}-darwin" =
      let pkgs = nixpkgs.legacyPackages."${ar}-darwin";
      in
      {
        forWasm = emscriptenPackage pkgs;
        forWindows = windowsPackage pkgs;
        default = quartzPackage pkgs;
        x11 = x11Package pkgs;
      };
    };
  in
  { packages =
      (linuxPkgs "x86_64") //
      (linuxPkgs "aarch64") //
      (darwinPkgs "x86_64") //
      (darwinPkgs "aarch64");
  };
}
