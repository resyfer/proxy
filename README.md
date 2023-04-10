# Proxy

Control the proxy settings with one command, and as configured as you want it to
be!

# Installation

**NOTE**: Installations don't work yet, but the following instructions are for how
it *will* work in future.

Just download the zips from the [Releases](https://github.com/resyfer/proxy/releases)
according to your architecture and operating system. Unzip it and run the script
with the name `setup`.

Then open your terminal and type `proxy`. For more information, use the following
command:

```sh
proxy -h
```

# Building from source

Requiremenets:
- gcc
- make

OS: Linux

Clone this repo. Open the terminal and move into the project folder. Then:

```sh
sudo make install SHELL=bash
# or
sudo make install SHELL=zsh
```


# Development

Requirements:
- gcc
- make
- uncrustify

```sh
sudo make install VARIANT=debug SHELL=zsh
# or
sudo make install VARIANT=debug SHELL=bash

proxy
```

# Updating the config
```sh
proxy -u
```

# Uninstalling
```sh
proxy -r
```

# Config Structure
```toml
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