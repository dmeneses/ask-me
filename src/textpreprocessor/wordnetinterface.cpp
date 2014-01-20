/* 
 * File:   wordnetinterface.cpp
 * Author: dann
 * 
 * Created on January 20, 2014, 3:20 PM
 */

#include "wordnetinterface.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/progress.hpp>
#include <boost/algorithm/string.hpp>

#include <wnb/core/wordnet.hh>
#include <wnb/core/load_wordnet.hh>
#include <wnb/core/info_helper.hh>
#include <wnb/std_ext.hh>

using namespace wnb;

void wn_like(wordnet& wn, std::string& word)
{
    static const unsigned nb_pos = POS_ARRAY_SIZE - 1;
    for (unsigned p = 1; p <= nb_pos; p++)
    {
        std::vector<synset> synsets = wn.get_synsets(word, (pos_t) p);
        if (synsets.size() == 0)
            continue;

        std::string mword = wn.morphword(word, (pos_t) p);
        std::cerr << word << " " << mword << std::endl;

        std::cout << "\nOverview of "
                << get_name_from_pos((pos_t) p)
                << " " << mword << "\n\n";

        std::cout << "The "
                << get_name_from_pos((pos_t) p)
                << " " << mword << " has "
                << synsets.size()
                << " senses";

        int tagsense_cnt = 0; // FIXME: already in index_list
        for (std::size_t j = 0; j < synsets.size(); j++)
            tagsense_cnt += (synsets[j].tag_cnt != 0);

        if (tagsense_cnt != 0)
            std::cout << " (first " << tagsense_cnt << " from tagged texts)";

        std::cout << "\n";
        std::cout << "                                      \n";

        for (std::size_t j = 0; j < synsets.size(); j++)
        {
            std::cout << j + 1 << ". "; // << (int)synsets[j].pos << "| ";
            if (synsets[j].tag_cnt != 0)
                std::cout << "(" << synsets[j].tag_cnt << ") ";
            std::cout << synsets[j].words[0];
            for (std::size_t k = 1; k < synsets[j].words.size(); k++)
                std::cout << ", " << synsets[j].words[k];
            boost::algorithm::trim(synsets[j].gloss);
            std::cout << " -- (" << synsets[j].gloss << ")";
            std::cout << std::endl;
        }
    }
}

void test()
{
    wordnet wn("/usr/local/WordNet-3.0/dict/");

    // read test file
    std::vector<std::string> wl;
    wl.push_back("cat");
    wl.push_back("dog");

    for (std::size_t i = 0; i < wl.size(); i++)
    {
        wn_like(wn, wl[i]);
    }
}
