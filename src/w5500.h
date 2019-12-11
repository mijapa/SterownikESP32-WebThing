#ifndef STEROWNIKESP32_WEBTHING_W5500_H
#define STEROWNIKESP32_WEBTHING_W5500_H

#endif //STEROWNIKESP32_WEBTHING_W5500_H

void setupW5500();

void loopW5500();

#define RESET_P    26                // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.

const uint16_t localPort = 55432;        // Local port for UDP packets.

/*
 * Choose the NTP server pool for your geographical region for best
 * performance (fewer lost packets).
 *
 * *** Uncomment only one of the following "timeServer[]" defines. ***
 */
const char timeServer[] = "pool.ntp.org";        // Default NTP server pool.
// const char timeServer[] = "africa.pool.ntp.org";		// Regional server pool.
// const char timeServer[] = "asia.pool.ntp.org";		// Regional server pool.
// const char timeServer[] = "europe.pool.ntp.org";		// Regional server pool.
// const char timeServer[] = "north-america.pool.ntp.org";	// Regional server pool.
// const char timeServer[] = "oceania.pool.ntp.org";		// Regional server pool.
// const char timeServer[] = "south-america.pool.ntp.org";	// Regional server pool.
// const char timeServer[] = "time.nist.gov";			// Original example target server (least preferred).

const uint8_t SLEEP_SECS = 15;            // Number of seconds to sleep between queries to the time
// server. Please don't set this any lower than 10 unless
// timeServer[] is a local NTP server on -your- network.
