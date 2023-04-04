#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LED_private.h"
#include "LED_cfg.h"
#include "LED_interface.h"








void H_LED_void_turnON (u8 LedID)
{
	switch (LedID)
	{
	case LED_RED:
	#if   (LED_RED_DIR    ==    LED_FORWARD_DIR)
		M_DIO_void_setPinValue(LED_RED_PIN, DIO_HIGH);
	#elif (LED_RED_DIR    ==   LED_LED_REVERSE_DIR)
		M_DIO_void_setPinValue(LED_RED_PIN, DIO_LOW);
	#else
	#error ("WRONG LED DIRECTION")

	#endif
		break;
	case LED_BLUE:
	#if   (LED_BLUE_DIR    ==    LED_FORWARD_DIR)
		M_DIO_void_setPinValue(LED_BLUE_PIN, DIO_HIGH);
	#elif (LED_BLUE_DIR    ==   LED_LED_REVERSE_DIR)
		M_DIO_void_setPinValue(LED_RED_PIN, DIO_LOW);
	#else
	#error ("WRONG LED DIRECTION")

	#endif
		break;

	case LED_GREEN:
	#if   (LED_GREEN_DIR    ==    LED_FORWARD_DIR)
		M_DIO_void_setPinValue(LED_GREEN_PIN, DIO_HIGH);
	#elif (LED_GREEN_DIR    ==   LED_LED_REVERSE_DIR)
		M_DIO_void_setPinValue(LED_GREEN_PIN, DIO_LOW);
	#else
	#error ("WRONG LED DIRECTION")
	#endif
		break;
	case LED_YELLOW:
#if   (LED_YELLOW_DIR    ==    LED_FORWARD_DIR)
		M_DIO_void_setPinValue(LED_YELLOW_PIN, DIO_HIGH);
	#elif (LED_YELLOW_DIR    ==   LED_LED_REVERSE_DIR)
		M_DIO_void_setPinValue(LED_YELLOW_PIN, DIO_LOW);
	#else
	#error ("WRONG LED DIRECTION")
	#endif
		break;

	}
}



void H_LED_TurnOff (u8 LedID)
{

	switch (LedID)
		{
		case LED_RED:
		#if   (LED_RED_DIR    ==    LED_FORWARD_DIR)
			M_DIO_void_setPinValue(LED_RED_PIN, DIO_LOW);
		#elif (LED_RED_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_void_setPinValue(LED_RED_PIN, DIO_LOW);
		#else
		#error ("WRONG LED DIRECTION")

		#endif
			break;
		case LED_BLUE:
		#if   (LED_BLUE_DIR    ==    LED_FORWARD_DIR)
			M_DIO_void_setPinValue(LED_BLUE_PIN, DIO_LOW);
		#elif (LED_BLUE_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_void_setPinValue(LED_RED_PIN, DIO_LOW);
		#else
		#error ("WRONG LED DIRECTION")

		#endif
			break;

		case LED_GREEN:
		#if   (LED_GREEN_DIR    ==    LED_FORWARD_DIR)
			M_DIO_void_setPinValue(LED_GREEN_PIN, DIO_LOW);
		#elif (LED_GREEN_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_void_setPinValue(LED_GREEN_PIN, DIO_LOW);
		#else
		#error ("WRONG LED DIRECTION")
		#endif
			break;
		case LED_YELLOW:
	#if   (LED_YELLOW_DIR    ==    LED_FORWARD_DIR)
			M_DIO_void_setPinValue(LED_YELLOW_PIN, DIO_LOW);
		#elif (LED_YELLOW_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_void_setPinValue(LED_YELLOW_PIN, DIO_LOW);
		#else
		#error ("WRONG LED DIRECTION")
		#endif
			break;

		}

}
void H_LED_Toggle (u8 LedID)
{

	switch (LedID)
		{
		case LED_RED:
		#if   (LED_RED_DIR    ==    LED_FORWARD_DIR)
			M_DIO_TogglePin(LED_RED_PIN);
		#elif (LED_RED_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_TogglePin(LED_RED_PIN);
		#else
		#error ("WRONG LED DIRECTION")

		#endif
			break;
		case LED_BLUE:
		#if   (LED_BLUE_DIR    ==    LED_FORWARD_DIR)
			M_DIO_TogglePin(LED_BLUE_PIN);
		#elif (LED_BLUE_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_TogglePin(LED_BLUE_PIN);
		#else
		#error ("WRONG LED DIRECTION")

		#endif
			break;

		case LED_GREEN:
		#if   (LED_GREEN_DIR    ==    LED_FORWARD_DIR)
			M_DIO_TogglePin(LED_GREEN_PIN);
		#elif (LED_GREEN_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_TogglePin(LED_GREEN_PIN);
		#error ("WRONG LED DIRECTION")
		#endif
			break;
		case LED_YELLOW:
	#if   (LED_YELLOW_DIR    ==    LED_FORWARD_DIR)
			M_DIO_TogglePin(LED_YELLOW_PIN);
		#elif (LED_YELLOW_DIR    ==   LED_LED_REVERSE_DIR)
			M_DIO_TogglePin(LED_YELLOW_PIN);
		#else
		#error ("WRONG LED DIRECTION")
		#endif
			break;

		}
}


