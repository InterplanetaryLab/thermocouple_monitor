#include <SPI.h>
#include <LoRa.h>

#define SS 8
#define RST 4
#define DIO0 7


int counter = 0;
int txPower = 2; //sets the transmittion power of LoRa modem 2-20 default is 17

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(437000000)) { //436957031
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(10); 
  LoRa.setSignalBandwidth(62.5E3);
  LoRa.enableCrc();
  LoRa.setTxPower(txPower);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
  //  Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println("");
    /*
    // RSSI and SNR of packet
    Serial.print("' SNR: ");
    Serial.print(LoRa.packetSnr());
    Serial.print("' RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.print("' Frequency Error: ");
    Serial.println((long) LoRa.packetFrequencyError());
    */
  }
}
