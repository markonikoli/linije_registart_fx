/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2020 NanoPi Developer <nanopi@nanopi-HP-Laptop-15-db1xxx>
 * 
 * TestComBX6K1 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TestComBX6K1 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <sys/poll.h>
#include <time.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dcprotocol.h>

int fd;
int fd2;
unsigned short tabel_CRC16[256] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};
unsigned short my_CRC(unsigned char *data, int size) 
{
    unsigned short tempcrc = 0;
    unsigned short temp = 0;
    int i =0;
    for (i=0; i<size; i++)
	{
        temp = ((tempcrc & 0x00ff) ^ (data[i] & 0x00ff));
        tempcrc = ((tempcrc>>8) & 0xff) ^ tabel_CRC16[temp];
    }
    return tempcrc;
}
int openport()
{
   	int fd;/*File Descriptor*/
	

	//printf("\n +----------------------------------+");
	//printf("\n |        Serial Port Read          |");
	//printf("\n +----------------------------------+");
	/*------------------------------- Opening the Serial Port -------------------------------*/

	/* Change /dev/ttyS1 to the one corresponding to your system */

   	fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY);	
	/* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
    /* O_RDWR   - Read/Write access to serial port       */
    /* O_NOCTTY - No terminal will control the process   */
    /* Open in blocking mode,read will wait              */
								                                       			
    if(fd == -1)						/* Error Checking */
        printf("\n  Error! in Opening ttyS1  ");
    else
		printf("\n  ttyS1 Opened Successfully ");

    /*---------- Setting the Attributes of the serial port using termios structure --------- */

	struct termios SerialPortSettings;	/* Create the structure                          */

	tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */



	/* Setting the Baud rate */
	cfsetispeed(&SerialPortSettings,B57600); /* Set Read  Speed as 9600                       */
	cfsetospeed(&SerialPortSettings,B57600); /* Set Write Speed as 9600                       */


	/* 8N1 Mode */
	SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */


	SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 


	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

		

	/* Setting Time outs */
	SerialPortSettings.c_cc[VMIN] = 10; /* Read at least 10 characters */
	SerialPortSettings.c_cc[VTIME] = 60; /* Wait indefinetly if 0. if 60 than wait 6 seconds  */





	if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	    printf("\n  ERROR ! in Setting attributes");
	else
        printf("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none");

			

    /*----------------------- Read data from serial port ---------------------*/



	tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */
          //ioctl(fd, TCFLSH, 0);
          //ioctl(fd, TCFLSH, 1);
    usleep(1000);
    return fd;

}
int openport2()
{
   	int fd;/*File Descriptor*/
	

	//printf("\n +----------------------------------+");
	//printf("\n |        Serial Port Read          |");
	//printf("\n +----------------------------------+");
	/*------------------------------- Opening the Serial Port -------------------------------*/

	/* Change /dev/ttyS1 to the one corresponding to your system */

   	fd = open("/dev/ttyUSB1",O_RDWR | O_NOCTTY);	
	/* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
    /* O_RDWR   - Read/Write access to serial port       */
    /* O_NOCTTY - No terminal will control the process   */
    /* Open in blocking mode,read will wait              */
								                                       			
    if(fd == -1)						/* Error Checking */
        printf("\n  Error! in Opening ttyS1  ");
    else
		printf("\n  ttyS1 Opened Successfully ");

    /*---------- Setting the Attributes of the serial port using termios structure --------- */

	struct termios SerialPortSettings;	/* Create the structure                          */

	tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */



	/* Setting the Baud rate */
	cfsetispeed(&SerialPortSettings,B19200); /* Set Read  Speed as 9600                       */
	cfsetospeed(&SerialPortSettings,B19200); /* Set Write Speed as 9600                       */


	/* 8N1 Mode */
	SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */


	SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 


	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

		

	/* Setting Time outs */
	SerialPortSettings.c_cc[VMIN] = 1; /* Read at least 10 characters */
	SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly if 0. if 60 than wait 6 seconds  */





	if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	    printf("\n  ERROR ! in Setting attributes");
	else
        printf("\n  BaudRate = 19200 \n  StopBits = 1 \n  Parity   = none");

			

    /*----------------------- Read data from serial port ---------------------*/



	tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */
          //ioctl(fd, TCFLSH, 0);
          //ioctl(fd, TCFLSH, 1);
    usleep(1000);
    return fd;

}


#if 0

int main()
{
        unsigned short arraylen;
        unsigned int bytes_written;
        unsigned int bytes_read;
        unsigned int bytes_read2;
        unsigned short crc_calculated;
        int fd;
        int a;
        unsigned char sendcommand[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, // 6 
            0xa5, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // 17 
            0x61, 0x02, 0x34+ 0x7c, 0x00, 0xa3, 0x06, 0x01, 0x00, 0x00, 0x00, 0x01,//28 
            0x21, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00,//39 
            0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01,//50 
            0x00, 0x00, 0x0a, 0x13+ 0x79, 0x00, 0x00, 0x00, //57
            '\\' , 'C' , '1' ,//60
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            'B' , 'U' , 'S' , 'P' , 'L' , 'U' , 'S' , ' ' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,//92 
            '\\' , 'C' , '2' ,//95
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , 'I' , 'N' ,
            'F' , 'O' , ' ' , 'S' , 'I' , 'S' , 'T' , 'E' ,
            'M' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,//127
            '\\' , 'C' , '3' ,//130
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            '*' , '0' , '1' , '1' , '*' , '7' , '2' , '2' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,//162 
            '\\' , 'C' , '4',//165
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , 'J' , 'u' ,
            'l' , 'i' , 'n' , 'o' , ' ' , 'b' , 'r' , 'd' ,
            'o' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,
            ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,//197

            0x60, 0x33, 0x5a};
        unsigned char readed[256];

        fd = openport();
        printf("Port opened\n");

        arraylen = sizeof(sendcommand);





        crc_calculated = my_CRC(&(sendcommand[8]), sizeof(sendcommand) - 11);
        printf("%x\n",crc_calculated);


        sendcommand[sizeof(sendcommand)-3] = (unsigned char)(crc_calculated & 0xFF);
        sendcommand[sizeof(sendcommand)-2] = (unsigned char)(( crc_calculated >> 8 ) & 0xFF);





        usleep(100);
        tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer*/

        printf("Sending to controller\n");
        bytes_written = write(fd, sendcommand, (sizeof(sendcommand)));

        printf("Sent to controller %d\n", bytes_written);
        printf("Reading from controller\n");
        bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
        bytes_read = read(fd,readed,256);

        printf("Readed from controller %d\n", bytes_read);
        for (a = 0; a < bytes_read; a++)
        {
           printf("%02x ",readed[a]);
        }

        printf("\n");

        close(fd);

        return (0);
}
#endif

void dynamicAreaDisplayText1(char *number, char *line01, char *line02)
{

	unsigned int bytes_written;


	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];

	
	int a;
	
		unsigned char sendcommand11[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 
	    0xa5, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	    0x61, 0x02, 0xB1, 0x00, 
		0xa3, 0x06, 0x01, 0x01, 0x00, 0xff, 
		0x03, //number of zones updated this time
	    0x3E, 0x00,//AreaDataLen0 
		0x06, //AreaType
		0x10, 0x00, //AreaX
		0x00, 0x00, //AreaY
		0x34, 0x00, //AreaWtdth
		0x20, 0x00, //AreaHeight
	    0x00, //DynamicAreaLoc 
		0x00, //Lines_sizes
		0x00, //RunMode
		0x02, 0x00,  //Timeout
		0x00,  //SoundMode
		0x00, // ExtendParaLen   
		0x00,  //TypeSetting
		0x02,  //TextAlignment
		0x02, //SingleLine
		0x01, //NewLine
	    0x00, //DisplayMode
		0x00, //ExitMode
		0x00, //Speed
		//0x0a, //StayTime
		0x23, 0x00, 0x00, 0x00, //57
	    '\\', 'F' , 'E' , '0' , '0' , '1', '\\' , 'C' , '5' , //66
	    ' ' , ' ' , ' ' , 'Z' , 'e' , 'l' , 'e' , 'z' , 'n' , 'i' , //76
		'c' , 'k' , 'a' , ' ' , 's' , 't' , 'a' , 'n' , //84
		'i' , 'c' , 'a' , ' ' , ' ' , ' ' , ' ' , ' ' ,	//92
	    // next 2 bajts are data area number of by  ,tes after this two bytes 
		0x3E, 0x00,//AreaDataLen2 
		0x08, //AreaType
		0x10, 0x00, //AreaX
		0x20, 0x00, //AreaY
		0x34, 0x00, //AreaWtdth (bytes if higher byte is 0)
		0x20, 0x00, //AreaHeight
	    0x01, //DynamicAreaLoc 
		0x00, //Lines_sizes
		0x00,  //RunMode
		0x02, 0x00,  //Timeout
		0x00,  //SoundMode
		0x00,  //ExtendParaLen     
		0x00,  //TypeSetting
		0x02, //TextAlignment
		0x02, //SingleLine
		0x01, //NewLine
	    0x00, //DisplayMode
		0x00, //ExitMode
		0x00, //Speed 115
		//0x10, //StayTime
		0x23, 0x00, 0x00, 0x00, //121
	    '\\', 'F' , 'E' , '0' , '0' , '1', '\\' , 'C' , '5' , //130
	    ' ' , ' ' , ' ' , ' ' , ' ' , 'B' , 'e' , 'o' , 'g' , 'r' , //140
		'a' , 'd' , ' ' , 'C' , 'e' , 'n' , 't' , 'a' , //148
		'r' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,	//156
		// next 2 bajts are data area number of bytes after this two bytes 
		0x30-0x08, 0x00,//AreaDataLen3 158
		0x09, //AreaType 159
		0x00, 0x00, //AreaX 161
		0x00, 0x00, //AreaY 163
		0x10, 0x00, //AreaWtdth 165
		0x40, 0x00, //AreaHeight 167
	    0x02, //DynamicAreaLoc 168
		0x00, //Lines_sizes 169
		0x00,  //RunMode 170
		0x02, 0x00, //Timeout 172
		0x00,  //SoundMode 173
		0x00,  //ExtendParaLen 174   
		0x00, //TypeSetting 175
		0x02, //TextAlignment 176
		0x02, //SingleLine 177
		0x01, //NewLine 178
	    0x00, //DisplayMode 179
		0x00, //ExitMode 180
		0x0a, //Speed 181
		//0x10, //StayTime
		0x10+ 0x07 -0x0a, 0x00, 0x00, 0x00, //DataLen 185
	    '\\', 'F' , 'E' , '0' , '0' , '3', '\\' , 'C' , '1' , //194
	    'E' , '6' , '6' , '6', //198
		//'v' , 'r' , 't' , 'a' , ' ' , 
	    //'L' , 'i' , 'n' , 'i' , 
			
	    0x60, 0x33, 0x5a, 0x00, 0x00}; //203


	
	//arraylen = sizeof(sendcommand11);

    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );

	for(a = 0; a <= 23; a++)
	{
		sendcommand11[a+67] = line01[a];
	}

	for(a = 0; a <= 23; a++)
	{
		sendcommand11[a+131] = line02[a];
	}

	for(a = 0; a <= 3; a++)
	{
		sendcommand11[a+195] = number[a];
	}
	

	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++; 
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;


    //printf("11CRCL = %d",sendcommand11[sizeof(sendcommand11)-3]);
    //printf("11CRCH = %d",sendcommand11[sizeof(sendcommand11)-2]);

    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

    //tcflush(fd, TCIFLUSH);   

	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));
	
	printf("Sent to controller %d\n", bytes_written);
	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("\n");
	*/

}

void dynamicAreaDisplayText2(char *number, char *line01, char *line02)
{

	unsigned int bytes_written;


	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];

	
	int a;

	unsigned char sendcommand11[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, //6
	    0xa5, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, //17
	    0x61, 0x02, 0xB1-0x40, 0x00, //command length   21
		0xa3, 0x06, 0x01, 0x01, 0x00, 0xff, //27
		0x02, //number of zones updated this time 28
	    0x3E, 0x00,//AreaDataLen0 30
		0x06, //AreaType 31
		0x10, 0x00, //AreaX 33
		0x00, 0x00, //AreaY 35
		0x34, 0x00, //AreaWtdth 37
		0x40, 0x00, //AreaHeight 39
	    0x00, //DynamicAreaLoc 40
		0x00, //Lines_sizes 41
		0x00, //RunMode 42
		0x02, 0x00,  //Timeout  44
		0x00,  //SoundMode 45
		0x00, // ExtendParaLen 46   
		0x00,  //TypeSetting 47
		0x02,  //TextAlignment 48
		0x02, //SingleLine  49
		0x01, //NewLine 50
	    0x00, //DisplayMode 51
		0x00, //ExitMode 52
		0x00, //Speed 53
		//0x0a, //StayTime
		0x23, 0x00, 0x00, 0x00, // 57
	    '\\', 'F' , 'E' , '0' , '0' , '3', '\\' , 'C' , '5' , // 66
	    'Z' , 'e' , 'l' , 'e' , 'z' , 'n' , 'i' , 'c' , 'k' , 'a' , // 76
		' ' , 'S' , 't' , 'a' , 'n' , 'i' , 'c' , 'a' , // 84
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,	// 92
		// next 2 bajts are data area number of bytes after this two bytes 
		0x30-0x08, 0x00,//AreaDataLen3 94
		0x09, //AreaType 95
		0x00, 0x00, //AreaX 97
		0x00, 0x00, //AreaY 99
		0x10, 0x00, //AreaWtdth 101
		0x40, 0x00, //AreaHeight 103
	    0x02, //DynamicAreaLoc 104
		0x00, //Lines_sizes 105
		0x00,  //RunMode 106
		0x02, 0x00, //Timeout 108
		0x00,  //SoundMode 109
		0x00,  //ExtendParaLen 110   
		0x00, //TypeSetting 111
		0x02, //TextAlignment 112
		0x02, //SingleLine 113
		0x01, //NewLine 114
	    0x00, //DisplayMode 115
		0x00, //ExitMode 116
		0x0a, //Speed 117
		//0x10, //StayTime
		0x10+ 0x07 -0x0a, 0x00, 0x00, 0x00, //DataLen 121
	    '\\', 'F' , 'E' , '0' , '0' , '3', '\\' , 'C' , '1' , //130
	    'E' , '6' , '6' , '6', //134
		//'v' , 'r' , 't' , 'a' , ' ' , 
	    //'L' , 'i' , 'n' , 'i' , 
			
	    0x60, 0x33, 0x5a, 0x00, 0x00}; //139

	
	//arraylen = sizeof(sendcommand11);

    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );

	for(a = 0; a<= 23; a++)
	{
		sendcommand11[a+67] = line01[a];
	}


	for(a = 0; a<= 3; a++)
	{
		sendcommand11[a+131] = number[a];
	}

	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;


    //printf("11CRCL = %d",sendcommand11[sizeof(sendcommand11)-3]);
    //printf("11CRCH = %d",sendcommand11[sizeof(sendcommand11)-2]);

    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

    //tcflush(fd, TCIFLUSH);   

	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));
	
	printf("Sent to controller %d\n", bytes_written);
	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("\n");
	*/
	

	
}

//back buss display
void dynamicAreaDisplayText3(char *number, char *line01, char *line02)
{

	unsigned int bytes_written;
	//unsigned int bytes_read;

	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	
	//unsigned char readed[256];
    unsigned char tocontroller[1024];

	
	int a;

	unsigned char sendcommand11[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, //6
	    0xa5, 0x03, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, //17
	    0x61, 0x02, 0xB1-0x40-0x40, 0x00, //command length   21
		0xa3, 0x06, 0x01, 0x01, 0x00, 0xff, //27
		0x01, //number of zones updated this time 28
		// next 2 bajts are data area number of bytes after this two bytes 
		0x30-0x08, 0x00,//AreaDataLen3 30
		0x09, //AreaType 31
		0x00, 0x00, //AreaX 33
		0x00, 0x00, //AreaY 35
		0x10, 0x00, //AreaWtdth 37
		0x40, 0x00, //AreaHeight 39
	    0x02, //DynamicAreaLoc 40
		0x00, //Lines_sizes 41
		0x00,  //RunMode 42
		0x02, 0x00, //Timeout 44
		0x00,  //SoundMode 45
		0x00,  //ExtendParaLen 46   
		0x00, //TypeSetting 47
		0x02, //TextAlignment 48
		0x02, //SingleLine 49
		0x01, //NewLine 50
	    0x00, //DisplayMode 51
		0x00, //ExitMode 52
		0x0a, //Speed 53
		//0x10, //StayTime
		0x10+ 0x07 -0x0a, 0x00, 0x00, 0x00, //DataLen 57
	    '\\', 'F' , 'E' , '0' , '0' , '3', '\\' , 'C' , '1' , //66
	    'E' , '6' , '6' , '6', //70
		//'v' , 'r' , 't' , 'a' , ' ' , 
	    //'L' , 'i' , 'n' , 'i' , 
			
	    0x60, 0x33, 0x5a, 0x00, 0x00}; //139

	
	//arraylen = sizeof(sendcommand11);

    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );

	//for(a = 0; a<= 23; a++)
	//{
	//	sendcommand11[a+67] = line01[a];
	//}


	for(a = 0; a<= 3; a++)
	{
		sendcommand11[a+67] = number[a];
	}

	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;


    //printf("11CRCL = %d",sendcommand11[sizeof(sendcommand11)-3]);
    //printf("11CRCH = %d",sendcommand11[sizeof(sendcommand11)-2]);

    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

	//usleep(100);

    //tcflush(fd, TCIFLUSH);   


	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));
	
	printf("Sent to controller %d\n", bytes_written);

	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("\n");
	*/
	

	
}



void setDisplayTime()
{

	unsigned int bytes_written;


	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];


	//int a;

	unsigned char sendcommand11[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, //6
	    0xa5, 0x04, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, //17
	    0x61, 0x02, 0x0d, 0x00, //command length   21
		0xa2, 0x03, 0x01, 0x00, 0x00, //26
		0x20, 0x21, 0x10, 0x22, 0x15, 0x02, 0x00, 0x04,
	    0x60, 0x33, 0x5a, 0x00, 0x00}; //139

	
	//arraylen = sizeof(sendcommand11);
	printf("Postavljanje vremena\n");
    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );

	//for(a = 0; a<= 23; a++)
	//{
	//	sendcommand11[a+67] = line01[a];
	//}


	//for(a = 0; a<= 3; a++)
	//{
	//	sendcommand11[a+67] = number[a];
	//}

	time_t rawtime;
	struct tm *ptm;
	rawtime = time(NULL);
	ptm = localtime(&rawtime);

	int year1000 = (ptm->tm_year + 1900) / 1000;
	int year100  = ((ptm->tm_year + 1900) - year1000 * 1000) / 100;
	int year10  = ((ptm->tm_year + 1900) - year1000 * 1000 - year100 * 100) / 10;
	int year1  = ((ptm->tm_year + 1900) - year1000 * 1000 - year100 * 100 - year10 * 10) / 1;
	
	int month10  = (ptm->tm_mon + 1) / 10;
	int month1  = ((ptm->tm_mon + 1) - month10 * 10) / 1;
	
	int day10  = ptm->tm_mday / 10;
	int day1  = (ptm->tm_mday - day10 * 10) / 1;
	
	int hour10  = ptm->tm_hour / 10;
	int hour1  = (ptm->tm_hour - hour10 * 10) / 1;

	int min10  = ptm->tm_min / 10;
	int min1  = (ptm->tm_min - min10 * 10) / 1;
	
	int sec10  = ptm->tm_sec / 10;
	int sec1  = (ptm->tm_sec - sec10 * 10) / 1;

	int wday  = (ptm->tm_wday == 0 ? 7 : ptm->tm_wday) ;

	

	sendcommand11[28] = year1000 * 16 + year100;
	sendcommand11[27] = year10 * 16 + year1;
	sendcommand11[29] = month10 * 16 + month1;
	sendcommand11[30] = day10 * 16 + day1;
	sendcommand11[31] = hour10 * 16 + hour1;
	sendcommand11[32] = min10 * 16 + min1;
	sendcommand11[33] = sec10 * 16 + sec1;
	sendcommand11[34] = wday;

	printf("Year High %2X\n", sendcommand11[28]);
	printf("Year Low  %2X\n", sendcommand11[27]);
	printf("Month     %2X\n", sendcommand11[29]);
	printf("Day       %2X\n", sendcommand11[30]);
	printf("Hour      %2X\n", sendcommand11[31]);
	printf("Minutes   %2X\n", sendcommand11[32]);
	printf("Seconds   %2X\n", sendcommand11[33]);
	printf("Week day  %2X\n", sendcommand11[34]);
	
	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;


    //printf("11CRCL = %d",sendcommand11[sizeof(sendcommand11)-3]);
    //printf("11CRCH = %d",sendcommand11[sizeof(sendcommand11)-2]);

    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

    //tcflush(fd, TCIFLUSH);   

	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));
	
	printf("Sent to controller %d\n", bytes_written);

	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("\n");
	*/
	

	
}




// inside bus display
void dynamicAreaDisplayText4(char *number, char *line01, char *line02)
{

	unsigned int bytes_written;


	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];

	
	int a;
	
		unsigned char sendcommand11[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, //6
	    0xa5, 0x04, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, //17
	    0x61, 0x02, 0xB1-0x2A+0x6+0x6, 0x00, //21
		0xa3, 0x06, 0x01, 0x01, 0x00, 0xff, //27
		0x02, //number of zones updated this time 28
	    0x3E + 0x06, 0x00,//AreaDataLen0 30
		0x06, //AreaType 31
		0x00, 0x00, //AreaX 33 in bytes
		0x00, 0x00, //AreaY 35
		0x20, 0x00, //AreaWtdth 37 in bytes
		0x10, 0x00, //AreaHeight 39
	    0x00, //DynamicAreaLoc 40
		0x00, //Lines_sizes 41
		0x00, //RunMode 42
		0x02, 0x00,  //Timeout 44
		0x00,  //SoundMode 45
		0x00, // ExtendParaLen 46  
		0x00,  //TypeSetting 47
		0x02,  //TextAlignment 48
		0x02, //SingleLine 49
		0x01, //NewLine 50
	    0x00, //DisplayMode 51
		0x00, //ExitMode 52
		0x00, //Speed 53
		//0x0a, //StayTime
		0x23+0x6, 0x00, 0x00, 0x00, //57
	    '\\', 'F' , 'E' , '0' , '0' , '0', '\\' , 'C' , '5' , //66
	    ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //76
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //84
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,	//92
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //98


	    // next 2 bajts are data area number of by  ,tes after this two bytes 
		0x3E + 0x06, 0x00,//AreaDataLen2 100
		0x07, //AreaType 101
		0x00, 0x00, //AreaX 103
		0x10, 0x00, //AreaY 105
		0x20, 0x00, //AreaWtdth (bytes if higher byte is 0) 107
		0x10, 0x00, //AreaHeight 109
	    0x01, //DynamicAreaLoc 110
		0x00, //Lines_sizes 111
		0x00,  //RunMode 112
		0x02, 0x00,  //Timeout 114
		0x00,  //SoundMode 115
		0x00,  //ExtendParaLen 116    
		0x00,  //TypeSetting 117
		0x02, //TextAlignment 118
		0x02, //SingleLine 119
		0x01, //NewLine 120
	    0x00, //DisplayMode 121
		0x00, //ExitMode 122
		0x00, //Speed 123
		//0x10, //StayTime
		0x23+0x6, 0x00, 0x00, 0x00, //127
	    '\\', 'F' , 'E' , '0' , '0' , '0', '\\' , 'C' , '5' , //136
	    ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //146
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //154
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' ,	//162
		' ' , ' ' , ' ' , ' ' , ' ' , ' ' , //168
		
		// next 2 bajts are data area number of bytes after this two bytes 			
	    0x60, 0x33, 0x5a, 0x00, 0x00}; //173


	
	//arraylen = sizeof(sendcommand11);

    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );

	for(a = 0; a <= 31; a++)
	{
		sendcommand11[a+67] = line01[a];
	}

	for(a = 0; a <= 31; a++)
	{
		sendcommand11[a+137] = line02[a];
	}

	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++; 
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;


    //printf("11CRCL = %d",sendcommand11[sizeof(sendcommand11)-3]);
    //printf("11CRCH = %d",sendcommand11[sizeof(sendcommand11)-2]);

    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

    //tcflush(fd, TCIFLUSH);   

	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));
	
	printf("Sent to controller %d\n", bytes_written);

	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("\n");
	*/

}

void specialDynamicAreaDorMatrix()
{

	unsigned int bytes_written;


	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];

	


    unsigned char sendcommand11[]={ 
		0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 
		0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0xFE, 0x02, 0x1D, 0x00, 
		0xa4, 0x01, 0x01, 0x00, 0x00, 
		0x00, 0x00, //Area X coordinate Unit bytes 
		0x00, 0x00, //Area Y coordinate Unit pixels
		0x08, 0x00, //Area W width, Unit: byte
		0x40, 0x00, //Area H height Unit pixels
		0x01,       //DataType 0-code format 1-dot matrix format 
		0x00,       //Pagetotal must be 0 for dot matrix format  
		0x02,       //RunState 
		0x0F, 0x00, //Timeout , units in seconds 
	    0x00,       //SingleLine, invalid in dot matrix, default 0 
		0x00,       //Line Sizes, invalid in dot matrix format 
		0x00,       //New Line  , invalid in dot matrix format 
		0x00, 0x00, //StayTime,  invalid in dot matrix format
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // reserved 
		0xfd, 0xc0, 0x5a, 0x00, 0x00};

	
	//arraylen = sizeof(sendcommand11);

    //printf("Duzina niza je 56\n");
	//printf("Arraylen duzina niza %d\n", arraylen);
	//printf("Izracunata duzina niza je %d\n", (int)(sizeof(sendcommand)-11) );


	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;



    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

    //tcflush(fd, TCIFLUSH);   

	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));

	//usleep(100);
	
	printf("Sent to controller %d\n", bytes_written);
	/*
	printf("Reading from controller\n");
    bzero(readed,sizeof(readed));
                    //printf("\nNow reading1\n");
    bytes_read = read(fd,readed,256);

	printf("Readed from controller %d\n", bytes_read);
    for (a = 0; a < bytes_read; a++)
	{
       printf("%02x ",readed[a]);
	}

	printf("Dotmatrix first command\n");

	
	usleep(100);
	printf("Dotmatrix first command exit\n");
	*/
}


void sendDotMatrixInformation()
{

	unsigned int bytes_written;

	unsigned short crc_calculated1;

    unsigned int crcindex = 0;
	unsigned int index = 0;
	unsigned int tocontrolerindex = 0;
	

    unsigned char tocontroller[1024];

	

	printf("Dot matrix function 2 begin\n");

	unsigned char sendcommand11[]={ 
		0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 
		0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0xFE, 0x02, 0x08, 0x02, 
		0xa4, 0x03, 0x01, 0x00, 0x00, 
		0x01, //Block flag, last block = 1, not last = 0
		0x00, 0x00, //Block address: every divided block's address
		// block data
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 
        0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,		
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		
		0xfd, 0xc0, 0x5a, 0x00, 0x00};

	



	crc_calculated1 = my_CRC(&(sendcommand11[8]), sizeof(sendcommand11) - 11 - 2);
    printf("Packet 1 crc %x\n",crc_calculated1);

    printf("%x\n",crc_calculated1);

    crcindex = sizeof(sendcommand11)-3-2;

    sendcommand11[crcindex] = (unsigned char)(crc_calculated1 & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = (unsigned char)(( crc_calculated1 >> 8 ) & 0xFF);
    crcindex++;
    sendcommand11[crcindex] = 0x5a;



    printf("11end fl %x\n",sendcommand11[crcindex]);//65

    tocontrolerindex = 0;
    for (index = 0; index < crcindex; index++)
	{

		if (index > 7)
		{
			
			if (sendcommand11[index] == 0xa5)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0xa6)
			{
				tocontroller[tocontrolerindex] = 0xa6;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5b)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x01;
				tocontrolerindex++;
			}
			else if (sendcommand11[index] == 0x5a)
			{
				tocontroller[tocontrolerindex] = 0x5b;
				tocontrolerindex++;
				tocontroller[tocontrolerindex] = 0x02;
				tocontrolerindex++;
			}
			else
			{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
			}
		}
		else
		{
				tocontroller[tocontrolerindex] = sendcommand11[index];
				tocontrolerindex++;
		}
	}

	tocontroller[tocontrolerindex] = sendcommand11[crcindex];//endflag

    printf("Sending to controller Command 1\n");

	
	//usleep(100);

    //tcflush(fd, TCIFLUSH);   


	bytes_written = write(fd, tocontroller, (tocontrolerindex+1));

	//usleep(1000);
	
	printf("Sent to controller %d\n", bytes_written);


	//usleep(100);

	
}

void formatDestination(char *intext, char *line1, char *line2)
{

	
	int init_size = strlen(intext);
	char delim[] = " ";
	char *ptr[20];
	char *token;
	int tokennumber=0;
	int i=0;
	int totallength = 0;

	char centeredline1[25];
	char centeredline2[25];

	token = strtok(intext, delim);
    ptr[tokennumber++]=token;
	while ((token != NULL) && (tokennumber < 20) )
	{
		printf("'%s'\n", token);
		token = strtok(NULL, delim);
		ptr[tokennumber++]=token;
	}
    tokennumber--; //because null pointer at end is not token 
	for( i=0; i < tokennumber; i++)
	{
		totallength += strlen(ptr[i]) + 1;
	}
	totallength--;
	printf("total length = %d\n",totallength);
	
	line2[0] = 0;
	line1[0] = 0;

	if (totallength < 17)
	{
		//one uppercase line
		line2[0] = 0;
		line1[0] = 0;
		for( i=0; i < tokennumber; i++)
		{
			strcat(line1,ptr[i]);
			if (i < (tokennumber - 1))
			{	
				strcat(line1," ");
			}
		}	

		printf("Velika slova jedna linija: %s\n",line1);
		int line1len = strlen(line1);
		//printf("line1len: %d\n",line1len);
		int spacesleft = (16 - line1len) / 2;
		//printf("spacesleft: %d\n",spacesleft);
		int spacesright = 16 - spacesleft - line1len;
		//printf("spacesright: %d\n",spacesright);
		if (spacesleft != 0)
			sprintf(centeredline1,"%*s%s%*s",spacesleft," ",line1, spacesright, " ");
		else
			sprintf(centeredline1,"%s",line1);
        printf("Line1 centered :\n %s\n",centeredline1);
		centeredline2[0] = 0; 
	}
	else if (totallength < 50)
	{
		// two lines each maximum 24 characters
		int firstlinelength=0;
		int secondlinelength=0;
		i=0;
		line2[0] = 0;
		line1[0] = 0;
		while(1)
		{
			if ((firstlinelength + strlen(ptr[i]) < (init_size/2)) && (i < tokennumber))
			{
				firstlinelength += strlen(ptr[i]);
				strcat(line1,ptr[i]);
				
				if (firstlinelength + strlen(ptr[i+1])  < (init_size/2) )
				{	
					strcat(line1," ");
					firstlinelength++;
				}
				i++;
				
			}
			else 
			 break;		
		}
		printf("Linija 1: %s\n",line1);

		int line1len = strlen(line1);
		int spacesleft = (24 - line1len) / 2;
		int spacesright = 24 - ( spacesleft + line1len );
		sprintf(centeredline1,"%*s%s%*s",spacesleft," ",line1, spacesright, " ");
        printf("Line1 centered :\n%s\n",centeredline1);
		
		while(1)
		{
			if ( i < tokennumber )
			{
				secondlinelength += strlen(ptr[i]);
				strcat(line2,ptr[i]);
				
				if (i < (tokennumber -1))
				{	
					strcat(line2," ");
					secondlinelength++;
				}
				i++;
			}
			else 
			 break;		
		}
		printf("Linija 2: %s\n",line2);

	    int line2len = strlen(line2);
		spacesleft = (24 - line2len) / 2;
		spacesright = 24 - ( spacesleft + line2len );
		sprintf(centeredline2,"%*s%s%*s",spacesleft," ",line2, spacesright, " ");
        printf("Line2 centered :\n%s\n",centeredline2);
		
	}
	else
	{
		line2[0] = 0;
		line1[0] = 0;
	}

	// center lines
	strcpy(line1,centeredline1);
	strcpy(line2,centeredline2);
    
}


void formatDestination2(char *intext, char *line1, char *line2)
{

	
	int init_size = strlen(intext);
	char delim[] = " ";
	char *ptr[20];
	char *token;
	int tokennumber=0;
	int i=0;
	int totallength = 0;

	char centeredline1[25];
	char centeredline2[25];

	token = strtok(intext, delim);
    ptr[tokennumber++]=token;
	while ((token != NULL) && (tokennumber < 20) )
	{
		printf("'%s'\n", token);
		token = strtok(NULL, delim);
		ptr[tokennumber++]=token;
	}
    tokennumber--; //because null pointer at end is not token 
	for( i=0; i < tokennumber; i++)
	{
		totallength += strlen(ptr[i]) + 1;
	}
	totallength--;
	printf("total length = %d\n",totallength);
	
	line2[0] = 0;
	line1[0] = 0;

	if (totallength < 32)
	{
		//one uppercase line
		line2[0] = 0;
		line1[0] = 0;
		for( i=0; i < tokennumber; i++)
		{
			strcat(line1,ptr[i]);
			if (i < (tokennumber - 1))
			{	
				strcat(line1," ");
			}
		}	

		printf("Velika slova jedna linija: %s\n",line1);
		int line1len = strlen(line1);
		//printf("line1len: %d\n",line1len);
		int spacesleft = (31 - line1len) / 2;
		//printf("spacesleft: %d\n",spacesleft);
		int spacesright = 31 - spacesleft - line1len;
		//printf("spacesright: %d\n",spacesright);
		if (spacesleft != 0)
			sprintf(centeredline1,"%*s%s%*s",spacesleft," ",line1, spacesright, " ");
		else
			sprintf(centeredline1,"%s",line1);
        printf("Line1 centered :\n %s\n",centeredline1);
		centeredline2[0] = 0; 
	}
	else if (totallength < 65)
	{
		// two lines each maximum 24 characters
		int firstlinelength=0;
		int secondlinelength=0;
		i=0;
		line2[0] = 0;
		line1[0] = 0;
		while(1)
		{
			if ((firstlinelength + strlen(ptr[i]) < (init_size/2)) && (i < tokennumber))
			{
				firstlinelength += strlen(ptr[i]);
				strcat(line1,ptr[i]);
				
				if (firstlinelength + strlen(ptr[i+1])  < (init_size/2) )
				{	
					strcat(line1," ");
					firstlinelength++;
				}
				i++;
				
			}
			else 
			 break;		
		}
		printf("Linija 1: %s\n",line1);

		int line1len = strlen(line1);
		int spacesleft = (32 - line1len) / 2;
		int spacesright = 32 - ( spacesleft + line1len );
		sprintf(centeredline1,"%*s%s%*s",spacesleft," ",line1, spacesright, " ");
        printf("Line1 centered :\n%s\n",centeredline1);
		
		while(1)
		{
			if ( i < tokennumber )
			{
				secondlinelength += strlen(ptr[i]);
				strcat(line2,ptr[i]);
				
				if (i < (tokennumber -1))
				{	
					strcat(line2," ");
					secondlinelength++;
				}
				i++;
			}
			else 
			 break;		
		}
		printf("Linija 2: %s\n",line2);

	    int line2len = strlen(line2);
		spacesleft = (32 - line2len) / 2;
		spacesright = 32 - ( spacesleft + line2len );
		sprintf(centeredline2,"%*s%s%*s",spacesleft," ",line2, spacesright, " ");
        printf("Line2 centered :\n%s\n",centeredline2);
		
	}
	else
	{
		line2[0] = 0;
		line1[0] = 0;
	}

	// center lines
	strcpy(line1,centeredline1);
	strcpy(line2,centeredline2);
    
}



int openUDPSocket()
{
    int z;
      char *srvr_addr = NULL;
      struct sockaddr_in adr_inet;

      int len_inet;                
      int s;                         




      srvr_addr = "127.0.0.1";//23 changed to 1

      s = socket(AF_INET,SOCK_DGRAM,0);
      if ( s == -1 )
         return(-1);

      memset(&adr_inet,0,sizeof adr_inet);
      adr_inet.sin_family = AF_INET;
      adr_inet.sin_port = htons(9090);
      adr_inet.sin_addr.s_addr =
          inet_addr(srvr_addr);

      if ( adr_inet.sin_addr.s_addr == INADDR_NONE )
          return(-1);

      len_inet = sizeof adr_inet;


      z = bind(s,
          (struct sockaddr *)&adr_inet,
          len_inet);
      if ( z == -1 )
          return(-1);
	return(s);
}


	
int main()
{

	/*
	
	unsigned char sendcommand1[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, // 6 
	    0xa5, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // 17 
	    0x61, 0x02, 0x34+ 0x7c, 0x00, 0xa3, 0x06, 0x01, 0x00, 0x00, 0x00, 0x01,//28 
	    0x21, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x00,//39 
	    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x01,//50 
	    0x00, 0x00, 0x0a, 0x13+ 0x79, 0x00, 0x00, 0x00, //57
	    '\\' , 'C' , '1' ,//60
	    'T' , 'e' , 'r' , 'z' , 'i' , 'c' , ' ' , 'S' , 
	    'a' , 'v' , 'a' , ' ' , 'j' , 'e' , ' ' , 'd' ,
	    'o' , 'b' , 'a' , 'r' , ' ' , 'd' , 'e' , 'c' , 
	    'k' , 'o' , ' ' , 'i' , 'z' , ' ' , ' ' , ' ' ,//92 
	    '\\' , 'C' , '2' ,//95
	    'M' , 'a' , 't' , 'e' , 'm' , 'a' , 't' , 'i' , 
	    'c' , 'k' , 'e' , ' ' , 'G' , 'i' , 'm' , 'n' ,
	    'a' , 'z' , 'i' , 'j' , 'e' , '.' , ' ' , ' ' , 
	    'M' , 'i' , 'r' , 'o' , 's' , 'l' , 'a' , 'v' ,//127
	    '\\' , 'C' , '3' ,//130
	    'M' , 'a' , 'r' , 'k' , 'o' , ' ' , 'N' , 'i' , 
	    'k' , 'o' , 'l' , 'i' , 'c' , ' ' , 'j' , 'e' ,
	    ' ' , 'p' , 'r' , 'e' , 's' , 'a' , 'o' , ' ' , 
	    'u' , ' ' , 'A' , 'p' , 'e' , 'x' , ' ' , ' ' ,//162 
	    '\\' , 'C' , '4',//165
	    'd' , 'a' , ' ' , 'b' , 'i' , ' ' , 'r' , 'a' , 
	    'd' , 'i' , 'o' , ' ' , 'o' , 'z' , 'b' , 'i' ,
	    'l' , 'j' , 'a' , 'n' , ' ' , 's' , 'o' , 'f' , 
	    't' , 'v' , 'e' , 'r' , '!' , '!' , '!' , '!' ,//197

	    0x60, 0x33, 0x5a};

	
		unsigned char sendcommand33[]={ 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 
	    0xa5, 0x02, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	    0x61, 0x02, 0xB1-0x40, 0x00, //command length
		0xa2, 0x01, 0x01, 0x00, 
		0x60, 0x33, 0x5a, 0x00, 0x00};




       */

	unsigned char readed[256];
	unsigned int bytes_read;

    int a;
	unsigned char ackresp54[]={ 0xfe, 0x0a, 0x00, 0x01, 0x16, 0xde};
	unsigned char ackresp52[]={ 0xfe, 0x0a, 0x00, 0x01, 0x17, 0xdd};
	unsigned char ackresp4F[]={ 0xfe, 0x0a, 0x00, 0x01, 0x19, 0xdb};
	unsigned char ackresp4E[]={ 0xfe, 0x0a, 0x00, 0x01, 0x1a, 0xda};
	unsigned char ackresp4C[]={ 0xfe, 0x0a, 0x00, 0x01, 0x13, 0xe1};
	unsigned char ackresp44[]={ 0xfe, 0x0a, 0x00, 0x01, 0x14, 0xe0};
	unsigned char ackresp50[]={ 0xfe, 0x0a, 0x00, 0x01, 0x12, 0xe2};
	unsigned char ackresp53[]={ 0xfe, 0x0a, 0x00, 0x01, 0x15, 0xdf};
	struct pollfd pfds[2];	
	//unsigned int bytes_written;

	fd = openport();
	
	fd2 = openport2();
	printf("Port2 opened\n");
	//usleep(100);

    tcflush(fd2, TCIFLUSH);   
	
	int rcvdcmd;
	int rcvcmdlen;
	bool havefronttitle = false;
	bool havelinenumber = false;
	bool internaldisplaytext = false;
	bool backdisplayshowline = false;
	unsigned char rcvcmd[256];
    int bytes_written;

	char linenumber[] = "    ";
	char str[128];  
	char istr[128]; 
	char linija1[36];
	char linija2[36];
	
    struct sockaddr_in adr_clnt;
	int len_inet; 
	int s;
	int z;
	int pollret = 0;
	int timeout_msecs = 500;
	char dgram[512];         
	
	s = openUDPSocket();

	if (s == -1) return(1);
	
	str[0] = 0;


	strcpy(linenumber, "    ");
	strcpy(linija1, "                                ");
	strcpy(linija2, "                                ");

	//dynamicAreaDisplayText3(linenumber, linija1, linija2);
	//dynamicAreaDisplayText4(linenumber, linija1, linija2);
	strcat(str, "Početni string za prednji displej");
	setDisplayTime();
	while (1)
	{
		pfds[0].fd = fd2;
		pfds[0].events = POLLIN;

		pfds[1].fd = fd;
		pfds[1].events = POLLIN;

		pfds[2].fd = s;
		pfds[2].events = POLLIN;

		timeout_msecs = 500;
		
		pollret = poll(pfds, 3, timeout_msecs);
		
		if (pollret > 0)
		{
			if (pfds[0].revents & POLLIN) 
			{
				bzero(readed,sizeof(readed));
						        //printf("\nNow reading1\n");
				printf("Reading Port 2\n");
				bytes_read = read(fd2,readed,256);
				
				printf("\n");
				for (a = 0; a < bytes_read; a++)
				{
				   printf("%02x ",readed[a]);
				}
				printf("\n");

				rcvdcmd = receiveStateMachine( readed, bytes_read, rcvcmd, &rcvcmdlen);
				if (rcvdcmd == 0x54)
				{
					printf("ACK 54 2\n");
					bytes_written = write(fd2, ackresp54, sizeof(ackresp54));
				}
				else if (rcvdcmd == 0x52)
				{
					printf("ACK 52 2\n");
					bytes_written = write(fd2, ackresp52, sizeof(ackresp52));
				}
				else if (rcvdcmd == 0x4F)
				{
					printf("ACK 4F 2\n");
					bytes_written = write(fd2, ackresp4F, sizeof(ackresp4F));
					printf("%s\n",rcvcmd);
				}
				else if (rcvdcmd == 0x4e)
				{
					printf("ACK 4E 2\n");
					bytes_written = write(fd2, ackresp4E, sizeof(ackresp4E));
				}
				else if (rcvdcmd == 0x4c)
				{
					printf("ACK 4C 2\n");
					bytes_written = write(fd2, ackresp4C, sizeof(ackresp4C));
					printf("Linija prednji displej\n");
					havelinenumber = true;
					strcpy(linenumber, &(rcvcmd[1]));
					printf("%s \n",&(rcvcmd[1]));
				}
				else if (rcvdcmd == 0x44)
				{
					printf("ACK 44 2\n");
					bytes_written = write(fd2, ackresp44, sizeof(ackresp44));
					//printf("%s\n",rcvcmd);
					printf("Na prednji displej\n");
					havefronttitle = true;
					strcpy(str, &(rcvcmd[1]));
					printf("%s \n",&(rcvcmd[1]));
				}
				else if (rcvdcmd == 0x50)
				{
					printf("ACK 50 2\n");
					bytes_written = write(fd2, ackresp50, sizeof(ackresp50));
				}
				else if (rcvdcmd == 0x53)
				{
					printf("ACK 53 2\n");
					bytes_written = write(fd2, ackresp53, sizeof(ackresp53));
					printf("%s\n",&(rcvcmd[1]));
					internaldisplaytext = true;
					strcpy(istr, &(rcvcmd[1]));
					
					
				}
				else
				{
					printf("\nNo ACK Response\n");
				}

				if (internaldisplaytext == true)
				{
					internaldisplaytext = false;

					if (strstr(istr,"Vreme") == NULL)
					{
						formatDestination2(istr, linija1, linija2);
					}
					else
					{
						strcpy(linija1, "         Datum: \\DD-\\DL-20\\DY      ");
						strcpy(linija2, "         Vreme: \\DH:\\DM:\\DS        ");
					}

					if (strlen(linija2) == 0)
					{
						strcpy(linija2, "                                ");
						dynamicAreaDisplayText4(linenumber, linija1, linija2);
					}
					else
					{
						dynamicAreaDisplayText4(linenumber, linija1, linija2);

					}
				}
				

				if (havelinenumber == true && havefronttitle == true)
				{
					havefronttitle = false;
					havelinenumber = false;
					formatDestination(str, linija1, linija2);

					if (strlen(linija2) == 0)
					{
						
						dynamicAreaDisplayText2(linenumber, linija1, linija2);
						backdisplayshowline = true;
						//dynamicAreaDisplayText3(linenumber, linija1, linija2);
					}
					else
					{
						
						dynamicAreaDisplayText1(linenumber, linija1, linija2);
						backdisplayshowline = true;
						//dynamicAreaDisplayText3(linenumber, linija1, linija2);

					}
				}
			}
			if (pfds[1].revents & POLLIN) 
			{
				printf("Reading from controller\n");
				bzero(readed,sizeof(readed));
						        //printf("\nNow reading1\n");
				bytes_read = read(fd,readed,256);
				//usleep(1000);

				printf("Readed from controller %d\n", bytes_read);
				for (a = 0; a < bytes_read; a++)
				{
				   printf("%02x ",readed[a]);
				}	
				printf("\n");
			}
			
			if (pfds[2].revents & POLLIN) 
			{
				len_inet = sizeof adr_clnt;
				z = recvfrom(	s, 
		        				dgram, 
		        				sizeof(dgram),
		        				0, 
		        				(struct sockaddr *) &adr_clnt, 
		        				&len_inet
					          );
				printf("\nReceived from socket\n");
			}
		}
		if (pollret == 0)
		{

			if (backdisplayshowline == true)
			{
				usleep(100);
				backdisplayshowline = false;
				dynamicAreaDisplayText3(linenumber, linija1, linija2);
			}	
		}
	}
	close(fd2);
	close(fd);
	close(s);
	return(0);
}


