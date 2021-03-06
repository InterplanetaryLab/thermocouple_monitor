#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_MAX31855.h>

// LoRa config vars
#define SS 8
#define RST 4
#define DIO0 7
#define SPREAD_FACTOR 10
#define CENTER_FREQ 437.5E6
#define BANDWIDTH 62.5E3
#define TX_POWER 4

//MAX31855 config vars
#define COUPLE_COUNT 5
#define SS_1 12
#define SS_2 11
#define SS_3 10
#define SS_4 9
#define SS_5 5

uint32_t time_temp =0;
float temp_data[COUPLE_COUNT];

Adafruit_MAX31855 couple_1(SS_1);
Adafruit_MAX31855 couple_2(SS_2);
Adafruit_MAX31855 couple_3(SS_3);
Adafruit_MAX31855 couple_4(SS_4);
Adafruit_MAX31855 couple_5(SS_5);

//function predefinitions
void lora_init();
void lora_transmit();
void init_couples();
void read_couples(uint32_t ms, float * temps);

void setup() {
	Serial.begin(9600);

	Serial.println("t-vac lora logger");
	lora_init();
	init_couples();

	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	read_couples(&time_temp, temp_data);	
	lora_transmit(); 
	delay(500);
}

// thermocouple section
void init_couples()
{
	if (!couple_1.begin())
	{
		Serial.println("error initing couple_1");
		while (1) delay(10);
	}

	if (!couple_2.begin())
	{
		Serial.println("error initing couple_2");
		while (1) delay(10);
	}

	if (!couple_3.begin())
	{
		Serial.println("error initing couple_3");
		while (1) delay(10);
	}
	if (!couple_4.begin())
	{
		Serial.println("error initing couple_4");
		while (1) delay(10);
	}
	if (!couple_5.begin())
	{
		Serial.println("error initing couple_5");
		while (1) delay(10);
	}
}

void read_couples(uint32_t *ms, float * temps)
{
	temps[0] = couple_1.readCelsius();
	temps[1] = couple_2.readCelsius();
	temps[2] = couple_3.readCelsius();
	temps[3] = couple_4.readCelsius();
	temps[4] = couple_5.readCelsius();

	*ms = millis();
	uint8_t i;
	Serial.print(*ms);
	for (i=0; i< COUPLE_COUNT; i++)
	{
		Serial.print(","); Serial.print(temps[i]);
	}
	Serial.println("");
}

// lora_section inits using the given config pins does a test begin to make sure the lora radio is works properly
void lora_init()
{
	LoRa.setPins(SS, RST, DIO0);

	if (!LoRa.begin(CENTER_FREQ)) { // loop until lora initializes properly
		Serial.println("Starting LoRa failed!");
		while (1);
	}
} 

// for now just transmitting the global variables for temp and time stamp when read of the temp
void lora_transmit()
{
	LoRa.begin(CENTER_FREQ);
	LoRa.setSpreadingFactor(SPREAD_FACTOR);
	LoRa.setSignalBandwidth(BANDWIDTH);
	LoRa.enableCrc();
	LoRa.setTxPower(TX_POWER);
	Serial.print("Sending packet: ");
	LoRa.beginPacket();
	LoRa.print(time_temp);
	uint8_t i;
	for (i=0; i<COUPLE_COUNT; i++)
	{
		LoRa.print(",");
		LoRa.print(temp_data[i]);
	}
	LoRa.endPacket();
}
