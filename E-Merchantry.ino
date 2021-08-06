
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>
#include <Firebase.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <string.h>
#include <Keypad.h>

 
#define FIREBASE_HOST "esp8266project-85998-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "bGvvWfOr7S6WA6uwhOg0WDnsns1j9Ylwz0QTDHZz"            
#define WIFI_SSID "Galaxym31s"                                  
#define WIFI_PASSWORD "1234567890"            

const byte n_rows = 4;
const byte n_cols = 4;
 
char keys[n_rows][n_cols] = {
 {'D','C','B','A'},
 {'#','9','6','3'},
 {'0','8','5','2'},
 {'*','7','4','1'}
};
 
byte colPins[n_rows] = {D3, D2, D1, D0};
byte rowPins[n_cols] = {D7, D6, D5, D4};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols);

void setup() 
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  } 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
  Serial.println("Enter product name");  
}

String item,user,price,type;
int i=0,f=0;

void loop(){ 
   if(f==0){
      
      char myKey = myKeypad.getKey();
       if (myKey != NULL){
        switch(myKey){
          case '1':
                  item="beans";
                 Serial.print("Beans");
//                 Serial.println(myKey);
                 break;
           case '2':
           item="raddish";
                 Serial.print("Raddish ");
//                 Serial.println(myKey);
                 break;
            case '3':
            item="greens";
                 Serial.print("Greens ");
//                 Serial.println(myKey);
                 break;
            case '4':
            item="beetroot";
                 Serial.print("Beetroot ");
//                 Serial.println(myKey);
                 break;
             case '5':
             item="brinjal";
                 Serial.print("Brinjal ");
//                 Serial.println(myKey);
                 break;
             case '6':
             item="carrot";
                 Serial.print("Carrot ");
//                 Serial.println(myKey);
                 break;
              case '7': 
              item="potato";
                 Serial.print("Potato ");
//                 Serial.println(myKey);
                 break;
              case '8':
              item="drumstick";
                 Serial.print("Drumstick ");
//                 Serial.println(myKey);
                 break;
              case '9':
              item="tomato";
                 Serial.print("Tomato ");
//                 Serial.println(myKey);
                 break;
              default:
                 myKey=NULL;
        }           
        i++;    
//        Serial.print("i value ");
//        Serial.println(i);
        Serial.println();
        String item1="10";
     
      user = Firebase.pushInt("user", i);
       String s1 = String(user+"/Product_name");    
          Firebase.setString(s1,item);
          Serial.println("Quantity");
          
        if (Firebase.failed()) {
          Serial.print("pushing /logs failed:");
          Serial.println(Firebase.error()); 
        }
        f=1;
       }
    }
if(f==1){
  
  char myQuantity = myKeypad.getKey();
   if (myQuantity != NULL){
    switch(myQuantity){
      case '1':
             item="5";
             Serial.print("5 kg ");
//             Serial.println(myQuantity);
             break;
       case '2':
       item="10";
             Serial.print("10 kg ");
//             Serial.println(myQuantity);
             break;
        case '3':
        item="15";
             Serial.print("15 kg ");
//             Serial.println(myQuantity);
             break;
        case '4':
        item="20";
             Serial.print("20 kg ");
//             Serial.println(myQuantity);
             break;
         case '5':
         item="25";
             Serial.print("25 kg ");
//             Serial.println(myQuantity);
             break;
         case '6':
         item="50";
             Serial.print("50 kg ");
//             Serial.println(myQuantity);
             break;
          case '7': 
          item="100";
             Serial.print("100 kg ");
//             Serial.println(myQuantity);
             break;
          case '8':
          item="250";
             Serial.print("250 kg ");
//             Serial.println(myQuantity);
             break;
          case '9':
          item="500";
             Serial.print("500 kg ");
//             Serial.println(myQuantity);
             break;
          default:
             myQuantity=NULL;
    }           

        
   String s2 = String(user+"/Quantity");
      Firebase.setString(s2,item);
      
    if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
     
    }
    Serial.println();
    Serial.println("Enter Excess or Demand: A->Excess B->Demand");
    f=2;
   }
}

if(f==2){
        char myType = myKeypad.getKey();
        if (myType != NULL){
  
            switch(myType){
                case 'A':
                    type="Excess";
//                    Serial.print("Excess ");
                    f=3;
                      Serial.println(type);
//                    Serial.println(myType);
                    Serial.println("Enter price Range: ");
                    break;
                case 'B':
                    type="Demand";
                    Serial.println(type);
//                    Serial.print("Demand ");
                    f=4;
//                    Serial.println(myType);
                    break;
                default:
                    myType=NULL;
            }
          String s3 = String(user+"/Type");
          Firebase.setString(s3,type);
//            Serial.println();
            if (Firebase.failed()) {
                Serial.print("pushing /logs failed:");
                Serial.println(Firebase.error()); 
            }
        }
    }
    
    if(f==3){
        char myPrice = myKeypad.getKey();
        if (myPrice != NULL){

            switch(myPrice){
                case '1':
                    price="1-10";
                    Serial.print("1-10 per kg ");
//                    Serial.println(myPrice);
                    break;
                case '2':
                    price="10-25";
                    Serial.print("10-25 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '3':
                    price="25-50";
                    Serial.print("25-50 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '4':
                    price="50-75";
                    Serial.print("50-75 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '5':
                    price="75-100";
                    Serial.print("75-100 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '6':
                    price="100-120";
                    Serial.print("100-120 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '7': 
                    price="120-150";
                    Serial.print("120-150 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '8':
                    price="150-250";
                    Serial.print("150-250 per Quantity");
//                    Serial.println(myPrice);
                    break;
                case '9':
                    price="250-500";
                    Serial.print("250-500 per Quantity");
//                    Serial.println(myPrice);
                    break;
                default:
                    price="";
            }
            String s4 = String(user+"/Price");
            Firebase.setString(s4,price);
              Serial.println();
            if (Firebase.failed()) {
            Serial.print("pushing /logs failed:");
            Serial.println(Firebase.error()); 
            }
//        Serial.println(price);
            Serial.println("Enter Phone Number");  // request for input
            f=5;
        }
    }
  if(f==4){
        price="nil";
          String s4 = String(user+"/Price");
          Firebase.setString(s4,price);
        if (Firebase.failed()) {
            Serial.print("pushing /logs failed:");
            Serial.println(Firebase.error()); 
        }
        Serial.println(price);
        Serial.println("Enter Phone Number");  // request for input
        f=5;
}

char myNum[10];
String n;
int c=1;
if(f==5){
  
  for (int i = 0; i < 10; i++){
    while((myNum[i] = myKeypad.getKey())==NULL) {
      c=i;
      delay(1); // Just wait for a key
    } 
    // Wait for the key to be released
    while(myKeypad.getKey() != NULL) {
      delay(1);
    } 

  }
  
//  Serial.print("Entered number is = ");
  Serial.print(myNum[0]);
  Serial.print(myNum[1]);
  Serial.print(myNum[2]);
  Serial.print(myNum[3]);
  Serial.print(myNum[4]);
  Serial.print(myNum[5]);
  Serial.print(myNum[6]);
  Serial.print(myNum[7]);
  Serial.print(myNum[8]);
  Serial.println(myNum[9]);
  
  String phone = String((String)myNum[0]+(String)myNum[1]+(String)myNum[2]+(String)myNum[3]);
  phone = String(phone+(String)myNum[4]+(String)myNum[5]+(String)myNum[6]+(String)myNum[7]);
  phone = String(phone+(String)myNum[8]+(String)myNum[9]);
  
//  Serial.println("Your phone number is "+ phone);
  delay(500);
     
    
    String s4 = String(user+"/Phone_Number");
      Firebase.setString(s4,phone);
      
      
    if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
  }
 
  f=0;
}
}
