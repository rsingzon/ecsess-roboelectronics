/* 
 * @File:   adc.h
 * @Author: Dirk
 *
 * @date September 15, 2013, 11:27 AM
 */

#ifndef ADC_H
#define	ADC_H

/**
*@brief An initalization function for the ADC
*@param[in] channel The analog channel to use with the adc
*@retval None
*@note Adjustes the ANSEL and TRIS settings for the corresponding channel
*/
void adcInit(unsigned char channel);

/**
*@brief A function the reads the ADC value
*@retval The bit value of the adc
*@note This function uses a busy wait for conversion to complete
*/
unsigned int adcRead(void);

#endif	/* ADC_H */

