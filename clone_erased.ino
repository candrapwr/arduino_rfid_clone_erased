
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   5     // Tentukan PIN RST MFRC522 
#define SS_PIN    4    // Tentukan PIN SS MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);  


boolean readyErased = false;
boolean readyClone = false;
byte cardErased[] = {0x6C, 0xBE, 0xD0, 0x38}; //Tentukan UID master kartu untuk proses hapus block
byte cardClone[] = {0xE5, 0x1F, 0xCE, 0x52}; //Tentukan UID master kartu untuk cloning kartu contoh UID kartu [E5 1F CE 52]
byte card[4];
byte cardNew[4];
  
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();       
  mfrc522.PCD_Init(); 
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Key default FFFFFFFFFFFFh
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if(readyErased){
    go_erased(); 
  }else if(readyClone){
    go_write();
  }else{
    go_read();
  }
}

void go_read(){
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  for (byte i = 0; i < 4; i++) {
    card[i] = mfrc522.uid.uidByte[i];
  }

  if(memcmp(card, cardErased, 4) == 0){
    readyErased = true;
    Serial.print(F("Siap untuk menghapus block 0"));
    Serial.println();
    delay(2000);  
  } else if (memcmp(card, cardClone, 4) == 0){
    readyClone = true;
    Serial.print(F("Siap untuk cloning"));
    Serial.println();
    delay(2000);  
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
    for (byte i = 0; i < 4; i++) {
      cardNew[i] = mfrc522.uid.uidByte[i];
    }
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);    
  }
}

void go_write(){ 
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    return;
  }
   
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 
  Serial.println();
  if ( mfrc522.MIFARE_SetUid(cardNew, (byte)4, true) ) {
    Serial.println(F("Menulis ke kartu "));
  }else{
    for (int i = 0; i < 8; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    } 
  }
  mfrc522.PICC_HaltA();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  readyClone = false; 
}

// Fungsi ini di gunakan untuk mengapus kartu yang rusak karena kesalahan UID atau untuk menghapus block 0 dan akan di reset UID ke 1234
void go_erased(){
  if ( mfrc522.MIFARE_UnbrickUidSector(false) ) {
    Serial.println(F("Cleared sector 0, set UID to 1234"));
  }else{
    Serial.println(F("Failed to erased card"));
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  readyErased = false;
}
