# flags.hh

A simple `getopt` wrapper for C++ in one header file.

## Usage

```
#include "flags.hh"
```

### Declaration

```
// Declare a non-boolean flag
template <typename T>
void Var(T & var, char shortFlag, std::string longFlag, T defaultValue, std::string description, std::string descriptionGroup = "");

// Declare a boolean flag
void Bool(bool & var, char shortFlag, std::string longFlag, std::string description, std::string descriptionGroup = "");
```

When setting through command-line flags:

`Flags::Var()`: the flag should be followed with an argument which is stored in the referenced variable `var`.

`Flags::Bool()`: if the flag is presented, the referenced boolean variable `var` is set to `true`; otherwise, it's set to `false`. The command-line flag should NOT be followed with an argument.

#### `var`

reference to the variable to store value.

#### `shortFlag`

short option of the declared variable; one character; this shouldn't contain the leading dash `-`.

#### `longFlag`

long option of the declared variable; this shouldn't contain the leading double dashes `--`.

#### `defaultValue`

the default value for the variable (non-boolean only).

#### `description`

description of the option for the help message; if this is too long, it will be wrapped.

#### `desciptionGroup`

if not empty, it is used to organize options into groups.

### Parsing

```
bool Parse(int argc, char ** argv);
```

### Auto-generated Help Message

```
void PrintHelp(char * argv0, std::ostream & to = std::cout);
```



## Example

### Code

```c++
/* Song Gao <song@gao.io> | June 2015 */

#include "Flags.hh"

#include <cstdint>
#include <iostream>

int main(int argc, char ** argv) {
  uint64_t var1;
  uint32_t var2;
  int32_t var3;
  std::string str;
  bool b, help;

  Flags flags;

  flags.Var(var1, 'a', "var1", uint64_t(64), "This is var1!");
  flags.Var(var2, 'b', "var2", uint32_t(32), "var2 haahahahaha...");
  flags.Var(var3, 'c', "var3", int32_t(42), "var3 is signed!", "Group 1");
  flags.Var(str, 's', "str", std::string("Hello World!"), "This is a string, and the description is too long to fit in one line and has to be wrapped blah blah blah blah...", "Group 1");
  flags.Bool(b, 'd', "bool", "this is a bool variable", "Group 2");

  flags.Bool(help, 'h', "help", "show this help and exit", "Group 3");

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
  std::cout << "b:    " << (b ? "set" : "unset") << std::endl;

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
  -s --str [default: Hello World!]
      This is a string, and the description is too long to fit in one line and h
      as to be wrapped blah blah blah blah...

Group 2:
  -d --bool [default: (unset)]
      this is a bool variable

Group 3:
  -h --help [default: (unset)]
      show this help and exit

```

```
$ ./example -a1 --var2 2 -c 3 -s 'multi word string' --bool
var1: 1
var2: 2
var3: 3
str:  multi word string
b:    set
```

```
$ ./example
var1: 64
var2: 32
var3: 42
str:  Hello World!
b:    unset
```
