# stm32 MacOS	[![Build Status](https://travis-ci.org/but0n/stm32_MacOS.svg?branch=master)](https://travis-ci.org/but0n/stm32_MacOS)

Simple Yet Powerful SDK for stm32f1

## Installation

```
$ git clone https://github.com/but0n/stm32_MacOS.git
$ cd stm32_MacOS && make install
```

## Usage

```
$ make
```
 - Cross compile

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
 - USART Serial debug


## In-System Programming

### stm32flash (with USART):

 - Installation:

```
$ brew install autoconf
$ brew install automake
$ brew install pkg-config
$ git clone https://github.com/ARMinARM/stm32flash.git
$ cd stm32flash
$ make
```
 - Usage:

```
make tty
```

### dfu-util (with USB):
*Note: This way is only supply `STM32F105xx/107xx` devices. An external clock (8 MHz, 14.7456 MHz or 25 MHz.) is required for DFU
and CAN bootloader execution after the selection phase.*

 - Installation:

```
brew install dfu-util
```

 - Usage:

```
make dfu
```


---
*You may need some tools as follows:*

* `coreutils` </br>
Read Path

```
$ brew install coreutils
```
