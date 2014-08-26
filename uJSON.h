/*
  uJSON.h - Library that implement JSON parser.
  Created by Filippo Sallemi, July 23, 2014.
  Released into the public domain.
*/

#ifndef __uJSON_H_
#define __uJSON_H_

#include <Arduino.h>
#include <jsmn.h>

#define TOKENS_SIZE 16

class uJSON{

  public:
    uJSON();
    int8_t decode(char *json);
    char *get(const char* key);

  private:
  	char *_json;
  	jsmn_parser _parser;
  	jsmntok_t _tokens[TOKENS_SIZE];

  	bool equals(jsmntok_t *token, const char *key);
  	char *tostring(jsmntok_t *token);
};

#endif