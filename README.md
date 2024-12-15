---
 На проекте: Лубсанов Д.А., Поляков И.А.

---

# pdp8

PDP-8 Emulator Project in C++

## General Tasks

* CPU emulator  (PDP-8/I)
* Peripherals (first and foremost EAE, memory extensions)
* GUI (Dear ImGUI-docked)

## Expected functionality

* Running programs
* Interactive CLI
* PTTY
* GUI

## Main Manuals

* [Small Computer Handbook, 1973 ed.](http://www.vandermark.ch/pdp8/uploads/PDP8/PDP8.Manuals/DEC-S8-OSSCH-A.pdf)
* [Processor Maintenance Manual, 1973, vol. 1](http://www.vandermark.ch/pdp8/uploads/PDP8/PDP8.Manuals/DEC-8E-HR1C-D.pdf)
* [Small Computer Handbook, 1970 ed.](https://bitsavers.org/pdf/dec/pdp8/handbooks/SmallComputerHandbook_1970.pdf)
* [Processor Maintenance Manual, Mar. 1970, vol. 1](https://bitsavers.org/pdf/dec/pdp8/pdp8i/DEC-8I-HR1A-D_8Imaint_Mar70.pdf)

## Running

The project is built using CMake

```bash
cmake -S . -B /build
cd build
make pdp8
```
