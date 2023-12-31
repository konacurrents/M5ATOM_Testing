

/*
 *******************************************************************************
 *                  Equipped with Atom-Lite/Matrix sample source code
 *                          配套  Atom-Lite/Matrix 示例源代码
 * Visit for more information: https://docs.m5stack.com/en/atom/atomic_qr
 * 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atomic_qr
 *
 * Product:  ATOM QR-CODE UART control.
 * Date: 2021/8/30
 *******************************************************************************
 Press the button to scan, and the scan result will be printed out through
 Serial. More Info pls refer: [QR module serial control command
 list](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/atombase/AtomicQR/ATOM_QRCODE_CMD_EN.pdf)
 
@ee https://github.com/konacurrents/ESP_IOT/issues/261
 */
#include "../../Defines.h"
#include "ATOM_SM.h"

#ifdef ATOM_QRCODE_MODULE
#include "ATOMQR_UART_CMD.h"

//#include <M5Atom.h>

#ifdef USE_FAST_LED
//! our own LED
#include "../LED_DisplayModule/M5Display.h"
#endif

#ifdef ESP_M5
//#include <M5StickCPlus.h>


//void M5StickCPlus::begin(bool LCDEnable, bool PowerEnable, bool SerialEnable) {
//void begin(bool LCDEnable=true, bool PowerEnable=true, bool SerialEnable=true);

#endif



//! 8.28.23  Adding a way for others to get informed on messages that arrive
//! for the set,val
void messageSetVal_ATOMQR_UARD_CMD(char *setName, char* valValue)
{
    boolean isTrue =  false; //isTrueString_mainModule(valValue);

    SerialTemp.printf("messageSetVal.ATOMQR_UARD_CMD(%s,%s - %s)\n", setName, valValue, isTrue?"TRUE":"FALSE");

}

boolean _shortPress = false;
boolean _longPress = false;
boolean _longLongPress = false;
#define MAX_SM 500

char _lastSemanticMarker[MAX_SM];

//!M5Atom is 39
//Button ButtonA = Button(39,true,10);

//!NOTE: Config.h has the M5
//!BUTTON_A_PIN 37
//!BUTTON_B_PIN 39
//!
//!RGB is GPIO 27
const int ledPin_M5Atom = 27;
#define LATER
#ifdef LATER
//! CRGB is RGB
//! https://github.com/FastLED/FastLED/wiki/Pixel-reference
//! https://github.com/FastLED/FastLED/wiki/RGBSet-Reference
//! https://gist.github.com/chemdoc77?page=3
//! https://github.com/marmilicious/FastLED_examples/blob/master/blink_variations.ino

//! @see https://community.m5stack.com/topic/5550/atom-lite-with-different-led-controllers-for-internal-led/7
// Choose the LED type from the list below.
// #define LED_TYPE LED_STRIP_WS2812
#define LED_TYPE LED_STRIP_SK6812
// #define LED_TYPE LED_STRIP_APA106
// #define LED_TYPE LED_STRIP_SM16703

#define LED_TYPE_IS_RGBW 1
#define LED_GPIO 27
#define LED_BRIGHT 100

#ifdef USE_FAST_LED

static const CRGB L_RED = 0xff0000;
static const CRGB L_GREEN = 0x00ff00;
static const CRGB L_BLUE = 0x0000ff;
static const CRGB L_WHITE = 0xe0e0e0;
static const CRGB L_YELLOW = 0xfff000;
#endif

//LiteLED myLED( LED_TYPE, LED_TYPE_IS_RGBW );
#endif //LATER
/*
 ATON:
 

 */
void setLEDLight(boolean onOff)
{
    //pin = 37
 //   digitalWrite(ledPin_M5Atom, onOff?HIGH:LOW);
}

boolean _LEDFlag = false;
void toggleLED()
{
    _LEDFlag = !_LEDFlag;
    setLEDLight(_LEDFlag);
}


//!big button on front of M5StickC Plus
void checkButtonB_ButtonProcessing()
{
    boolean buttonTouched = true;
    _shortPress = false;
    _longPress = false;
    _longLongPress = false;

#ifdef ESP_M5
    //    SerialDebug.println(" checkButtonA_ButtonProcessing ***");
//    if (M5.BtnB.isPressed()) {
//                SerialDebug.println("M5.BtnB.isPressed");
//        _shortPress = true;
//    }
    
    //  M5.dis.fillpix(0x00ff00);  // GREEN  绿色
    //    while (Serial2.available() > 0) {
    //        char ch = Serial2.read();
    //        SerialDebug.printf("CH= %c\n", ch);
    //    }
    

    //!NOTE: ths issue is the timer is interruped by the scanner.. so make long-long very long..
    //was 1000  (from 500)
    if (M5.BtnB.wasReleasefor(3500))
    {
        //        buttonA_LongPress();
        SerialDebug.println(" **** LONG LONG PRESS ***");
        _longLongPress = true;
    }
    else if (M5.BtnB.wasReleasefor(1000))
    {
        //        buttonA_LongPress();
        SerialDebug.println(" **** LONG PRESS ***");
        _longPress = true;
    }
    else if (M5.BtnB.wasReleased())
    {
        //        buttonA_ShortPress();
        SerialDebug.println(" **** SHORT PRESS ***");
        _shortPress = true;
#ifdef USE_FAST_LED

        fillpix(0x0000ff);
#endif

        toggleLED();
    }
    else
    {
        buttonTouched = false;
    }
    //if a button was touched, update the delay since no touch..
    if (buttonTouched)
    {
        //        refreshDelayButtonTouched();
    }

#endif //ESP_M5
}

uint8_t wakeup_cmd       = 0x00;
uint8_t start_scan_cmd[] = {0x04, 0xE4, 0x04, 0x00, 0xFF, 0x14};
uint8_t stop_scan_cmd[]  = {0x04, 0xE5, 0x04, 0x00, 0xFF, 0x13};
uint8_t host_mode_cmd[]  = {0x07, 0xC6, 0x04, 0x08, 0x00, 0x8A, 0x08, 0xFE, 0x95};


uint8_t buzzerVolumeHigh[]    = {0x07, 0xC6, 0x04, 0x08, 0x00, 0xFE, 0x9B};
uint8_t buzzerVolumeMiddle[]  = {0x07, 0xC6, 0x04, 0x08, 0x01, 0xFE, 0x9A};
uint8_t buzzerVolumeLow[]     = {0x07, 0xC6, 0x04, 0x08, 0x02, 0xFE, 0x99};

uint8_t bootSoundProhibit[]   = {0x08, 0xC6, 0x04, 0x08, 0x00, 0xF2, 0x0D, 0x00, 0xFE, 0x27};

//more
uint8_t continuous_mode_cmd[]  = {0x07, 0xC6, 0x04, 0x08, 0x00, 0x8A, 0x04, 0xFE, 0x99};

//!adding
uint8_t factory_reset[]  = {0x08, 0xC6, 0x04, 0x08, 0x00, 0xF2, 0xFF, 0x00, 0xFD, 0x35};

void setup_ATOMQR_UARD_CMD()
{
    SerialDebug.println("setup_ATOMQR_UARD_CMD");
    M5.begin(true, false, true);
    Serial2.begin(
                  9600, SERIAL_8N1, 22,
                  19);  // Set the baud rate of serial port 2 to 115200,8 data bits, no
                        // parity bits, and 1 stop bit, and set RX to 22 and TX to 19.
                        // 设置串口二的波特率为115200,8位数据位,没有校验位,1位停止位,并设置RX为22,TX为19
    //SerialDebug.println("step 2");

#ifdef USE_FAST_LED
    setup_M5Display();
    fillpix(L_GREEN);
#endif
    
    //    M5.dis.fillpix(0xfff000);  // YELLOW 黄色
//#define LATER
#ifdef LATER2
    //pinMode(ledPin_M5Atom, OUTPUT);
    myLED.begin( LED_GPIO, 1 );
    myLED.brightness( LED_BRIGHT );
    myLED.setPixel( 0, L_RED, 1 );

#endif
    
    //! first wakeup the device
    Serial2.write(wakeup_cmd);
    delay(50);
    
    //Serial2.write(factory_reset, sizeof(factory_reset));

    //        Serial2.write(buzzerVolumeLow, sizeof(buzzerVolumeLow));
    
    //NOT WORKING.. it was 12.9.23 (but then no beep on detection either)
    Serial2.write(bootSoundProhibit, sizeof(bootSoundProhibit));
    
//#define TRY_HOST
#ifdef TRY_HOST
    //! then send the command (host .. or maybe continuous)
    Serial2.write(host_mode_cmd, sizeof(host_mode_cmd));
#else
#define TRY_CONTINUOUS
#endif
    
    
//    Serial2.write(buzzerVolumeLow, sizeof(buzzerVolumeLow));
//    Serial2.write(bootSoundProhibit, sizeof(bootSoundProhibit));
//#define TRY_CONTINUOUS
#ifdef  TRY_CONTINUOUS
    //THIS IS WORKING..
      Serial2.write(continuous_mode_cmd, sizeof(continuous_mode_cmd));
#endif
    
   // strcpy(_lastSemanticMarker,"https://iDogWatch.com/bot/feed/test/test");
  //  strcpy(_lastSemanticMarker,"https://iDogWatch.com/bot/smart/test/test");
    strcpy(_lastSemanticMarker,"https://SemanticMarker.org/bot/smart?uuid=QHmwUurxC3&flow=1674517131429");

}



//! the loop
void loop_ATOMQR_UARD_CMD() 
{
    M5.update();
    //    checkButtonA_ButtonProcessing();
    checkButtonB_ButtonProcessing();
//#ifndef TRY_CONTINUOUS
#ifdef NOT_HERE
    //  if (M5.BtnA.isPressed()) {
    if (!_shortPress && !_longPress)
    {
        //        SerialDebug.println("button pressed");
        
        //     M5.dis.fillpix(0x0000ff);
        //        Serial2.write(wakeup_cmd);
        
        delay(50);
        Serial2.write(start_scan_cmd, sizeof(start_scan_cmd));
        delay(1000);
        Serial2.write(stop_scan_cmd, sizeof(stop_scan_cmd));
        
        //continuous not working..
        
//        Serial2.write(buzzerVolumeLow, sizeof(buzzerVolumeLow));
//        Serial2.write(bootSoundProhibit, sizeof(bootSoundProhibit));
        
        //bug in original .. typo
        // Serial2.write(start_scan_cmd, sizeof(stop_scan_cmd));
    }
#endif
    
#define read_serial_monitor
#ifdef read_serial_monitor
    //???  reads from the serial monitor it seems
    // Actually .. there is a way to send a message form the serial monitor..
    boolean serialData = false;
    while (Serial.available()) {
        serialData = true;
        int ch = Serial.read();
        //        Serial2.write(ch);
                SerialDebug.write(ch);
    }
    if (serialData)
        SerialDebug.println();

#endif
    //???
    //    if (Serial2.available()) {
    //        int ch = Serial2.read();
    //        Serial.write(ch);
    //    }
    char semanticMarker[MAX_SM];
    char buf[2];
    sprintf(semanticMarker,"");
    boolean valid = false;
    //! This read from the Serial2 -- the QR Scanner device, and outputs to the serial debug
    //! BUT there seems to be strange charancters...
    while (Serial2.available() > 0)
    {
        char ch = Serial2.read();
        if (ch >= '!' && ch <= '~')
            if (ch != ',')
            {
                valid = true;
                //                SerialDebug.printf("0x%x ",ch);
                //                SerialDebug.print(ch);
                sprintf(buf,"%c",ch);
                strcat(semanticMarker,buf);
                
                if (strlen(semanticMarker) >= MAX_SM)
                {
                    SerialDebug.printf(" *** TOO LONG A STRING *** '%s'\n", semanticMarker);
                    strcpy(semanticMarker,"");
                }
            }
    }
    if (valid)
    {
        //        SerialDebug.println();
        sprintf(buf,"%c",NULL);
        
        strcat(semanticMarker,buf);
        SerialDebug.printf("SM = '%s'\n", semanticMarker);
        
    
        
        //!process the semantic marker.  It will save to _lastSemanticMarker unless scannedDevice
        boolean saveSM = ATOM_processSemanticMarker(semanticMarker);
        
        //!save globally..
         if (saveSM)
             strcpy(_lastSemanticMarker, semanticMarker);
#ifdef USE_FAST_LED
        fillpix(L_GREEN);
#endif

    }

    if (_longPress)
    {
        SerialDebug.printf("Sending last SM = '%s'\n", _lastSemanticMarker);
            // send the _lastSemanticMarker again ...
        //!send this as a DOCFOLLOW message
      //  sendSemanticMarkerDocFollow_mainModule(_lastSemanticMarker);
        
        //!process the semantic marker AGAIN
        //!used _lastSemanticMarker
        ATOM_processSemanticMarker(_lastSemanticMarker);
#ifdef USE_FAST_LED
        fillpix(L_YELLOW);
#endif

    }
    else if (_longLongPress)
    {
#ifdef USE_FAST_LED
        fillpix(L_RED);
#endif
        
        SerialDebug.printf("CLEAN CREDENTIALS and reboot to AP mode\n");
#ifdef PROCESS_SEMANTIC_MARKER
        //! dispatches a call to the command specified. This is run on the next loop()
        main_dispatchAsyncCommand(ASYNC_CALL_CLEAN_CREDENTIALS);
#endif
    }
#ifdef TRY_HOST  ///no
    else if (_shortPress)
    {
        //     M5.dis.fillpix(0x0000ff);

        
        delay(50);
        Serial2.write(start_scan_cmd, sizeof(start_scan_cmd));
        delay(1000);
        Serial2.write(stop_scan_cmd, sizeof(stop_scan_cmd));
        

    }
#else
    else if (_shortPress)
    {
        SerialDebug.printf("Feed BLE\n");
        // send the _lastSemanticMarker again ...
        //!send this as a DOCFOLLOW message
        //sendSemanticMarkerDocFollow_mainModule(_lastSemanticMarker);
//        strcpy(_lastSemanticMarker,"https://iDogWatch.com/bot/feed/test/test");
   
#ifdef PROCESS_SEMANTIC_MARKER
        ///feed always  (done after the code below..)
        main_dispatchAsyncCommand(ASYNC_SEND_MQTT_FEED_MESSAGE);
#endif
    }
#endif
}

/*
 Seems to have a length issue on one loop of the serial ..  OR the next one shows up.. see line 2 below.. https starts up ..
 SM = 'https://SemanticMarker.org/bot/smflowinfo?uuid=QHmwUurxC3&flow=1681834107821&flowname=MotionSensor&flowcat=ESP&USERNAME='
 SM = '&PASSWORD=&M5_DEVICE_1=https://idogwatch.com/bot/feedguestdevice/scott@konacurrents.com/doggy/HowieFeeder'
 SM = 'https://idogwatch.com/bot/feedguestdevice/scott@konacurrents.com/doggy/ScoobyDoo'
 SM = 'https://iDogWatch.com/bot/set/scott@konacurrents.com/pass/SM_VideoPlayback/on'
 SM = 'https://idogwatch.com/bot/feedguestdevice/scott@konacurrents.com/doggy/ScoobyDoo'
 
 */
#endif
