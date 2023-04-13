# Windows

# Config Structure

Check the the [Windows Config Structure](./config_win)

<br/>
<br/>

**NOTE**: The building and installation happens through MSYS2, but the program is supposed to be run using Powershell.

# Building from Source

Tools required:
- [MSYS2](https://www.msys2.org/)
- Powershell (Almost certainly pre-installed on your Windows)

**1) Open MSYS2 terminal:**

**NOTE**: Unless you know how to set `http_proxy` and `https_proxy` environment variables,
I would suggest you to use mobile data for this step.

For 64-bit Windows:
```sh
$ pacman -Syu git make mingw-w64-x86_64-toolchain --noconfirm
```

**2) Add `gcc` to path:**

In MSYS2 terminal:
```sh
$ echo "export PATH=/mingw64/bin:$PATH" >> ~/.bashrc
$ source ~/.bashrc
```

Check if `gcc` command works:
```sh
$ gcc --version
```

**3) Build/Install:**

Clone the repo, and [go to the folder in MSYS2 terminal](https://stackoverflow.com/questions/11376899/browsing-folders-in-msys).

While staying in MSYS2 terminal:

Build:
```sh
$ make OS=WIN32
```

Install:
```sh
$ make install OS=WIN32
```

# Development

For development, follow all the steps above, except change the commands for build and install in
final step to the below:

Build:
```sh
$ make OS=WIN32 VARIANT=debug
```

Install:
```sh
$ make install OS=WIN32 VARIANT=debug
```

Also ensure auto CRLF is True (stay in windows terimanl:
```sh
$ git config --global core.autocrlf false
```

# Initial Setup after installation

The following steps are run in Powershell.

**1) Set Execution Policy:**

Open a powershell window in **Administrator Mode**, and then:
```sh
Set-ExecutionPolicy Unrestricted
```

**NOTE**: If you followed this step, please be **VERY** careful of scripts found on the internet, and only run scripts from trusted source. If you regret your decision of following the above command, you can revert back using:
```sh
$ Set-ExecutionPolicy Restricted
```
If you set it back to `Restricted`, I'm sorry you can not use this utility (yet).

**2) Get the PATH of `proxy.exe`'s directory:**

In Powershell:
```sh
echo "C:/Users/$env:USERNAME/proxy/"
```

**3) Add to PATH:**

Taskbar -> Search -> "Edit The System Enviornment Variables" -> "Environment Variables"

Then under "System Variables" -> Double-click "Path" -> "New" -> Paste the path from Step 1.

Then "Ok" -> "Ok" -> "Ok".

Then close the powershell used in Step 1.

# Run

**NOTE**: If you followed the initial setup steps, please remember to close its powershell.

In a powershell/cmd window
```sh
$ proxy
```

That's it.

# Contributing

Please check [Contributing Guidelines](./CONTRIBUTING.md)
