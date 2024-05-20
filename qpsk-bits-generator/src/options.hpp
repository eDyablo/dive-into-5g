#pragma once

#include <cxxopts.hpp>
#include <filesystem>
#include <string>

class options_t : public cxxopts::ParseResult {
  auto constexpr static repetition_count_option = "number";
  auto constexpr static pattern_option = "pattern";

  static auto define() {
    auto definition = cxxopts::Options{""};
    definition.add_options()
      (pattern_option, "", cxxopts::value<std::string>())
      (repetition_count_option, "", cxxopts::value<unsigned int>());
    return definition;
  }

public:
  options_t(int argc, char const* argv[]) {
    auto definition = define();
    definition.parse_positional({pattern_option, repetition_count_option});
    static_cast<cxxopts::ParseResult&>(*this) = definition.parse(argc, argv);
  }

  auto pattern() const {
    return (*this)[pattern_option].as<std::string>();
  }

  auto has_pattern() const {
    return count(pattern_option) and not std::empty(pattern());
  }

  auto has_repetition_count() const {
    return count(repetition_count_option);
  }

  auto repetition_count() const {
    return (*this)[repetition_count_option].as<unsigned int>();
  }

  auto finite_repetition() const {
    return has_pattern() and has_repetition_count();
  }

  auto infinite_repetition() const {
    return has_pattern() and not finite_repetition();
  }
};
