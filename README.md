# flags.cc

A light-weight `getopt` wrapper for C++. Just two header files.

## Example

### Code

```c++
#include "Flags.hh"

#include <iostream>

int main(int argc, char ** argv) {
  uint64_t var1;
  uint32_t var2;
  int32_t var3;
  std::string str;
  bool flag, help;

  Flags flags;

  flags.Var(var1, 'a', "var1", uint64_t(64), "This is var1!");
  flags.Var(var2, 'b', "var2", uint32_t(32), "var2 haahahahaha...");
  flags.Var(var3, 'c', "var3", int32_t(42), "var3 is signed!", "Group 1");
  flags.Var(str, 's', "str", std::string("Hello!"), "This is a string, and the description is too long to fit in one line and has to be wrapped blah blah blah blah...", "Group 1");
  flags.Flag(flag, 'f', "flag", "this is a flag", "Group 2");

  flags.Flag(help, 'h', "help", "show this help and exit", "Group 3");

  if (!flags.Parse(argc, argv)) {
    flags.PrintHelp(argv[0]);
    return 1;
  } else if (help) {
    flags.PrintHelp(argv[0]);
    return 0;
  }

  std::cout << "var1: " << var1 << std::endl;
  std::cout << "var2: " << var2 << std::endl;
  std::cout << "var3: " << var3 << std::endl;
  std::cout << "str:  " << str << std::endl;
  std::cout << "flag: " << (flag ? "set" : "unset") << std::endl;

  return 0;
}
```

### Outputs

```
$ ./example -h
Usage: ./example [options]

  -a --var1 [default: 64]
      This is var1!
  -b --var2 [default: 32]
      var2 haahahahaha...

Group 1:
  -c --var3 [default: 42]
      var3 is signed!
  -s --str [default: Hello!]
      This is a string, and the description is too long to fit in one line and h
      as to be wrapped blah blah blah blah...

Group 2:
  -f --flag [default: (unset)]
      this is a flag

Group 3:
  -h --help [default: (unset)]
      show this help and exit
```

```
$ ./example -a1 --var2 2 -c 3 -sHahaha -f
var1: 1
var2: 2
var3: 3
str:  Hahaha
flag: set
```

```
$ ./example
var1: 64
var2: 32
var3: 42
str:  Hello!
flag: unset
```
