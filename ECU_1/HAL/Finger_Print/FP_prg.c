#include "STD_TYPES.h"
#include "UART_interface.h"
#include "UART_services.h"
#include "FP_interface.h"
#include "FP_private.h"
#include "util/delay.h"
#include "LCD_interface.h"

u8 Recieving_Buffer [30];
u8 Recieve_Index;

const u8 Handshake [12]                  ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x03,0x40,0x00,0x44};
const u8 Collect_IMG_Ins[12]             ={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x01,0x00,0x05};
const u8 Generate_Char_File_Buffer1[13]  ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x01,0x00,0x08};
const u8 Generate_Char_File_Buffer2[13]   ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x04,0x02,0x02,0x00,0x09};
const u8 Generate_Template [12]            ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x03,0x05,0x00,0x09};
const u8 Search_Finger_Lib[17]             ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x0A,0x00,0x18};
const u8 Empty_Finger_Lib [12]           ={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x03,0x0D,0x00,0x11};


void FP_Init (void)
{
	FP_Error_t Response;

	M_void_UART_Init();
	_delay_ms(250);


	/*UART_SendArr(Handshake,12);
	_delay_ms(250);

	Response=Recieving_Buffer[9];

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Handshake done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("error in H.S");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		H_LCD_WriteBinary(Response);
		_delay_ms(4000);
		H_LCD_ClearDisplay();
	}*/


}



FP_Error_t FB_Operation (FP_OperationsID_t OperationID, FP_BufferID_t BufferID, FP_PageID_t PageID)
{
	FP_Error_t Response;
	//Arr for store template instruction as it has many variables
	u8 local_Store_Template_Arr [15]={0xEF,0x01,0xFF,0XFF,0xFF,0xFF,0x01,0x00,0x06,0x06,0x01};

	/*******Flushing**********/
	for (u8 i=0; i<30; i++)
	{
		Recieving_Buffer[i]=0;
	}
	Recieve_Index=0;
	/*************************/

	if (OperationID == STORE_TEMPLATE)
		{
			local_Store_Template_Arr[11]=0x00;
			local_Store_Template_Arr[12]=PageID;
			local_Store_Template_Arr[13]=0x00;
			local_Store_Template_Arr[14]=0x0E + local_Store_Template_Arr[12];
		}

	switch(OperationID)
	{
	case COLLECT_IMG:
		UART_SendArr(Collect_IMG_Ins,12);
		_delay_ms(250);
		Response=Recieving_Buffer[9];

		break;

	case GEN_CHAR_FILE:
		switch(BufferID)
			{
			case FP_BUFFER_1:
				UART_SendArr(Generate_Char_File_Buffer1,13);
				break;

			case FP_BUFFER_2:
				UART_SendArr(Generate_Char_File_Buffer2,13);
				break;
			}

		_delay_ms(250);
		Response=Recieving_Buffer[9];

		break;

	case GEN_TEMPLATE:
		UART_SendArr(Generate_Template,12);
		_delay_ms(250);

		Response=Recieving_Buffer[9];

		break;


	case STORE_TEMPLATE:
		UART_SendArr(local_Store_Template_Arr,15);
		_delay_ms(250);

		Response=Recieving_Buffer[9];

		break;


	case SEARCH_FINGER_LIB:
		UART_SendArr(Search_Finger_Lib,17);
		_delay_ms(250);
		Response=Recieving_Buffer[9];

		break;

	case EMPTY_FINGER_LIB:
		UART_SendArr(Empty_Finger_Lib,12);
		_delay_ms(250);
		Response=Recieving_Buffer[9];

		break;

	}

	return Response;
}




FP_Error_t FP_New_Scan (FP_PageID_t PageID)
{
	FP_Error_t Response=CMD_EXCUTION_COMPLETE;

	H_LCD_ClearDisplay();

	/****collect first image****/

	Response=FB_Operation(COLLECT_IMG,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Collecting Sample Done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("error in Collect Sample 1");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****Generate char file in buffer1****/

	Response=FB_Operation(GEN_CHAR_FILE,FP_BUFFER_1,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate ch.file1 done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Generate ch.file1");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****Collect for 2nd time****/

	Response=FB_Operation(COLLECT_IMG,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Collecting Sample Done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Collect Sample 2");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}


	/****Generate char file in buffer2****/

	Response=FB_Operation(GEN_CHAR_FILE,FP_BUFFER_2,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate ch.file2 done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err Generate ch.file2");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}


	/****Generate template that stored in both buffers****/


	Response=FB_Operation(GEN_TEMPLATE,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate 1st temp done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Generate 1st temp");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}


	/*****future extention --> collect again then generate char file in buffer 2
	 * the generate another template
	 * more accuracy achieved
	 *
	 * but for now let's gust store this template
	 */

	/****Collect for 3rd time****/

	Response=FB_Operation(COLLECT_IMG,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Collecting Sample Done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Collecting Sample");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****generate char file in buffer 2****/


	Response=FB_Operation(GEN_CHAR_FILE,FP_BUFFER_2,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate ch.file2 done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Generate ch.file2");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****Generate 2nd template that stored in both buffers****/


	Response=FB_Operation(GEN_TEMPLATE,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate template done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Generate template");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}


	/****Store the template produced****/

	Response=FB_Operation(STORE_TEMPLATE,FP_BUFFER_1,PageID);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Storage success");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err in Storage success");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	return Response;
}

void FP_Empty_Finger_Lib (void)
{
	FP_Error_t Response=100;
	Response=FB_Operation(EMPTY_FINGER_LIB, FP_BUFFER_NONE, FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Empty Done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("error in deleting");
		H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		H_LCD_WriteBinary(Response);
		_delay_ms(4000);
	}

}


FP_Error_t FP_Check (void)
{
	FP_Error_t Response=100;

	/****collect image****/

	Response=FB_Operation(COLLECT_IMG,FP_BUFFER_NONE,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Collecting Sample Done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err Collect Sample");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****Generate char file in buffer1****/

	Response=100;
	Response=FB_Operation(GEN_CHAR_FILE,FP_BUFFER_1,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		H_LCD_Writestr("Generate ch.file1 done");
		_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		H_LCD_Writestr("err Generate ch.file1");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	/****Search Finger Library****/
	Response=100;
	Response=FB_Operation(SEARCH_FINGER_LIB,FP_BUFFER_1,FP_PAGE_NONE);

	if (Response == CMD_EXCUTION_COMPLETE)
	{
		//H_LCD_Writestr("Found matching Finger");
		//_delay_ms(2000);
		H_LCD_ClearDisplay();
	}
	else
	{
		//H_LCD_Writestr("error in check 3");
		//H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
		//H_LCD_WriteBinary(Response);
		_delay_ms(2000);
		return Response;
	}

	return Response;

}

