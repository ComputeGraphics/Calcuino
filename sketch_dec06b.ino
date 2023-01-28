#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

byte dots[] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10101
};

int RECV_PIN = 11; // Pin des Infrarot Sensors
LiquidCrystal_I2C lcd(0x27,16,2);
byte screen = 0; // Position des Eingegebenen auf dem Display
//////////////////////////////////////////
long ergebnis = 0L; // Hier wird das Ergebnis der Rechnung gespeichert
long a = 0L; // Variable A für das einsetzen in Rechnungen
byte a_cache = 0;
byte a_pressed = 0; // Variable für doppel Druck von A zur speicherung von A
long v_ergebnis = 0L; // Cache für das Ergebnis der letzten Rechnung für B
byte q = 0L; //Ziffern Cache
long w = 0L; // Cache für Zwischenergebnisse
long e = 0L; // 2. Zahl der Rechnung
long t = 0L; // 1. Zahl der Rechnung
byte z = 0; // Rechenzeichen Cache
long o = 0L; // 2. Zahl Endergebnis für Seriellen Monitor, um Ergebnisse zu überprüfen
long p = 0L;// Für ... wen Zahl zu lange ist
long u = 0L;// Cache für ...
byte on_changed = 0;//Für ... wenn T zu lang ist
byte on_changed_e = 0;//Für ... wenn 2. Zahl zu lang ist
//////////////////////////////////////////
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()

{
  lcd.createChar(0, dots); //Erstelle das "..." Zeichen
Serial.begin(9600);
Serial.println("LADEN");
lcd.init(); // initialize the lcd
lcd.backlight(); //Aktiviert die Hintergrundbeleuchtung des I2C Screens

lcd.setCursor(1,0);
lcd.print("Taschenrechner");
lcd.setCursor(2,1);
//.print(" ÷");
lcd.write(byte(0));
delay(1500);

lcd.setCursor(1,0);
lcd.print("Taschenrechner");
lcd.setCursor(2,1);
lcd.print("Sam & Arthur");
delay(1500);
lcd.scrollDisplayLeft();
delay(200);
lcd.clear();
lcd.setCursor(0,0);//Platziert den Cursor für den "Rechner:" Schriftzug
lcd.print("Rechner:");

irrecv.enableIRIn();// Für die Remote

}
//////////////////////////////////////////////////////////////
void loop() {
  if (a_cache == 1 && t != 0) {
  w = w/10;
  a_cache = 0;
  on_changed = 0;
  Serial.println("ACTIVE");
  goto display_t;
  }


  
if (t == 0 && results.value == 16712445)// Wenn die erste Zahl nicht definiert ist soll E auf T übertragen werden
{
  delay(100);
  if (a_cache == 1) {
  e = e/10;
  a_cache = 0;
  on_changed = 0;
  }
  t = e;// Werte übertragen
  e = 0;// Reset für das neu Schreiben von E
  w = 0;
  q = 0;
  o = 0;
  lcd.print("Beendet");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rechner:");
  display_t:
  p = t;
  for(t != 0; p >= 100000;) { //Um "..." zu zeigen, wenn die Zahl nicht auf den Screen passt
    p = p/10;
    lcd.setCursor(11,0);
    lcd.print(p);
    lcd.setCursor(15,0);
    lcd.write(byte(0));
    on_changed = 1;
  }
  if(on_changed != 1){
  lcd.setCursor(11,0);
  lcd.print(p);
  }
}
if (irrecv.decode(&results)) {


//Serial.println(results.value, DEC);
if (results.value == 16738455)   //Wenn der Infrarotempfänger die Zahl 
//„16738455“ ausgelesen hat (Entsprechend der Taste“1“ der Fernbedienung)
{//Serial.println("1");
lcd.setCursor(screen,1);
lcd.print("1");
screen = screen+1;
q = 1;
if(a_pressed != 2) {a_pressed = 0;}
}  //Setzt A Pressed auf Null, damit der Rechner nicht in den Variablen Definieren Modus wechselt

if (results.value == 16750695)   //Wenn der Infrarotempfänger die Zahl 
//„16750695“ ausgelesen hat (Entsprechend der Taste“2“ der Fernbedienung), 
{//Serial.println("2");
lcd.setCursor(screen,1);
lcd.print("2");
screen = screen+1; // Setzt den Cursor eins weiter
q = 2;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16756815)   //Wenn der Infrarotempfänger die Zahl 
//„16756815“ ausgelesen hat (Entsprechend der Taste“3“ der Fernbedienung), 
{//Serial.println("3");
lcd.setCursor(screen,1);
lcd.print("3");
screen = screen+1;
q = 3; // Schreibt die Zahl in einen Cache für die Übertragung in "w"
if(a_pressed != 2) {a_pressed = 0;}}


if (results.value == 16724175)   //Wenn der Infrarotempfänger die Zahl 
//„16724175“ ausgelesen hat (Entsprechend der Taste“4“ der Fernbedienung)
{//Serial.println("4");
lcd.setCursor(screen,1);
lcd.print("4");
screen = screen+1;
q = 4;
if(a_pressed != 2) {a_pressed = 0;}}


if (results.value == 16718055)   //Wenn der Infrarotempfänger die Zahl 
//„16718055“ ausgelesen hat (Entsprechend der Taste“5“ der Fernbedienung), 
{//Serial.println("5");
lcd.setCursor(screen,1);
lcd.print("5");
screen = screen+1;
q = 5;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16743045)   //Wenn der Infrarotempfänger die Zahl 
//„16743045“ ausgelesen hat (Entsprechend der Taste“6“ der Fernbedienung), 
{//Serial.println("6");
lcd.setCursor(screen,1);
lcd.print("6");
screen = screen+1;
q = 6;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16716015)   //Wenn der Infrarotempfänger die Zahl 
//„16716015“ ausgelesen hat (Entsprechend der Taste“7“ der Fernbedienung), 
{//Serial.println("7");
lcd.setCursor(screen,1);
lcd.print("7");
screen = screen+1;
q = 7;
if(a_pressed != 2) {a_pressed = 0;}}  //soll die LED aus gehen.

if (results.value == 16726215)   //Wenn der Infrarotempfänger die Zahl 
//„16726215“ ausgelesen hat (Entsprechend der Taste“8“ der Fernbedienung), 
{//Serial.println("8");
lcd.setCursor(screen,1);
lcd.print("8");
screen = screen+1;
q = 8;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16734885)   //Wenn der Infrarotempfänger die Zahl 
//„16734885“ ausgelesen hat (Entsprechend der Taste“9“ der Fernbedienung), 
{//Serial.println("9");
lcd.setCursor(screen,1);
lcd.print("9");
screen = screen+1;
q = 9;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16769055)   //Wenn der Infrarotempfänger die Zahl 
//„16769055“ ausgelesen hat (Entsprechend der Taste“0“ der Fernbedienung), 
{//Serial.println("0");
lcd.setCursor(screen,1);
lcd.print("0");
screen = screen+1;
q = 0;
if(a_pressed != 2) {a_pressed = 0;}}

if (results.value == 16748655)   //Wenn der Infrarotempfänger die Funktion
//„16748655“ ausgelesen hat (Entsprechend der Taste“C“ der Fernbedienung) für "CLEAR" 
{//Serial.println("CLS");
lcd.clear();
lcd.print("CLEAR");
delay (500); //Für Lesbarkeit der Schrift
lcd.clear();
lcd.setCursor(0,0); //Stellt den alten Schriftzug wiederher
lcd.print("Rechner:");
screen = 0; //Löscht die Variablen
w = 0;
q = 0;
e = 0;
t = 0;
o = 0;
z = 0;
p = 0;
on_changed_e = 0;
on_changed = 0;
ergebnis = 0;
a_pressed = 0;}

if (w <= -1 || ergebnis <= -1 || e <= -1 || t <= -1 || o <= -1) { //Für den Reset von Variablen, sollte ein Fehler auftreten,
  //da bei einem Fehler immer eine Negative Zahl zurück gegeben wird, müssen wir negative Zahlen sperren
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR");
    lcd.setCursor(0,1);
  lcd.print("Reset"); //Weist den nutzer an die "CLS" Taste zu drücken
  screen = 0;
a = 0;
w = 0;
q = 0;
e = 0;
z = 0;
t = 0;
o = 0;
p = 0;
on_changed_e = 0;
on_changed = 0;
ergebnis = 0;
v_ergebnis = 0;
a_pressed = 0;
}
if (results.value == 16736925)   //Wenn der Infrarotempfänger die Zahl 
//„16718055“ ausgelesen hat (Entsprechend der Taste“hoch“ der Fernbedienung), 
{Serial.println("+");
lcd.setCursor(screen,1);
lcd.print("+");
z = 2; 
screen = screen+1;
q = q/10;//Löscht "q", um "w" und damit auch "e", "o" oder sogar "t" nicht zu verfälschen, da der x10
//Multiplikator nicht nur bei Zahlen ausgeführt wird
a_pressed = 0;} //Setzt Den Counter für den Double-Click zurück, da diese Taste im Variablendefinitionsmodus
//nicht benötigt wird

if (results.value == 16754775)   //Wenn der Infrarotempfänger die Zahl 
//„16718055“ ausgelesen hat (Entsprechend der Taste“runter“ der Fernbedienung), 
{Serial.println("-");
lcd.setCursor(screen,1);
lcd.print("-");
z = 3; //Setzt den Code des Rechenzeichens, um das benutzte Rechenzeichen zu speichern
screen = screen+1;
q = q/10;
a_pressed = 0;}

if (results.value == 16720605)   //Wenn der Infrarotempfänger die Zahl 
//„16720605“ ausgelesen hat (Entsprechend der Taste“links“ der Fernbedienung), 
{Serial.println("÷");
lcd.setCursor(screen,1);
lcd.print("/");
z = 1;
screen = screen+1; 
q = q/10;
a_pressed = 0;}

if (results.value == 16761405)   //Wenn der Infrarotempfänger die Zahl 
//„16761405“ ausgelesen hat (Entsprechend der Taste“rechts“ der Fernbedienung), 
{Serial.println("x");
lcd.setCursor(screen,1);
lcd.print("x");
z = 4;
screen = screen+1;
q = q/10;
a_pressed = 0;
}


if (results.value == 16769565) //Taste B (ANS)
{Serial.println("B");
lcd.print("B");
screen = 0;
q = 0;
e = 0;
w = v_ergebnis;
a_cache = 1;
lcd.clear();
lcd.setCursor(0,0);//Platziert den Cursor für den "Rechner:" Schriftzug
lcd.print("Rechner:");
lcd.setCursor(0,1);
lcd.print("B");
screen = 1;
a_pressed = 0;
} 

if (results.value == 16712445)   //Wenn der Infrarotempfänger die Zahl 
//„16712445“ ausgelesen hat (Entsprechend der Taste“rechts“ der Fernbedienung), 
{Serial.println("OK");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Verarbeite...");
q = q/10;
  if (a_pressed == 2) {
  Serial.print("W:");
  Serial.println(w);
  a = w;
  t = 0;
  e = 0;
  w = 0;
  Serial.print("T:");
  Serial.println(t);
  a_pressed = 0;
  } 
}
if (results.value == 16753245) //Taste A
{Serial.println("A");
lcd.print("A");
screen = 0;
q = 0;
e = 0;
w = a;
lcd.clear();
lcd.setCursor(0,0);//Platziert den Cursor für den "Rechner:" Schriftzug
lcd.print("Rechner:");
lcd.setCursor(0,1);
lcd.print("A");
screen = 1;
a_cache = 1;
a_pressed++;
} 
if ( a_pressed == 2 && results.value == 16753245)   //Wenn der Infrarotempfänger die Zahl 
//„16753245“ ausgelesen hat (Doppel A), 
{Serial.println("A");
screen = 0;
a = 0;
w = 0;
e = 0;
lcd.clear();
lcd.setCursor(0,0);//Platziert den Cursor für den "Definiere {n}:" Schriftzug
lcd.print("Definiere A:");
lcd.setCursor(0,1);
} 
w = w*10+q;
e = w/10;

delay (50);
irrecv.resume();

if (z == 1 && t != 0 && e != 0)
//Rechenbefehl /
{
ergebnis = t/e;
lcd.clear();
////////////////
lcd.setCursor(0,0);
lcd.print(t);
////////////////
lcd.setCursor(7,0);
lcd.print("/");
////////////////
o = w/10;
u = o;
  on_changed_e = 0;
  for(t != 0; u >= 1000000;) { //Um "..." zu zeigen, wenn die Zahl nicht auf den Screen passt
    u = u/10;
    lcd.setCursor(10,0);
    lcd.print(u);
    lcd.setCursor(15,0);
    lcd.write(byte(0));
    on_changed_e = 1;
  }
  if(on_changed_e != 1){
  lcd.setCursor(10,0);
  lcd.print(u);
  }
///////////////
lcd.setCursor(0,1);
lcd.print("=");
lcd.setCursor(5,1);
lcd.print(ergebnis);
v_ergebnis = ergebnis;
 
}
if (z == 1 && e == 0) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR");
    lcd.setCursor(0,1);
  lcd.print("Mathm. Fehler");
  screen = 0;
a = 0;
w = 0;
q = 0;
e = 0;
z = 0;
t = 0;
o = 0;
p = 0;
on_changed_e = 0;
on_changed = 0;
ergebnis = 0;
v_ergebnis = 0;
a_pressed = 0;
}
if (z == 1 && t == 0) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR");
    lcd.setCursor(0,1);
  lcd.print("Mathm. Fehler");
  screen = 0;
a = 0;
w = 0;
q = 0;
e = 0;
z = 0;
t = 0;
o = 0;
p = 0;
on_changed_e = 0;
on_changed = 0;
ergebnis = 0;
v_ergebnis = 0;
a_pressed = 0;
}



if (z == 2)
//Rechenbefehl + 
{
ergebnis = t+e;
lcd.clear();
////////////////
lcd.setCursor(0,0);
lcd.print(t);
////////////////
lcd.setCursor(7,0);
lcd.print("+");
////////////////
o = w/10;
u = o;
  on_changed_e = 0;
  for(t != 0; u >= 1000000;) { //Um "..." zu zeigen, wenn die Zahl nicht auf den Screen passt
    u = u/10;
    lcd.setCursor(10,0);
    lcd.print(u);
    lcd.setCursor(15,0);
    lcd.write(byte(0));
    on_changed_e = 1;
  }
  if(on_changed_e != 1){
  lcd.setCursor(10,0);
  lcd.print(u);
  }
///////////////
lcd.setCursor(0,1);
lcd.print("=");
lcd.setCursor(5,1);
lcd.print(ergebnis);
v_ergebnis = ergebnis;
 
}
if (z == 3)
//Rechenbefehl -
{
ergebnis = t-e;
lcd.clear();
////////////////
lcd.setCursor(0,0);
lcd.print(t);
////////////////
lcd.setCursor(7,0);
lcd.print("-");
////////////////
o = w/10;
u = o;
  on_changed_e = 0;
  for(t != 0; u >= 1000000;) { //Um "..." zu zeigen, wenn die Zahl nicht auf den Screen passt
    u = u/10;
    lcd.setCursor(10,0);
    lcd.print(u);
    lcd.setCursor(15,0);
    lcd.write(byte(0));
    on_changed_e = 1;
  }
  if(on_changed_e != 1){
  lcd.setCursor(10,0);
  lcd.print(u);
  }
///////////////
lcd.setCursor(0,1);
lcd.print("=");
lcd.setCursor(5,1);
lcd.print(ergebnis);
v_ergebnis = ergebnis;
 
}
if (z == 4)
//Rechenbefehl x
{
ergebnis = t*e;
lcd.clear();
////////////////
lcd.setCursor(0,0);
lcd.print(t);
////////////////
lcd.setCursor(7,0);
lcd.print("x");
////////////////
o = w/10;
u = o;
  on_changed_e = 0;
  for(t != 0; u >= 1000000;) { //Um "..." zu zeigen, wenn die Zahl nicht auf den Screen passt
    u = u/10;
    lcd.setCursor(10,0);
    lcd.print(u);
    lcd.setCursor(15,0);
    lcd.write(byte(0));
    on_changed_e = 1;
  }
  if(on_changed_e != 1){
  lcd.setCursor(10,0);
  lcd.print(u);
  }
///////////////
lcd.setCursor(0,1);
lcd.print("=");
lcd.setCursor(5,1);
lcd.print(ergebnis);
v_ergebnis = ergebnis;
}
if (o != e && z >= 1) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ERROR");
    lcd.setCursor(0,1);
  lcd.print("Tech. Fehler");
  screen = 0;
a = 0;
w = 0;
q = 0;
e = 0;
z = 0;
t = 0;
o = 0;
p = 0;
on_changed_e = 0;
on_changed = 0;
ergebnis = 0;
v_ergebnis = 0;
a_pressed = 0;
}

Serial.println("Pause");
Serial.println(t);
Serial.println(o);
Serial.println(ergebnis);
Serial.print("Cached:");
Serial.println(v_ergebnis);
Serial.print("A Pressed:");
Serial.println(a_pressed);
Serial.print("A:");
Serial.println(a);
delay(50);
}
}
