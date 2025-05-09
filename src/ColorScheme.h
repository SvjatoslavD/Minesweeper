//
// Created by svjat on 5/9/2025.
//

#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include "SFML/Graphics.hpp"

constexpr sf::Color mono_green     = sf::Color(166, 226, 46);   // Strings
constexpr sf::Color mono_red       = sf::Color(249, 38, 114);   // Keywords, errors
constexpr sf::Color mono_orange    = sf::Color(253, 151, 31);   // Constants, numbers
constexpr sf::Color mono_yellow    = sf::Color(230, 219, 116);  // Classes, attributes
constexpr sf::Color mono_blue      = sf::Color(102, 217, 239);  // Functions, methods
constexpr sf::Color mono_purple    = sf::Color(174, 129, 255);  // Operators, keywords

constexpr sf::Color mono_grey_dark     = sf::Color(39, 40, 34);    // Background
constexpr sf::Color mono_grey_medium   = sf::Color(117, 113, 94);  // Comments
constexpr sf::Color mono_grey_light    = sf::Color(248, 248, 242); // Default text (Foreground)

#endif //COLORSCHEME_H
