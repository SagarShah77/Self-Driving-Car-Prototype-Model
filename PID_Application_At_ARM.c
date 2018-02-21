#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/fs.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <sys/stat.h>
#include "24cXX.h"
#include <termios.h> // POSIX terminal control
definitionss
#include <sys/time.h> // time calls
#include <string.h>
int main(int argc, char** argv)
{
int fdu;// n;
char *DeviceName;
struct termios port_settings;
struct lsm303 e;
if(argc>1)
{
DeviceName = (char*)malloc(strlen(argv[1])+1);
strcpy(DeviceName, argv[1]); //Lay tham so nhap vao
//printf("Device Name=%s\n", DeviceName);
}
else
DeviceName = "/dev/ttySAC1";
//Open com port
fdu = open(DeviceName, O_RDWR | O_NOCTTY |
O_NDELAY);
if(fdu<0)
{
printf("Open com port %s failed\n", DeviceName);
return fdu;
}
fcntl(fdu, F_SETFL, FNDELAY); /* Configure port
reading */
int error[4];
int prev_value = 0, value,Kp = 20 , Ki= 15 , Kd = 10,
PID = 0;
int angle = 0;
char str2[10],str[10];
//Cau hinh tham so com port
//baudrate 9600, 8N1
cfsetispeed(&port_settings, B9600);
cfsetospeed(&port_settings, B9600);
port_settings.c_cflag &= ~PARENB; //Set no parity
port_settings.c_cflag &= ~CSTOPB; //Set 1 stop bit
port_settings.c_cflag &= ~CSIZE; //Set 8 bit data using
mask bit
port_settings.c_cflag |= CS8;
port_settings.c_cflag &= ~CRTSCTS; //No hadware
handshaking
tcsetattr(fdu, TCSANOW, &port_settings); // apply the
settings to the port
printf("Desired Path Value from Sensor(0 to 5000):");
scanf("%d", &prev_value);
printf("\r\n");
error[0] = 0;
error[1] = 0;
error[2] = 0;
while(1){
error[3] = ((magread()) - prev_value) / 100;
PID = Kp * error[1] + Ki * (error[3] * error[3] +
error[2] * error[2] + error[1] * error[1] + error[0] *
error[0]) + Kd * (error[1] - error[0]);
printf("PID Value = %d \r\n",PID);
error[0] = error[1];
error[1] = error[2];
error[2] = error[3];
angle = 0.04 * PID - 90;
if(angle > 270) angle = angle;
if(angle <-90) angle = 0;
//printf("Error = %d\r\n", error[3]);
printf("Angle = %d\r\n",(angle & 0xFF));
//write(fdu, (angle & 0xFF), 2);
//write(fdu, (angle & 0xFF), 1);
//read(fdu, str2, 2);
str2[0] = (angle & 0xFF);
str2[1] = 0x00;
write(fdu,str2,1);
read(fdu,str,8);
//str2[5] = 0x00;
printf("%s \r\n",str);
//write(fdu, angle>>8, 1);
//printf("angle = %d \r\n", angle);
sleep(1);
}
close(fdu);
return 0;
}
