#include "iodefine.h"
#include "INP.h"
#include "vect.h"
#include "typedefine.h"

// レシーバ関係のプログラム

unsigned short /*Pwidth*/Sl3,Yw1,Pt2,Rl4,FR,FL,RR,RL,Org1,Org2,Org4,MTU2flag, MTU4flag, MTU9flag;;

/* インプットキャプチャ関数*/
// １ｃｈ設定
void init_MTU2(void)
{
	//MTU2 reset?
	MTU2.TGRA=0;
	//WakeupMTU2
	MSTP(MTU2)=0;
	//ICU for MTIO2A is enable
	PORT2.DDR.BIT.B6=0;
	PORT2.ICR.BIT.B6=1;
	//PLCK/64
	MTU2.TCR.BIT.TPSC=3;
	//Input capture start by falling edge
	MTU2.TIOR.BIT.IOA=10;
	//TCNT
	MTU2.TCR.BIT.CCLR=1;
	//MTU2.TCNTA performs count operation
	MTUA.TSTR.BIT.CST2=1;
	//TGIEA of MTU2 interrnpt is enabled
	MTU2.TIER.BIT.TGIEA=1;
	//TGIEA of MTU2 interrupt is enabled
	IEN(MTU2,TGIA2)=1;
	//TGIEA of MTU2 interrupt priority level is 1
	IPR(MTU2,TGIA2)=1;
	//Org1=MTU2.TGRA;
}
// ２ｃｈ設定
void init_MTU4(void)
{
	//MTU4 reset?
	MTU4.TGRA=0;
	//WakeupMTU4
	MSTP(MTU4)=0;
	//ICU for MTIO4A is enable
	PORT2.DDR.BIT.B4=0;
	PORT2.ICR.BIT.B4=1;
	//PLCK/64
	MTU4.TCR.BIT.TPSC=3;
	//Input capture start by falling edge
	MTU4.TIORH.BIT.IOA=10;
	//TCNT
	MTU4.TCR.BIT.CCLR=1;
	//MTU4.TCNTA performs count operation
	MTUA.TSTR.BIT.CST4=1;
	//TGIEA of MTU4 interrnpt is enabled
	MTU4.TIER.BIT.TGIEA=1;
	//TGIEA of MTU4 interrupt is enabled
	IEN(MTU4,TGIA4)=1;
	//TGIEA of MTU4 interrupt priority level is 1
	IPR(MTU4,TGIA4)=1;
	//Org2=MTU4.TGRA;	
}
// ３ｃｈ設定
void init_MTU8(void)
{
	//MTU8 reset?
	MTU8.TGRA=0;
	//WakeupMTU8
	MSTP(MTU8)=0;
	//ICU for MTIO8A is enable
	PORTA.DDR.BIT.B6=0;
	PORTA.ICR.BIT.B6=1;
	//PLCK/64
	MTU8.TCR.BIT.TPSC=3;
	//Input capture start by falling edge
	MTU8.TIOR.BIT.IOA=10;
	//TCNT
	MTU8.TCR.BIT.CCLR=1;
	//MTU8.TCNTA performs count operation
	MTUB.TSTR.BIT.CST2=1;
	//TGIEA of MTU8 interrnpt is enabled
	MTU8.TIER.BIT.TGIEA=1;
	//TGIEA of MTU8 interrupt is enabled
	IEN(MTU8,TGIA8)=1;
	//TGIEA of MTU8 interrupt priority level is 5
	IPR(MTU8,TGIA8)=1;
}
// ４ｃｈ設定
void init_MTU9(void)
{
	//MTU9 reset?
	MTU9.TGRA=0;
	//WakeupMTU9
	MSTP(MTU9)=0;
	//ICU for MTIO9A is enable
	PORTB.DDR.BIT.B0=0;
	PORTB.ICR.BIT.B0=1;
	//PLCK/64
	MTU9.TCR.BIT.TPSC=3;
	//Input capture start by falling edge
	MTU9.TIORH.BIT.IOA=10;
	//TCNT
	MTU9.TCR.BIT.CCLR=1;
	//MTU9.TCNTA performs count operation
	MTUB.TSTR.BIT.CST3=1;
	//TGIEA of MTU9 interrnpt is enabled
	MTU9.TIER.BIT.TGIEA=1;
	//TGIEA of MTU9 interrupt is enabled
	IEN(MTU9,TGIA9)=1;
	//TGIEA of MTU9 interrupt priority level is 1
	IPR(MTU9,TGIA9)=1;
	//Org4=MTU9.TGRA;
}

/* PWM 関数設定*/
void init_MTU0(void)
{
	//WakeupMTU0
	MSTP(MTU0)=0;
	//Counts on PCLK/1
	MTU0.TCR.BIT.TPSC=3;
	//TCNT0 is cleard by TGRA compare match
	MTU0.TCR.BIT.CCLR=1;
	//PWM mode
	MTU0.TMDR.BIT.MD=2;
	//(inital:High)->(CompareMatch:Low)
	MTU0.TIORH.BIT.IOA=2;
	//(inital:Low)->(CompareMatch:High)
	MTU0.TIORH.BIT.IOB=1;
	//count is 13ms
	MTU0.TGRA=4875;
	//PWM duty is 1.2ms
	//Sl3=450;
	MTU0.TGRB=Sl3;
	// 割り込み
	MTU0.TIER.BIT.TGIEA=1;
	IEN(MTU0,TGIA0)=1;
	IPR(MTU0,TGIA0)=6;
}

void init_MTU1(void)
{
	//WakeupMTU1
	MSTP(MTU1)=0;
	//Counts on PCLK/1
	MTU1.TCR.BIT.TPSC=3;
	//TCNT1 is cleard by TGRA compare match
	MTU1.TCR.BIT.CCLR=1;
	//PWM mode
	MTU1.TMDR.BIT.MD=2;
	//(inital:High)->(CompareMatch:Low)
	MTU1.TIOR.BIT.IOA=2;
	//(inital:Low)->(CompareMatch:High)
	MTU1.TIOR.BIT.IOB=1;
	//count is 13ms
	MTU1.TGRA=4875;
	//PWM duty is 1.2ms?
	//Pwidth=450;
	MTU1.TGRB=Sl3;
	// 割り込み
	MTU1.TIER.BIT.TGIEA=1;
	IEN(MTU1,TGIA1)=1;
	IPR(MTU1,TGIA1)=3;
}

void init_MTU6(void)
{
	//WakeupMTU6
	MSTP(MTU6)=0;
	//Counts on PCLK/1
	MTU6.TCR.BIT.TPSC=3;
	//TCNT6 is cleard by TGRA compare match
	MTU6.TCR.BIT.CCLR=1;
	//PWM mode
	MTU6.TMDR.BIT.MD=2;
	//(inital:High)->(CompareMatch:Low)
	MTU6.TIORH.BIT.IOA=2;
	//(inital:Low)->(CompareMatch:High)
	MTU6.TIORH.BIT.IOB=1;
	//count is 13ms
	MTU6.TGRA=4875;
	//PWM duty is 1.2ms
	//Pwidth=450;
	MTU6.TGRB=Sl3;
	// 割り込み
	MTU6.TIER.BIT.TGIEA=1;
	IEN(MTU6,TGIA6)=1;
	IPR(MTU6,TGIA6)=5;
}

void init_MTU7(void)
{
	//WakeupMTU7
	MSTP(MTU7)=0;
	//Counts on PCLK/1
	MTU7.TCR.BIT.TPSC=3;
	//TCNT7 is cleard by TGRA compare match
	MTU7.TCR.BIT.CCLR=1;
	//PWM mode
	MTU7.TMDR.BIT.MD=2;
	//(inital:High)->(CompareMatch:Low)
	MTU7.TIOR.BIT.IOA=2;
	//(inital:Low)->(CompareMatch:High)
	MTU7.TIOR.BIT.IOB=1;
	//count is 13ms
	MTU7.TGRA=4875;
	//PWM duty is 1.2ms
	//Pwidth=450;
	MTU7.TGRB=Sl3;
	// 割り込み
	MTU7.TIER.BIT.TGIEA=1;
	IEN(MTU7,TGIA7)=1;
	IPR(MTU7,TGIA7)=2;
}

/* カウントスタート */
void start_MTU0(void)
{
	//Count start
	MTUA.TSTR.BIT.CST0=1;
}
void start_MTU1(void)
{
	//Count start
	MTUA.TSTR.BIT.CST1=1;
}
void start_MTU6(void)
{
	//Count start
	MTUB.TSTR.BIT.CST0=1;
}
void start_MTU7(void)
{
	//Count start
	MTUB.TSTR.BIT.CST1=1;
}

/* PWM 全関数出力 */
void sta_MTU0(void)
{
	//MTU0 initialization
	init_MTU0();
	//MTU0 count start
	start_MTU0();

}
void sta_MTU1(void)
{
	//MTU1 initialization
	init_MTU1();
	//MTU1 count start
	start_MTU1();

}
void sta_MTU6(void)
{
	//MTU0 initialization
	init_MTU6();
	//MTU0 count start
	start_MTU6();
}
void sta_MTU7(void)
{
	//MTU7 initialization
	init_MTU7();
	//MTU7 count start
	start_MTU7();

}

// 送信機信号処理設定
void receiver_main(void)
{
	long i;
	//MTU2 initialization
	init_MTU2();
	init_MTU4();
	init_MTU8();
	init_MTU9();
	sta_MTU0();
	sta_MTU1();
	sta_MTU6();
	sta_MTU7();
	if(MTU8.TGRA>730){
		while(MTU8.TGRA>730){
			FR=Sl3;
			FL=Sl3;
			RR=Sl3;
			RL=Sl3;
		}
		for(i=0;i<=5000000;i++){
			FR=Sl3;
			FL=Sl3;
			RR=Sl3;
			RL=Sl3;
		}
	}
	for(i=0;i<=100000;i++);
	Org1=Yw1;
	MTU2flag=1;
	Org2=Pt2;
	MTU4flag=1;
	Org4=Rl4;
	MTU9flag=1;

}

void serial_g(long x,long y,long z)
{
	char detas[10];
	
	if(x<0){
		sendString("-");
	}
	itoa(x,detas);
	sendString(detas);
	sendString(",");
	if(y<0){
		sendString("-");
	}
	itoa(y,detas);
	sendString(detas);
	sendString(",");
	if(z<0){
		sendString("-");
	}
	itoa(z,detas);
	sendString(detas);
	sendString("\r");
	
}

// 送信機信号処理
void receiver_main_while(void)
{
	long x,y,z;
	
	FR=Sl3+Pt2-Rl4+Yw1;
	FL=Sl3+Pt2+Rl4-Yw1;
	RR=Sl3-Pt2-Rl4-Yw1;
	RL=Sl3-Pt2+Rl4+Yw1;
	
	
	if(FR>710)FR=700;
	if(FR<460)FR=460;
	if(FL>710)FL=700;
	if(FL<460)FL=460;
	if(RR>710)RR=700;
	if(RR<460)RR=460;
	if(RL>710)RL=700;
	if(RL<460)RL=460;
	
	x=X_gyro_esc();
	y=Y_gyro_esc();
	z=Z_gyro_esc();
	
	serial(x,y,z);
	
	if(x<500){
		FR=FR+100;
		RR=RR+100;
		//FL=FL-100;
		//RL=RL-100;
	}
	if(x<-500){
		FL=FL+100;
		RL=RL+100;
		//FR=FR-100;
		//RR=RR-100;
	}
	if(y<700){
		FR=FR+100;
		FL=FL+100;
		//RR=RR-100;
		//RL=RL-100;
	}
	if(y<-700){
		RR=RR+100;
		RL=RL+100;
		//FR=FR-100;
		//FL=FL-100;
	}
	
}

void fr1(void)
{
	//FR1
	MTU7.TGRB=FR;
}

void rl2(void)
{
	//RL2
	MTU6.TGRB=RL;
}

void fl3(void)
{
	//FL3
	MTU1.TGRB=FL;
}

void rr4(void)
{
	//RR4
	MTU0.TGRB=RR;
}

void ch1(void)
{
	//1ch
	if(MTU2.TGRA<800){
		if(MTU2flag==0){
			Yw1=MTU2.TGRA;
		}
		else{		
			Yw1=MTU2.TGRA-Org1;
		}
	}
}

void ch2(void)
{
	//2ch
	if(MTU4.TGRA<800){
		if(MTU4flag==0){
			Pt2=MTU4.TGRA;
		}
		else{
			Pt2=MTU4.TGRA-Org2;
		}
	}
}

void ch3(void)
{
	//3ch
	if(MTU9.TGRA<800){
		if(MTU9flag==0){
			Rl4=MTU9.TGRA;
		}
		else{
			Rl4=MTU9.TGRA-Org4;
		}
	}
}

void ch4(void)
{
	//4ch
	if(MTU8.TGRA<800){
		Sl3=MTU8.TGRA;
	}
}




