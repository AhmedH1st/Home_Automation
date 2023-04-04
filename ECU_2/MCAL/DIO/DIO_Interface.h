
#ifndef DIO_INT_H_
#define DIO_INT_H_


/******************************************
  INCLUDES
*******************************************/
#include "DIO_cfg.h"
#include "STD_TYPES.h"
#include "DIO_types.h"
/******************************************
 *  Includes
 ******************************************/
/*  GLOBAL CONSTANT MACROS
*******************************************

/******************************************
  GLOBAL FUNCTIONS MACROS
*******************************************/


/******************************************
  GLOBAL DATA TYPES AND STRUCTURES
*******************************************/

/******************************************
  GLOBAL DATA PROTOTYPES
*******************************************/

/******************************************
   GLOBAL FUNCTIONS PROTOTYPES
*******************************************/

/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/

void M_DIO_void_setPinValue (Dio_Pin_Type Pin_ID,Dio_LevelType level);
/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/
Dio_LevelType M_DIO_getPinValue (Dio_Pin_Type pin_ID);
/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/
void M_DIO_TogglePin (Dio_Pin_Type pin_ID);
/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/
void M_Dio_void_setPortValue (Dio_PortType port,Dio_PortLevelType level);
/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/
Dio_PortLevelType M_Dio_void_getPort (Dio_PortType port);
/******************************************
  syntax :

  Description :

  Synch/Asynch     : Synchronouse
  Reentrance       : Reentrant
  parameters (in)  :
  parameters (out) :  Non
  Return Value     :
******************************************/

#endif /* DIO_INT_H_ */
