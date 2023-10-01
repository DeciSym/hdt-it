# HDT-it

This repository currently includes notes for building the historical HDT-it on a
recent Linux distribution. The currently maintained codebase for HDT-it is https://github.com/rdfhdt/hdt-cpp.

## Build

Test system: Ubuntu 22.04.3 LTS

Build libcds-v1.0.12. Note that this sequence is non-reentrant. The
`make clean` command does not undo the results of the
compilation. Removing the contents from `includes` and `lib` seems to
help.

```
cd libcds-v1.0.12
mkdir includes
mkdir lib
make -j
cd ..
```

Build hdt-lib:

```
sudo apt install libserd-dev libraptor2-dev
cd hdt-lib
make -j
cd ..
```

The hdt-it tool has a `hdt-it.pro` file for building the Qt project
with `qmake`.

```
sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
cd hdt-it
qmake hdt-it.pro
make
```

The final binary will be `hdt-it/unix/HDT-it`.

## Test

Example HDT datasets can be found at
https://www.rdfhdt.org/datasets/. Note that some of the links are
dead. Therefore the file content should be verified before it is used
for testing.

## Issues

The C++ code has not been run through a lint tool. Therefore, it can
be difficult to evaluate changes versus other repositories.

The C++ code does not compile without warnings.

Each submodule is build separately. The dependent libcds and hdt-lib
are included directly in this repository rather than via reference to
their maintained sources.
