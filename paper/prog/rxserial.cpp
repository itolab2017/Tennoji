/*
 * rxserial.c
 *
 *  Created on: 2017/08/16
 *      Author: kouhei
 */
#include "iodefine.h"
#include "rxserial.h"

volatile char Buf[BUFSIZE];
volatile short Buf_start=0;
volatile short Buf_end=0;
volatile unsigned char Buffer_protect = 0;
volatile unsigned char SCI_stop = 1;

void init_serial(void)
{
	long i;

	Buf_start=0;
	Buf_end = 0;
	Buffer_protect = 0;
	SCI_stop = 1;
	/*
	MSTP(SCI1) = 0;			// SCI1のスタンバイを解除
	//IOPORT
	PORT2.DDR.BIT.B6 = 1;	// PORT2-6 TxD1 出力に設定
	PORT3.DDR.BIT.B0 = 0;	// PORT3-0 RxD1 入力に設定
	PORT3.ICR.BIT.B0 = 1;	// 入力バッファ有効 [1]
	//SCI1初期化スタート
	SCI1.SCR.BYTE = 0;		// SCR レジスタ初期化
	SCI1.SCR.BIT.CKE  = 0;	// クロック選択0:内臓ボーレートジェネレータ [2]
	//SMR
	SCI1.SMR.BIT.CKS = 0;	// クロック選択　PCLK/1 n=0[3]
	SCI1.SMR.BIT.MP = 0;	// マルチプロセッサ通信機能　0: 禁止   1: 許可
	SCI1.SMR.BIT.STOP = 0;	// ストップビット長　0:1 ビット　1:2 ビット [3]
	//SCI1.SMR.BIT.PM = 0;	// パリティモードビット 0: 偶数パリティ　1: 奇数パリティ
	SCI1.SMR.BIT.PE = 0;	// パリティビットなし [3]
	SCI1.SMR.BIT.CHR = 0;	// データ長 0:8 ビット 1:7 ビット
	SCI1.SMR.BIT.CM = 0;	// コミニケーションモード　0: 調歩同期　1: クロック同期
	SCI1.SCMR.BYTE = 0xF2;	// スマートカードモードレジスタ　スマートカード使用しない(0xF2 初期値)
	SCI1.BRR = 77;			// ビットレート設定　9600bps PCLK=24MHZ n=0 N=77
	for(i=0;i<100000;i++);	//謎の1ビット期間以上待つ(1/9600秒か？)
	SCI1.TDR=0;
	//SCI1.SCR.BIT.TIE = 1;	//TXI 割込みを許可
	IPR(SCI1,TXI1) = 0x7;	//SCI1 の RXI1 の割り込み優先度を7 に設定
	IEN(SCI1,TXI1) = 0x1;	//SCI1 の RXI1 の割り込みを有効化
	IR(SCI1,TXI1) = 0x0;	//SCI1 の RXI1 の割り込みフラグをクリア
	IPR(SCI1,TEI1) = 0x7;	//SCI1 の RXI1 の割り込み優先度を7 に設定
	IEN(SCI1,TEI1) = 0x1;	//SCI1 の RXI1 の割り込みを有効化
	IR(SCI1,TEI1) = 0x0;	//SCI1 の RXI1の割り込みフラグをクリア
	*/
	//SCI1.SCR.BYTE = 0x30;	// 受信許可ビットRE と送信許可ビットTE を同時に1 にして双方を許可する
	
	MSTP(SCI3) = 0;			//SCI1 のスタンバイを解除
	//IOPORT
	PORT2.DDR.BIT.B3 = 1;	//PORT2-3 TxD3 出力に設定
	PORT2.DDR.BIT.B5 = 0;	//PORT2-5 RxD3 入力に設定
	PORT2.ICR.BIT.B5 = 1;	// 入力バッファ有効 [1]
	//SCI1初期化スタート
	SCI3.SCR.BYTE = 0;		//SCR レジスタ初期化
	SCI3.SCR.BIT.CKE  = 0;	// クロック選択 0: 内臓ボーレートジェネレータ [2]
	//SMR
	SCI3.SMR.BIT.CKS = 0;	// クロック選択　PCLK/1 n=0[3]
	SCI3.SMR.BIT.MP = 0;	// マルチプロセッサ通信機能　0: 禁止   1: 許可
	SCI3.SMR.BIT.STOP = 0;	// ストップビット長　0:1 ビット　1:2 ビット[3]
	//SCI1.SMR.BIT.PM = 0;	// パリティモードビット 0: 偶数パリティ　1: 奇数パリティ
	SCI3.SMR.BIT.PE = 0;	// パリティビットなし [3]
	SCI3.SMR.BIT.CHR = 0;	// データ長 0:8 ビット 1:7 ビット
	SCI3.SMR.BIT.CM = 0;	// コミニケーションモード　0: 調歩同期　1: クロック同期
	SCI3.SCMR.BYTE = 0xF2;	// スマートカードモードレジスタ　スマートカード使用しない(0xF2 初期値)
	SCI3.BRR = 77;			// ビットレート設定　9600bps PCLK=24MHZ n=0 N=77
	for(i=0;i<100000;i++);	// 謎の1ビット期間以上待つ(1/9600 秒か？)
	SCI3.TDR=0;
	//SCI1.SCR.BIT.TIE = 1;	//TXI 割込みを許可
	IPR(SCI3,TXI3) = 0x7;	//SCI3 のRXI3 の割り込み優先度を7 に設定
	IEN(SCI3,TXI3) = 0x1;	//SCI3 のRXI3 の割り込みを有効化
	IR(SCI3,TXI3) = 0x0;	//SCI3 のRXI3 の割り込みフラグをクリア
	IPR(SCI3,TEI3) = 0x7;	//SCI3 のRXI3 の割り込み優先度を7 に設定
	IEN(SCI3,TEI3) = 0x1;	//SCI3 のRXI3 の割り込みを有効化
	IR(SCI3,TEI3) = 0x0;
}

int writeBuffer(char *s)
{
	//short i;
	int space;


	//Buffer に書き込める余地があるか調べる
	space=queryBufferSpace();
	if (space<strlen(s)+10) {


		return 1;
	}

	while(*s!='\0'){
		Buf[Buf_end]=*s;
		Buf_end ++;
		Buf_end = Buf_end%BUFSIZE;
		s++;
	}
	return 0;
}


int queryBufferSpace(void)
{
	if (Buf_start==Buf_end)return BUFSIZE-1;
	else return (BUFSIZE- Buf_end + Buf_start)%BUFSIZE-1;
}

int sendString(char *s)
{

	while(writeBuffer(s)==1);

	//PORTD.DR.BYTE= 1;
	SCI3.SCR.BYTE = 0xb0;                   //TIE,RIE , RE ，TE を設定して割り込みを有効化
	if(SCI_stop){
		//PORTD.DR.BIT.B0=~PORTD.DR.BIT.B0;
		//PORTD.DR.BIT.B1=~PORTD.DR.BIT.B1;


		SCI3.SCR.BYTE = 0xb0;                   //TIE,RIE , RE ，TE を設定して割り込みを有効化
		SCI_stop = 0;
	}
	return 0;
}

int strlen(char *s)
{
	int cnt;
	cnt=0;
	while(*s!='\0'){
		s++;
		cnt++;
	}
	return cnt;
}

int itoa(long x, char *s)
{
	int i,j;
	if(x>0){
		for(i = 1; i*10<= x; i*=10);
		for(j = 0; 0 < i; i /=10,j++,s++){
			*s = x/i+'0';
			x %= i;
		}
	}
	else{
		x=-x;
		
		for(i = 1; i*10<= x; i*=10);
		for(j = 0; 0 < i; i /=10,j++,s++){
			*s = x/i+'0';
			x %= i;
		}
	}
	*s = '\0';
	return 0;
}
