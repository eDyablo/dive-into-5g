#include <iostream>
#include <iterator>

#include "qpsk/reader.hpp"
#include "demodulator.hpp"

int main() {
  qpsk::reader_t{}.read(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(),
    qpsk::demodulator_t{'0', '1'}.iterator(std::ostream_iterator<char>(std::cout, "")));
}
