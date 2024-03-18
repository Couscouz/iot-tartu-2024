const int PIN_RED   = D5;
const int PIN_GREEN = D6;
const int PIN_BLUE  = D7;
const int PIN_BUTTON = D4;
int state_button = 0;
int button_state;
void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  button_state = digitalRead(PIN_BUTTON);
  if(button_state == LOW){
    state_button += 1;
  }
  state_button = state_button % 3;
  if(state_button == 0){
    digitalWrite(PIN_RED, LOW);
    analogWrite(PIN_GREEN, 201);
    digitalWrite(PIN_BLUE, LOW);
  }
    if(state_button == 1){
    analogWrite(PIN_RED,   200);
    digitalWrite(PIN_GREEN, LOW);
    digitalWrite(PIN_BLUE,  LOW);
  }  
  if(state_button == 2){
    digitalWrite(PIN_RED, LOW);
    digitalWrite(PIN_GREEN,LOW);
    analogWrite(PIN_BLUE,  200);
  }
  delay(500);
}