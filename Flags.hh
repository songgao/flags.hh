#ifndef FLAGS_HH
#define FLAGS_HH

/* Song Gao <song@gao.io> | June 2015 */

#include <cstdint>
#include <getopt.h>

#include <string>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Flags {
  public:
    Flags() : autoId(256) { }

    template <typename T>
    void Var(T & var, char shortFlag, std::string longFlag, T defaultValue, std::string description, std::string descriptionGroup = "");

    void Flag(bool & var, char shortFlag, std::string longFlag, std::string description, std::string descriptionGroup = "");

    bool Parse(int argc, char ** argv);
    void PrintHelp(char * argv0, std::ostream & to = std::cout);

  private:
    int autoId;
    std::map<int, std::function< void(std::string optarg) > > setters; // flag id -> setters
    std::set<std::string> longFlags;
    std::map<std::string, std::vector<std::string> > help; // group -> help itmes
    std::vector<struct option> options;
    std::string optionStr;

    template <typename T>
    void set(T & var, std::string optarg);

    template <typename T>
    void entry(struct option & op, char shortFlag, std::string longFlag, T & defaultValue, std::string description, std::string descriptionGroup);
};

#include "Flags.tcc"

#endif
