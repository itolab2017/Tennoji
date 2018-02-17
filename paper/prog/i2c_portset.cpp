#include "CMT.h"
#include "vect.h"
#include "typedefine.h"
#include "iodefine.h"

void i2c_portset(void)
{
	PORTD.DDR.BYTE=0xff;
	PORTD.DR.BYTE=0x00;
	
	/*port set*/
	PORT1.DDR.BIT.B3=0;
	PORT1.DDR.BIT.B2=0;
	PORT1.ICR.BIT.B3=1;
	PORT1.ICR.BIT.B2=1;
}

void time_CMT0(void)
{
	MSTP(CMT0)=0;
	
	CMT0.CMCR.BIT.CKS=1;
	CMT0.CMCOR=37500;		//0.05s?
	CMT0.CMCR.BIT.CMIE=1;
		
	IEN(CMT0,CMI0)=1;
	IPR(CMT0,CMI0)=1;
	
	CMT.CMSTR0.BIT.STR0=1;
	
}
