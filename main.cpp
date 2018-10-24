#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <iterator>

#include "fraction.h"

struct Symbol
{
    char symbol;
    Fraction low;
    Fraction high;
};

void frequency(std::string& str, std::map<char, Fraction>& mapFrequency);
Fraction encode_text(std::vector<Symbol> &vectStrRange);
std::string decode_text(unsigned length, Fraction number, std::vector<Symbol> &vectRange);

int main()
{
    std::setlocale(LC_ALL, "");
    // input a string to code;
    std::string str;
    std::cout << "Please, enter a string: ";
    std::getline(std::cin, str);

    std::map<char, Fraction> mapFrequency;
    // calculate frequency of symbols
    frequency(str, mapFrequency);

    std::vector<std::map<char, Fraction>::iterator> vectPtrMapFrequency;
    for (auto iter = mapFrequency.begin(); iter != mapFrequency.end(); ++iter)
    {
        vectPtrMapFrequency.push_back(iter);
    }

    std::cout << "\nUnique symbols and their frequency:\n";

    for (auto& item : mapFrequency)
    {
        std::cout << item.first << " "
                   << item.second.getNumerator() << "/" << item.second.getDenominator()
                   << std::endl;
    }

    std::vector<Symbol> vectRange(mapFrequency.size());
    // set a character and range for Symbols;
    vectRange[0].symbol = vectPtrMapFrequency[0]->first;
    vectRange[0].low = Fraction(0, 1);
    vectRange[0].high = vectPtrMapFrequency[0]->second;

    for (unsigned i = 1; i < vectRange.size(); ++i)
    {
        vectRange[i].symbol = vectPtrMapFrequency[i]->first;
        vectRange[i].low = vectRange[i - 1].high;
        vectRange[i].high = vectRange[i].low + vectPtrMapFrequency[i]->second;
    }

    std::cout << "\nRange of Symbols:\n";
    for (unsigned i = 0; i < vectRange.size(); ++i)
    {
        std::cout << vectRange[i].symbol << " "
                   << "[" << vectRange[i].low.getNumerator() << "/" << vectRange[i].low.getDenominator() << "; "
                   << vectRange[i].high.getNumerator() << "/" << vectRange[i].high.getDenominator() << ")\n";
    }
    std::cout << std::endl;

    std::vector<Symbol> vectStrRange;
    for (char ch : str)
    {

        for (Symbol x : vectRange)
        {
            if (ch == x.symbol)
            {
                vectStrRange.push_back(x);
                break;
            }
        }
    }
    for (unsigned i = 0; i < vectStrRange.size(); ++i)
    {
        std::cout << vectStrRange[i].symbol << " "
                   << "[" << vectStrRange[i].low.getNumerator() << "/" << vectStrRange[i].low.getDenominator() << "; "
                   << vectStrRange[i].high.getNumerator() << "/" << vectStrRange[i].high.getDenominator() << ")\n";
    }
    std::cout << std::endl;

    // to encode;
    std::cout << "\n------------------------------------------------------------\n";
    Fraction encode = encode_text(vectStrRange);
    std::cout << "Result of Arithmetic Coding: "
               << encode.getNumerator() << "/" << encode.getDenominator()
               << std::endl;
    std::cout << "------------------------------------------------------------\n";

    // to decode;
    std::cout << "------------------------------------------------------------\n";
    std::string result = decode_text(str.length(), encode, vectRange);
    std::cout << "Result of Arithmetic Decode: " << result << std::endl;
    std::cout << "------------------------------------------------------------\n";

    std::cout << "\n==================================================\n";
    std::cout << "Original string: " << str << std::endl
               << "Final string: " << result << std::endl;
    std::cout << "==================================================\n";

    return 0;
}

void frequency(std::string& str, std::map<char, Fraction>& mapFrequency)
{
    // calculate the number of every unique symbol
    for (char symbol : str)
    {
        mapFrequency[symbol] = mapFrequency[symbol] + Fraction(1, 1);
    }
    // calculate frequency of symbols;
    for (auto iter = mapFrequency.begin(); iter != mapFrequency.end(); ++iter)
    {
        iter->second = iter->second / Fraction(str.length(), 1);
    }
}

Fraction encode_text(std::vector<Symbol> &vectStrRange)
{
    std::cout << "\n------------------------------------------------------------\n";

    Fraction low(0,1);
    Fraction high(1,1);

    for (unsigned i = 0; i < vectStrRange.size(); ++i)
    {
        Fraction previous_low = low;
        Fraction range = high - low;

        char symbol = vectStrRange[i].symbol;
        low = previous_low + (range * vectStrRange[i].low);
        high = previous_low + (range * vectStrRange[i].high);

        std::cout << symbol << ": ["
                   << low.getNumerator() << "/" << low.getDenominator() << "; "
                   << high.getNumerator() << "/" << high.getDenominator() << ")\n";
    }

    std::cout << "------------------------------------------------------------\n";

    return low;
}

std::string decode_text(unsigned length, Fraction number, std::vector<Symbol> &vectRange)
{
    std::string result = "";
    Fraction low;
    Fraction high;

    for (unsigned i = 0; i < length; ++i)
    {
        for (Symbol& x : vectRange)
        {
            if (number >= x.low && number < x.high)
            {
                result += x.symbol;
                low = x.low;
                high = x.high;

                std::cout << number.getNumerator() << "/" << number.getDenominator() << " ∈ "
                           << "[" << low.getNumerator() << "/" << low.getDenominator() << "; "
                           << high.getNumerator() << "/" << high.getDenominator() << ") => "
                           << "'" << x.symbol << "'\n";
                break;
            }
        }

        number = (number - low) / (high - low);
        std::cout << "New number = " << number.getNumerator() << "/" << number.getDenominator()
                   << std::endl << std::endl;
    }
    return result;
}
