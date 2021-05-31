#include "HelpLib.h"
#include <arduino.h>

float filter(float* mass){
  float tmp[3] = {mass[0],mass[1],mass[2]};
  for(int j = 0; j < 2; j++){
    for(int i = 0; i < 2; i++){
      if (tmp[i] > tmp[i+1]){
        int temp = tmp[i];
        tmp[i] = tmp[i+1];
        tmp[i+1] = temp;
      }
    }
  }
  return tmp[1];
} 
void showGraph(float tf, float hf){
   delay(20);
   Serial.println("$"); 
   Serial.println(tf); 
   Serial.println(" ");
   Serial.println(hf); 
   Serial.println(";");
}
