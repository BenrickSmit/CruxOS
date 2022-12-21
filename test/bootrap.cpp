#include <Arduino.h>
#include <gtest/gtest.h>

#include <cruxos_constants.h>

// Code to run all Tests

/** For Native Tests*/ 
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


/** For Embedded Tests*/
void setup(){
    Serial.begin(BAUD_RATE);
    delay(2000);

    testing::InitGoogleTest();
    if(!RUN_ALL_TESTS()){
        Serial.println("Tests Failures Ignored: PASS");
    } else {
        Serial.println("Tests Failures Ignored: FAIL");
    }
}
