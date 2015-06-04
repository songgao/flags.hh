
/* Song Gao <song@gao.io> | June 2015 */

// This file provides implementations of template member function of Flags
// class. It should not be used directly. Include `Flags.hh` instead.

#include "Flags.hh" // to make vim-YCM happy

#include <sstream>

template <typename T>
void Flags::entry(struct option & op, char shortFlag, std::string longFlag, T & defaultValue, std::string description, std::string descriptionGroup) {
  if (!shortFlag && !longFlag.size()) {
    throw std::string("no flag specified");
  }

  if (shortFlag) {
    if (this->setters.find((int)(shortFlag)) != this->setters.end()) {
      throw std::string("short flag exists: ") + shortFlag;
    }
    this->optionStr += shortFlag;
    op.val = shortFlag;
  } else {
    op.val = this->autoId++;
  }
  if (longFlag.size()) {
    if (this->longFlags.find(longFlag) != this->longFlags.end()) {
      throw std::string("long flag exists: ") + longFlag;
    }
    op.name = this->longFlags.insert(longFlag).first->c_str();
  }

  op.flag = NULL;

  // generate help item
  std::stringstream ss;
  ss << "  ";
  if (shortFlag) {
    ss << "-" << shortFlag << " ";
  }
  if (longFlag.size()) {
      ss << "--" << longFlag << " ";
  }
  ss << "[default: " << defaultValue << "]";
  ss << std::endl;
  constexpr size_t step = 80 - 6;
  for (size_t i = 0; i < description.size(); i += step) {
    ss << "      ";
    if (i + step < description.size()) {
      ss << description.substr(i, step) << std::endl;
    } else {
      ss << description.substr(i);
    }
  }
  this->help[descriptionGroup].push_back(ss.str());
}

template <typename T>
void Flags::Var(T & var, char shortFlag, std::string longFlag, T defaultValue, std::string description, std::string descriptionGroup) {
  struct option op;
  this->entry(op, shortFlag, longFlag, defaultValue, description, descriptionGroup);

  this->optionStr += ":";

  op.has_arg = required_argument;
  var = defaultValue;

  this->setters[op.val] = std::bind(&Flags::set<T>, this, std::ref(var), std::placeholders::_1);

  this->options.push_back(op);
}

void Flags::Flag(bool & var, char shortFlag, std::string longFlag, std::string description, std::string descriptionGroup) {
  struct option op;
  this->entry(op, shortFlag, longFlag, "(unset)", description, descriptionGroup);

  op.has_arg = no_argument;
  var = false;

  this->setters[op.val] = [&var](std::string) {
    var = true;
  };

  this->options.push_back(op);
}

bool Flags::Parse(int argc, char ** argv) {
  this->options.push_back({NULL, 0, NULL, 0});
  int ch;
  while ((ch = getopt_long(argc, argv, this->optionStr.c_str(), &this->options[0], NULL)) != -1) {
    auto it = this->setters.find(ch);
    if (it != this->setters.end()) {
        if (optarg) {
          it->second(optarg);
        } else {
          it->second("");
        }
    } else {
      return false;
    }
  }
  return true;
}

void Flags::PrintHelp(char * argv0, std::ostream & to) {
  to << "Usage: " << argv0 << " [options]" << std::endl <<std::endl;
  for (auto& it : this->help) {
    if (it.first.size()) {
      to << it.first << ":" << std::endl;
    }
    for (auto& h : it.second) {
      to << h << std::endl;
    }
    to << std::endl;
  }
}

template <typename T>
void Flags::set(T & var, std::string optarg) {
  std::stringstream ss(optarg);
  ss >> var;
}
