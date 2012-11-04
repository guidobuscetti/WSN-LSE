/*
 * cc2520.h
 *
 *  Created on: 31/01/2012
 *      Author: pablo
 */

#ifndef CC2520_H_
#define CC2520_H_

#define SSEL_Set() {LPC_GPIO0->FIOSET = 1<<6;}
#define SSEL_Clr() {LPC_GPIO0->FIOCLR = 1<<6;}

/* ------------------------------------------------------------------------------------------------
 *                                    Target Specific Defines
 * ------------------------------------------------------------------------------------------------
 */

/* strobe command registers */
#define SNOP                        0x00
#define IBUFLD                      0x02
#define SIBUFEX                     0x03
#define SSAMPLECCA                  0x04
#define SRES                        0x0F
#define MEMRD                       0x10
#define MEMWR                       0x20
#define RXBUF                       0x30
#define RXBUFCP                     0x38
#define RXBUFMOV                    0x32
#define TXBUF                       0x3A
#define TXBUFCP                     0x3E
#define RANDOM                      0x3C
#define SXOSCON                     0x40
#define STXCAL                      0x41
#define SRXON                       0x42
#define STXON                       0x43
#define STXONCCA                    0x44
#define SRFOFF                      0x45
#define SXOSCOFF                    0x46
#define SFLUSHRX                    0x47
#define SFLUSHTX                    0x48
#define SACK                        0x49
#define SACKPEND                    0x4A
#define SNACK                       0x4B
#define SRXMASKBITSET               0x4C
#define SMRMASKBITCLR               0x4D
#define RXMASKAND                   0x4E
#define RXMASKOR                    0x4F
#define MEMCP                       0x50
#define MEMCPR                      0x52
#define MEMXCP                      0x54
#define MEMXWR                      0x56
#define BCLR                        0x58
#define BSET                        0x59
#define CTR_UCTR                    0x60
#define CBCMAC                      0x64
#define UCBCMAC                     0x66
#define CCM                         0x68
#define UCCM                        0x6A
#define ECB                         0x70
#define ECBO                        0x72
#define ECBX                        0x74
#define ECBXO                       0x76
#define INC                         0x78
#define ABORT                       0x7F
#define REGRD                       0x80
#define REGWR                       0xC0

/* configuration registers */
#define FRMFILT0                    0x00
#define FRMFILT1                    0x01
#define SRCMATCH                    0x02
#define SRCSHORTEN0                 0x04
#define SRCSHORTEN1                 0x05
#define SRCSHORTEN2                 0x06
#define SRCEXTEN0                   0x08
#define SRCEXTEN1                   0x09
#define SRCEXTEN2                   0x0A
#define FRMCTRL0                    0x0C
#define FRMCTRL1                    0x0D
#define RXENABLE0                   0x0E
#define RXENABLE1                   0x0F
#define EXCFLAG0                    0x10
#define EXCFLAG1                    0x11
#define EXCFLAG2                    0x12
#define EXCMASKA0                   0x14
#define EXCMASKA1                   0x15
#define EXCMASKA2                   0x16
#define EXCMASKB0                   0x18
#define EXCMASKB1                   0x19
#define EXCMASKB2                   0x1A
#define EXCBINDX0                   0x1C
#define EXCBINDX1                   0x1D
#define EXCBINDY0                   0x1E
#define EXCBINDY1                   0x1F
#define GPIOCTRL0                   0x20
#define GPIOCTRL1                   0x21
#define GPIOCTRL2                   0x22
#define GPIOCTRL3                   0x23
#define GPIOCTRL4                   0x24
#define GPIOCTRL5                   0x25
#define GPIOPOLARITY                0x26
#define GPIOCTRL                    0x28
#define DPUCON                      0x2A
#define DPUSTAT                     0x2C
#define FREQCTRL                    0x2E
#define FREQTUNE                    0x2F
#define TXPOWER                     0x30
#define TXCTRL                      0x31
#define FSMSTAT0                    0x32
#define FSMSTAT1                    0x33
#define FIFOPCTRL                   0x34
#define FSMCTRL                     0x35
#define CCACTRL0                    0x36
#define CCACTRL1                    0x37
#define RSSI                        0x38
#define RSSISTAT                    0x39
#define TXFIFO_BUF                  0x3A
#define RXFIRST                     0x3C
#define RXFIFOCNT                   0x3E
#define TXFIFOCNT                   0x3F
#define CHIPID                      0x40
#define VERSION                     0x42
#define EXTCLOCK                    0x44
#define MDMCTRL0                    0x46
#define MDMCTRL1                    0x47
#define FREQEST                     0x48
#define RXCTRL                      0x4A
#define FSCTRL                      0x4C
#define FSCAL0                      0x4E
#define FSCAL1                      0x4F
#define FSCAL2                      0x50
#define FSCAL3                      0x51
#define AGCCTRL0                    0x52
#define AGCCTRL1                    0x53
#define AGCCTRL2                    0x54
#define AGCCTRL3                    0x55
#define ADCTEST0                    0x56
#define ADCTEST1                    0x57
#define ADCTEST2                    0x58
#define MSMTEST0                    0x5A
#define MSMTEST1                    0x5B
#define DACTEST0                    0x5C
#define DACTEST1                    0x5D
#define ATEST                       0x5E
#define DACTEST2                    0x5F
#define PTEST0                      0x60
#define PTEST1                      0x61
#define RESERVED                    0x62
#define DPUTEST                     0x7A
#define ACTTEST                     0x7C
#define RAM_BIST_CTRL               0x7E

/* RAM memory spaces */
#define RAM_PANID                   0x3F2
#define RAM_SHORTADR                0x3F4
#define RAM_IEEEADR                 0x3EA

/* Src matching table */
#define SRC_MATCH_TABLE             0x380
#define SRCSHORTPENDEN0             0x3E7
#define SRCEXTPENDEN0               0x3E4
#define SRCRESINDEX                 0x3E3

/* status byte */
#define XOSC16M_STABLE              (1 << 7)
#define RSSI_VALID                  (1 << 6)
#define EXCEPTION_A                 (1 << 5)
#define EXCEPTION_B                 (1 << 4)
#define DPU_H_ACTIVE                (1 << 3)
#define DPU_L_ACTIVE                (1 << 2)
#define TX_ACTIVE                   (1 << 1)
#define RX_ACTIVE                   (1 << 0)

/* CHIPID */
#define CHIPID_RESET_VALUE          0x84

/* CHIP VERSION */
#define REV_A                       0

/* FRMCTRL0 */
#define FRMCTRL0_RESET_VALUE        0x40
#define RX_MODE(x)                  ((x) << 2)
#define RX_MODE_INFINITE_RECEPTION  RX_MODE(2)
#define RX_MODE_NORMAL_OPERATION    RX_MODE(0)
#define AUTOACK_BV                  (1 << 5)

/* FRMCTRL1 */
#define FRMCTRL1_RESET_VALUE        0x01
#define PENDING_OR_BV               (1 << 2)

/* FIFOPCTRL */
#define FIFOP_THR_RESET_VALUE       64

/* FRMFILT0 */
#define FRMFILT0_RESET_VALUE        0x0D
#define MAX_FRAME_VERSION_MASK      (3 << 2)
#define MAX_FRAME_VERSION           (1 << 3)
#define PAN_COORDINATOR_BV          (1 << 1)
#define ADR_DECODE_BV               (1 << 0)

/* FREQCTRL */
#define FREQCTRL_BASE_VALUE         0
#define FREQCTRL_FREQ_2405MHZ       11

/* FSMSTAT1 */
#define SAMPLED_CCA_BV              (1 << 3)

/* TXPOWER */
#define TXPOWER_BASE_VALUE          0

/* FSMSTATE */
#define FSM_FFCTRL_STATE_RX_MASK    0x3F
#define FSM_FFCTRL_STATE_RX_INF     31

/* SRCMATCH */
#define SRCMATCH_RESET_VALUE        0x07
#define SRC_MATCH_EN                (1 << ( 0 ))
#define AUTOPEND                    (1 << ( 1 ))
#define PEND_DATAREQ_ONLY           (1 << ( 2 ))

/* SRCRESINDEX */
#define AUTOPEND_RES                (1 << ( 6 ))

/* FRMFILT1 */
#define FRMFILT1_RESET_VALUE        0x78

/* MDMCTRL1 */
#define MDMCTRL1_RESET_VALUE        0x2E
#define CORR_THR_MASK               0x1F

/* GPIO directional control */
#define GPIO_DIR_RADIO_INPUT        0x80
#define GPIO_DIR_RADIO_OUTPUT       0x00

/* GPIO command strobes */
#define GPIO_CMD_SIBUFEX            0x00
#define GPIO_CMD_SRXMASKBITCLR      0x01
#define GPIO_CMD_SRXMASKBITSET      0x02
#define GPIO_CMD_SRXON              0x03
#define GPIO_CMD_SSAMPLECCA         0x04
#define GPIO_CMD_SACK               0x05
#define GPIO_CMD_SACKPEND           0x06
#define GPIO_CMD_SNACK              0x07
#define GPIO_CMD_STXON              0x08
#define GPIO_CMD_STXONCCA           0x09
#define GPIO_CMD_SFLUSHRX           0x0A
#define GPIO_CMD_SFLUSHTX           0x0B
#define GPIO_CMD_SRXFIFOPOP         0x0C
#define GPIO_CMD_STXCAL             0x0D
#define GPIO_CMD_SRFOFF             0x0E
#define GPIO_CMD_SXOSCOFF           0x0F

/* GPIO exceptions */
#define EXCEPTION_ECG_EXT_CLOCK     0x00
#define EXCEPTION_RF_IDLE           0x01
#define EXCEPTION_TX_FRM_DONE       0x02
#define EXCEPTION_TX_ACK_DONE       0x03
#define EXCEPTION_TX_UNDERFLOW      0x04
#define EXCEPTION_TX_OVERFLOW       0x05
#define EXCEPTION_RX_UNDERFLOW      0x06
#define EXCEPTION_RX_OVERFLOW       0x07
#define EXCEPTION_RXENABLE_ZERO     0x08
#define EXCEPTION_RX_FRM_DONE       0x09
#define EXCEPTION_RX_FRM_ACCEPTED   0x0A
#define EXCEPTION_SRC_MATCH_DONE    0x0B
#define EXCEPTION_SRC_MATCH_FOUND   0x0C
#define EXCEPTION_FIFOP             0x0D
#define EXCEPTION_SFD               0x0E
#define EXCEPTION_DPU_DONE_L        0x0F
#define EXCEPTION_DPU_DONE_H        0x10
#define EXCEPTION_MEMADDR_ERROR     0x11
#define EXCEPTION_USAGE_ERROR       0x12
#define EXCEPTION_OPERAND_ERROR     0x13
#define EXCEPTION_SPI_ERROR         0x14
#define EXCEPTION_RF_NO_LOCK        0x15
#define EXCEPTION_RX_FRM_ABORTED    0x16
#define EXCEPTION_RXBUFMOV_TIMEOUT  0x17
#define EXCEPTION_UNUSED            0x18
#define EXCEPTION_CHANNEL_A         0x21
#define EXCEPTION_CHANNEL_B         0x22
#define EXCEPTION_CHANNEL_COMP_A    0x23
#define EXCEPTION_CHANNEL_COMP_B    0x24
#define EXCEPTION_RFC_FIFO          0x27
#define EXCEPTION_RFC_FIFOP         0x28
#define EXCEPTION_RFC_CCA           0x29
#define EXCEPTION_RFC_SFD_SYNC      0x2A
#define EXCEPTION_RFC_SNIFFER_CLK   0x31
#define EXCEPTION_RFC_SNIFFER_DATA  0x32

/* GPIO exception bit in EXCFLAG0 */
#define RF_IDLE_BIT                 (1<<0)
#define TX_FRM_DONE_BIT             (1<<1)
#define TX_ACK_DONE_BIT             (1<<2)
#define TX_UNDERFLOW_BIT            (1<<3)
#define TX_OVERFLOW_BIT             (1<<4)
#define RX_UNDERFLOW_BIT            (1<<5)
#define RX_OVERFLOW_BIT             (1<<6)
#define RXENABLE_ZERO_BIT           (1<<7)

/* GPIO exception bit in EXCFLAG1 */
#define RX_FRM_DONE_BIT             (1<<0)
#define RX_FRM_ACCEPTED_BIT         (1<<1)
#define SRC_MATCH_DONE_BIT          (1<<2)
#define SRC_MATCH_FOUND_BIT         (1<<3)
#define FIFOP_BIT                   (1<<4)
#define SFD_BIT                     (1<<5)
#define DPU_DONE_L_BIT              (1<<6)
#define DPU_DONE_H_BIT              (1<<7)

/* GPIO exception bit in EXCFLAG2 */
#define MEMADDR_ERROR_BIT           (1<<0)
#define USAGE_ERROR_BIT             (1<<1)
#define OPERAND_ERROR_BIT           (1<<2)
#define SPI_ERROR_BIT               (1<<3)
#define RF_NO_LOCK_BIT              (1<<4)
#define RX_FRM_ABORTED_BIT          (1<<5)
#define RXBUFMOV_TIMEOUT_BIT        (1<<6)
#define UNUSED_BIT                  (1<<7)

/* Clear GPIO exception in EXCFLAG0 */
#define RF_IDLE_FLAG                ((1<<0)^0xFF)
#define TX_FRM_DONE_FLAG            ((1<<1)^0xFF)
#define TX_ACK_DONE_FLAG            ((1<<2)^0xFF)
#define TX_UNDERFLOW_FLAG           ((1<<3)^0xFF)
#define TX_OVERFLOW_FLAG            ((1<<4)^0xFF)
#define RX_UNDERFLOW_FLAG           ((1<<5)^0xFF)
#define RX_OVERFLOW_FLAG            ((1<<6)^0xFF)
#define RXENABLE_ZERO_FLAG          ((1<<7)^0xFF)

/* Clear GPIO exception in EXCFLAG1 */
#define RX_FRM_DONE_FLAG            ((1<<0)^0xFF)
#define RX_FRM_ACCEPTED_FLAG        ((1<<1)^0xFF)
#define SRC_MATCH_DONE_FLAG         ((1<<2)^0xFF)
#define SRC_MATCH_FOUND_FLAG        ((1<<3)^0xFF)
#define FIFOP_FLAG                  ((1<<4)^0xFF)
#define SFD_FLAG                    ((1<<5)^0xFF)
#define DPU_DONE_L_FLAG             ((1<<6)^0xFF)
#define DPU_DONE_H_FLAG             ((1<<7)^0xFF)

/* Clear GPIO exception in EXCFLAG2 */
#define MEMADDR_ERROR_FLAG          ((1<<0)^0xFF)
#define USAGE_ERROR_FLAG            ((1<<1)^0xFF)
#define OPERAND_ERROR_FLAG          ((1<<2)^0xFF)
#define SPI_ERROR_FLAG              ((1<<3)^0xFF)
#define RF_NO_LOCK_FLAG             ((1<<4)^0xFF)
#define RX_FRM_ABORTED_FLAG         ((1<<5)^0xFF)
#define RXBUFMOV_TIMEOUT_FLAG       ((1<<6)^0xFF)
#define UNUSED_FLAG                 ((1<<7)^0xFF)


/* Funciones */

s8 ccInit(u16 panid, u16 shortAddr, u64 extAddr, u8 autoAck);
u8 ccCmd(u8 cmd, u16 addr, u8 n, void * data);
u8 ccRegRd(u8 reg, u8 n, void * out);
u8 ccRegWr(u8 reg, u8 n, void * in);

#endif /* CC2520_H_ */
