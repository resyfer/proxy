1) Follow the [Development and Build Instructions in README](./README.md#development-and-building-from-source).
2) Code lines should not be more than 80 columns wide, unless necessary or for readability.
3) Tabs of width 4 for indentation for any C files. Not spaces.
4) Follow the coding style used in the codebase.
5) Clone the repo. Add upstream using:
```sh
$ git remote add upstream https://github.com/resyfer/proxy.git
```

5) If you want to add/request a feature, first open an issue regarding it in this repo.
6) The feature needs to be discussed as well as its implementation details. Wait for green signal from maintainer to start coding.
7) The above applied for new/existing issues as well as existsing feature requests.
8) Once green signal is received, make your changes in a new branch from main.
9) Push and create a Pull Request (PR).
10) The PR name should be "[#Issue-No.] Issue-Name]" eg. "[#1] Say Hi".
11) Make your commits. Always rebase before push:

```sh
$ git fetch upstream
$ git rebase upstream/main
```

12) Once the commits have been approved by maintainer, checkout your working branch, **rebase the branch** (as shown above) and then squash the commits using:
```sh
$ git reset --soft main
$ git add .
$ git commit -m "[#issue-no.] issue-name"
```

13) Wait for merge!
