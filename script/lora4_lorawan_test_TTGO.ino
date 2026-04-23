//by : Nyoman Yudi Kurniawan
//for : TRSE - Undiksha - 2025
//www.aisi555.com


#include <SPI.h>
#include <LoRa.h>
#include <LoRaWanPacket.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Gunakan pin ini untuk TTGO, sesuaikan jika berbeda
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

//Sesuaikan dev address dari device dan key ANTARES LoRawan

//aab66dbfca477674:1825d880382c9d9f

const char *devAddr = "796b7fdb";
const char *nwkSKey = "aab66dbfca4776740000000000000000";
const char *appSKey = "00000000000000001825d880382c9d9f";

uint16_t cobake =1; 


struct LoRa_config
{
  long Frequency;
  int SpreadingFactor;
  long SignalBandwidth;
  int CodingRate4;
  bool enableCrc;
  bool invertIQ;
  int SyncWord;
  int PreambleLength;
};

//jika ingin scanning ke semua frekuensi, guanakan ini ========
//hapus atau // jika menggunakan frekuensi statis

long LoRa_frek_INA_923_start = 921200000 ;
long LoRa_frek_INA_923_end   = 922600000 ;
long LoRa_frek_step = 200000;
long LoRa_frek_INA_923 = LoRa_frek_INA_923_start;
                                     
static LoRa_config txLoRa = {LoRa_frek_INA_923, 12, 125000, 5, true, false, 0x34, 8};

//==========================================================



void LoRa_setConfig(struct LoRa_config config)
{
  LoRa.setFrequency(config.Frequency);
  LoRa.setSpreadingFactor(config.SpreadingFactor);
  LoRa.setSignalBandwidth(config.SignalBandwidth);
  LoRa.setCodingRate4(config.CodingRate4);
  if (config.enableCrc)
    LoRa.enableCrc();
  else
    LoRa.disableCrc();
  if (config.invertIQ)
    LoRa.enableInvertIQ();
  else
    LoRa.disableInvertIQ();
  LoRa.setSyncWord(config.SyncWord);
  LoRa.setPreambleLength(config.PreambleLength);
}

void LoRa_TxMode()
{
  LoRa_setConfig(txLoRa);
  LoRa.idle();
}

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORAWAN UNDIKSHA");
  display.setCursor(0,10);
  display.println("- Test Kirim -");
  display.display();
  
  Serial.println("LoRaWan Antares Test");
  delay(1000);
  LoRaWanPacket.personalize(devAddr, nwkSKey, appSKey);

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(txLoRa.Frequency)) {
    Serial.println("LoRa Gagal. Cek perkabelan kamu...");
    while (true);
  }

  Serial.println("LoRa init berhasil.");
  Serial.println();
  display.setCursor(0,20);
  display.println("LoRa Initializing OK!");
  display.display();

}



void loop() {
  if (runEvery(5000)) {
    Serial.print ("Frekuensi : ");
    Serial.println (LoRa_frek_INA_923);
    LoRa_sendMessage();
    Serial.println ("....Kirim data!");
  }
}

void LoRa_sendMessage()
{
  LoRa_TxMode();
  
  LoRaWanPacket.clear();
  LoRaWanPacket.print("{\"Pengiriman Ke\":");
  LoRaWanPacket.print(cobake);
  LoRaWanPacket.print(",");
  LoRaWanPacket.print("\"Frek\":");
  LoRaWanPacket.print(LoRa_frek_INA_923);
  LoRaWanPacket.print("}");

  
  

  display.clearDisplay();
  display.setCursor(0,10);
  display.print("Kirim LoRaWan Ke : ");
  display.print(cobake);
  display.setCursor(0,20);
  display.print("Frek : ");
  display.print(LoRa_frek_INA_923);
  display.display(); 

  Serial.print ("Percobaan ke : "); 
  Serial.print (cobake); 
  Serial.print ("  Frekuensi : "); 
  Serial.println (LoRa_frek_INA_923); 
  
  cobake++;
  
  if (LoRaWanPacket.encode()) 
  {
    LoRa.beginPacket();
    LoRa.write(LoRaWanPacket.buffer(), LoRaWanPacket.length());
    LoRa.endPacket();
  }

  //hapus atau // jika menggunakan frekuensi statis atau tetap 
  //ini untuk menggeser frekuensi ke ch lorawan lainnya  
  if( LoRa_frek_INA_923 >= LoRa_frek_INA_923_end ) LoRa_frek_INA_923 = LoRa_frek_INA_923_start;
  else LoRa_frek_INA_923 += LoRa_frek_step;

}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
