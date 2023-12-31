//
//  ATOM_SM.hpp
//  M5ATOM_Testing
//
//  Created by Scott Moody on 12/18/23.
//

#ifndef ATOM_SM_hpp
#define ATOM_SM_hpp
#include "../../Defines.h"
#include <stdio.h>

#ifdef ATOM_QRCODE_MODULE

//! process the semantic marker (maybe from a click or a scan)
//! If a SMART button, it will tack on username, password and optionally scannedDevice
//! 12.15.23
boolean ATOM_processSemanticMarker(char *semanticMarker);
#endif
#endif /* ATOM_SM_hpp */
