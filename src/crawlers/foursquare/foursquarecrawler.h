/* 
 * File:   foursquarecrawler.h
 * Author: Luis Aguirre
 *
 * Created on 13 de enero de 2014, 10:35
 */

#ifndef FOURSQUARECRAWLER_H
#define	FOURSQUARECRAWLER_H

#include "../crawler.h"
#include <string>

/**
 * Crawler for the social network Foursquare
 */
class FoursquareCrawler : public Crawler
{
public:
    
    /**
     * Constructor
     */
    FoursquareCrawler();
    
    /**
     * Collect venues from the Foursquare
     * 
     * @param location Latitude and longitude for the searching
     * @param radius Limit results to venues in meters
     * 
     * @return A social information list with the venues found.
     */
    SocialInformationList collect(Location location, float radius);

private:
    
    /**
     * Search venues in a radios from a location
     * 
     * @param location Latitude and longitude where search
     * @param radius Limit results
     * 
     * @return A social information list with the venues found.
     */
    std::string search(Location location, float radius);
    
    
    /**
     * Build the url query adding the location and the radius
     * i.e.                      "https://api.foursquare.com/v2/venues/search?
                                  ll=-17.367023,-66.174488&
                                  radius=100&
                                  client_id=<CLIEN_ID>&
                                  client_secret=<CLIENT_SECRET>&
                                  v=20140113"
     */
    std::string buildUrl(Location location, float radius);
    
    /**
     * Parse the json information and save it in a list
     * 
     * @param information Information given in json
     * 
     * @return The list with the results
     */
    SocialInformationList parse(const std::string& information);
        
};

#endif	/* FOURSQUARECRAWLER_H */

