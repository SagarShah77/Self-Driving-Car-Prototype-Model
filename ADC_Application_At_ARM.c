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
#include <termios.h> // POSIX terminal control
definitionss
#include <sys/time.h> // time calls
#include <string.h>
#include <math.h>
struct Complex
{ double a; //Real Part
double b; //Imaginary Part
}X[11];
void FFT(void)
{
int M=5,i=1,j=1,k=1,LE=0,LE1=0,IP=0;
struct Complex U, W, T, Tmp;
int N=pow(2.0,M);
for(k=1;k<=M;k++)
{
LE=pow(2.0,M+1-k);
LE1 = LE / 2;
U.a = 1.0;
U.b = 0.0;
W.a = cos(M_PI / (double)LE1);
W.b = -sin(M_PI / (double)LE1);
for (j = 1; j <= LE1; j++)
{
for (i = j; i <= N; i = i + LE)
{
IP = i + LE1;
T.a = X[i].a + X[IP].a;
T.b = X[i].b + X[IP].b;
Tmp.a = X[i].a - X[IP].a;
Tmp.b = X[i].b -
X[IP].b;
X[IP].a = (Tmp.a * U.a)
- (Tmp.b * U.b);
X[IP].b = (Tmp.a * U.b)
+ (Tmp.b * U.a);
X[i].a = T.a;
X[i].b = T.b;
}
Tmp.a = (U.a * W.a) - (U.b *
W.b);
Tmp.b = (U.a * W.b) + (U.b *
W.a);
U.a = Tmp.a;
U.b = Tmp.b;
}
}
int NV2 = N/2;
int NM1 = N-1;
int K = 0;
j = 1;
for (i = 1; i <= NM1; i++)
{
if (i >= j) goto TAG25;
T.a = X[j].a;
T.b = X[j].b;
X[j].a = X[i].a;
X[j].b = X[i].b;
X[i].a = T.a;
X[i].b = T.b;
TAG25: K = NV2;
TAG26: if (K >= j) goto TAG30;
j = j - K;
K = K / 2;
goto TAG26;
TAG30: j = j + K;
}
}
int main(int argc, char** argv)
{
//sleep(20);
int i=0;
unsigned int arr1[100];
unsigned int arr2[100];
float power[100];
float mean;
fprintf(stderr, "press Ctrl-C to stop\n");
int fdu;// n;
char *DeviceName;
struct termios port_settings; //Cau truc de luu tru
cau hinh uart
if(argc>1)
{
	DeviceName = (char*)malloc(strlen(argv[1])+1);
strcpy(DeviceName, argv[1]); //Lay tham so nhap vao
//printf("Device Name=%s\n", DeviceName);
}
else
DeviceName = "/dev/ttySAC1"; //Cong com mac
dinh
//Open com port
fdu = open(DeviceName, O_RDWR | O_NOCTTY |
O_NDELAY);
if(fdu<0)
{
printf("Open com port %s failed\n", DeviceName);
return fdu;
}
for(i = 0; i < 64; i++)
arr1[i] = 0;
fcntl(fdu, F_SETFL, FNDELAY); /* Configure port
reading */
//baudrate 9600, 8N1
cfsetispeed(&port_settings, B9600);
cfsetospeed(&port_settings, B9600);
port_settings.c_cflag &= ~PARENB; //Set no parity
port_settings.c_cflag &= ~CSTOPB; //Set 1 stop bit
port_settings.c_cflag &= ~CSIZE; //Set 8 bit data
using mask bit
port_settings.c_cflag |= CS8;
port_settings.c_cflag &= ~CRTSCTS; //No hadware
handshaking
tcsetattr(fdu, TCSANOW, &port_settings); // apply
the settings to the port
while(1){
write(fdu, "ReadyToSent",11);
for (i=0; i<64; i++)
read(fdu,&arr1[i],1);
write(fdu, "DataSent",8);
for(i = 0; i<64;i++){
printf("\r\nUART Values %d: %d ",i,arr1[i]);
}
for (i=0; i <=32;i++){
arr2[i] = 0;
}
arr2[0] = 0;
//sleep(2);
for(i = 1;i<=32;i++)
{
arr2[i] = (256 * arr1[(2*i)-2]) +
arr1[(2*i)-1];
}
for (i=1; i <=32;i++){
	printf("arr %d: %d \r\n",i,arr2[i]);
}
for (i = 1; i <= 32; i++)
{
X[i].a = arr2[i];
X[i].b = 0.0;
}
printf ("*********Before*********\n");
for (i = 1; i <= 32; i++)
printf ("X[%d]:real == %f imaginary
== %f\n", i, X[i].a, X[i].b);
FFT();
for (i = 1; i <= 32; i++)
{
X[i].a = X[i].a/32;
X[i].b = X[i].b/32;
}
printf ("\n\n**********After*********\n");
for (i = 1; i <= 32; i++)
printf ("X[%d]:real == %f imaginary
== %f\n", i, X[i].a, X[i].b);
for (i = 1; i <= 32; i++)
{
power[i]=
sqrt(((X[i].a*X[i].a)+(X[i].b*X[i].b)));
printf("power spectrum value of
power[%d] is = %f \n",i,power[i]);
}
mean=0;
for(i=20;i<=29;i++)
{
mean= mean+ power[i];
}
mean/=10;
printf("mean is %f \n",mean);
if(mean<(0.5*power[1]))
printf("values are valid \n");
else
printf("values are not valid \n");
for(i=0;i<=32; i++)
{
X[i].a = 0;
X[i].b = 0;
}
sleep(2);
}
}

