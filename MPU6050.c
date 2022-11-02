#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <stdint.h>
#include <wiringPiI2C.h>
#include <math.h>
#define Sample_rate 25 //0x19
#define Config 26
#define Gyro_config 27
#define Acc_config 28
#define Interrupt 56
#define PWR_Managment 107
#define Acc_X 59
#define Acc_Y 61
#define Acc_Z 63
int mpu;
int Steps=0;
int bt;
float Aprevious;
int16_t read_sensor(unsigned char sensor)
{
    uint16_t high, low, data;
    high = wiringPiI2CReadReg8(mpu,sensor);
    low = wiringPiI2CReadReg8(mpu,sensor+1);
    data = (high<<8) | low;

    return data;
}
void Init_6050()
{
    //setup status
    wiringPiI2CWriteReg8(mpu,Sample_rate,15);
    // Khong su dung nguon xung ngoai, tat DPFL
    wiringPiI2CWriteReg8(mpu,Config,0);
    //gyro FS: +- 500 o/s
    wiringPiI2CWriteReg8(mpu,Gyro_config,0x08);
    //acc FS: +- 4g
    wiringPiI2CWriteReg8(mpu,Acc_config,0x10);
    //mo interrupt cua data ready
    wiringPiI2CWriteReg8(mpu,Interrupt,1);
    //Chon nguon xung Gyro X
    wiringPiI2CWriteReg8(mpu,PWR_Managment,0x01);
    
}
int main(void)
{
    //Setup giao tiep I2C
    mpu = wiringPiI2CSetup(0x68);
    //Thiet lap che do do cho MPU6050
    Init_6050();
    //Doc gia tri do
    /*int data;
    data = wiringPiI2CReadReg8(mpu,117);
    printf("%d",data);*/
    
    //temp = wiringPiI2CReadReg8(mpu,0x41);
    //temp = temp/340 + 36.53;
    bt = Steps;
    printf("buoc chan: %d\n",bt);
    while(1)
    {
        float Ax = (float)read_sensor(Acc_X)/4096.0;
        float Ay = (float)read_sensor(Acc_Y)/4096.0;
        float Az = (float)read_sensor(Acc_X)/4096.0;
        float A = sqrt(Ax*Ax + Ay*Ay +Az*Az)*9.81;
        // float totalA = A - Aprevious;   
        // if(totalA > 14)
        // {
        //     Steps++;
        // }
        // if(bt != Steps)
        // {
        //     bt = Steps;
        //     printf("buoc chan: %d\n",bt);
        // }
        //Aprevious = A ;
        //float pich = atan2(Ax,sqrt((Ay*Ay)+(Az*Az)))*180/M_PI;
        //float roll = atan2(Ay,sqrt((Ax*Ax)+(Az*Az)))*180/M_PI;
        //printf("y la: %f\n",pich);
        //printf("x la: %f\n",roll);
        printf("A la: %f\n",A);
        //printf("Steps: %d\n",Steps);
        //printf("Steps: %d\n",bt);
        // printf("Ax la: %f\n",Ax);
        // printf("Ay la: %f\n",Ay);
        // printf("Az la: %f\n",Az);
        delay(300);

    }
    return 0;
}
