#pragma once

#include <cxxopts.hpp>
#include <sstream>

class options_t : public cxxopts::ParseResult {
  auto constexpr static sampling_option = "sampling";
  auto constexpr static interval_option = "interval";

  auto constexpr static default_interval() {
    auto const stream = std::stringstream{} << 1'000'000;
    return stream.str();
  }

  auto static define() {
    auto definition = cxxopts::Options{""};
    definition.add_options()
      (sampling_option, "", cxxopts::value<std::string>())
      (interval_option, "", cxxopts::value<size_t>()->default_value(default_interval()));
    return definition;
  }

public:
  options_t(int argc, char const* argv[]) {
    auto definition = define();
    definition.parse_positional({sampling_option, interval_option});
    static_cast<cxxopts::ParseResult&>(*this) = definition.parse(argc, argv);
  }

  auto has_sampling() const {
    return count(sampling_option);
  }

  auto sampling() const {
    return (*this)[sampling_option].as<std::string>();
  }

  auto interval() const {
    return (*this)[interval_option].as<size_t>();
  }
};
