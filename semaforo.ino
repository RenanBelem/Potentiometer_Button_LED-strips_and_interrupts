#define semA_G 4
#define semA_Y 5
#define semA_R 6

#define semB_G 7
#define semB_Y 8
#define semB_R 9

#define pot A0

#define buttonA 2
#define buttonB 3

int potValor;

const int X = 2;
const int Y = 2;
const int G_total = 10;

int G_A = 6;
int G_B = G_total - G_A;

float fracVerde;

bool butA = false;
bool butB = false;
int pausa = 50;

void botaoApertadoA(){
	butA = true;
}
void botaoApertadoB(){
	butB = true;
}

int toMs(int t){
  return t*1000;
}

void setup() {
  pinMode(semA_R, OUTPUT);  
  pinMode(semA_Y, OUTPUT);
  pinMode(semA_G, OUTPUT);
  pinMode(semB_R, OUTPUT);
  pinMode(semB_Y, OUTPUT);
  pinMode(semB_G, OUTPUT);

  pinMode(pot, INPUT);

  digitalWrite(semA_R, LOW);
  digitalWrite(semA_Y, LOW);
  digitalWrite(semA_G, LOW);
  digitalWrite(semB_R, LOW);
  digitalWrite(semB_Y, LOW);
  digitalWrite(semB_G, LOW);  

  attachInterrupt(buttonA - 2, botaoApertadoA, RISING);
  attachInterrupt(buttonB - 2, botaoApertadoB, RISING);
  
  Serial.begin(9600);
}

void loop() { 
  potValor = analogRead(A0);
  if(potValor<342){
    fracVerde = map(potValor, 0, 341, 250, 500)/1000.00;
  }
  else{
    fracVerde = map(potValor, 342, 1023, 500, 667)/1000.00;
  }
  
  G_A = G_total * fracVerde;
  G_B = G_total - G_A;
  
  if(butA == true && butB == true){
    delay(toMs(pausa));
  }
  
  digitalWrite(semA_G, HIGH);
  digitalWrite(semA_R, LOW);
  digitalWrite(semB_R, HIGH);
  delay(toMs(G_A));

  digitalWrite(semA_G, LOW);
  digitalWrite(semA_Y, HIGH);
  delay(toMs(Y));
  
  digitalWrite(semA_Y, LOW);
  digitalWrite(semA_R, HIGH);
  delay(toMs(X));
  
  digitalWrite(semB_R, LOW);
  digitalWrite(semB_G, HIGH);
  delay(toMs(G_B));
  
  digitalWrite(semB_G, LOW);
  digitalWrite(semB_Y, HIGH);
  delay(toMs(Y));

  digitalWrite(semB_Y, LOW);
  digitalWrite(semA_R, HIGH);
  digitalWrite(semB_R, HIGH);
  delay(toMs(X));
}
