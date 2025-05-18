#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>


std::vector<std::string> grepLines(
    const std::regex& re, 
    const std::string& filename, 
    const std::string& flag,
    const std::string& to_find)
{
    std::ifstream file(filename);
    std::vector<std::string> matchedLines;  // Vector stringneric - regexin hamapatasxanox toxery pahelu hamar

    //std::regex_constants::syntax_option_type options = std::regex_constants::ECMAScript;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return matchedLines;  // ete filey chi bacvum parzapes veradardznum enq ayd pahin datark toxy
    }

    std::string line;
    bool founded = false;

    bool invertMatch = (flag.find("v") != std::string::npos);// with -v we searching patterns that don t match that s why !
    bool wholeWord = (flag.find("w") != std::string::npos);
    bool wholeLine = (flag.find("x") != std::string::npos);

    while (std::getline(file, line)) {
        bool foundedMatch = false;

        //if (flag.find("i") != std::string::npos) //until the end of the string - npos
        //{
        //    foundedMatch = std::regex_search(line, re); // Case-insensitive search - std::regex_search returns bool - true if finds matchs
        //}
        if (flag.find("i") != std::string::npos) {

        }
        if (invertMatch) 
        {
            foundedMatch = !std::regex_search(line, re);  
        }
        else if (wholeWord)
        {
            std::string wBoundary = "\\b(" + to_find + ")\\b"; // construction of word boundaries, ^start of line, $end of line, \\b word boundary, sm.str() originally matched pattern
            std::regex wordRe(wBoundary, re.flags()); //the new pattern with word boundaries, pahelov arden exac flagnery orinak i, re.flags()
            foundedMatch = std::regex_search(line, wordRe); // Searches line for the whole-word pattern if exists returns true
        }
        else if (wholeLine)
        {
            foundedMatch = std::regex_match(line, re); // if any part of the string matches the regex - true
        }
        else {
            foundedMatch = std::regex_search(line, re); // if the entire string matches the regex - true
        }

        //if (invertMatch)
        //{
        //    foundedMatch = !foundedMatch;
        //}
        if (foundedMatch) {  // ete liney(toxayin art.) parunakum e artahaytutyuny if i paymany true e veradardznum - hamapatasxanox toxerum avelacnum enq 
            matchedLines.push_back(line);   // avelacvum e hamapatasxan toxy mer pahac vectorin
            founded = true;
        }
    }

    file.close();
    if (!founded)
    {
        std::cout << "There s no match for pattern -" << std::endl;
        matchedLines.clear(); 
    }
     return matchedLines;  
}

int main() {
    std::string filename;
    std::string to_find;
    std::string flag;
    std::cout << "Enter filename where you want to search for pattern" << std::endl;
    std::cin >> filename;
    std::cout << "Enter pattern you want to find in file" << std::endl;
    std::cin >> to_find;
    std::cout << "Enter flag" << std::endl;
    std::cin >> flag;

    std::regex_constants::syntax_option_type flags = std::regex_constants::basic; //default is ECAmScript JS format regex we setting it with basic grammar used for grep
    if (flag.find("i") != std::string::npos) {
        flags |= std::regex_constants::icase;  // Enable case-insensitive matching
    }

    std::regex re(to_find, flags);

    auto results = grepLines(re, filename, flag, to_find); //himnakan functioni kanch
    for (const auto& line : results) {
        std::cout << line << std::endl;
    }

    return 0;
}
