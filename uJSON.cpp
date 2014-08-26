/*
  uJSON.cpp - Library that implement JSON parser.
  Created by Filippo Sallemi, July 23, 2014.
  Released into the public domain.
*/

#include "uJSON.h"

uJSON::uJSON(){}

int8_t uJSON::decode(char *json){
	_json = json;
	jsmn_init(&_parser);

	uint8_t status = jsmn_parse(&_parser, _json, strlen(_json), _tokens, TOKENS_SIZE);
	if(status < 0) return status;

	jsmntok_t *cursor = &_tokens[0];
	if(cursor->start == -1 || cursor->end == -1) return -4;

	if(cursor->type != JSMN_OBJECT){
		Serial.println("Invalid response: root element must be an object.");
		return -4;
	}

	if(cursor->size % 2 != 0){
		Serial.println("Invalid response: object must have even number of children.");
		return -4;
	}

	return status;
}

char *uJSON::get(const char *key){
	char buffer[16] = {0};
	typedef enum { START, KEY, VALUE, SKIP, STOP } parse_state;
    parse_state state = START;

    size_t object_tokens = 0;
    for(size_t i = 0, j = 1; j > 0; i++, j--){
		jsmntok_t *cursor = &_tokens[i];
		if(cursor->start != -1 && cursor->end != -1){
			if(cursor->type == JSMN_ARRAY || cursor->type == JSMN_OBJECT) j += cursor->size;
			switch(state){
				case START:
                    state = KEY; object_tokens = cursor->size;
                    if(object_tokens == 0) state = STOP;
                	break;
                case KEY:
                	object_tokens--;

                	state = STOP;
                	if (cursor->type == JSMN_STRING){
                		state = SKIP; if(equals(cursor, key)) state = VALUE;
                	}
                	
                	break;
                case SKIP:
                	state = STOP;

                	if(cursor->type == JSMN_STRING || cursor->type == JSMN_PRIMITIVE){
                		object_tokens--; state = KEY;
                		if (object_tokens == 0) state = STOP;
                	}
                	break;
                case VALUE:{
                	if(cursor->type == JSMN_STRING || cursor->type == JSMN_PRIMITIVE){
                		memcpy(buffer, (_json + cursor->start), (cursor->end - cursor->start));
                		buffer[(cursor->end - cursor->start)] = '\0';
                		return buffer;
                	}

                	object_tokens--; state = KEY;
                	if(object_tokens == 0) state = STOP;
                	break;
                }
                case STOP:
                	break;
                default:
                	return NULL;
			}
		}
	}
	return NULL;
}

bool uJSON::equals(jsmntok_t *token, const char *key){
	uint8_t size = token->end - token->start;
	return (strncmp(_json + token->start, key, size) == 0 && strlen(key) == size);
}