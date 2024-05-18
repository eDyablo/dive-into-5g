#pragma once

#include <cxxopts.hpp>

class options_t : public cxxopts::ParseResult {
  auto constexpr static repetition_count_option = "number";
  auto constexpr static pattern_option = "pattern";

  static auto define() {
    auto definition = cxxopts::Options{""};
    definition.add_options()
      (pattern_option, "", cxxopts::value<std::string>()->default_value(""))
      (repetition_count_option, "", cxxopts::value<unsigned int>());
    return definition;
  }

public:
  options_t(int argc, char const* argv[]) {
    auto definition = define();
    definition.parse_positional({pattern_option, repetition_count_option});
    static_cast<cxxopts::ParseResult&>(*this) = definition.parse(argc, argv);
  }

  auto finite_repetition() const {
    return count(repetition_count_option);
  }

  auto infinite_repetition() const {
    return not finite_repetition();
  }

  auto repetition_count() const {
    return (*this)[repetition_count_option].as<unsigned int>();
  }

  auto pattern() const {
    return (*this)[pattern_option].as<std::string>();
  }
};
