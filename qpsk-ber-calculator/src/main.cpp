#include <iostream>
#include <ranges>

#include "ber_calculator.hpp"
#include "options.hpp"

int main(int argc, char const* argv[]) {
  bool input_received = false;
  auto const receiving_input = [&input_received](auto) {
    input_received = true;
    return input_received;
  };
  auto const has_input = [&input_received](auto) {
    auto const received = input_received;
    input_received = false;
    return received;
  };
  auto const options = options_t{argc, argv};
  if (options.has_sampling()) {
    using namespace std::views;
    qpsk::ber_calculator_t{}.compute(
      istream<char>(std::cin) | take_while(receiving_input),
      repeat(options.sampling()) | join | take_while(has_input),
      std::ostream_iterator<qpsk::percentage_error_rate_t>(std::cout, " "), options.interval());
  }
}
