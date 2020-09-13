#include<stdio.h>
#include <stdlib.h>
// #include "commmon_algorithm.h"
#include "AVW_distance.h"
#include "EEBL_distance.h"
#include "FCW_distance.h"
#include "ICW_distance.h"

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

    // while(fgets(str, sizeof(str), fspeed)) {
    //     sscanf(str, "%f", &behind_v);
    //     behind_v = (float)behind_v / 3.6;
    //     distance = Vetalk_calcAVWWarningDistance(0, behind_v, 0);
    //     fprintf(fd0, "%f\n", distance);
    //     distance = Vetalk_calcAVWWarningDistance(1, behind_v, 0);
    //     fprintf(fd1, "%f\n", distance);
    //     distance = Vetalk_calcAVWWarningDistance(3, behind_v, 0);
    //     fprintf(fd3, "%f\n", distance);
    //     distance = Vetalk_calcAVWWarningDistance(5, behind_v, 0);
    //     fprintf(fd5, "%f\n", distance);
    //     distance = Vetalk_calcAVWMajorDistance(0, behind_v, 0);
    //     fprintf(fdmajor, "%f\n", distance);
    //     distance = Vetalk_calcAVWEmergencyDistance(0, behind_v, 0);
    //     fprintf(fdemergency, "%f\n", distance);
    //     printf("behind_v:%f, distance:%f\n",behind_v, distance);
    // }

    // fclose(fspeed);
    // fclose(fd0);
    // fclose(fd1);
    // fclose(fd3);
    // fclose(fd5);
    // fclose(fdmajor);
    // fclose(fdemergency);

    // distance = Vetalk_calcAVWWarningDistance(2.1, 6.46, -0.25);

    // distance = Vetalk_calcEEBLWarningDistance(11.5, 9.06, -9.6);
    TA_EvaluateThreatFCW(0.0, 40/3.6, 0, 0);
    TA_EvaluateThreatFCW(40.0/3.6, 40/3.6, -1.15, 0);
    TA_EvaluateThreatEBW(80.0/3.6, 60.0/3.6, -7.17, 0);
    TA_EvaluateThreatICW(40/3.6);
    TA_EvaluateThreatICW(60/3.6);
}