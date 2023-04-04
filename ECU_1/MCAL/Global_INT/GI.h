/*
 * GI.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Ahmed Hesham
 */

#ifndef GLOBAL_INT_GI_H_
#define GLOBAL_INT_GI_H_




void GI_Enable (void);
void GI_Disable (void);


#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)



#endif /* GLOBAL_INT_GI_H_ */
