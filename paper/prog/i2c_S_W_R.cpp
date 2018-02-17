#include "iodefine.h"

// �W���C�����[�h�ݒ�A�h���X���M
void gyro_set()
{
	
	// i2c �o�X�r�W�[�A�G���v�e�B����
	while(RIIC0.ICCR2.BIT.BBSY==1);
	
	// �X�^�[�g�R���f�B�V�������s
	RIIC0.ICCR2.BIT.ST=1;
	
	if(RIIC0.ICSR2.BIT.NACKF==0)
	{
		// �G���v�e�B�t���O
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		// ���M���[�h�A�h���X���M
		RIIC0.ICDRT=0xd2;
		
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		// �f�[�^�A�h���X�w��
		RIIC0.ICDRT=0x20;
		
		while(RIIC0.ICSR2.BIT.TDRE==0)PORTD.DR.BYTE=0x02;	
		
		// �f�[�^���M
		RIIC0.ICDRT=0x8f;
		
		while(RIIC0.ICSR2.BIT.TEND==0)PORTD.DR.BYTE=0x01;
				
		// �X�g�b�v����
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
	
	// ���̒ʐM�ւ̏���
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
}

// ���W�X�^�A�h���X���M
void write_addr(unsigned char addr)
{
	// i2c �o�X�r�W�[�A�G���v�e�B����
	while(RIIC0.ICCR2.BIT.BBSY==1);
	
	// �X�^�[�g�R���f�B�V�������s
	RIIC0.ICCR2.BIT.ST=1;
	
	// �G���v�e�B�t���O
	while(RIIC0.ICSR2.BIT.TDRE==0);
	
	// ���M���[�h�A�h���X���M
	RIIC0.ICDRT=0xd2;
	
	while(RIIC0.ICSR2.BIT.TDRE==0);
	
	if(RIIC0.ICSR2.BIT.NACKF==0){
		
		// �f�[�^�A�h���X�w��
		RIIC0.ICDRT=addr;
		while(RIIC0.ICSR2.BIT.TDRE==0);
		
		while(RIIC0.ICSR2.BIT.TEND==0);
		
		// �X�g�b�v����
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
	}
	
	else if(RIIC0.ICSR2.BIT.NACKF==1)
	{
		
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
	}
	
	while(RIIC0.ICSR2.BIT.STOP==0);
		
	// ���̒ʐM�ւ̏���
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
}

// �f�[�^�����炤
char read_data(char deta)
{
	
	// �}�X�^��M�J�n
	while(RIIC0.ICCR2.BIT.BBSY==1);
	RIIC0.ICCR2.BIT.ST=1;
	
	while(RIIC0.ICSR2.BIT.TDRE==0);
		
	// ��M���[�h�A�h���X���M
	RIIC0.ICDRT=0xd3;
	while(RIIC0.ICSR2.BIT.RDRF!=1);
	
	// �f�[�^��M����
	if(RIIC0.ICSR2.BIT.NACKF==0)
	{
		RIIC0.ICMR3.BIT.WAIT=1;
		RIIC0.ICMR3.BIT.RDRFS=1;
		RIIC0.ICMR3.BIT.ACKBT=1;
		
		// �_�~�[��M
		deta=RIIC0.ICDRR;
		
		while(RIIC0.ICSR2.BIT.RDRF!=1);
		
		// �X�g�b�v����
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
		
		// �f�[�^��M
		deta=RIIC0.ICDRR;
		
		RIIC0.ICMR3.BIT.ACKBT=1;
		RIIC0.ICMR3.BIT.WAIT=0;
		
	}
	
	else if(RIIC0.ICSR2.BIT.NACKF==1)
	{
		RIIC0.ICSR2.BIT.STOP=0;
		RIIC0.ICCR2.BIT.SP	=1;
		
		// �_�~�[��M
		deta=RIIC0.ICDRR;
	}
		
	while(RIIC0.ICSR2.BIT.STOP==0);
	
	// ���̒ʐM�ւ̏���
	RIIC0.ICSR2.BIT.NACKF=0;
	RIIC0.ICSR2.BIT.STOP=0;
	
	return(deta);
}
