#include <iostream>
#include <iterator>

#include "modulator.hpp"

int main() {
  qpsk::modulator_t{'0', '1'}.modulate(
    std::istream_iterator<char>(std::cin), std::istream_iterator<char>(),
    std::ostream_iterator<qpsk::symbol_t>(std::cout, " "));
}
