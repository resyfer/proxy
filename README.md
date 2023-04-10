# Proxy

Control the proxy settings with one command, and as configured as you want it to
be! Easier time changing from one proxy to another in the campus or any corporate http proxy!

Cross-platform, and has 0 dependencies!!

# Installation

**NOTE: Installation instructions don't work yet as there are not releases, but the following instructions are for how it *will* work in future**. Please [build from source](#building-from-source) in the meantime till there's a stable release!

Just download the zips from the [Releases](https://github.com/resyfer/proxy/releases)
according to your architecture and operating system. Unzip it and run the script
with the name `setup`.

Then open your terminal and type `proxy`. For more information, use the following
command:

```sh
proxy -h
```

# Building from source

Requirements:
- gcc
- make

OS: Linux

Clone this repo. Open the terminal and move into the project folder. Then:

```sh
$ sudo make install SHELL=zsh
```

The shell values can be `bash` or `zsh`. `bash` is the default value.


# Development

Requirements:
- gcc
- make
- uncrustify

```sh
$ sudo make install VARIANT=debug SHELL=zsh
$ proxy
```

The shell values can be `bash` or `zsh`. `bash` is the default value.

# Updating the config
```sh
$ proxy -u
```

# Config Structure
```
[proxy]
college = NITS
desktop = GNOME
os = Linux
shell = zsh
extra = extra_1, extra_2, extra_3, ..., extra_n

[Name 1]
host = 0.0.0.0
port = 0000

[Name 2]
host = 0.0.0.0
port = 0000

...

[Name m]
host = 0.0.0.0
port = 0000
```

**NOTE**: The only elements in `extra` supported yet are `git` and `npm`

# Uninstalling
```sh
$ proxy -r
```
