#include "Welcome_SubGHz_ide.h"		// Additional Header

#define LED 26						// pin number of Blue LED
#define SUBGHZ_CH		36			// channel number (frequency)
#define SUBGHZ_PANID	0xabcd		// panid
#define HOST_ADDRESS	0xD992		// distination address

unsigned char send_data[2] ;

void setup(void) {
	
	SubGHz.init();					// initializing Sub-GHz
	Serial.begin(115200);
	pinMode(LED,OUTPUT);			// setting of LED
	digitalWrite(LED,HIGH);			// setting of LED
}

void loop(void) {
	SUBGHZ_MSG msg;

	unsigned int data = Serial.read();
	if(data == '\r') {
		Serial.println("sending");
		Serial.println(send_data);
		send_data[0] = data;
		send_data[1] = '\n';

		SubGHz.begin(SUBGHZ_CH, SUBGHZ_PANID,  SUBGHZ_100KBPS, SUBGHZ_PWR_20MW);		// start Sub-GHz

		digitalWrite(LED,LOW);														// LED ON
		msg = SubGHz.send(SUBGHZ_PANID, HOST_ADDRESS, &send_data, sizeof(send_data),NULL);// send data
		digitalWrite(LED,HIGH);														// LED off
		SubGHz.msgOut(msg);
	
		SubGHz.close();																// Sub-GHz module sets into power down mode.
	
		sleep(1000);																// sleep
	}
}

