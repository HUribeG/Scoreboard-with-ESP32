void clc(bool s){
  //Limpiar tablero
  if(s){
    for(int i=0;i<8;i++){
      lmd1.setDigit(i,LEDMatrixDriver::BCD_BLANK);
      lmd2.setDigit(i,LEDMatrixDriver::BCD_BLANK);
      lmd1.display();
      lmd2.display();
      }
  }
  else{
    for(int i=0;i<8;i++){
      lmd1.setDigit(i,8,true);
      lmd2.setDigit(i,8,true);
      lmd1.display();
      lmd2.display();
  }
  }
}


void MarcadorLoc(int numLoc, bool poses){
  //Set marcador local
  MarLoc=numLoc;
//  Serial.print("Marcador:");
//  Serial.println(MarLoc);
  int DIG=MarLoc;
  for(int i=5; i<8;i++){
    int DIGITO=DIG % 10;
    DIG=DIG/10;
    lmd1.setDigit(i,DIGITO, poses? 1:0);
    lmd1.display();
  }
}

void MarcadorVis(int numVis,bool poses){
  MarVis=numVis;
  int DIG=MarVis;
  for(int i=0; i<3;i++){
    int DIGITO=DIG % 10;  
    DIG=DIG/10;
    lmd1.setDigit(i,DIGITO,poses? 0:1);
    lmd1.display();
  }
}

void setPeriodo(int period){

  int DIG=period;
  for(int i=3; i<5; i++){
    int DIGITO=DIG % 10;
    DIG=DIG/10;
    lmd1.setDigit(i, DIGITO);
    lmd1.display();   
  }
}


void FaultLocal(int variable, bool bonuss){ 
  int DIG=variable;
  for(int i=6; i<8;i++){
    int DIGITO=DIG % 10;  
    DIG=DIG/10;
    lmd2.setDigit(i,DIGITO, bonuss? 1:0);
    lmd2.display();
  }
}
void FaultVisitante(int variable, bool bonuss){ 
  int DIG=variable;
  for(int i=4; i<6;i++){
    int DIGITO=DIG % 10;  
    DIG=DIG/10;
    lmd2.setDigit(i,DIGITO, bonuss? 0:1);
    lmd2.display();
  }
}



void UpdateTime(){
  //Serial.println(rtc.getTime("%M%S"));
  
  if(Activate==1){
  
    if(TimeStop){
      Time1=millis();
      if((Time1)-(Time2)>1000){
        Time2=Time1;
        
        if(secs<=0 && minu<=0){
          TimeStop= !TimeStop;
          return;
        }
        secs = secs==0? 60:secs; 
        minu = minu - (secs/60);
        secs = secs-1;
  //      Serial.print(minu);
  //      Serial.print(":");
  //      Serial.println(secs);
      }
      }
      int Secs=secs;
      for(int i=0; i<2;i++){
        int DIGITO=Secs % 10;
        Secs=Secs/10;
        lmd2.setDigit(i,DIGITO);
        lmd2.display(); 
      }    
      int Minu=minu;
      for(int i=2; i<4;i++){
        int DIGITO=Minu % 10;
        Minu=Minu/10;
        lmd2.setDigit(i,DIGITO, i==2? 1:0);
        lmd2.display();
      }}
    else if(Activate==0){
      clc(0);
        }
    else{
      clc(1);
    }
      //Serial.println(Time);
}


void sonido(){
  digitalWrite(Chicharra, Chicha);
}

void commandProcessWifi(){

  MarcadorVis(Vis,Pos);
  MarcadorLoc(Loc,Pos);
//  Stop ? TimeStop=!TimeStop:TimeStop;
  TimeStop=Stop;
  setPeriodo(Periodo);

  
  FaultLocal(FaultL,Tablero? 0:Bonus);
  FaultVisitante(FaultV,Tablero? 1:Bonus);
  sonido();
  
  if(TimeSetState){
  MinutosIniciales=TimeSet;
  minu=MinutosIniciales/100;
  secs=MinutosIniciales%100;
  if(secs>=60 && secs<100){
  minu=minu+(1*(secs/60));
  secs=secs%60;
  
  }}
  
}


/////       Funciones de comunicación

void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
  Activate=1;
  Serial.println("Alguien se conecto a la raiz");
  //MarcadorLoc(10);
}

void handlePost(){
  
  String mensaje="Body not available";
  Serial.println(server.args());
  for(int i=0;i<server.args();i++){
    Serial.print(server.argName(i)+":\t");
    Serial.println(server.arg(i));
  }
  if(server.hasArg("plain")){
    deserializeJson(doc,server.arg(0));
    Loc = doc["Loc"]; //Marcador local
    Vis = doc["Vis"];   //Marcador visitante
    TimeSet = doc["TimeSet"]; //Variable del tiempo recibido
    TimeSetState = doc["TimeSetState"]; //True: actualiza tiempo del reloj, False: no actualiza el tiempo del reloj
    Stop = doc["Stop"];//True: reloj avanza , False: reloj no avanza
    Periodo = doc["Periodo"];//Periodo actual
    Bonus = doc["Bonus"];//Numero bonus
    Pos= doc["Posesion"];//Cambiar posesion
    FaultL = doc["FaultL"];//Faltas del equipo visitante
    FaultV = doc["FaultV"]; //Faltas del equipo visitante
    Chicha = doc["Chicha"]; //si activar chicharra o no
    Tablero = doc["Tablero"]; //True:modo volley, false: modo basquet
    Activate= doc["Activate"]; //True:modo volley, false: modo basquet
    
//    mensaje = "Loc: ";
//    mensaje += String(Loc);
//    mensaje += "\nVis: ";
//    mensaje += String(Vis);
//    mensaje += "\nTimeSet: "; 
//    mensaje += String(TimeSet);
//    mensaje += "\nTimeSetState: "; 
//    mensaje += String(TimeSetState);
//    mensaje += "\nStop: "; 
//    mensaje += String(Stop);
    commandProcessWifi();
  }
  else{
    
  }
  //Serial.println(mensaje);
  
  server.send(200, "text/plain", mensaje);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
} 



///////// MULTIPROCESAMIENTO//////////

//    Serial.println((actual-anterior));
//      if((actual-anterior)>500){
//        Serial.println("entra");
//        anterior=actual;
//        stateT= stateT? 0:1; 
//      }
