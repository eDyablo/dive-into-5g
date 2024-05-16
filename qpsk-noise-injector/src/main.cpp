#include <iostream>
#include <cxxopts.hpp>

#include "qpsk/reader.hpp"
#include "noise_injector.hpp"

auto constexpr snr_option = "snr";

struct options_t : public cxxopts::ParseResult {
  bool has_snr() const {
    return count(snr_option);
  }

  auto snr() const {
    return qpsk::snr_t{(*this)[snr_option].as<float>()};
  }
};

auto get_options(int argc, char const* argv[]) {
  auto definition = cxxopts::Options{""};
  definition.add_options()(
    snr_option, "", cxxopts::value<float>()
  );
  try {
    definition.parse_positional({snr_option});
    return options_t{definition.parse(argc, argv)};
  } catch (...) {
    return options_t{cxxopts::ParseResult{}};
  }
}

void output_symbols_untouched() {
  qpsk::reader_t{}.read(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(),
    std::ostream_iterator<qpsk::symbol_t>(std::cout, ""));
}

void output_distorted_symbols(qpsk::snr_t snr) {
  qpsk::reader_t{}.read(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(),
    qpsk::noise_injector_t{snr}.iterator(std::ostream_iterator<qpsk::symbol_t>(std::cout, "")));
}

int main(int argc, char const* argv[]) {
  auto const options = get_options(argc, argv);
  if (options.has_snr()) {
    output_distorted_symbols(options.snr());
  } else {
    output_symbols_untouched();
  }
}
