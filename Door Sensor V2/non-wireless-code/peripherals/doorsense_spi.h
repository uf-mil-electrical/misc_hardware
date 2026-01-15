#ifndef DOORSENSE_SPI_H
#define DOORSENSE_SPI_H

/******************<Summary>*****************
 * Name: doorsense_spi.h
 * Purpose:
 *      > Functions for SPI communication
 * Written / updated by:
 *      > Russell
******************</Summary>*****************/


/******************<Dependencies>*****************/
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

#include "hardware/spi.h"

#include "setup.h"
/******************</Dependencies>*****************/


/******************<Defines>*****************/
/******************</Defines>*****************/


/******************<Functions>*****************/
void init_doorsense_spi(void);
/******************</Functions>*****************/

#endif // DOORSENSE_SPI_H