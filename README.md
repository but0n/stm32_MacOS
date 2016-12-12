[![Build Status](https://travis-ci.org/but0n/stm32_Mac.png)](https://travis-ci.org/but0n/stm32_Mac)
## Config
```
$ ls -l /dev/ 
```
* Find your device name (Mine is `tty.SLAB_USBtoUART`)</br>
* Then change Makefile (`flash`)

And Config file `linker.ld`


## Usage
```
$ make
```
> Cross compile `/src`

```
$ make flash
```
> Flash

```
$ make dump
```
> Disassembly 

```
$ make clean
```

# You may need some tools as follows:

* `stm32flash` </br>
Flash program for the STM32 ARM processors using the ST serial bootloader over UART or I2C
* `coreutils` </br>
Readlink
* `gcc-arm-none-eabi`

## stm32flash
install some tools that `make` need:

```
$ brew install autoconf
```

```
$ brew install automake
```

```
$ brew install pkg-config
```

Then install stm32flash:

```
$ git clone https://github.com/ARMinARM/stm32flash.git
$ cd stm32flash
$ make
```

## coreutils
```
$ brew install coreutils
```
## gcc-arm-none-eabi
```
$ brew top px4/px4
$ brew install gcc-arm-none-eabi
```

