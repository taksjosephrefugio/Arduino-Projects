// NEOPIXEL DEFINES
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NEOPIXEL_PIN 6
#define NUMPIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

typedef struct rgb_val {
  int red_val, green_val, blue_val;
} rgb_val;

#define NUMCOLORS 4
rgb_val MY_COLORS[NUMCOLORS] = {
  {0,0,0},        // OFF
  {255, 0, 0},    // RED
  {0, 255, 0},    // GREEN
  {0, 0, 255},    // BLUE
};


// TEMP SENSOR DEFINES
#include "DHT.h"
#define DHTPIN 8     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);


//********** MY DEFINES HERE ************** //
#define AVG_SAMPLES 10 
#define BASELINE_LMT 1000
#define BASELINE_DELAY 1000
#define DIFF_THRESHOLD 5
float baseline_temp = 0;
int baseline_ctr = 0;
bool event_flag = false;


void setup() {
  Serial.begin(9600);
  dht.begin();
  strip.begin();
  baseline_temp = _GET_BASELINE_TEMP();
}


void loop() {
  // Delay between measurements in milliseconds
  delay(50);

  // Read temperature as Fahrenheit (isFahrenheit = true)
  float temp_now = dht.readTemperature(true);
  float diff = temp_now - baseline_temp;
  if (diff < 0.0) {
    diff = -diff;
  }

  // Determine if temp_now is over the Temperature Threshold, then update event_flag
  event_flag = _UPDATE_EVENT_FLAG(diff, DIFF_THRESHOLD);
  _print_temp_now_and_diff(temp_now, diff);

  if (event_flag == true) { 
    loadingEffect(0, MY_COLORS[3]);
  }
  else { loadingEffect(0, MY_COLORS[0]); }

  // Increment baseline counter
  baseline_ctr++;
  if (baseline_ctr == BASELINE_LMT && event_flag == false) {
    baseline_temp = _GET_BASELINE_TEMP();
  }
}


float _GET_BASELINE_TEMP() {
  float total = 0;
  Serial.println("Getting Baseline Temp...");
  for (int i = 0; i < AVG_SAMPLES; i++) {
    total += dht.readTemperature(true);
    delay(BASELINE_DELAY);
  }
  Serial.print("...Done... Baseline Temp = ");
  Serial.println(total / AVG_SAMPLES);
  return total / AVG_SAMPLES;
}


void _print_temp_now_and_diff(int temp_now, int diff) {
    Serial.print("TempNow: ");
    Serial.print(temp_now);
    Serial.print("\t");
    Serial.print("Diff: ");
    Serial.println(diff);
}


bool _UPDATE_EVENT_FLAG(int diff, int diff_threshold) {
  bool local_event_flag = false;
  // Determine if temp_now is over the Temperature Threshold, then update event_flag
  if (diff > diff_threshold) {
    Serial.print("It's getting cooler!\t");
    local_event_flag = true;
  }
  else {
    Serial.print("Boring.\t");
    local_event_flag = false;
  }
  return local_event_flag;
}


void loadingEffect(int delayval, rgb_val setColor){
    for(int i=0;i<NUMPIXELS;i++){

    // strip.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(
      setColor.red_val, 
      setColor.green_val,
      setColor.blue_val)
    );
    
    // This sends the updated pixel color to the hardware.
    strip.show(); 
    delay(delayval);
  }
}