/*
  Name:		NimBLE_PetTutor_Server.ino
  Created:	8/25/2021 7:49:11 PM
  Author:	scott
*/

//!defines.h defines the #ifdef USE_MODULE statements, as they are included elsewhere.. Don't define them here.
#include "Defines.h"

// ******************************************
//!note: setup only called one time...
//! so, the first time the doneWIFIModuleCredentials is set.. call setup()
//!main setup
void setup() {

  Serial.begin(115200);
  Serial.println();
    
    
  SerialInfo.println("******************");
  SerialMin.println(VERSION);
  
  //Timestamp the compile
  SerialDebug.print("Compiled ");
  SerialDebug.print(__DATE__);
  SerialDebug.print(" @ ");
  SerialDebug.println(__TIME__);

  SerialInfo.println("******************");
#ifdef ATOM_QRCODE_MODULE
    //setup the ATOM QR Reader
    setup_ATOMQRCodeModule();
#endif
    

//! try a call..  NOTE, if the WIFI isn't working, this won't work either..
#ifdef USE_REST_MESSAGING
   setupSecureRESTCall();
#endif

}


// ****************************************
//! main loop() of the Arduino runtime
void loop() {
    //! 8.1.23 for the ATOM Lite QRCode Reader
#ifdef ATOM_QRCODE_MODULE
    loop_ATOMQRCodeModule();
#endif
  delay(100);  //this delays the feed trigger response

}
