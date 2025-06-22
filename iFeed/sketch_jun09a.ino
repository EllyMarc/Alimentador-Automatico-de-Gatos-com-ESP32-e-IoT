#include <WiFi.h>
#include <SPIFFS.h>
#include <FS.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESP32Servo.h>

WebServer server(80);
Servo myServo;

// Dados do Wi-Fi
const char* ssid = "Portela";
const char* password = "kikuxi10";

// Pino do servo motor
const int servoPin = 26;

// Variáveis de controle
bool acionarServo = false;
bool acabouTempo = false;
bool tempoCongelado = false;


// Controle do temporizador
unsigned long tempoAnterior = 0;
unsigned long tempoAlvo = 0;

//entrega o arquivo JavaScript
void handleJS() {
  File file = SPIFFS.open("/script.js", "r");
  if (!file) {
    server.send(404, "text/plain", "Arquivo JS não encontrado");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

//entrega o arquivo CSS
void handleCSS() {
  File file = SPIFFS.open("/style.css", "r");
  if (!file) {
    server.send(404, "text/plain", "Arquivo CSS não encontrado");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

//entrega o arquivo html
void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Erro ao abrir index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

//requisição pra ativar o servo motor
void handleAtivarServo() {
  acionarServo = true;
  server.send(200, "text/plain", "Comando recebido: Ativar Servo");
}

//função que congela o temporizador
void handleTempoRestante() {
  if (tempoCongelado) {
    server.send(200, "text/plain", "0");  // Responde "tempo parado"
    return;
  }

  unsigned long tempoRestante;
  if (millis() - tempoAnterior >= tempoAlvo) {
    tempoRestante = 0;
  } else {
    tempoRestante = (tempoAlvo - (millis() - tempoAnterior)) / 1000;
  }

  String resposta = String(tempoRestante);
  server.send(200, "text/plain", resposta);
}

//função que gera um tempo aleatório de acordo com deteminada faixa
void gerarNovoTempo() {
  int segundos = random(15, 17);

  tempoAlvo = segundos * 1000;   // milissegundos
  tempoAnterior = millis();
  acabouTempo = false;

  Serial.print("Novo tempo gerado: ");
  Serial.print(segundos);
  Serial.println(" segundos.");
}


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Inicializa a geração de números aleatórios

  // Inicializa o servo
  myServo.attach(servoPin);
  myServo.write(0); // posição inicial

  // Inicializa SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());

  // Rotas do servidor
  server.on("/style.css", HTTP_GET, handleCSS);
  server.on("/script.js", HTTP_GET, handleJS);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/servo", HTTP_GET, handleAtivarServo);
  server.on("/tempo", HTTP_GET, handleTempoRestante);
  server.on("/imagens/osso.png", HTTP_GET, []() {
  File file = SPIFFS.open("/imagens/osso.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Imagem não encontrada");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
});

server.on("/imagens/alarme.png", HTTP_GET, []() {
  File file = SPIFFS.open("/imagens/alarme.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Imagem não encontrada");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
});

server.on("/imagens/notifica.png", HTTP_GET, []() {
  File file = SPIFFS.open("/imagens/notifica.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Imagem não encontrada");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
});
server.on("/imagens/iFeed.png", HTTP_GET, []() {
  File file = SPIFFS.open("/imagens/iFeed.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Favicon não encontrado");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
});
server.on("/imagens/favicon.png", HTTP_GET, []() {
  File file = SPIFFS.open("/imagens/favicon.png", "r");
  if (!file) {
    server.send(404, "text/plain", "Favicon não encontrado");
    return;
  }
  server.streamFile(file, "image/png");
  file.close();
});

  server.begin();
  Serial.println("Servidor iniciado");

  // Gera o primeiro tempo aleatório
  gerarNovoTempo();
}



void loop() {
  server.handleClient();

  // Verifica o tempo
  if (millis() - tempoAnterior >= tempoAlvo) {
    acabouTempo = true;
  }

  // Se acionou o botão ou acabou o tempo, então ativa o servo
  if (acionarServo || acabouTempo) {
  tempoCongelado = true; // CONGELA O TEMPO

  Serial.println("Ativando servo...");
  myServo.write(90);
  delay(1000);
  myServo.write(60);
  Serial.println("Servo voltou.");

  acionarServo = false;
  acabouTempo = false;

  delay(6000); //tempo de espera

  gerarNovoTempo();       // Novo tempo só depois da pausa
  tempoCongelado = false; // LIBERA o tempo novamente
}

}
