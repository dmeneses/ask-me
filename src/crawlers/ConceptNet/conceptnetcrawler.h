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

using namespace std;


class ConceptNetCrawler {
public:
    ConceptNetCrawler(const std::string& language);
    ~ConceptNetCrawler();
    
    /**
     * Function to retrieve all related word to a given word translations not included.
     * @param word Word to be process  language = it or global address like en:english es:spanish
     * @param language Language to search related words.
     * @return Set of related words
     */
    std::set<string> collectRelatedWords(string word);

    /**
     * Collect associated words given a list of words from ConceptNet.
     * 
     * @param words Words to associate.
     * @return Set of associated words.
     */
    std::set<string> collectAssociatedWords(const std::vector<string>& words);

private:
    /**
     * Function to connect to conceptnet web api and retrieve related words.
     * 
     * @param request Rest path
     * 
     * @return Path of json file with the results.
     */
    bool retrieveRelations(string request);
    
    /**
     * Function to parse the json file returned by the query to conceptnet.
     * 
     * @param path Json file path.
     * @return Set of related words found in the file.
     */
    std::set<string> parseJsonFile();
    
    /**
     * Delete the json file after parsing.
     * 
     * @param filename File name to delete.
     */
    void deleteCreatedFile(const char* filename);
    
    /**
     * Builds a path in home for the generated json file.
     * 
     * @param filename File name to build the entire path.
     * @return Json file path.
     */
    const char* getJsonFilePath(const char* filename);
    
    /**
     * Given the full language name in english return its code.
     * For example: "english" = "en", "spanish" = "es"
     * 
     * @param language Language to get the code.
     * @return Code of a language.
     */
    std::string getLanguageCode(const std::string& language);
    
    std::string languageCode_;
    char* relationsFile_;
    char* associationsFile_;
};

#endif	/* CONCEPTNETCRAWLER_H */

