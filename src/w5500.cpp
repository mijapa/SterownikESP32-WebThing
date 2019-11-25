#include <SPI.h>
#include <Ethernet.h>
#include "w5500.h"

/*
* W5500 "hardware" MAC address.
*/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10, 0, 0, 177);


/*
 * Define the static network settings for this gateway's ETHERNET connection
 * on your LAN.  These values must match YOUR SPECIFIC LAN.  The "eth_IP"
 * is the IP address for this gateway's ETHERNET port.
 */
//IPAddress eth_IP(192, 168, 1, 100);		// *** CHANGE THIS to something relevant for YOUR LAN. ***
//IPAddress eth_MASK(255, 255, 255, 0);		// Subnet mask.
//IPAddress eth_DNS(192, 168, 1, 2);		// *** CHANGE THIS to match YOUR DNS server.           ***
//IPAddress eth_GW(192, 168, 1, 1);		// *** CHANGE THIS to match YOUR Gateway (router).     ***


#define RESET_P    26                // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.

void hardwareStatus() {
    Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    Ethernet.begin(mac, ip);
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.println("Ethernet shield was not found.");
    } else if (Ethernet.hardwareStatus() == EthernetW5100) {
        Serial.println("W5100 Ethernet controller detected.");
    } else if (Ethernet.hardwareStatus() == EthernetW5200) {
        Serial.println("W5200 Ethernet controller detected.");
    } else if (Ethernet.hardwareStatus() == EthernetW5500) {
        Serial.println("W5500 Ethernet controller detected.");
    }
}