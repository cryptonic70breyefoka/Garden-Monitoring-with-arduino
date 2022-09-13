//www.elegoo.com
//2018.10.25


#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];
int measurement=0;
int beep=12; 


void setup( )
{
  Serial.begin( 9600);
  pinMode (12,OUTPUT);
}


static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis();
      return( true );
    }
  }

  return( false );
}


void loop( )
{
  float temperature;
  float humidity;
  int value = analogRead(adc_id); 
   measurement=analogRead(A1);

  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }
    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC %d level is %d\n",adc_id, value);
      measurement=analogRead(A1);
       Serial.print("Moisture measurement:");
        Serial.println(measurement);
      
      Serial.print(printBuffer);
      HistoryValue = value;
    }
    if (measurement > 500){
    digitalWrite(beep, HIGH);
    }
    else{
      digitalWrite(beep, LOW);
      }



}
