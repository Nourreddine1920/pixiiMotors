#include"main.h"




#define MAX_LED 36
#define USE_BRIGHTNESS 0
#define BlinkerLEDs 10

uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];

int BlinkerSpeed = 50; //Blinker Running LED Speed. Adjust this to match with your Bike blinker speed.


void Set_LED (int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

#define PI 3.14159265

void Set_Brightness (int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}

uint16_t pwmData[(24*MAX_LED)+50];



void Reset_LED (void)
{
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Data[i][0] = i;
		LED_Data[i][1] = 0;
		LED_Data[i][2] = 0;
		LED_Data[i][3] = 0;
	}
}





// functions
// brakeFull : all leds red with 100% Brightness : 36 leds

void BrakeFull()
{
  for (int i = 0; i < MAX_LED; i++)
  {
	  Set_LED (i, 255, 0 , 0);
  }
    WS2812_Send();
}

// BrakeMidlle : led 10 to led 36-10

void BrakeMiddle()
{
  for (int i = BlinkerLEDs; i < (MAX_LED - BlinkerLEDs); i++)
  {
    Set_LED(i,255,0,0);
  }
    WS2812_Send();
}

// ParkFull : all led are red with 25% Brightness

void ParkFull()
{
  for (int i = 0; i < MAX_LED; i++)
  {
	  Set_LED(i,60,0,0);
  }
      WS2812_Send();
}

// ParkMiddle : led 10 to 36 : red with 25%brightness

void ParkMiddle()
{
  for (int i = BlinkerLEDs; i < (MAX_LED - BlinkerLEDs); i++)
  {
	  Set_LED (i,60,0,0);
	   }
	       WS2812_Send();
	 }

// Left Functions

// Led for BlinkerLEDs-1 to 0 are Blinking with delay equal to BlinkerSpeed

void LeftBlinker()
{
  for (int i = (BlinkerLEDs-1); i >= 0; i--)
  {
	  Set_LED(i,255, 165, 0);
	  WS2812_Send();
	  HAL_Delay(BlinkerSpeed) ;

  }
}

//Led for 0 to BlinkerLEDs are reset to 0

void LeftDim()
{
  for (int i = 0; i < BlinkerLEDs; i++)
  {
	  Set_LED(i,0, 0, 0);
  }
  WS2812_Send();
}

// Led for 0 to (MAX_LED - BlinkerLEDs) are set to Red color with 30% Brightness

void LeftLit()
{
  for (int i = 0; i < (MAX_LED - BlinkerLEDs); i++)
  {
	  Set_LED(i,75, 0, 0);
  }
  WS2812_Send();
}

// Led for 0 to (MAX_LED - BlinkerLEDs) are set to Red color with full Brightness

void LeftFull()
{
  for (int i = 0; i < (MAX_LED - BlinkerLEDs); i++)
  {
	  Set_LED(i,255, 0, 0);
  }
  WS2812_Send();
}

// Right Functions

//Led for (MAX_LED - BlinkerLEDs) to MAX_LED are Blinking with delay equal to BlinkerSpeed

void RightBlinker()
{
  for (int i = (MAX_LED - BlinkerLEDs); i < MAX_LED; i++)
  {
	  Set_LED(i,255, 165, 0);
	  WS2812_Send();
      HAL_Delay(BlinkerSpeed);
  }
}

//Led for (MAX_LED - BlinkerLEDs) to MAX_LED are reset to 0

void RightDim()
{
   for (int i = (MAX_LED - BlinkerLEDs); i < MAX_LED; i++)
  {
	   Set_LED(i,0, 0, 0);
  }
   WS2812_Send();
}

// Led for BlinkerLEDs to MAX_LED are set to Red color with 30% Brightness

void RightLit()
{
  for (int i = BlinkerLEDs; i < MAX_LED; i++)
  {
	  Set_LED(i,75, 0, 0);
  }
  WS2812_Send();
}

// Led for BlinkerLEDs to MAX_LED are set to Red color with full Brightness

void RightFull()
{
  for (int i = BlinkerLEDs; i < MAX_LED; i++)
  {
	  Set_LED(i,255, 0, 0);
  }
  WS2812_Send();
}

// Dual blinking

void DualBlinker()
{
  for (int i = (BlinkerLEDs-1); i >= 0; i--)
  {
	  Set_LED(i,255, 165, 0);
	  Set_LED(MAX_LED-1-i,255, 165, 0);
	  WS2812_Send();
      HAL_Delay(BlinkerSpeed);
  }
}
