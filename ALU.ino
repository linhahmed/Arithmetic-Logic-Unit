#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int j = -1;
const int up = 0;
const int down = 1;
struct ALU_Driver {
  int First;
  int Second;
  byte opCode : 3;
};

ALU_Driver Driver[8];

int Result_Array[8];

String output[8];

void input(){
  parse("10,1,000", 0);
  parse("15,1,001", 1);
  parse("17,1,010", 2);
  parse("5,2,100", 3);
  parse("8,1,011", 4);
  parse("9,5,101", 5);
  parse("80,10,110", 6);
  parse("45,68,111", 7);
}

void setup(){
  lcd.begin(16, 2);
  lcd.print("Press Up Or Down");
  input();
  pinMode(up,INPUT_PULLUP);
  pinMode(down,INPUT_PULLUP);
  for(int i = 0; i < 8; i++){
    String k = operate(i);
    output[i] = k;
  }
}

void loop(){
  if (digitalRead(up) == LOW){
    j++;
    if(j == 8)
      j = 0;
    lcd.clear();
    lcd.print(output[j]);
    delay(500);
  }
  else if (digitalRead(down) == LOW){
    j--;
    if(j == -1 || j == -2){
      j = 7;
    } 
    lcd.clear();
    lcd.print(output[j]);
    delay(500);
  }
}


void parse(char str[], int index){
  char *t;
  char *temp[3]; int j = 0;
  t = strtok(str, ",");
  while (t != NULL) { 
  	temp[j++] = t;
    t = strtok(NULL, ","); 
  } 
  Driver[index].First = atoi( temp[0]);
  Driver[index].Second = atoi(temp[1]);
  Driver[index].opCode = byte(atoi(temp[2])); 
} 


String operate(int i) {
  switch(Driver[i].opCode) {
    case 0: {
      int Addition = Driver[i].First + Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " + ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += Addition;
      Result_Array[i] = Addition;
      return Result;
    }
    case 1: {
      int Subtraction = Driver[i].First - Driver[i].Second;
      String Result = "";
      Result += String(Driver[i].First);
      Result += " - ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += Subtraction;
      Result_Array[i] = Subtraction;
      return Result;
    }
    case 2: {
      int ShiftL = Driver[i].First << Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " << ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += ShiftL;
      Result_Array[i] = ShiftL;
      return Result; 
    }
    case 3: {
      int ShiftRUS = (unsigned) Driver[i].First >> Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " US>> ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += ShiftRUS;
      Result_Array[i] = ShiftRUS;
      return Result;
      }
    case 4: {
      int ShiftRS = Driver[i].First >> Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " >> ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += ShiftRS;
      Result_Array[i] = ShiftRS;
      return Result;
    }
    case 5: {
      int AND = Driver[i].First & Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " & ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += AND;
      Result_Array[i] = AND;
      return Result;
    }
    case 6: {
      int OR = Driver[i].First | Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " | ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += OR;
      Result_Array[i] = OR;
      return Result;
    }
    case 7: {
      int XOR = Driver[i].First ^ Driver[i].Second;
      String Result;
      Result += String(Driver[i].First);
      Result += " ^ ";
      Result += String(Driver[i].Second);
      Result += " = ";
      Result += XOR;
      Result_Array[i] = XOR;
      return Result;
    }
  }
}
