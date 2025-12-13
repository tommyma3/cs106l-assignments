#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  Corpus tokens;

  auto spaces = find_all(source.begin(), source.end(), [] (char x) {return std::isspace(x);});

  std::insert_iterator<Corpus> tokens_insert = std::insert_iterator(tokens, tokens.end());

  auto out_range = std::transform(spaces.begin(), spaces.end() - 1, spaces.begin() + 1, tokens_insert, 
      [&source] (auto x, auto y) {return Token(source, x, y);});

  std::erase_if(tokens, [](const auto& token) {return token.content.empty();});

  return tokens;

}


std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */

  namespace rv = std::ranges::views;

  auto view = source 
      | rv::filter([&dictionary] (const Token& token) {return !dictionary.contains(token.content);})
      | rv::transform([&dictionary] (const Token& token) {
            auto mispell_view = dictionary 
                                  | rv::filter([&token] (const std::string& vocab) {return levenshtein(token.content, vocab) == 1;});
            std::set<std::string> suggestions(mispell_view.begin(), mispell_view.end());
            return Misspelling(token, suggestions);
          })
      | rv::filter([] (const Misspelling& mispelling) {return !mispelling.suggestions.empty();});
  
  std::set<Misspelling> misses(view.begin(), view.end());
  return misses;
};

/* Helper methods */

#include "utils.cpp"