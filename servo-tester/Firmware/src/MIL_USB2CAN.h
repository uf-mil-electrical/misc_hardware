#include "stdbool.h"
#include "stdint.h"

#ifndef MIL_USB2CAN_H_
#define MIL_USB2CAN_H_

/* -------------------------------------------------------------------------- */
/*                                 SYNC VALUE                                 */
/* -------------------------------------------------------------------------- */

#define SYNC_VALUE                  0x3701

/* -------------------------------------------------------------------------- */
/*                                  CLASS IDS                                 */
/* -------------------------------------------------------------------------- */

#define META_CLASSID                0x00
#define SUB8TK_CLASSID              0x01
#define SUB9TK_CLASSID              0x02
#define BATMON_CLASSID              0x03
#define ACTUATOR_CLASSID            0x04
#define SYSSTATUS_CLASSID           0x05
#define SUB8SER_CLASSID             0x06

#define NAVRF_CLASSID               0x10

/* -------------------------------------------------------------------------- */
/*                                SUBCLASS IDS                                */
/* -------------------------------------------------------------------------- */

#define META_SUBID_NAKPACK          0x00
#define META_SUBID_ACKPACK          0x01

/* ---------------------------- Sub 8 Thrust Kill --------------------------- */

#define SUB8TK_SUBID_HRT_PACK       0x00
#define SUB8TK_SUBID_THR_SETPACK    0x01
#define SUB8TK_SUBID_THR_KILLSET    0x02
#define SUB8TK_SUBID_THR_KILLREC    0x03

/* ---------------------------- Sub 9 Thrust Kill --------------------------- */

#define SUB9TK_SUBID_HRT_SETPACK    0x00
#define SUB9TK_SUBID_HRT_RECPACK    0x01
#define SUB9TK_SUBID_THR_SETPACK    0x02
#define SUB9TK_SUBID_THR_KILLSET    0x03
#define SUB9TK_SUBID_THR_KILLREC    0x04

#define SUB9TK_SUBID_TEMP_REQUEST   0x05
#define SUB9TK_SUBID_TEMP_RECEIVE   0x06

/* ----------------------------- Battery Monitor ---------------------------- */

#define BATMON_SUBID_REQPACK        0x00
#define BATMON_SUBID_RESPACK        0x01

/* -------------------------------- Actuator -------------------------------- */

#define ACTUATOR_SUBID_SETPACK      0x00
#define ACTUATOR_SUBID_POLLREQPACK  0x01
#define ACTUATOR_SUBID_POLLRESPACK  0x02

/* ---------------------------- SUB 8 SERVO TUBE ---------------------------- */

#define SUB8SER_SUBID_DROPPER       0x00
#define SUB8SER_SUBID_TORPEDO       0x01
#define SUB8SER_SUBID_GRIPPER       0x02
#define SUB8SER_SUBID_SQUEEZER      0x03


#define SUB8SER_SUBID_CHGDELAY      0x10
#define SUB8SER_SUBID_CHGINCR       0x20

/* ------------------------------ System Status ----------------------------- */

#define SYSSTATUS_SUBID_SETLEDREQ   0x00

/* ------------------------------ NaviGator RF ------------------------------ */

#define NAVRF_SUBID_KILLSET         0x00
#define NAVRF_SUBID_KILLREC         0x01
#define NAVRF_SUBID_SETMOVE         0x02
#define NAVRF_SUBID_IGNRFKL         0x03

/* -------------------------------------------------------------------------- */
/*                              THURST KILL BOARD                             */
/* -------------------------------------------------------------------------- */

typedef enum thruster_id {
    FLH = 0,
    FRH = 1,
    FLV = 2,
    FRV = 3,
    BLH = 4,
    BRH = 5,
    BLV = 6,
    BRV = 7
} thruster_id_t;

typedef enum sub9tk_killstatus {
	BATTERY_LOW = 4,
    BOARD_HEARTBEAT_LOST = 2,
    KILL_SWITCH = 3,
    MOBO_HEARTBEAT_LOST = 1,
    SOFTWARE_REQUESTED = 0, 
    NOT_KILLED = -1 // keep this as a little secret between you and me for now bc I am lazy :^)
} sub9tk_killstatus_t;

typedef struct sub9tk_setpack {
    thruster_id_t id;
    float speed;
} sub9tk_thrust_set_pack_t;

typedef struct sub9tk_killset {
    bool set;
    sub9tk_killstatus_t status;
} sub9tk_killset_t;

typedef struct sub9tk_killrec {
    bool set;
    sub9tk_killstatus_t status;
} sub9tk_killrec_t;

/* -------------------------------------------------------------------------- */
/*                               BATTERY MONITOR                              */
/* -------------------------------------------------------------------------- */

typedef struct old_batmon_pollresp {
    float bat1_volt;
    float bat2_volt;
    float bat1_current;
    float bat2_current;
} old_batmon_pollresp_t;

typedef struct baton_pollresp {
    float bat_volt;
} baton_pollresp_t;

/* -------------------------------------------------------------------------- */
/*                                  Actuator                                  */
/* -------------------------------------------------------------------------- */

typedef struct actuator_setpack {
    uint8_t address;
    bool open;
} actuator_setpack_t;

typedef struct actuator_pollres {
    uint8_t value;
} actuator_pollres_t;

/* -------------------------------------------------------------------------- */
/*                              NaviGator RF KILL                             */
/* -------------------------------------------------------------------------- */

typedef enum navrf_killstatus {
    MOBO_REQUESTED = 0,
    RF_KILL = 1,
    EMERGENCY_BUTTON_PRESSED = 2,
    UNKILLED = 3
} navrf_killstatus_t;

#endif // MIL_USB2CAN_H_
