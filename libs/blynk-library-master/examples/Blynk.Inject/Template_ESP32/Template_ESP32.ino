/*************************************************************
  This is a DEMO. You can use it only for development and testing.
  You should open Setting.h and modify General options.

  If you would like to add these features to your product,
  please contact Blynk for Businesses:

                   http://www.blynk.io/

 *************************************************************/

//#define USE_WROVER_BOARD
#define USE_CUSTOM_BOARD          // See "Custom board configuration" in Settings.h

#define APP_DEBUG        // Comment this out to disable debug prints

#define BLYNK_SSL_USE_LETSENCRYPT   // Comment this out, if using public Blynk Cloud

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#include "BlynkProvisioning.h"

void setup() {
  delay(100);
  Serial.begin(115200);

  BlynkProvisioning.begin();

}

void loop() {
  // This handles the network and cloud connection
  BlynkProvisioning.run();

}

