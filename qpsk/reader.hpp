#pragma once

#include <algorithm>
#include <array>
#include <limits>
#include <ranges>
#include <sstream>

#include "qpsk/symbol.hpp"

namespace qpsk {
  struct reader_t {
    template <typename I, typename O>
    void read(I first, I last, O destination) const {
      constexpr auto delimiter_to_whitespace = [](auto item) {
        using std::array;
        using std::ranges::contains;
        constexpr auto delimiters = array{' ', '\t', '(', ')'};
        if (contains(delimiters, item)) {
          return ' ';
        }
        return item;
      };

      constexpr auto to_float = [](auto range) {
        using std::numeric_limits;
        using std::ranges::contains;
        using std::string;
        using std::stringstream;
        using std::views::filter;
        auto str = string{numeric_limits<float>::digits10 + 1};
        auto stream = stringstream{str};
        constexpr auto is_symbol = [](auto item) {
          using std::array;
          constexpr auto symbols = array{
            '+', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
          return contains(symbols, item);
        };
        for (auto item: range | filter(is_symbol)) {
          stream << item;
        }
        float number;
        stream >> number;
        return number;
      };

      using std::views::lazy_split;
      using std::ranges::subrange;
      using std::views::transform;
      using std::begin;
      using std::end;

      auto pairs_sequence = subrange(first, last)
        | transform(delimiter_to_whitespace)
        | lazy_split(' ');
      for (auto pair: pairs_sequence) {
        auto numbers = pair | lazy_split(',');
        qpsk::symbol_t symbol{};
        auto i = begin(numbers);
        if (i == end(numbers))
          continue;
        symbol.in_phase = to_float(*i);
        if (++i == end(numbers))
          continue;
        symbol.quadrature = to_float(*i);
        if (symbol.is_valid()) {
          *destination = symbol;
        }
      }
    }
  };
}
