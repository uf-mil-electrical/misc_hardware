#ifndef BMP5_SELFTEST_H_
#define BMP5_SELFTEST_H_

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif


/******************<Dependencies>*****************/
#include "libraries/BMP5_SensorAPI/bmp5.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
// Min/max temperatures and pressures
#ifdef BMP5_USE_FIXED_POINT
#define BMP5_MIN_TEMPERATURE        (0)         /* 0 degree celsius */
#define BMP5_MAX_TEMPERATURE        (40)        /* 40 degree celsius */
#define BMP5_MIN_PRESSURE           (900)       /* 900 hecto Pascals */
#define BMP5_MAX_PRESSURE           (1100)      /* 1100 hecto Pascals */

#else
#define BMP5_MIN_TEMPERATURE        (0.0f)      /* 0 degree celsius */
#define BMP5_MAX_TEMPERATURE        (40.0f)     /* 40 degree celsius */
#define BMP5_MIN_PRESSURE           (900.0f)    /* 900 hecto Pascals */
#define BMP5_MAX_PRESSURE           (1100.0f)   /* 1100 hecto Pascals */
#endif


// Error codes for self test
#define BMP5_COMMUNICATION_ERROR_OR_WRONG_DEVICE            INT8_C(-11)
#define BMP5_TRIMMING_DATA_OUT_OF_BOUND                     INT8_C(-12)
#define BMP5_TEMPERATURE_BOUND_WIRE_FAILURE_OR_MEMS_DEFECT  INT8_C(-13)
#define BMP5_PRESSURE_BOUND_WIRE_FAILURE_OR_MEMS_DEFECT     INT8_C(-14)
#define BMP5_IMPLAUSIBLE_TEMPERATURE                        INT8_C(-15)
#define BMP5_IMPLAUSIBLE_PRESSURE                           INT8_C(-16)
#define BMP5_E_SELFTEST_TIMEOUT                             INT8_C(-17)

// Polling interval applied when data-ready is not yet asserted (microseconds)
#define BMP5_SELFTEST_POLL_PERIOD_US                        UINT16_C(1000)

// Maximum number of 1 ms polling iterations before the loop is aborted (10 s total)
#define BMP5_SELFTEST_TIMEOUT_MS                            UINT16_C(10000)

/******************</Defines>*****************/



/******************<Public Function Definitions>*****************/
/**
 * \ingroup bmp5
 * \defgroup bmp5ApiSelftest Self test
 * @brief Perform self test of sensor
 */

/*!
 * \ingroup bmp5ApiSelftest
 * \page bmp5_api_bmp5_selftest_check bmp5_selftest_check
 * \code
 * int8_t bmp5_selftest_check(struct bmp5_dev *dev);
 * \endcode
 * @details Self-test API for the BMP5
 *
 * @param[in]   dev    : Structure instance of bmp5_dev
 *
 * @return Result of API execution status
 * @retval 0  -> Success
 * @retval <0 -> Error
 */
int8_t bmp5_selftest_check(struct bmp5_dev *dev);

/******************</Public Function Definitions>*****************/

#endif /* BMP5_SELFTEST_H_ */
