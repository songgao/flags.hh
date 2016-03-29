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
