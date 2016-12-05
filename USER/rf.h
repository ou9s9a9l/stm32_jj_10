
#ifndef __RF_H__
#define	__RF_H__

#define RF_SX1278   

//unsigned char RFSendData( unsigned char *buf, unsigned char size );
extern const char *rfName;
extern unsigned short	iSend, iRev;

extern unsigned char	sendBuf[256];
extern unsigned char	revBuf[256];


void SPI2_Init(void);

unsigned char RFRevData( unsigned char *buf );
void RFRxMode( void );
void RFInit( void );

#endif
