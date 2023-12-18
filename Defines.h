//
//  Defines.h
//
//  Created by Scott Moody on 3/8/22.
//


#ifndef Defines_h
#define Defines_h

#define ESP_M5_ATOM_LITE_QR_SCANNER_CONFIGURATION


//This is an easy way to turn on the smart clicker configuration...
//! https://docs.m5stack.com/en/atom/atomic_qr
//! library:  M5Stack-ATOM (actually using M5Stack-C-Plus)
#ifdef ESP_M5_ATOM_LITE_QR_SCANNER_CONFIGURATION
#define VERSION "Version-(2.19)-12.16.23.2023-ESP_M5_ATOM_QR_HTTPS_SMART"
#define ESP_M5
#define ATOM_QRCODE_MODULE

//! 11.14.23 try "https" secure web call (to SemanticMarker.org/bot/...)
//!  See https://GitHub.com/konacurrents/SemanticMarkerAPI for more info
//#define USE_REST_MESSAGING

#endif //ESP_M5_ATOM_LITE_QR_SCANNER_CONFIGURATION


//https://forum.arduino.cc/t/single-line-define-to-disable-code/636044/4
// Turn on/off Serial printing being included in the executable
//NOTE: if multiple lines of code say are creating a string to print, wrap that
//code with #if (SERIAL_DEBUG_INFO) - or whatever level of printing
//Use:  SerialError.print...
#define SERIAL_DEBUG_ERROR true
#define SerialError if (SERIAL_DEBUG_ERROR) Serial
#define SERIAL_DEBUG_LOTS false
#define SerialLots  if (SERIAL_DEBUG_LOTS) Serial
#define SERIAL_DEBUG_DEBUG true
#define SerialDebug  if (SERIAL_DEBUG_DEBUG) Serial
#define SERIAL_DEBUG_INFO false
#define SerialInfo  if (SERIAL_DEBUG_INFO) Serial
#define SERIAL_DEBUG_MINIMAL true
#define SerialMin  if (SERIAL_DEBUG_MINIMAL) Serial
// a temporary debug.. without having to set the above..
#define SERIAL_DEBUG_TEMP true
#define SerialTemp  if (SERIAL_DEBUG_TEMP) Serial
//turn on CALLS to see the methods called in order, etc
#define SERIAL_DEBUG_CALL false
#define SerialCall  if (SERIAL_DEBUG_CALL) Serial
// *** REST ARE NORMAL INCLUDES based on these #defines ****
#define NOTSET_STRING (char*)"notset"


#define ESP_M5

#ifdef ESP_M5
#include <M5StickCPlus.h>
#else
#include <Arduino.h>
#endif



#ifdef ATOM_QRCODE_MODULE
#include "src/ATOM_QRCode_Module/ATOMQRCodeModule.h"
#endif


//! try a call..
#ifdef USE_REST_MESSAGING
#include "src/MQTTModule/RESTMessaging.h"
#endif

 #endif // Defines_h
