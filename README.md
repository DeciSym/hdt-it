## Build

Test system:
- Ubuntu 22.04.3 LTS

Build hdt-lib first.

```
sudo apt get libserd-dev
cd hdt-lib
make
```

The hdt-it tool has a `hdt-it.pro` file for building the Qt project
with `qmake`.

```
sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
cd ../hdt-it
qmake hdt-it.pro
make
```
