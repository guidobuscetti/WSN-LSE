/*
 * cc2520-mac.h
 *
 *  Created on: 03/02/2012
 *      Author: pablo
 */

#ifndef CC2520_MAC_H_
#define CC2520_MAC_H_

typedef enum
{
	MAC_FRAME_TYPE_BEACON=0,
	MAC_FRAME_TYPE_DATA=1,
	MAC_FRAME_TYPE_ACK=2,
	MAC_FRAME_TYPE_MAC_CMD=3,
	MAC_FRAME_TYPE_4_RESERVED,
	MAC_FRAME_TYPE_5_RESERVED,
	MAC_FRAME_TYPE_6_RESERVED,
	MAC_FRAME_TYPE_7_RESERVED
}macFrameType_e;

typedef enum
{
	MAC_ADDR_MODE_NO_PAN_ADDR=0,
	MAC_ADDR_MODE_1_RESERVED=1,
	MAC_ADDR_MODE_SHORT=2,
	MAC_ADDR_MODE_EXTENDED=3
}macAddrMode_e;

typedef union
{
	struct
	{
		u16 panid;
		u16 addr;
	}shortAddr;
	struct
	{
		u16 panid;
		u64 addr;
	}extAddr;
}macaddr_t;

typedef struct _frameData
{

	u16 fcf;
	u8 seqn;
	macaddr_t dst;
	macaddr_t src;
	s8 rssi;
	u8 corr_crc;
	u8 pl_length;
	u8 payload[128];
}frameData;

#define macFCFGetDestAddrMode(x) (((x)&0x0C00)>>10)
#define macFCFGetSrcAddrMode(x) (((x)&0xC000)>>14)
#define macFCFGetFrameVersion(x) (((x)&0x3000)>>12)
#define macFCFGetFrameType(x) ((x)&0x07)

#define PAN_ID_COMPRESSION_FLAG (1<<6)

u8 ccSetLocalShortAddr(u16 addr);
u16 ccGetLocalShortAddr(void);
u8 ccSetLocalPANID(u16 panid);
u16 ccGetLocalPANID(void);
u8 ccSetLocalExtAddr(u64 addr);
u64 ccGetLocalExtAddr(void);
u8 ccSetSrcShortAddr(u8 n, u32 panid_addr);
u32 ccGetSrcShortAddr(u8 n);
u8 ccSetSrcExtAddr(u8 n, u64 addr);
u64 ccGetSrcExtAddr(u8 n);
u16 ccWrapperFCF(u8 frameType, u8 securityEnabled, u8 framePending, u8 ackRequested,
		u8 PANIDcompression, u8 destAddrMode, u8 frameVersion, u8 sourceAddrMode);
s8 ccFrameTx(frameData d);
frameData ccFrameRx(void);

void memorycpy(void * dst, void * src, int n);

#endif /* CC2520_MAC_H_ */
