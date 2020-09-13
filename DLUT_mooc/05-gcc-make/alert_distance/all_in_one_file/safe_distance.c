#include <stdio.h>
#include <stdlib.h>
#include "main_in.h"

void main()
{
    float behind_v, distance;
    // int ahead_v;
    // char str[100];
    // FILE * warning_d, *fspeed, *fd0, *fd1,*fd3,*fd5,*fdmajor,*fdemergency;
    // if((fspeed = fopen("./behind_speed.txt", "r")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fd0 = fopen("./warning_d_aheadV0.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fd1 = fopen("./warning_d_aheadV1.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fd3 = fopen("./warning_d_aheadV3.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fd5 = fopen("./warning_d_aheadV5.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fdmajor = fopen("./warning_d_major.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // if((fdemergency = fopen("./warning_d_emergency.txt", "w")) == 0) {
    //     printf("打开文件失败");
    // };
    // fclose(fspeed);
    // fclose(fd0);
    // fclose(fd1);
    // fclose(fd3);
    // fclose(fd5);
    // fclose(fdmajor);
    // fclose(fdemergency);

    TA_EvaluateThreatFCW(0.0, 40/3.6, 0, 0);
    TA_EvaluateThreatFCW(40.0/3.6, 40/3.6, -1.15, 0);
    TA_EvaluateThreatEBW(80.0/3.6, 60.0/3.6, -7.17, 0);
    TA_EvaluateThreatICW(40/3.6);
    TA_EvaluateThreatICW(60/3.6);
}