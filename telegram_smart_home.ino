#include <Arduino.h>//бібліотета для роботи з бібліотекою Ардуїно
#include <ESP8266WiFi.h>//бібліотека для роботи протокол WIFI
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>//бібліотека для роботи з Telegram
#include <DallasTemperature.h>//бібліотека для роботи з DS18B20
#include <Wire.h>//бібліотека для роботи з інтерфейсом 1wire

#define WIFI_SSID "Назва WIFI мережі"
#define WIFI_PASSWORD "Пароль до WIFI мережі"

#define critical_temp 25  //критична норма температури

//макроси для зміни номеру виходу esp8266
//в разі зміни плати управління
#define RELAY1 16   //D0- 1реле
#define RELAY2 5    //D1- 2 реле
#define RELAY3 4    //D2- 3 реле
#define RELAY4 14   //D5- 4 реле
#define RELAY5 2    //D6- 5 реле
#define RELAY6 14   //D7-6 реле
#define RELAY7 5    //RX- 7 реле
#define RELAY8 5    //TX- 8 реле
#define LedWIFI 15  //D8 - LED_WIFI

//макроси для легкої зміни високого на низький стан
//виходу ESP8266 в разі зміни модуля реле
#define HIGH 1
#define LOW 0

#define ONE_WIRE_BUS 9  //SSD2 - DS18B20

bool ventilator = 0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const unsigned long BOT_MTBS = 100;  // частота перевірки команд
unsigned long bot_lasttime;          // last time messages' scan has been done
String chat_id = "382645765";        // чат айді

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/Relay1ON")  //повідомлення відповідає передбаченій команді
    {
      digitalWrite(RELAY1, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 1 ON", "");
    }
    if (text == "/Relay1OFF") {
      digitalWrite(RELAY1, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 1 OFF", "");
    }

    if (text == "/Relay2ON") {
      digitalWrite(RELAY2, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 2 ON", "");
    }
    if (text == "/Relay2OFF") {
      digitalWrite(RELAY2, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 2 OFF", "");
    }

    if (text == "/Relay3ON") {
      digitalWrite(RELAY3, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 3 ON", "");
    }
    if (text == "/Relay3OFF") {
      digitalWrite(RELAY3, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 3 OFF", "");
    }

    if (text == "/Relay4ON") {
      digitalWrite(RELAY4, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 4 ON", "");
    }
    if (text == "/Relay4OFF") {
      digitalWrite(RELAY4, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 4 OFF", "");
    }

    if (text == "/Relay5ON") {
      digitalWrite(RELAY5, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 5 ON", "");
    }
    if (text == "/Relay5OFF") {
      digitalWrite(RELAY5, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 5 OFF", "");
    }

    if (text == "/Relay6ON") {
      digitalWrite(RELAY6, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 6 ON", "");
    }
    if (text == "/Relay6OFF") {
      digitalWrite(RELAY6, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 6 OFF", "");
    }

    if (text == "/Relay7ON") {
      digitalWrite(RELAY6, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 7 ON", "");
    }

    if (text == "/Relay7OFF") {
      digitalWrite(RELAY6, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 7 OFF", "");
    }

    if (text == "/Relay8ON") {
      digitalWrite(RELAY6, LOW);  //включити чайник
      bot.sendMessage(chat_id, "RELAY 8 ON", "");
    }

    if (text == "/Relay8OFF") {
      digitalWrite(RELAY6, HIGH);  //виключити чайник
      bot.sendMessage(chat_id, "RELAY 8 OFF", "");
    }

    if (text == "/temp") {
      sensors.requestTemperatures();                                     //запитуєм дані з датчика
      float temp = sensors.getTempCByIndex(0);                           //записуєм дані з дачтика в зміну
      String message = "Current temperature: " + String(temp) + "°C\n";  // виводимо дані температури в чат
      bot.sendMessage(chat_id, message, "");                             //
    }

    if (text == "/help") {
      String welcome = "Welcome to ESP8266 WiFi Telegram Test!\n";
      welcome += "Enter the following commands to configure:\n\n";
      welcome += "/Relay1ON:   Включити  1 реле\n";
      welcome += "/Relay1OFF:  Виключити 1 реле\n\n";

      welcome += "/Relay2ON :  Включити  2 реле\n  ";
      welcome += "/Relay2OFF:  Виключити 2 реле\n\n ";

      welcome += "/Relay3ON :  Включити  3 реле\n   ";
      welcome += "/Relay3OFF:  Виключити 3 реле\n\n  ";

      welcome += "/Relay4ON :  Включити  4 реле\n  ";
      welcome += "/Relay4OFF:  Виключити 4 реле \n\n ";

      welcome += "/Relay5ON :  Включити  5 реле\n ";
      welcome += "/Relay5OFF:  Виключити 5 реле\n\n ";

      welcome += "/Relay6ON :  Включити  6 реле\n ";
      welcome += "/Relay6OFF:  Виключити 6 реле\n\n";

      welcome += "/Relay7ON :  Включити  7 реле \n";
      welcome += "/Relay7OFF:  Виключити 7 реле \n\n ";

      welcome += "/Relay8ON :  Включити  8 реле \n ";
      welcome += "/Relay8OFF:  Виключити 8 реле\n\n";

      welcome += "/temp : Получити температуру data\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    } else {
      bot.sendMessage(chat_id, "Невірна команда.Наберіть /help, щоб получити перелік доступних команд");
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  //всі виходи для управління модулем реле на вихід
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);

  //всі виходи які відповідають за реле високий стан
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);
  digitalWrite(RELAY5, HIGH);
  digitalWrite(RELAY6, HIGH);
  digitalWrite(RELAY7, HIGH);
  digitalWrite(RELAY8, HIGH);

  // Спробувати підключитися до мережі Wi-Fi:
  configTime(0, 0, "pool.ntp.org");       // Отримати UTC-час через NTP
  secured_client.setTrustAnchors(&cert);  // Додати кореневий сертифікат для api.telegram.org

  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);  //повідомлення назви мережі до якої підключена ESP8266
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)  //перевірка статусу підключення
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(chat_id, "Wifi Home online!", "");
  digitalWrite(LedWIFI, HIGH);//засвічення світлодіода який відповідає за підключення до WIFI
  sensors.begin();  //старт роботи датчика
}

void loop() {
  sensors.requestTemperatures();            //запитуєм дані з датчика
  float temp = sensors.getTempCByIndex(0);  //записуєм дані з дачтика в зміну

  if (temp >= critical_temp)  // якщо значення температури перевищує критичне- включити вентилятор
  {
    bot.sendMessage(chat_id, "Перевищення допустимої норми температури!", "");
    if (ventilator == 1)  //перевірка стану дозволу включення вентилятора
    {
      digitalWrite(RELAY2, LOW);  //включити вентилятор
      bot.sendMessage(chat_id, "Включився вентилятор!!", "");
      ventilator == 1;
    }
  }
  if (ventilator == 0) {
    digitalWrite(RELAY2, HIGH);  //виключити вентилятор
    bot.sendMessage(chat_id, "Включився вентилятор", "");
  }

  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}

