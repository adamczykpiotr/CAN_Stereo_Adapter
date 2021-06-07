#include "src/CAN/CanBus.hpp"
#include "src/MAX5160/DigiPot.hpp"
#include "Brightness.hpp"
#include "CanDevice.hpp"
#include "Handbrake.hpp"
#include "Buttons.hpp"
#include "Reverse.hpp"

Can::CanBus can0;
Reverse reverse(PB5);
Handbrake handbrake(PB7);
Brightness brightness(PB4, 0x7F);
DigiPot channel1(PA15, PA11, PA12, PB3);
DigiPot channel2(PB14, PB12, PB13, PB15);
Buttons buttons(&channel1, &channel2);

void setup() {
	Serial.begin(9600);

	bool ret = can0.begin(Can::Bitrate::CAN_33K3BPS, Can::Pinout::RX_PB8_TX_PB9);
	Serial.println(ret ? "BOOT OK" : "BOOT FAILURE");
	if (!ret) while(true);

	reverse.begin();
	handbrake.begin();
	brightness.begin();
	buttons.begin();
}

Can::Frame rx;

void loop() {
	buttons.iterate();

	if(can0.checkReceive()) {
		can0.receive(&rx);

		if( reverse.parseFrame(&rx) )     return;
		if( handbrake.parseFrame(&rx) )   return;
		if( brightness.parseFrame(&rx) )  return;
		if( buttons.parseFrame(&rx) )     return;
	}
}