/* 
 * File:   Base64.h
 * Author: jorge
 *
 * Created on November 26, 2013, 12:56 PM
 */

#ifndef BASE64_H
#define	BASE64_H

#include <string>

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int len);
std::string base64_decode(std::string const& s);

#endif	/* BASE64_H */

