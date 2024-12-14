{
  lib,
  stdenv,
  # Note: either stdenv.mkDerivation or, for octaveFull, the qt-5 mkDerivation
  # with wrapQtAppsHook (comes from libsForQt5.callPackage)
  mkDerivation,
  fetchgit,
  libX11,
  libGL,
  libGLU,
  # Both are needed for discrete Fourier transform
  # - Include support for GNU readline:
  # - Build Octave Qt GUI:
  libiconv,
  darwin,
  cmake,
  qtbase,
  qtsvg,
  qt3d,
  jinja2-cli,
  qtscript,
  qttools,
}:
mkDerivation rec {
  version = "5.2.0";
  pname = "octave";

  src =
    (fetchgit {
      url = "git@github.com:panzergame/dxfplotter.git";
      rev = "1.4.1";
      hash = "sha256-V9yXIMt7j/pV94CiLuDEEbTSZpyNtVc0RBkyZejUuwI=";
      fetchSubmodules = true;
      leaveDotGit = true;
    })
    .overrideAttrs (_: {
      GIT_CONFIG_COUNT = 1;
      GIT_CONFIG_KEY_0 = "url.https://github.com/.insteadOf";
      GIT_CONFIG_VALUE_0 = "git@github.com:";
    });

  buildInputs =
    [
      qtbase
      qtsvg
      qt3d
    ]
    ++ (lib.optionals (!stdenv.isDarwin) [libGL libGLU libX11])
    ++ (lib.optionals (stdenv.isDarwin) [
      libiconv
      darwin.apple_sdk.frameworks.Accelerate
      darwin.apple_sdk.frameworks.Cocoa
    ]);
  nativeBuildInputs = [
    cmake
    jinja2-cli
    qtscript
    qttools
  ];

  doCheck = !stdenv.isDarwin;

  enableParallelBuilding = true;
}
