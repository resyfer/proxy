# Proxy

Control the proxy settings with one command, and as configured as you want it to
be! Easier time changing from one proxy to another in the campus or any corporate http proxy!

Cross-platform, and has 0 dependencies!!

# Demo
[Screencast from 2023-04-11 00-17-04.webm](https://user-images.githubusercontent.com/74897008/230973059-8f2ff77c-3058-4e4f-8549-f02631532836.webm)

[Screencast from 2023-04-11 00-27-43.webm](https://user-images.githubusercontent.com/74897008/230973961-a21bbb1b-2938-4e3f-8cee-0412e758ce69.webm)

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

# Development and Building from Source

The instructions are different based on the operating systems, so please have a look at [Windows Instructions](./Windows.md) or [Unix instructions](./Unix.md)

**NOTE**: The only elements in `extra` supported yet are `git` and `npm`

# Uninstalling
```sh
$ proxy -r
```
