/*
 * FP_types.h
 *
 *  Created on: Mar 12, 2023
 *      Author: Ahmed Hesham
 */

#ifndef FINGER_PRINT_FP_TYPES_H_
#define FINGER_PRINT_FP_TYPES_H_

typedef enum{
	CMD_EXCUTION_COMPLETE=0x00,                       //
	ERR_REC_DATA,                                     //
	NO_FINGER_ON_SENSOR,                              //
	FAIL_ENROLL_FINGER,                               //
	FAIL_GEN_CH_FILE_OVER_DISORDER_FP_IMG,            //
	FAIL_GEN_CH_FILE_SMALL_FP_IMG,                    //
	FINGER_NOT_MATCH,                                 //
	FAIL_FIND_MATCHING_FINGER,                        //
	FAIL_COMPINE_CHAR_FILES=0x0A,                     //
	ADDRESSING_PAGEID_BEYOND_FINGER_LIB,
	ERR_READ_TEMPELATE_FROM_LIB_OR_TEMP_INVALID,      //
	ERR_UPLOAD_TEMPLATE,
	MODULE_CANT_RECIEVE_DATA_PACKAGE,                 //
	ERR_UPLOADING_IMG,
	FAIL_DELETE_TEMPLATE,
	FAIL_CLEAR_FINGER_LIB,                            //
	WRONG_PASS,
	FAIL_GEN_IMAGE_LAKE_VALID_PRIM_IMG,               //
	ERR_WRITE_FLASH,
	NO_DEF_ERR,
	INVALID_REG_NUM,
	INVALID_CFG_OF_REG,
	WRONGNOTEPAD_PAGE_NUM,
	FAIL_COMM_PROTOCOL

}FP_Error_t;


#define CharBuffer1  0x01
#define CharBuffer2  0x02



typedef enum{
	COLLECT_IMG,
	GEN_CHAR_FILE,
	GEN_TEMPLATE,
	STORE_TEMPLATE,
	SEARCH_FINGER_LIB,
	EMPTY_FINGER_LIB

}FP_OperationsID_t;


typedef enum{
	FP_BUFFER_NONE,
	FP_BUFFER_1,
	FP_BUFFER_2

}FP_BufferID_t;

typedef enum{
	FP_PAGE_NONE=0,
	FP_Page_1=0,
	FP_Page_2,
	FP_Page_3,
	FP_Page_4,
	FP_Page_5,
	FP_Page_6,
	FP_Page_7


}FP_PageID_t;


#endif /* FINGER_PRINT_FP_TYPES_H_ */
