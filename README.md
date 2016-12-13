# stm32 MacOS	[![Build Status](https://travis-ci.org/but0n/stm32_MacOS.svg?branch=master)](https://travis-ci.org/but0n/stm32_MacOS)

Simple Yet Powerful SDK for stm32f1

## Installation

```
$ brew tap px4/px4
$ brew install gcc-arm-none-eabi
```

```
$ git clone https://github.com/but0n/stm32_MacOS.git
```
You may need some tools as follows:

* `stm32flash` </br>
Flash program for the STM32 ARM processors using the ST serial bootloader over UART or I2C
* `coreutils` </br>
Read Path

stm32flash

```
$ brew install autoconf
$ brew install automake
$ brew install pkg-config
```

```
$ git clone https://github.com/ARMinARM/stm32flash.git
$ cd stm32flash
$ make
```

coreutils

```
$ brew install coreutils
```


## Makefile Config

```
$ ls -l /dev/
```
* Find your device name (Like  `tty.SLAB_USBtoUART`)</br>
* Change Makefile (`flash`)

And Config `linker.ld`


## Usage

```
$ make
```

 - Cross compile

```
$ make flash
```

 -  Flash program

```
$ make dump
```

 - Disassembly

```
$ make clean
```

 - Clean

```
$ make tty
```

 - Serial debug after flash program
