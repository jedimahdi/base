{ pkgs ? import <nixpkgs> { } }:
let
  buildInputs = with pkgs; [
    criterion
  ];
in
pkgs.mkShell {
  inherit buildInputs;
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath buildInputs;
}
