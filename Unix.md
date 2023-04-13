# Linux/Unix

# Config Structure

Check the the [Unix Config Structure](./config_unix)

<br/>
<br/>

**NOTE**: The building and installation happens through MSYS2, but the program is supposed to be run using Powershell.

# Building from Source

Tools required:
- gcc
- make

**1:**

Check if `gcc` command works:
```sh
$ gcc --version
```

**3) Build/Install:**

Clone the repo, and [go to the folder in MSYS2 terminal](https://stackoverflow.com/questions/11376899/browsing-folders-in-msys).

While staying in MSYS2 terminal:

Build:
```sh
$ make
```

Install:
```sh
$ sudo make install
```

**NOTE**: These instructions are for `bash`.
If you have a different preferred shell follow the following instructions:

The currently supported shell values are:
- `bash` (default)
- `zsh`

Build:
```sh
$ make SH=zsh
```

Install:
```sh
$ sudo make install SH=zsh
```

# Development

For development, follow all the steps above, except change the commands for build and install in
final step to the below:

Build:
```sh
$ make VARIANT=debug
```

Install:
```sh
$ make install VARIANT=debug
```
You can add your preferred shell like in Step 3.

# Contributing

Please check [Contributing Guidelines](./CONTRIBUTING.md)
