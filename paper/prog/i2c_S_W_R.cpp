#include "iodefine.h"

// ジャイロモード設定アドレス送信
void gyro_set()
{
	
	// i2c バスビジー、エンプティ判定
	while(RIIC0.ICCR2.BIT.BBSY==1);
	
	// スタートコンディション発行
	RIIC0.ICCR2.BIT.ST=1;
	
	if(RIIC0.ICSR2.BIT.NACKF==0)
	{
		// エンプティフラグ
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		// 送信モードアドレス送信
		RIIC0.ICDRT=0xd2;
		
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		// データアドレス指定
		RIIC0.ICDRT=0x20;
		
		while(RIIC0.ICSR2.BIT.TDRE==0)PORTD.DR.BYTE=0x02;	
		
		// データ送信
		RIIC0.ICDRT=0x8f;
		
		while(RIIC0.ICSR2.BIT.TEND==0)PORTD.DR.BYTE=0x01;
				
		// ストップ動作
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
		
	}
	
	else if(RIIC0.ICSR2.BIT.NACKF==1)
	{

		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
	}
	
	while(RIIC0.ICSR2.BIT.STOP==0);
	PORTD.DR.BYTE=0x00;
	
	// 次の通信への処理
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
}

// レジスタアドレス送信
void write_addr(unsigned char addr)
{
	// i2c バスビジー、エンプティ判定
	while(RIIC0.ICCR2.BIT.BBSY==1);
	
	// スタートコンディション発行
	RIIC0.ICCR2.BIT.ST=1;
	
	// エンプティフラグ
	while(RIIC0.ICSR2.BIT.TDRE==0);
	
	// 送信モードアドレス送信
	RIIC0.ICDRT=0xd2;
	
	while(RIIC0.ICSR2.BIT.TDRE==0);
	
	if(RIIC0.ICSR2.BIT.NACKF==0){
		
		// データアドレス指定
		RIIC0.ICDRT=addr;
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		while(RIIC0.ICSR2.BIT.TEND==0);
		
		// ストップ動作
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
	}
	
	else if(RIIC0.ICSR2.BIT.NACKF==1)
	{
		
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
	}
	
	while(RIIC0.ICSR2.BIT.STOP==0);
		
	// 次の通信への処理
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
}

// データをもらう
char read_data(char deta)
{
	
	// マスタ受信開始
	while(RIIC0.ICCR2.BIT.BBSY==1);
	RIIC0.ICCR2.BIT.ST=1;
	
	while(RIIC0.ICSR2.BIT.TDRE==0);
		
	// 受信モードアドレス送信
	RIIC0.ICDRT=0xd3;
	while(RIIC0.ICSR2.BIT.RDRF!=1);
	
	// データ受信動作
	if(RIIC0.ICSR2.BIT.NACKF==0)
	{
		RIIC0.ICMR3.BIT.WAIT=1;
		RIIC0.ICMR3.BIT.RDRFS=1;
		RIIC0.ICMR3.BIT.ACKBT=1;
		
		// ダミー受信
		deta=RIIC0.ICDRR;
		
		while(RIIC0.ICSR2.BIT.RDRF!=1);
		
		// ストップ動作
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
		
		// データ受信
		deta=RIIC0.ICDRR;
		
		RIIC0.ICMR3.BIT.ACKBT=1;
		RIIC0.ICMR3.BIT.WAIT=0;
		
	}
	
	else if(RIIC0.ICSR2.BIT.NACKF==1)
	{
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
		
		// ダミー受信
		deta=RIIC0.ICDRR;
	}
		
	while(RIIC0.ICSR2.BIT.STOP==0);
	
	// 次の通信への処理
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
	
	return(deta);
}
