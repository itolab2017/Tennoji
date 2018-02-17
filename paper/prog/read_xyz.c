
#include "iodefine.h"
#include "Deta.h"
#include "CALC.h"

unsigned char status;
long x_deta_ave,y_deta_ave,z_deta_ave;
int c;

void read_xyz()
{
	//xlデータ受信
	write_addr(0x28);
	Xl=read_data();
	
	//xhデータ受信
	write_addr(0x29);
	Xh=read_data();
	
	//ylデータ受信
	write_addr(0x2a);
	Yl=read_data();
	
	//yhデータ受信
	write_addr(0x2b);
	Yh=read_data();
	
	//zlデータ受信
	write_addr(0x2c);
	Zl=read_data();
	
	//zhデータ受信
	write_addr(0x2d);
	Zh=read_data();
	
	//PORTD.DR.BYTE=0x03;
}

//キャリブレーション用データ
void deta_HL_ave(void)
{
	//データを合わせる
	x_deta=Xh*256+Xl;
	y_deta=Yh*256+Yl;
	z_deta=Zh*256+Zl;
	
	x_deta=x_deta-65536/2;
	y_deta=y_deta-65536/2;
	z_deta=z_deta-65536/2;
	
}

//データを合わせた時の値を見る
void deta_cross(long x,long y,long z)
{
	char deta[10];

	itoa(x,deta);
	sendString(deta);
	sendString(",");
	itoa(y,deta);
	sendString(deta);
	sendString(",");
	itoa(z,deta);
	sendString(deta);
	sendString("\r");
}

//積分結果を見る
void serial(long x,long y,long z)
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


//積分するよ？
void integral(long x,long y,long z)
{
	long x_deta_before,y_deta_before,z_deta_before;
	long Sum_x,Sum_y,Sum_z;
	long dx,dy,dz;
	long i;
	
	
	//台形面積求める
	dx=((x_deta_before+x)/2)/30;
	dy=((y_deta_before+y)/2)/30;
	dz=((z_deta_before+z)/2)/30;
	
	//前のデータ保存
	x_deta_before=x;
	y_deta_before=y;
	z_deta_before=z;
	
	//角度計算
	x_de=dx+x_de;
	y_de=dy+y_de;
	z_de=dz+z_de;

	PORTD.DR.BYTE= 2;
	
	//角度データを見る
	serial(x_de,y_de,z_de);
	
}

//安定化制御用のデータを合わせる
void deta_HL(void)
{
	long x_d,y_d,z_d;
	
	//データを合わせる
	x_deta=Xh*256+Xl;
	y_deta=Yh*256+Yl;
	z_deta=Zh*256+Zl;
	
	x_d=x_deta-x_deta_ave;
	y_d=y_deta-y_deta_ave;
	z_d=z_deta-z_deta_ave;
	
	//台形積分する
	integral(x_d,y_d,z_d);
	
	//データを見る
	//deta_cross(x_d,y_d,z_d);
	
	
}

//受信データを見る関数
void deta_look(void)
{
	char deta[10];
	
	itoa(Xl,deta);
	sendString(deta);
	sendString(",");
	itoa(Yl,deta);
	sendString(deta);
	sendString(",");
	itoa(Zl,deta);
	sendString(deta);
	sendString(",");
	itoa(Xh,deta);
	sendString(deta);
	sendString(",");
	itoa(Yh,deta);
	sendString(deta);
	sendString(",");
	itoa(Zh,deta);
	sendString(deta);
	sendString("\r");

}

//キャリブレーション時のデータを見る
void deta_ave(unsigned short x,unsigned short y,unsigned short z)
{
	char deta[10];

	itoa(x,deta);
	sendString(deta);
	sendString(",");
	itoa(y,deta);
	sendString(deta);
	sendString(",");
	itoa(z,deta);
	sendString(deta);
	sendString("\r");
}

void CTRL_REG1(void)
{
	char b[100];
	itoa(status,b);
	sendString(b);
	sendString("\r");
}

//データキャリブレーション
void cya(void)
{
	/*unsigned short x_a=9999;
	unsigned short y_a=9999;
	unsigned short z_a=9999;*/
	long x,y,z;
	int count=1;
	long cou=0;
	x=0;
	y=0;
	z=0;
	x_deta_ave=0;
	y_deta_ave=0;
	z_deta_ave=0;
	
	while(count<=10000){
		do{
			//ステータスアドレス送信
			write_addr(0x20);
			
			//ステータスデータ受信
			status=read_data();
		
			//ステータスレジスタ見る
			//CTRL_REG1();
			
		}while(status&0x08!=0x08);
	
		//各xyzデータ受信
		read_xyz();
			
		//deta_look();
	
		//HとLのデータを合わせる
		deta_HL_ave();
		//
		if(count>=3001){
			//deta_cross();
			x=x+x_deta;
			y=y+y_deta;
			z=z+z_deta;
			cou++;
		}
		
		if(count==10000){
			x_deta_ave=x/cou;
			y_deta_ave=y/cou;
			z_deta_ave=z/cou;
			
			/*x_a=(unsigned short)x_deta_ave;
			y_a=(unsigned short)y_deta_ave;
			z_a=/*cou;(unsigned short)z_deta_ave;*/
			
		}
		count++;
		
	}
	//deta_ave(x_a,y_a,z_a);
}

