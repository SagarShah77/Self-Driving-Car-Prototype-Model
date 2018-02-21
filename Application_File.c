DEFINE Kp 1
DEFINE Kd 0.25
DEFINE Ki 0.25
DEFINE SET_LED_OFF 0
DEFINE SET_LED_ON 1
DEFINE GET_SWITCH 3
int M = 5;
int N;
struct Complex
{ double a; //Real Part
double b; //Imaginary Part
} X[33];
static int fd = -1;
static int fd1= -1;
static void close_buzzer(void);
static void open_buzzer(void)
{
fd = open("/dev/harita_pwm", 0);
IF (fd < 0)
{
perror("open pwm_buzzer device");
exit(1);
}
fd1 = open("/dev/harita_leds0", 0);
IF (fd1 < 0)
{
fd1 = open("/dev/harita_leds", 0);
}
IF (fd1 < 0)
{
perror("open device leds");
exit(1);
}
// any function exit call will stop the buzzer
atexit(close_buzzer);
}
static void close_buzzer(void)
{
IF (fd >= 0) {
ioctl(fd, PWM_IOCTL_STOP);
IF (ioctl(fd, 2) < 0) {
perror("ioctl 2:");
}
close(fd);
close(fd1);
fd = -1;
fd = -1;
}
}
static void set_buzzer_freq(int freq)
{
// this IOCTL command is the key to set frequency
int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
IF (ret < 0) {
perror("set the frequency of the buzzer");
exit(1);
}
}
static void stop_buzzer(void)
{
int ret = ioctl(fd, PWM_IOCTL_STOP);
IF (ret < 0) {
perror("stop the buzzer");
exit(1);
}
IF (ioctl(fd, 2) < 0) {
perror("ioctl 2:");
}
}
