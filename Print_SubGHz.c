#include "Print_SubGHz_ide.h"		// Additional Header

#define MotorA1	4
#define MotorA2 5
#define MotorB1 6
#define MotorB2 7
const uint8_t speeds = 255;

#define SUBGHZ_CH	36
#define SUBGHZ_PANID	0xABCD
uint8_t rx_data[256];

#define BLUE_LED	26

static const unsigned char *aes_key = NULL;		// disable AES key

void setup(void) {
	SUBGHZ_MSG msg;

	Serial.begin(115200);
	
	msg = SubGHz.init();
	if(msg != SUBGHZ_OK) {
		SubGHz.msgOut(msg);
		while(1){ }
	}

	SubGHz.setKey(aes_key);
	
	msg = SubGHz.begin(SUBGHZ_CH, SUBGHZ_PANID,  SUBGHZ_100KBPS, SUBGHZ_PWR_20MW);
	if(msg != SUBGHZ_OK) {
		SubGHz.msgOut(msg);
		while(1){ }
	}
	msg = SubGHz.rxEnable(NULL);
	if(msg != SUBGHZ_OK) {
		SubGHz.msgOut(msg);
		while(1){ }
	}

	pinMode(BLUE_LED,OUTPUT);
	digitalWrite(BLUE_LED,HIGH);

	return;
}

void loop(void) {
	short rx_len;
	
	rx_len = SubGHz.readData(rx_data,sizeof(rx_data));
	rx_data[rx_len] = 0;
	if(rx_len > 0) {
		digitalWrite(BLUE_LED, LOW);
		Motor_Move();
		Motor_Stop();
		digitalWrite(BLUE_LED, HIGH);
		
	}
	return;
}


void Motor_Move(void){
	analogWrite(MotorA1,speeds);
	analogWrite(MotorA2,0);
	analogWrite(MotorB1,speeds);
	analogWrite(MotorB2,0);
  	delay(1000);
}

void Motor_Stop(void){
	analogWrite(MotorA1,speeds);
	analogWrite(MotorA2,speeds);
	analogWrite(MotorB1,speeds);
	analogWrite(MotorB2,speeds);
//	delay(1000);
}

