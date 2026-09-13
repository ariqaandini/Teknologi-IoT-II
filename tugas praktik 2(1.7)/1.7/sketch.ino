// Definisi Pin sesuai rangkaian Wokwi
const int buttonPin = 4;   // Pin input push button (GPIO 4)
const int ledPin = 5;      // Pin output LED (GPIO 5)

// Variabel untuk melacak status sistem (latching)
bool ledState = LOW;       // Status terakhir LED (nyala/mati)
bool lastButtonState = LOW;// Status pembacaan tombol sebelumnya
bool currentButtonState = LOW;

// Variabel untuk debouncing (mengatasi pantulan mekanis tombol)
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // Jeda waktu debounce dalam milidetik

void setup() {
  Serial.begin(115200);
  
  // Konfigurasi mode pin
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // Pastikan sistem mulai dengan kondisi LED mati
  digitalWrite(ledPin, LOW);
  Serial.println("Sistem Siap - Mode Latching Toggle Aktif");
}

void loop() {
  // Membaca status tombol saat ini
  int reading = digitalRead(buttonPin);

  // Jika status tombol berubah (karena ditekan atau dilepas), reset timer debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Jika selisih waktu sudah melebihi debounceDelay, anggap status tombol benar-benar stabil
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    // Jika ada perubahan status tombol yang stabil
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // Logika Latching: Eksekusi HANYA KETIKA tombol baru saja DITEKAN (HIGH)
      if (currentButtonState == HIGH) {
        ledState = !ledState; // Membalik status LED (jika mati jadi nyala, jika nyala jadi mati)
        digitalWrite(ledPin, ledState);

        // Cetak status ke Serial Monitor
        if (ledState == HIGH) {
          Serial.println("Tombol ditekan 1x -> LED MENYALA dan tetap menyala");
        } else {
          Serial.println("Tombol ditekan 1x lagi -> LED MATI dan tetap mati");
        }
      }
    }
  }

  // Simpan status pembacaan untuk perbandingan di loop berikutnya
  lastButtonState = reading;
}