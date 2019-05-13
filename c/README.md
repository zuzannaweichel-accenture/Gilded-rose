# Instructions for building GildedRoseTest

## Install CppUTest using homebrew:
```
brew install cpputest
```
## Edit Makefile to set CPPUTEST_HOME
__You may not need to change this.__

You can verify the location of CppUTest with the following command:
```
find / -name "CppUTest" 2>/dev/null
```
Any path that has the `include` and `lib` directories with `CppUTest` will work.
For example, my list from the `find` command was:
```
/usr/local/include/CppUTest
/usr/local/lib/CppUTest
/usr/local/Cellar/cpputest/3.8/include/CppUTest
/usr/local/Cellar/cpputest/3.8/lib/CppUTest
```
I placed `/usr/local` into the Makefile as this is the most generic option.
Homebrew creates a symlink into that directory for the specific installations.
This is very helpful and matches what is generally done on Linux environments.

## Build
To build the project:
```
make
```

## Run the Test
The `-c` option colors the output.
The `-v` option lists the test names.
These options may not be valuable when there is only one test. Just noting this
in case you add more tests to the project.
```
./GildedRoseTest -c -v
```
