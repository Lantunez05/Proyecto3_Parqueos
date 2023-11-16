
/*============================================Librerias=====================================================*/
#include <stdio.h>
#include <WiFi.h> //manejo wifi
#include <WiFiClient.h> //manejo clientes
#include <WebServer.h> //conexion servidor
#include <ESPmDNS.h> //IP fija
/*==============================================================================================================*/


/*============================================Config UART=====================================================*/
char tiva1;
char tiva2;
/*==============================================================================================================*/

/*============================================Config Server=====================================================*/
/* Put your SSID & Password */
const char* ssid = "ESPRED";  // nombre de red
const char* password = "12345678";  //Password red

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t pv1 = 0;
uint8_t pv2 = 0;
uint8_t pv3 = 0;
uint8_t pv4 = 0;
uint8_t pv5 = 0;
uint8_t pv6 = 0;
uint8_t pv7 = 0;
uint8_t pv8 = 0;

bool p1 = true;
bool p2 = true;
bool p3 = true;
bool p4 = true;
bool p5 = true;
bool p6 = true;
bool p7 = true;
bool p8 = true;

/*==============================================================================================================*/


/*============================================Config Display=====================================================*/
const int a = 22;
const int b = 2;
const int c = 26;
const int d = 4;
const int e = 5;
const int f = 15;
const int g = 27;
const int push1 = 19;
const int push2 = 18;
int contador = 0;
int valor;


//                     8         7         6         5         4         3         2         1         0   */
char val7[9][8] = {"1111111","0000111","1111101","1101101","1100110","1001111","1011011","0000110","0111111"};
int seg7[7] = {g,f,e,d,c,b,a};
/*==============================================================================================================*/



/*============================================SETUP=====================================================*/
void setup() {
  Serial.begin(115200); //UART0
  Serial2.begin(115200); //UART2

  for(int i=0; i<8; i++)
    {
      pinMode(seg7[i], OUTPUT);
    }

  pinMode(push1, INPUT_PULLUP);
  pinMode(push2, INPUT_PULLUP);
  

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/actualizar",handle_actualizar);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");

  asignar(contador);
}
/*==============================================================================================================*/



/*================================================MAIN=====================================================*/
void loop() 
{ 
  server.handleClient();
  Parqueotiva1(); 
  Parqueotiva2(); 
  contador = pv1 + pv2 + pv3 + pv4 + pv5 + pv6 + pv7 + pv8; 
  asignar(contador);
}

/*==============================================================================================================*/


/*================================================Funciones=====================================================*/
  void Parqueotiva1(){
    tiva1 = Serial.read();
    char bit = tiva1;
     if(bit == 'A')//ocupado
        { 
          pv1 = 1;
          p1 = false;
        } 
        else if(bit == 'a') //libre
        {
          pv1 = 0;
          p1 = true;
        }
        
        if(bit == 'B')//ocupado
        { 
          pv2 = 1;
          p2 = false;
        } 
        else if(bit == 'b') //libre
        {
          pv2 = 0;
          p2 = true;
        }

        if(bit == 'C') //ocupado
        {
          pv3 = 1;
          p3 = false;
        } 
        else if(bit == 'c') //libre
        {
          pv3 = 0;
          p3 = true;
        }

        if(bit == 'D') //ocupado
        { 
          pv4 = 1;
          p4 = false;
        } 
        else if(bit == 'd') //libre
        {
          pv4 = 0;
          p4 = true;
        }
    /*char tiva1[8];//señal tiva 1
    size_t bytesRead = Serial.readBytes(tiva1, 7); //"A|B|C|D|"
    tiva1[bytesRead]='\0';
    Serial.println(tiva1);
    delay(100);
      for (int j = 0; j < 7; j++)
    {   
        char bit = tiva1[j]; // Obtiene el bit menos significativo de la cadena i
        
       
    }   */ 
    
  }

  void Parqueotiva2(){

  tiva2 = Serial.read();
    char bit = tiva2;
   if(bit == 'E')//ocupado
        { 
          pv5 = 1;
          p5 = false;
        } 
        else if(bit == 'e') //libre
        {
          pv5 = 0;
          p5 = true;
        }
        
        if(bit == 'F')//ocupado
        { 
          pv6 = 1;
          p6 = false;
        } 
        else if(bit == 'f') //libre
        {
          pv6 = 0;
          p6 = true;
        }

        if(bit == 'G') //ocupado
        {
          pv7 = 1;
          p7 = false;
        } 
        else if(bit == 'g') //libre
        {
          pv7 = 0;
          p7 = true;
        }

        if(bit == 'H') //ocupado
        { 
          pv8 = 1;
          p8 = false;
        } 
        else if(bit == 'h') //libre
        {
          pv8 = 0;
          p8 = true;
        } 
    
  } 

void asignar(int valor)
{
  for (int j = 0; j < 7; j++)
  {
    char bit = val7[valor][j]; // Obtiene el bit menos significativo de la cadena i
    
    if(bit == '1')
      digitalWrite(seg7[j], HIGH);
    else if(bit == '0')
      digitalWrite(seg7[j], LOW);
  }    
}

void handle_OnConnect() 
{
  server.send(200, "text/html", SendHTML(p1,p2,p3,p4,p5,p6,p7,p8));
}
void handle_NotFound()
{
  server.send(404, "text/plain", "Not found :(");
}
void handle_actualizar()
{
  server.send(200, "text/html", SendHTML(p1,p2,p3,p4,p5,p6,p7,p8));
}

/*==============================================================================================================*/



/*================================================PAGINA=====================================================*/
String SendHTML(bool pp1, bool pp2, bool pp3, bool pp4, bool pp5, bool pp6, bool pp7, bool pp8){
String ptr = "<!DOCTYPE html>\n";
ptr += "<html>\n";
ptr +="<head>\n";
ptr +="<meta name=viewport content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
ptr +="<link rel=stylesheet href=https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css integrity=sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk crossorigin=anonymous>\n";
ptr +="<title>LED Control</title>\n";
ptr +="<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center}body{margin-top:50px}h1{color:#444;margin:50px auto 30px}h3{color:#444;margin-bottom:50px}.button{display:block;width:160px;background-color:#3498db;border:0;color:white;padding:13px 30px;text-decoration:none;font-size:25px;margin:0 auto 35px;cursor:pointer;border-radius:4px}";
ptr +=".button-on{background-color:#3498db}.button-on:active{background-color:#2980b9}.button-off{background-color:#34495e}.button-off:active{background-color:#2c3e50}p{font-size:14px;color:#888;margin-bottom:10px}table tr:last-child td:first-child{border:2px solid orange;border-bottom-left-radius:10px}</style>\n";
ptr +="</head>\n";
ptr +="<body style=background-color:gray>\n";
ptr +="<center>\n";
ptr +="<h1 style=color:white>Parqueo Los Santos &#129725; </h1> </center>\n";
ptr +="<br>\n";
ptr +="<a class=\"button button-off\" href=actualizar>Actualizar</a>\n";
ptr +="<br>\n";
ptr +="<center>\n";
ptr +="<table class=table style=width:50%;border:1px;border-radius:10px>\n";
ptr +="<thead class=table-dark>\n";
ptr +="<tr>\n";
ptr +="<th scope=col># Parqueo</th>\n";
ptr +="<th scope=col>Estado</th>\n";
ptr +="</tr>\n";
ptr +="</thead>\n";
ptr +="<tbody>\n";

if(pp1 == true)
{
  ptr +="<tr class=table-success >\n";
  ptr +="<th scope=row>1</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>1</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp2 == true)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>2</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>2</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp3)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>3</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>3</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp4)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>4</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>4</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp5)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>5</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>5</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp6)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>6</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>6</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

if(pp7)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>7</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>7</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
};

if(pp8)
{
  ptr +="<tr class=table-success>\n";
  ptr +="<th scope=row>8</th>\n";
  ptr +="<td>Disponible &#9989;</td>\n";
  ptr +="</tr>\n";
}
else
{
  ptr +="<tr class=table-danger>\n";
  ptr +="<th scope=row>8</th>\n";
  ptr +="<td>Ocupado &#128683</td>\n";
  ptr +="</tr>\n";
}

ptr +="</tbody>\n";
ptr +="</table>\n";
ptr +="</center>\n";
ptr +="<script src=https://code.jquery.com/jquery-3.5.1.slim.min.js integrity=sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj crossorigin=anonymous></script>\n";
ptr +="<script src=https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js integrity=sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo crossorigin=anonymous></script>\n";
ptr +="<script src=https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js integrity=sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI crossorigin=anonymous></script>\n";
ptr +="</body>\n";
ptr +="</html>";
return ptr;
}
/*==============================================================================================================*/