#include <uJSON.h>

//char data[] = "{}"; 
//char data[] = "{\"id\": 1, \"mode\": \"OUTPUT\", \"value\": \"HIGH\"}"; 
char data[] = "{\"id\": 1, \"mode\": \"OUTPUT\", \"value\": \"HIGH\", \"obj\": {\"name\": \"myhome\"}}"; 


uJSON json = uJSON();
void setup(){
	Serial.begin(9600);
}

void loop(){
	uint8_t status = json.decode(data);
	Serial.println(status);

	if(status > 0){
		//json.get("id");
		//Serial.println(json.get("id"));
		//Serial.println(json.get("mode"));
		//Serial.println(json.get("value"));
		//Serial.println(json.get("state"));
		//Serial.println(json.get("config"));
		//Serial.println(json.get("cazzi"));
		//Serial.println(json.get("mazzi"));
		
		//Serial.println(json.get("mode"));
	}
	delay(1000);
}