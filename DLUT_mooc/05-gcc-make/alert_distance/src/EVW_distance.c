#include <stdio.h>
#include <stdlib.h>
#include "common_algorithm.h"
/*
 * Vetalk_calcEVWInformationDistance()
 * 
 * 计算提示级别的EVWinformation级别的安全距�? * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 *
 *
 * return
 * float，提示级别的EVW安全距离
 */
float Vetalk_calcEVWInformationDistance(float frontvehicle_speed, float rearvehicle_speed)
{
    float d = 0.0f;
    float EVW_MAX_DISTANCE_M = 300;
    float EVW_EXPECT_SPEED_MPS = 12;
    float EVW_INFO_MIN_DISTANCE_M = 100;
    float EVW_ADD_SPEED_MPS = 2;
    float EVW_INFO_OVERTAKE_TIME_S = 10;

    rearvehicle_speed = rearvehicle_speed + EVW_ADD_SPEED_MPS;
    rearvehicle_speed = rearvehicle_speed < EVW_EXPECT_SPEED_MPS ? EVW_EXPECT_SPEED_MPS : rearvehicle_speed;
    d = (rearvehicle_speed - frontvehicle_speed) * EVW_INFO_OVERTAKE_TIME_S;

    if (d < EVW_INFO_MIN_DISTANCE_M) {
        return EVW_INFO_MIN_DISTANCE_M;
    } else if (d > EVW_MAX_DISTANCE_M)  {
        return EVW_MAX_DISTANCE_M;
    } else {
        return d;
    }
}


/*
 * Vetalk_calcEVWWarningDistance()
 * 
 * 计算提示级别的EVWwarning级别的安全距�? * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 *
 *
 * return
 * float，提示级别的EVW安全距离
 */
float Vetalk_calcEVWWarningDistance(float frontvehicle_speed, float rearvehicle_speed)
{
    float d = 0.0f;
    float EVW_MAX_DISTANCE_M = 300;
    float EVW_EXPECT_SPEED_MPS = 12;
    float EVW_WARNING_MIN_DISTANCE_M = 50;
    float EVW_ADD_SPEED_MPS = 3;
    float EVW_WARNING_OVERTAKE_TIME_S = 7;


    rearvehicle_speed = rearvehicle_speed + EVW_ADD_SPEED_MPS;
    rearvehicle_speed = rearvehicle_speed < EVW_EXPECT_SPEED_MPS ? EVW_EXPECT_SPEED_MPS : rearvehicle_speed;
    d = (rearvehicle_speed - frontvehicle_speed) * EVW_WARNING_OVERTAKE_TIME_S;

    if (d < EVW_WARNING_MIN_DISTANCE_M) {
        return EVW_WARNING_MIN_DISTANCE_M;
    } else if (d > EVW_MAX_DISTANCE_M)  {
        return EVW_MAX_DISTANCE_M;
    } else {
        return d;
    }
}

/*
 * TA_EvaluateThreatEVW()
 * 
 * 
 * @brief  EVW危险等级�?��
 * 
 * 
 * 
 * @param pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @param pLocalVector: 指针，指向结构体tVector，代表本车数�? * @param pRemote: 指针，指向结构体tTCRemote，代表远车数�? * @param pUser: 指针，指向结构体tTARemote，代表输出TA数据
 * @param VSstate: 指针，指向结构体tVStateState�?代表本车can数据
 *
 * @return
 * void
 */
void TA_EvaluateThreatEVW(float frontvehicle_speed, float rearvehicle_speed)
{
    double d_info;
    double d_warning;
    
    d_info = Vetalk_calcEVWInformationDistance(frontvehicle_speed, rearvehicle_speed);
    d_warning = Vetalk_calcEVWWarningDistance(frontvehicle_speed, rearvehicle_speed);
    printf("<EVW>:d_info:%4.2f, d_warning:%4.2f\n", d_info, d_warning);
    return;

}

