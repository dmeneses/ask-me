/*
 * File:   ConceptNetCrawler.h
 * Author: quique
 *
 * Created on December 14, 2013, 1:15 AM
 */

#ifndef CONCEPTNETCRAWLER_H
#define	CONCEPTNETCRAWLER_H

#include <set>
#include <string>
#include <vector>
#include "../semanticcrawler.h"


class ConceptNetCrawler : public SemanticCrawler
{
public:
    ConceptNetCrawler(const std::string& language);
    ~ConceptNetCrawler();

    /**
     * Collect all the related words for a given word. 
     * Includes associations and relationships.
     * 
     * @param word to search for relationships.
     * @param wordList to search for associations.
     * 
     * @return Collection of relations with the searched word.
     */
    std::set<std::string> collectAllRelatedWords(const std::string& word, const std::vector<std::string>& wordList);

    /**
     * Collect all the relationships for a given word.
     * 
     * @param word Word to search
     * @param language Language to search related words.
     * @return Set of related words
     */
    std::set<std::string> collectRelationships(const std::string& word);

    /**
     * Collect associated words given a list of words.
     * 
     * @param words Words to associate.
     * @return Set of associated words.
     */
    std::set<std::string> collectAssociations(const std::vector<std::string>& words);

private:

    /**
     * Retrieve the given request and return a string with the content.
     * 
     * @param request Url to make the request and retrieve information.
     * 
     * @return A string contaning the request result.
     */
    const char* retrieve(const std::string& request);

    /**
     * Function to parse the json file returned by the query to conceptnet.
     * 
     * @param path Json file path.
     * @return Set of related words found in the file.
     */
    std::set<std::string> parseRelationsData(const char* relationsInfo);

    /**
     * Parse the associations file to get all the associations words.
     * 
     * @return Set of found word in the file.
     */
    std::set<std::string> parseAssociationsData(const char* associationsInfo);

    /**
     * Given the full language name in english return its code.
     * For example: "english" = "en", "spanish" = "es"
     * 
     * @param language Language to get the code.
     * @return Code of a language.
     */
    std::string getLanguageCode(const std::string& language);

    /**
     * Build a string with the word in the received list separated by commas.
     * For example: "banana,apple,strawberry".
     * @param words Words to append in the string.
     * @return String with all the words in the list separated by commas.
     */
    std::string getWordsAsSentence(const std::vector<std::string>& words);

    /**
     * Process the association url retrieved from Concept net.
     * If the association has a percentage of 50% or more, take it in count.
     * If the association is negative (/assoc/en/dog/neg). Don't take it in count.
     * 
     * @param association Association url containing the word.
     * @param percentage Percentage of association.
     * 
     * @return Word extracted from the association url if the percentage of association is 50% or more,
     *  in other case returns empty.
     */
    std::string processAssociation(const std::string& association, double percentage);


    std::string languageCode_;
};

#endif	/* CONCEPTNETCgRAWLER_H */

