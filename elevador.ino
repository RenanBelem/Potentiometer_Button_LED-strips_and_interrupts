#include <Adafruit_NeoPixel.h>

#define botaoSubir A1
#define botaoDescer A0
#define painelControle A3
#define botoesElevador A2
#define ledOperante 11
#define ledPortas 12
#define ledEmergencia 10
#define fitaLedAndar 13

int condicaoSubir = 0;
int condicaoDescer = 0;
int botaoPainel = 0;
int botaoElevador = 0;

int andarAtual = 0;
int andarSolicitado = 0;

bool operante = false;
bool portasAbertas = false;
bool emergencia = false;

Adafruit_NeoPixel fitaLed = Adafruit_NeoPixel(10, fitaLedAndar, NEO_GRB + NEO_KHZ800);

enum { INOPERANTE,
	   OCIOSO,
	   ALINHADO_S,
	   MOVENDO_S,
	   ESTACIONADO_S,
	   FIM_S,
	   ALINHADO_D,
	   MOVENDO_D,
	   ESTACIONADO_D,
	   FIM_D} estado = INOPERANTE;

void setup()
{
  Serial.begin(9600);
  pinMode(ledOperante, OUTPUT);
  pinMode(ledPortas, OUTPUT);
  pinMode(ledEmergencia, OUTPUT);
  fitaLed.begin();
}

void abreFechaPortas(){
	portasAbertas = !portasAbertas;
	digitalWrite(ledPortas, portasAbertas);
}

void toggleEmergencia(){
	emergencia = !emergencia;
	digitalWrite(ledEmergencia, emergencia);
}

void solicitarAndar(int andar){
	andarSolicitado = andar;
}

void verificarDemanda(){
	if(andarSolicitado>andarAtual){
		estado = MOVENDO_S;
	}
	else if(andarSolicitado<andarAtual){
		estado = MOVENDO_D;
	}
}

void verificarBotoesPainel(){
	botaoPainel = analogRead(painelControle);
	if(botaoPainel == 930){
		operante = !operante;
	} else if(botaoPainel == 853){
		abreFechaPortas();
	} else if(botaoPainel == 787){
		toggleEmergencia();
	}
}

void verificarBotoesElevador(){
	botaoElevador = analogRead(botoesElevador);
	if(botaoElevador == 930){
		solicitarAndar(0);
	} else if(botaoElevador == 853){
		solicitarAndar(1);
	} else if(botaoElevador == 787){
		solicitarAndar(2);
	} else if(botaoElevador == 731){
		solicitarAndar(3);
	} else if(botaoElevador == 682){
		solicitarAndar(4);
	} else if(botaoElevador == 639){
		solicitarAndar(5);
	} else if(botaoElevador == 602){
		solicitarAndar(6);
	} else if(botaoElevador == 568){
		solicitarAndar(7);
	} else if(botaoElevador == 538){
		solicitarAndar(8);
	}
}

void verificarBotoesSubir(){
	condicaoSubir = analogRead(botaoSubir);
	if(condicaoSubir == 930){
		Serial.println("Botao para subir do terreo pressionado");
	} else if(condicaoSubir == 853){
		Serial.println("Botao para subir do 1 andar pressionado");
	} else if(condicaoSubir == 787){
		Serial.println("Botao para subir do 2 andar pressionado");
	} else if(condicaoSubir == 731){
		Serial.println("Botao para subir do 3 andar pressionado");
	} else if(condicaoSubir == 682){
		Serial.println("Botao para subir do 4 andar pressionado");
	} else if(condicaoSubir == 639){
		Serial.println("Botao para subir do 5 andar pressionado");
	} else if(condicaoSubir == 602){
		Serial.println("Botao para subir do 6 andar pressionado");
	} else if(condicaoSubir == 568){
		Serial.println("Botao para subir do 7 andar pressionado");
	} else if(condicaoSubir == 538){
		Serial.println("Botao para subir do 8 andar pressionado");
	}
}

void verificarBotoesDescer(){
	condicaoDescer = analogRead(botaoDescer);
	if(condicaoDescer == 930){
		Serial.println("Botao para descer do terreo pressionado");
	} else if(condicaoDescer == 853){
		Serial.println("Botao para descer do 1 andar pressionado");
	} else if(condicaoDescer == 787){
		Serial.println("Botao para descer do 2 andar pressionado");
	} else if(condicaoDescer == 731){
		Serial.println("Botao para descer do 3 andar pressionado");
	} else if(condicaoDescer == 682){
		Serial.println("Botao para descer do 4 andar pressionado");
	} else if(condicaoDescer == 639){
		Serial.println("Botao para descer do 5 andar pressionado");
	} else if(condicaoDescer == 602){
		Serial.println("Botao para descer do 6 andar pressionado");
	} else if(condicaoDescer == 568){
		Serial.println("Botao para descer do 7 andar pressionado");
	} else if(condicaoDescer == 538){
		Serial.println("Botao para descer do 8 andar pressionado");
	}
}

void loop() {
  Serial.print("Entrando no loop ");
  Serial.print("[");
  Serial.print(estado);
  Serial.print("] ");

  verificarBotoesPainel();
  verificarBotoesDescer();
  verificarBotoesSubir();
  verificarBotoesElevador();
  
  if(!operante){
  	estado = INOPERANTE;
  	digitalWrite(ledOperante, LOW);
  } else {
	  fitaLed.setPixelColor(andarAtual, fitaLed.Color(255,0,0));
	  fitaLed.show();
  }

  switch (estado)
  {
	case INOPERANTE: estado_INOPERANTE(); break;
	case OCIOSO: estado_OCIOSO(); break;
	case ALINHADO_S: estado_ALINHADO_S(); break;
	case MOVENDO_S: estado_MOVENDO_S(); break;
	case ESTACIONADO_S: estado_ESTACIONADO_S(); break;
	case FIM_S: estado_FIM_S(); break;
	case ALINHADO_D: estado_ALINHADO_D(); break;
	case MOVENDO_D: estado_MOVENDO_D(); break;
	case ESTACIONADO_D: estado_ESTACIONADO_D(); break;
	case FIM_D: estado_FIM_D(); break;
	default: Serial.println("ESTADO INVÁLIDO");
  }
  
  delay(1000); // apenas para teste inicial da máquina de estados
}

void estado_INOPERANTE()
{
  Serial.println("==> INOPERANTE");
  if(operante){
  	digitalWrite(ledOperante, HIGH);
  	estado = OCIOSO;
  }
}

void estado_OCIOSO()
{
  Serial.println("==> OCIOSO");
  if(!portasAbertas){
  	abreFechaPortas();
  }
  verificarDemanda();
}

void estado_ALINHADO_S()
{
  Serial.println("==> ALINHADO_S");
  estado = ESTACIONADO_S;
}

void estado_MOVENDO_S()
{
  Serial.println("==> MOVENDO_S");
  if(portasAbertas){
  	abreFechaPortas();
  }
  if(andarAtual!=andarSolicitado){
  	fitaLed.setPixelColor(andarAtual, fitaLed.Color(0,0,0));
  	andarAtual+=1;
  }
  else{
  	estado = ALINHADO_S;
  }
}

void estado_ESTACIONADO_S()
{ 
  Serial.println("==> ESTACIONADO_S");
  if(!portasAbertas){
  	abreFechaPortas();
  }
  verificarDemanda();
  estado = FIM_S;
}

void estado_FIM_S()
{
  Serial.println("==> FIM_S");
  estado = ALINHADO_D;
}

void estado_ALINHADO_D()
{
  Serial.println("==> ALINHADO_D");
  estado = ESTACIONADO_D;
}

void estado_MOVENDO_D()
{
  Serial.println("==> MOVENDO_D");
  if(portasAbertas){
  	abreFechaPortas();
  }
  if(andarAtual!=andarSolicitado){
  	fitaLed.setPixelColor(andarAtual, fitaLed.Color(0,0,0));
  	andarAtual-=1;
  }
  else{
  	estado = ALINHADO_D;
  }
}

void estado_ESTACIONADO_D()
{
  Serial.println("==> ESTACIONADO_D");
  verificarDemanda();
  estado = FIM_D;
}

void estado_FIM_D()
{
  Serial.println("==> FIM_D");
  if(andarAtual==0){
  	estado = OCIOSO;
  	return;
  }
  andarSolicitado = 0;
  estado = MOVENDO_D;
}
