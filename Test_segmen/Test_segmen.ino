#include <LEDMatrixDriver.hpp>

#define BUTTON 0
#define LED 2

int digit_lmd1 = 0;
int digit_lmd2 = 0;
int module_selection = 0;


int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin  

// Other pins are Arduino specific SPI pins (MOSI=DIN, SCK=CLK of the LEDMatrix) see https://www.arduino.cc/en/Reference/SPI
const uint8_t LEDMATRIXA_CS_PIN = 5;
//const uint8_t LEDMATRIXA_CS_PIN = 15;

const int LEDMATRIX_SEGMENTS = 1;
//const int LEDMATRIX_WIDTH    = LEDMATRIX_SEGMENTS * 8;


//esp32

LEDMatrixDriver lmd1(LEDMATRIX_SEGMENTS, LEDMATRIXA_CS_PIN,0 ); //Crono y fault
//LEDMatrixDriver lmd2(LEDMATRIX_SEGMENTS, LEDMATRIXB_CS_PIN,0 ); //Marcador y periodo

int number = 0;
  int startTime = 0;
void setup() {
  
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  lmd1.setEnabled(true);  
  lmd1.setIntensity(0);   // 0 = low, 10 = high
  lmd1.setScanLimit(7);
  lmd1.setDecode(0xFF);
  
  // lmd2.setEnabled(true);
  // lmd2.setIntensity(0);   // 0 = low, 10 = high
  // lmd2.setScanLimit(7);
  // lmd2.setDecode(0xFF);

  lmd1.clear();
  //clc(0);

  // lmd1.setDigit(1, LEDMatrixDriver::BCD_BLANK);
  // lmd1.setDigit(2, 6);
  // lmd1.setDigit(3, LEDMatrixDriver::BCD_BLANK);
  // lmd1.display();
  // lmd1.clear();

  delay(1000);  
}

void loop() {

  // digitalWrite(LED, HIGH);
  // delay(300);
  // digitalWrite(LED, LOW);
  // delay(300);
  
digitalWrite(LED, LOW);
  int rowbits = B000;
  lmd1.clear();
  delay(100);
  for (int i=0; i<8; i++) {
   // lmd1.clear();
    //delay(5);
   //lmd1.clear();
    lmd1.setDigit(i-1, LEDMatrixDriver::BCD_BLANK);
    //lmd1.clear();
    lmd1.setDigit(i, rowbits);
    lmd1.setDigit(i+1, LEDMatrixDriver::BCD_BLANK);
    lmd1.display();
    rowbits = rowbits + B1;
    delay(250);
   }
 // testbench();

 }

void testbench(){

  lmd1.clear();
  lmd1.setDigit(1, 2);
  lmd1.setDigit(2, LEDMatrixDriver::BCD_BLANK);
  lmd1.setDigit(3, 4);
  lmd1.setDigit(4, LEDMatrixDriver::BCD_BLANK);      
  lmd1.setDigit(5, 7);
  lmd1.setDigit(7, LEDMatrixDriver::BCD_BLANK);  
  lmd1.display();
}
 
  // if(digitalRead(BUTTON) == LOW) { //Push button pressed

  // // Key debounce handling
  //   delay(100);
  //   int startTime = millis();
  //   while(digitalRead(BUTTON) == LOW) delay(50);
  //   int endTime = millis();

  //   if((endTime - startTime) > 3000) {
  //     //Cambia el modulo
      
  //     module_selection +=1;
  //     if(module_selection > 1){
  //       module_selection = 0;
  //     }
  //     else{
  //     //   digitalWrite(LED, HIGH);
  //     //   delay(100);
  //     //   digitalWrite(LED, LOW);
  //     //   delay(100);
  //     //   digitalWrite(LED, HIGH);
  //     //   delay(100);
  //     //   digitalWrite(LED, LOW);
  //     }
  //     clc(0);
  //   } 

  //   else{
  //   // Cambia de digito
  //     clc(0);
  //     if (module_selection==0) {
  //       digit_lmd1 +=1;
  //       if(digit_lmd1 > 7){
  //         digit_lmd1 = 0;          
  //       }
        
  //       digitalWrite(LED, HIGH);
  //       delay(100);
  //       digitalWrite(LED, LOW);
  //     }
  //     else {
  //       digit_lmd2 +=1;
  //       if (digit_lmd2 > 7) {
  //         digit_lmd2 = 0;
  //       }

  //       digitalWrite(LED, HIGH);
  //       delay(100);
  //       digitalWrite(LED, LOW);    
  //     }

  //   }   
  // }


  // int cambio = 300;
  
  // if(millis() > (startTime+cambio)){
  //   startTime = millis();
  //   if(number > 8){
  //     number = 0;
  //   }
  //   else{
  //     number +=1;
  //   }
  // }

  // if(module_selection == 0){
    
  //   //lmd1.setDigit(0, 2);
  //   // lmd1.clear();
  //   // lmd1.display();
  //   lmd1.setDigit(7, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(6, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(5, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(4, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(3, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(2, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(1, LEDMatrixDriver::BCD_BLANK);
  //   lmd1.setDigit(digit_lmd1, number);    
  //   lmd1.display();

  // }
  // else{
  //   lmd2.setDigit(digit_lmd2, 2);
  //   lmd2.display();

      
  // }
  
//}


// void clc(bool s){
//   //Limpiar tablero
//   if(s){
//     for(int i=0;i<9;i++){
//       lmd1.setDigit(i,LEDMatrixDriver::BCD_BLANK);
//       lmd2.setDigit(i,LEDMatrixDriver::BCD_BLANK);
//       lmd1.display();
//       lmd2.display();
//       }
//   }
//   else{
//     for(int i=0;i<9;i++){
//       lmd1.setDigit(i,8,1);
//       lmd2.setDigit(i,8,1);
//       lmd1.display();
//       lmd2.display();
//     }
//   }
// }

// // Paso 1
// #include <LedControl.h>

// // Paso 2
//                           //din clk cs
// LedControl lc = LedControl(11, 13, 10, 1);

// // Paso 3
// void setup() {
//   lc.shutdown(0, false); 
//   lc.setIntensity(0, 8);
//   lc.clearDisplay(0);
// }

// // Paso 5
// void loop() { 
//     displayNumber(1234);
//     delay(1000);
// }

// // Paso 4
// void displayNumber( long number) {
//   long result;
//   int pos = 0 ;
//   lc.clearDisplay(0);
//   while ( number > 0 ) {
//     result = number % 10 ; 
//     number = number / 10 ;
//     lc.setDigit(0,pos++,result,false);
//   }
// }
