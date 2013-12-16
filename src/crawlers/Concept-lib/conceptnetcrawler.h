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

using namespace std;


class ConceptNetCrawler {
public:
    ConceptNetCrawler();
    ConceptNetCrawler(const ConceptNetCrawler& orig);
    ~ConceptNetCrawler();
    
    /**
     * Function to retrieve all related word to a given word translations not included.
     * @param word Word to be process  language = it or global address like en:english es:spanish
     * @param language Language to search related words.
     * @return Set of related words
     */
    std::set<string> collectRelatedWords(string word,string language);

private:
    /**
     * Function to connect to conceptnet web api and retrieve related words.
     * 
     * @param request Rest path
     * 
     * @return Path of json file with the results.
     */
    bool connect(string request);
    
    /**
     * Function to parse the json file returned by the query to conceptnet.
     * 
     * @param path Json file path.
     * @return Set of related words found in the file.
     */
    std::set<string> parseJsonFile();
    
    /**
     * Delete the json file after parsing.
     */
    void deleteCreatedFile();
    
    /**
     * Builds a path in home for the generated json file.
     * 
     * @return Json file path.
     */
    const char* getJsonFilePath();
    
    char* jsonPath_; 
};

#endif	/* CONCEPTNETCRAWLER_H */

