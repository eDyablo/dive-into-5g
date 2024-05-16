#include <iostream>
#include <iterator>

#include "qpsk/reader.hpp"
#include "demodulator.hpp"

int main() {
  qpsk::demodulator_t demodulator{'0', '1'};
  qpsk::reader_t reader;
  reader.read(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(),
    demodulator.iterator(std::ostream_iterator<char>(std::cout, "")));
}
