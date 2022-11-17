
#pragma once
#include "include.h"

namespace pigIt { // https://www.codewars.com/kata/520b9d2ad5c005041100000f/train/cpp //TODO: unfinished
    std::string pig_it(std::string str)
    {
        std::vector<char> ignoreList = {',', '.', '!', ':'};

        auto isCharInIgnore = [&](char ch) -> bool {
        for (auto i = 0ull; i < ignoreList.size(); ++i) {
            if (ch == ignoreList[i]) { return true; }
        }
            return false;
        };
        
        std::string cacheWord;
        char cacheChar = '\0';
        char prevChar = '\0';
        std::string cacheStr;


        auto resetWord_l = [&](){ cacheWord = ""; };
        auto resetChar_l = [&](){ cacheChar = '\0'; };

        auto addChar_l  = [&](char ch, bool bIgnore) {

            cacheWord += ch;
        };
        auto saveWord_l = [&](bool bLastIndex) {
            if (!bLastIndex) { cacheWord += ' '; }
            cacheStr += cacheWord;
            resetWord_l();
        };
        auto modifyWord_l = [&](){
            cacheWord += cacheChar;
            resetChar_l();
            cacheWord += "ay";
        };
        for (auto i = 0ull ; i < str.size(); ++i) {
            char ch = str[i];
            bool bLastIndex = i == str.size() - 1;
            bool bIgnore = isCharInIgnore(ch);
            bool bSaveWordChar = ch == ' ';

            if (bSaveWordChar || bLastIndex) {
                if (bLastIndex) { addChar_l(ch, bIgnore); } //save last char
                if (isCharInIgnore(prevChar)) {
                    saveWord_l(bLastIndex);
                    continue;
                }
                modifyWord_l();
                saveWord_l(bLastIndex);
                continue;
            }
            if (cacheWord == "") { //first char of word
                if ( cacheChar == '\0') { addChar_l(ch, bIgnore); continue; }
                else { addChar_l(ch, bIgnore); continue; };
            }
            addChar_l(ch, bIgnore);
            prevChar = ch;
        }
        return cacheStr;
    }
    void Test () {
        std::cout << pig_it("st ! f!") << '\n' << "ctaAay steay abulafay";
    }
}