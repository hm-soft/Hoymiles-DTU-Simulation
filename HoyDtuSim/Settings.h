#ifndef __SETTINGS_H
#define __SETTINGS_H

// Ausgabe von Debug Infos auf der seriellen Console
#define DEBUG
#define SER_BAUDRATE            (115200)

#include "Debug.h"

// Hardware configuration
#ifdef ESP8266
#define RF1_CE_PIN  (D4)
#define RF1_CS_PIN  (D8)
#define RF1_IRQ_PIN (D3)
#else
#define RF1_CE_PIN  (9)
#define RF1_CS_PIN  (10)
#define RF1_IRQ_PIN (2)
#endif
#define PA_LEVEL    RF24_PA_LOW         // RF24_PA_MAX


// WR und DTU
#define RF_MAX_ADDR_WIDTH       (5) 
#define MAX_RF_PAYLOAD_SIZE     (32)
#define DEFAULT_RF_DATARATE     (RF24_250KBPS)  // Datarate

// Ausgabe was gesendet wird; 0 oder 1 
#define DEBUG_SEND  1   

// soll zwichen den Sendekanälen 23, 40, 61, 75 ständig gewechselt werden
#define CHANNEL_HOP
#define USE_POOR_MAN_CHANNEL_HOPPING_RCV  1     // 0 = not use

#define DUMMY_RADIO_ID          ((uint64_t)0xDEADBEEF01ULL) 
#define DTU_RADIO_ID            ((uint64_t)0x1234567801ULL)
#define MAX_MEASURE_PER_INV 25    // hier statisch, könnte auch dynamisch erzeugt werden, aber Overhead für dyn. Speicher?

#define MAX_ANZ_INV             1                       // <<<<<< anpassen oder dyn.
#define POLL_INTERVALL_WR       10                      // für jeden WR
uint16_t WAIT_TILL_NEXT_SEND;

#include "Inverters.h"

#if MAX_ANZ_INV >= 1 
#include "HM600.h"                            // <<<<<< anpassen und folgende Defs
#define WR1_NAME "HM-600"
#define WR1_SERIAL 0x114100000001ULL
#define WR1_MEASUREDEF hm600_measureDef
#define WR1_MEASURECALC hm600_measureCalc
#define WR1_FRAGMENTS hm600_fragmentLen
uint16_t WR1_MODULEPEAKS[] = {2, 370, 370};
#endif

// Beispiel für 2. WR
#if MAX_ANZ_INV >= 2                        
#define WR2_NAME "HM-600-1"
#define WR2_SERIAL 0x114100000002ULL
#define WR2_MEASUREDEF hm600_measureDef
#define WR2_MEASURECALC hm600_measureCalc
#define WR2_FRAGMENTS hm600_fragmentLen
uint16_t WR2_MODULEPEAKS[] = {2, 375, 375};
#endif

// Beispiel für 3. WR
#if MAX_ANZ_INV >= 3 
#include "HM400.h"                            // <<<<<< anpassen und folgende Defs
#define WR3_NAME "HM-400"
#define WR3_SERIAL 0x114100000003ULL
#define WR3_MEASUREDEF hm400_measureDef
#define WR3_MEASURECALC hm400_measureCalc
#define WR3_FRAGMENTS hm400_fragmentLen
uint16_t WR3_MODULEPEAKS[] = {1, 425};
#endif

// ##########################  WIFI  ##############################
// Webserver
#define WEBSERVER_PORT          80

// mit OTA Support, also update der Firmware über WLan mittels IP/update
#define WITH_OTA

// Time Server
//#define TIMESERVER_NAME "pool.ntp.org"
#define TIMESERVER_NAME "fritz.box"

#ifdef WITH_OTA
// OTA Einstellungen
#define UPDATESERVER_PORT   WEBSERVER_PORT+1
#define UPDATESERVER_DIR    "/update"
#define UPDATESERVER_USER   "??????"				      // <<<<<< anpassen
#define UPDATESERVER_PW     "??????"				      // <<<<<< anpassen
#endif

// internes WLan
// PREFIXE dienen dazu, die eigenen WLans (wenn mehrere) von fremden zu unterscheiden
// gehe hier davon aus, dass alle WLans das gleiche Passwort haben. Wenn nicht, dann mehre Passwörter hinterlegen
#define SSID_PREFIX1         "??????"					      // <<<<<< anpassen
//#define SSID_PREFIX2         "??????"					      // <<<<<< anpassen
#define SSID_PASSWORD        "13234567890123456"		// <<<<<< anpassen


// zur Berechnung von Sonnenauf- und -untergang
#define  geoBreite  49.2866							          // <<<<<< anpassen
#define  geoLaenge  7.3416							          // <<<<<< anpassen


#define TEST_MULTI 1

void setupInverters() {
//-----------------  
#if MAX_ANZ_INV >= 1 
  addInverter (anzInv, WR1_NAME, WR1_SERIAL,    
               WR1_MEASUREDEF, sizeof(WR1_MEASUREDEF) / sizeof(measureDef_t),
               WR1_MEASURECALC, sizeof(WR1_MEASURECALC) / sizeof(measureCalc_t),
               WR1_FRAGMENTS,
               WR1_MODULEPEAKS);
#endif
#if MAX_ANZ_INV >= 2 
  addInverter (anzInv, WR2_NAME, WR2_SERIAL,    
               WR2_MEASUREDEF, sizeof(WR2_MEASUREDEF) / sizeof(measureDef_t),
               WR2_MEASURECALC, sizeof(WR2_MEASURECALC) / sizeof(measureCalc_t),
               WR2_FRAGMENTS,
               WR2_MODULEPEAKS);
#endif
#if MAX_ANZ_INV >= 3 
   addInverter (anzInv, WR3_NAME, WR3_SERIAL,    
               WR3_MEASUREDEF, sizeof(WR3_MEASUREDEF) / sizeof(measureDef_t),
               WR3_MEASURECALC, sizeof(WR3_MEASURECALC) / sizeof(measureCalc_t),
               WR3_FRAGMENTS,
               WR3_MODULEPEAKS);
#endif
  WAIT_TILL_NEXT_SEND = POLL_INTERVALL_WR / anzInv;
  if (WAIT_TILL_NEXT_SEND < 5) 
    WAIT_TILL_NEXT_SEND = 5;
  WAIT_TILL_NEXT_SEND=10;  
}

#endif
