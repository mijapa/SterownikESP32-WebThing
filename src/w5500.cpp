#include <SPI.h>
#include <Ethernet.h>
#include "w5500.h"

/*
 * W5500 "hardware" MAC address.
 */
uint8_t eth_MAC[] = {0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01};

/*
 * Define the static network settings for this gateway's ETHERNET connection
 * on your LAN.  These values must match YOUR SPECIFIC LAN.  The "eth_IP"
 * is the IP address for this gateway's ETHERNET port.
 */
IPAddress eth_IP(192, 168, 1, 100);        // *** CHANGE THIS to something relevant for YOUR LAN. ***
IPAddress eth_MASK(255, 255, 255, 0);        // Subnet mask.
IPAddress eth_DNS(192, 168, 1, 2);        // *** CHANGE THIS to match YOUR DNS server.           ***
IPAddress eth_GW(192, 168, 1, 1);        // *** CHANGE THIS to match YOUR Gateway (router).     ***

/*
 * Wiz W5500 reset function.  Change this for the specific reset
 * sequence required for your particular board or module.
 */
void WizReset() {
    Serial.print("Resetting Wiz W5500 Ethernet Board...  ");
    pinMode(RESET_P, OUTPUT);
    digitalWrite(RESET_P, HIGH);
    delay(250);
    digitalWrite(RESET_P, LOW);
    delay(50);
    digitalWrite(RESET_P, HIGH);
    delay(350);
    Serial.println("Done.");
}

/*
 * Print the result of the hardware status enum
 * as a string.
 */
void prt_hwval(uint8_t refval) {
    switch (refval) {
        case 0:
            Serial.println("No hardware detected.");
            break;
        case 1:
            Serial.println("WizNet W5100 detected.");
            break;
        case 2:
            Serial.println("WizNet W5200 detected.");
            break;
        case 3:
            Serial.println("WizNet W5500 detected.");
            break;
        default:
            Serial.println
                    ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}


/*
 * Print the result of the ethernet connection
 * status enum as a string.
 */
void prt_ethval(uint8_t refval) {
    switch (refval) {
        case 0:
            Serial.println("Uknown status.");
            break;
        case 1:
            Serial.println("Link flagged as UP.");
            break;
        case 2:
            Serial.println("Link flagged as DOWN. Check cable connection.");
            break;
        default:
            Serial.println
                    ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}


void setupW5500() {
    Serial.println("\n\tUDP NTP Client v3.0\r\n");

    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(W5500_CS);           // GPIO5 on the ESP32.
    WizReset();

    /* 
     * Network configuration - all except the MAC are optional.
     */
    Serial.println("Starting ETHERNET connection...");
    Ethernet.begin(eth_MAC, eth_IP, eth_DNS, eth_GW, eth_MASK);

    delay(200);

    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());

    /*
     * Sanity checks for W5500 and cable connection.
     */
    Serial.print("Checking connection.");
    bool rdy_flag = false;
    for (uint8_t i = 0; i <= 5; i++) {
        if ((Ethernet.hardwareStatus() == EthernetNoHardware)
            || (Ethernet.linkStatus() == LinkOFF)) {
            Serial.print(".");
            rdy_flag = false;
            delay(80);
        } else {
            rdy_flag = true;
            break;
        }
    }
    if (rdy_flag == false) {
        Serial.println
                ("\n\r\tHardware fault, or cable problem... cannot continue.");
        Serial.print("Hardware Status: ");
        prt_hwval(Ethernet.hardwareStatus());
        Serial.print("   Cable Status: ");
        prt_ethval(Ethernet.linkStatus());
    } else {
        Serial.println(" OK");
    }

}
