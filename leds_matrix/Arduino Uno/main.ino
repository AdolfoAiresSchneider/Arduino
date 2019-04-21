const byte data = 4;
const byte latch = 5;
const byte clock = 6;

const byte maskRow[8] = {127, 191, 223, 239, 247, 251, 253, 254};
const byte mask[][8] = {
  {4,10,17,17,31,17,17,17},
  {30,17,17,17,30,17,17,30},
  {31,16,16,16,16,16,16,31},
  {28,18,17,17,17,17,18,28},
  {31,16,16,16,31,16,16,31},
  {31,16,16,16,31,16,16,16},
  {6,9,16,16,19,17,9,6},
  {17,17,17,17,31,17,17,17},
  {31,4,4,4,4,4,4,31},
  {7,1,1,1,1,17,17,14},
  {17,18,20,24,24,20,18,17},
  {16,16,16,16,16,16,16,31},
  {17,27,21,17,17,17,17,17},
  {17,25,25,29,23,19,17,17},
  {14,17,17,17,17,17,17,14},
  {30,17,17,30,16,16,16,16},
  {14,17,17,17,17,21,14,1},
  {30,17,17,28,24,20,18,17},
  {14,17,16,14,1,1,17,14},
  {0,31,4,4,4,4,4,4},
  {17,17,17,17,17,17,17,14},
  {17,17,17,17,17,17,10,4},
  {17,17,17,17,17,21,27,17},
  {17,10,10,4,4,10,10,17},
  {17,10,4,4,4,4,4,4},
  {31,2,2,4,8,8,16,31},
  {0,0,0,0,0,0,0,0}
};

void setup(){
  DDRD = 0xFF;
}

void loop(){
 while(1)
 {
   digitalWrite(7, HIGH);
  // show("AAAAAAAAAAAAA",6);
   
   }
  
}

void shift(byte data, byte clock, long value){
  shiftOut(data, clock, LSBFIRST, byte(value));
  shiftOut(data, clock, LSBFIRST, byte(value >> 8));
  shiftOut(data, clock, LSBFIRST, byte(value >> 16));
  shiftOut(data, clock, LSBFIRST, byte(value >> 24));
}

void show(const char* s, int t){ // assume que s tem 4 espaços no final
  unsigned long atual[8] = {0};
  for(byte i = 0; i < 4; ++i){
    for(byte row = 0; row < 8; ++row){
      atual[row] = (atual[row] << 6) | mask[s[i] - 'A'][row];
    }
  }
  
  for(int i = 4; s[i]; ++i){
    for(int idx = 5; idx >= 0; --idx){
      for(byte row = 0; row < 8; ++row){  // terra da linha row
        atual[row] = (atual[row] & 0x0FFFFFF) | ((long)maskRow[row] << 24);
      }
      
      for(int j = 0; j < t; ++j){
        for(byte row = 0; row < 8; ++row){
          digitalWrite(latch,LOW);
          shift(data, clock, atual[row]);
          digitalWrite(latch, HIGH);
          delay(2);
        }
      }

      for(byte row = 0; row < 8; ++row){
        atual[row] = (atual[row] << 1) | ((mask[s[i] - 'A'][row] >> idx) & 1);
      }
    }
  }
}

