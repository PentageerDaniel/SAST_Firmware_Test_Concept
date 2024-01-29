/* ************************************************************************** */
/** Descriptive File Name

  @Company
 Pentageer

  @File Name
    MUX1_ADG732.h

  @Summary
 

  @Description
    Describe the purpose of this file.
*/
/* ************************************************************************** */

/*************************************************************************
 * Include
 ************************************************************************/
#include "Init.h"

/*******************************************************************************
 * Internal Function declaration 
 ******************************************************************************/
void MUX1_ADG732_INIT(void); 
void MUX1_ADG732_CHIP_SELECT(uint8_t port);
void MUX1_ADG732_CHIP_DESELECT(uint8_t port);