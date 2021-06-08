/***************************************************************************
 *            dcprotocol.c
 *
 *  пон септембар 28 17:37:52 2020
 *  Copyright  2020  NanoPi Developer
 *  <user@host>
 ****************************************************************************/

#include<stdio.h>
#include<stdbool.h>


int receiveStateMachine( unsigned char *inbuff, int inbuflen, unsigned char *retbuff, unsigned int *retlen)
{
	static unsigned int state=0;
	static  int startflagindex = 0;
	unsigned int a;
	unsigned int b;
	static int reccmdlen = 0;
    bool startflag;
	static unsigned char receivebuffer[512]; 
	static unsigned int cmdlen = 0;
	int retvalue;

	retvalue = 0;
	// frst copy currend segment at end of buffer
	for(a = 0; a < inbuflen; a++)
	{
		receivebuffer[reccmdlen+a] = inbuff[a];
	}
    reccmdlen = reccmdlen + inbuflen; 
	
	switch(state)
	{
		case 0:
			// search for start flag
			startflagindex = 0;
			startflag = false;
			for (a = 0; (a < reccmdlen) && (startflag == false); a++)
			{
				if ( receivebuffer[a] == 0xfe  ) 
				{
					startflag = true;
					break;
				}
			}
			if (startflag != true) 
			{
				for ( b=0; b < reccmdlen; b++) receivebuffer[a] = 0;
				reccmdlen = 0;
				startflagindex = 0;
				break;
			}
			startflagindex = a;
			state = 1;
		case 1:
		    // search for length
			if ((reccmdlen - startflagindex) < 4)
			{
				// still do not have length field
				break;
			}
			// received length field
			cmdlen =	
				((unsigned int)receivebuffer[startflagindex+2]) * 256 + 
				((unsigned int)receivebuffer[startflagindex+3]);

			state = 2;
		case 2:
			if (cmdlen + 4 + startflagindex > reccmdlen) break;
		    // entire command is in buffer
			//printf("Received package \n");
			int i;
			unsigned int chksum;

			// Here change check sum
			chksum = 0;
			for(a = startflagindex + 1; a <= (startflagindex + cmdlen + 3); a++)
			{
				chksum += receivebuffer[a];
			}

			chksum = (chksum  & 0xFF) ^ 0xFF;
			if (chksum != receivebuffer[startflagindex + cmdlen + 4])
			{
				cmdlen += 4;// DC bug fixing
			}
            /*
			if (chksum != receivebuffer[startflagindex + cmdlen + 4])
			{
				printf("Check Sum is NotGood");
				startflagindex = 0;
				cmdlen = 0;
				reccmdlen = 0;
				state = 0;
				break;
			}
			*/
			i=0;
			for (a = startflagindex+5; a <= (startflagindex + cmdlen + 4); a++)
			{

				if ( receivebuffer[a] == 0xC4 ||
				     receivebuffer[a] == 0xC5 )
				{

					if ( receivebuffer[a + 1] == 0x86 )
					{
						retbuff[i++] = 29;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0x87 )
					{
						retbuff[i++] = 28;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0x8C )
					{
						retbuff[i++] = 31;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0x8D )
					{
						retbuff[i++] = 30;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0x90 )
					{
						retbuff[i++] = 27;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0x91 )
					{
						retbuff[i++] = 26;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0xA0 )
					{
						retbuff[i++] = 25;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0xA1 )
					{
						retbuff[i++] = 24;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0xBD )
					{
						retbuff[i++] = 23;
						a++;
					}
					else if ( receivebuffer[a + 1] == 0xBE )
					{
						retbuff[i++] = 22;
						a++;
					}
					
							
				}
				else
				{
					retbuff[i++] = receivebuffer[a];
				}				
			}
			retbuff[i-1] = 0; //check sum izbaci
			//retbuff[startflagindex+5+cmdlen]=0;
			//printf("\nReceived package \n");	
			(*retlen) = cmdlen;

			retvalue = receivebuffer[startflagindex + 4];
			for (a = 0; a <= (startflagindex + cmdlen + 5); a++)
			{
				receivebuffer[a] = 0;
			}
			startflagindex = 0;
			cmdlen = 0;
			reccmdlen = 0;
			state = 0;
			break;
		default:
		printf("No such state \n");		
			
	}


	return retvalue;

	
}