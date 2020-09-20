#include<stdio.h>
#include <stdlib.h>

static float _Vetalk_calcSafeDistance_Oncoming(float readiness_time, float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed, float rearvehicle_lonaccel, float min_safety_distance)
{
    float Distance;
    
    Distance = 0.0f;

    // printf("rearvehicle_speed %f, frontvehicle_speed %f, frontvehicle_lonaccel %f, rearvehicle_lonaccel %f, readiness_time %f\n", rearvehicle_speed, frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, readiness_time);

    /*d = (v1 - v0) * t + 1/2 * v1 *v1 / a1 - v0 * v1/ a1 - 1/2 * a0 * (v1/a1) ^ 2+ d0 */
    Distance = readiness_time * (rearvehicle_speed - frontvehicle_speed) 
                + 0.5f * rearvehicle_speed *  rearvehicle_speed / (-rearvehicle_lonaccel) 
                - frontvehicle_speed * rearvehicle_speed / (-rearvehicle_lonaccel) 
                - 0.5f * frontvehicle_lonaccel * rearvehicle_speed / (-rearvehicle_lonaccel) * rearvehicle_speed / (-rearvehicle_lonaccel)
                + min_safety_distance;

    return Distance;
}

/*
 * _Vetalk_calcSafeDistance_Inreadinesstime()
 * 
 * 计算反映时间内的安全距离
 * 
 * @readiness_time: 反映时间
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 * @rearvehicle_lonaccel: 后车加速度
 * @min_safety_distance: 最小安全距离
 *
 * return float，反映时间内的安全距离
 */
static float _Vetalk_calcSafeDistance_Inreadinesstime(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float min_safety_distance)
{
    float Distance;

    Distance = 0.0f;

    // printf("join in readines time safe distance\n");    

    /* d = (v1-v2) * t - 1/2 * a2 * t ^2  + d0 */
    Distance =  readiness_time * (rearvehicle_speed - frontvehicle_speed) - 0.5f  * frontvehicle_lonaccel * readiness_time * readiness_time  + min_safety_distance;

    return Distance;
}

/*
 * _Vetalk_calcSafeDistance_RearVehicleStopedFirst()
 * 
 * 计算后先停止的安全距��?
 * 
 * @readiness_time: 反映时间
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 * @rearvehicle_lonaccel: 后车加速度
 * @min_safety_distance: 最小安全距离
 *
 * return float，后车先停止的安全距离
 */

static float _Vetalk_calcSafeDistance_RearVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
{
    float Distance;
    float equal_time; /* The moment when the front and rear cars are at the same speed. */

    Distance = 0.0f;
    equal_time = 0.0f;

    equal_time = (rearvehicle_speed - frontvehicle_speed - readiness_time * frontvehicle_lonaccel) / (frontvehicle_lonaccel - rearvehicle_lonaccel);

    // printf("join in rear vehicle stop first\n");    

    if (equal_time < 0.0f) {
        printf("calc error, the speed of front vehicle can not equal to rear\n");
        return 1000;
    }

    // printf("rearvehicle_speed %f, frontvehicle_speed %f, frontvehicle_lonaccel %f, rearvehicle_lonaccel %f, readiness_time %f, equal_time %f\n", rearvehicle_speed, frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, readiness_time, equal_time);

    /* d= -v1 * t *et - 1/2 * a1 *et ^2 + 1/2(t + et)^2 +d0 */
    Distance = -rearvehicle_lonaccel * readiness_time * equal_time - 0.5f * rearvehicle_lonaccel * equal_time * equal_time \
               + 0.5f * frontvehicle_lonaccel * (equal_time + readiness_time) * (equal_time + readiness_time) \
                + min_safety_distance;
    // printf("disd %f", Distance);
    
    return Distance;
}

/*
 * _Vetalk_calcSafeDistance_FrontVehicleStopedFirst()
 * 
 * 计算前车先停止的安全距离
 * 
 * @readiness_time: 反映时间
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 * @rearvehicle_lonaccel: 后车加速度
 * @min_safety_distance: 最小安全距离
 *
 * return float，前车先停止的安全距离
 */
static float _Vetalk_calcSafeDistance_FrontVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
{
    float Distance;
    
    Distance = 0.0f;

    // printf("rearvehicle_speed %f, frontvehicle_speed %f, frontvehicle_lonaccel %f, rearvehicle_lonaccel %f, readiness_time %f\n", rearvehicle_speed, frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, readiness_time);

    /*d = v1 *t + 1/2 * v1 *v1 /a1 - 1/2 * v2 * v2/a2 + d0  */
    Distance = readiness_time * rearvehicle_speed + 0.5f * rearvehicle_speed *  rearvehicle_speed / (-rearvehicle_lonaccel) - 0.5f * frontvehicle_speed * frontvehicle_speed / (-frontvehicle_lonaccel) + min_safety_distance;

    return Distance;
}

/*
 * _Vetalk_calcSafeDistance()
 * 
 * 计算安全距离
 * 
 * @readiness_time: 反映时间
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 * @rearvehicle_lonaccel: 后车加速度
 * @min_safety_distance: 最小安全距离
 *
 * return float，安全距离
 */
static float _Vetalk_calcSafeDistance(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
{
        float  frontvehicle_slowdown_time; /* the time of front vehicle slow down to zero */
        float  rearvehicle_slowdown_time; /* the time of rear vehicle slow down to zero */
        float  frontvehicle_speedup_time; /* the time of front vehicle time accelerate to the rear vehicle  */

        frontvehicle_slowdown_time = 0.0f;
        rearvehicle_slowdown_time = 0.0f;
        frontvehicle_speedup_time = 0.0f;

       /* The direction of the rear vehicle is in the positive direction */
        if (frontvehicle_speed < 0) { 
            return _Vetalk_calcSafeDistance_Oncoming(readiness_time, frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed, rearvehicle_lonaccel, min_safety_distance);
        } else {
       
            if (frontvehicle_lonaccel > 0) {
                /* front vehicle speed up */

                frontvehicle_speedup_time = (rearvehicle_speed - frontvehicle_speed) / frontvehicle_lonaccel;

                if (frontvehicle_speedup_time < 0.0f) {
                /* front vehicle is quicker than rear vehicle */
                    return 1000;
                } else if (frontvehicle_speedup_time < readiness_time) {
                    return _Vetalk_calcSafeDistance_Inreadinesstime(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, min_safety_distance);                  

                } else { 
                    /* front vehicle speed up in low acceleration , use the formula of rearvehicle speed stop first*/                  
                    return _Vetalk_calcSafeDistance_RearVehicleStopedFirst(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
                }
            } else if (frontvehicle_lonaccel == 0) {
            /* front vehicle uniform, use the formula of rearvehicle speed stop first*/

                return _Vetalk_calcSafeDistance_RearVehicleStopedFirst(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

            } else {
            /* front vehicle slow down */
                frontvehicle_slowdown_time = frontvehicle_speed / (-frontvehicle_lonaccel);
                rearvehicle_slowdown_time = readiness_time + rearvehicle_speed / (-rearvehicle_lonaccel);
                
                if (frontvehicle_slowdown_time < rearvehicle_slowdown_time) {
                    return _Vetalk_calcSafeDistance_FrontVehicleStopedFirst(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

                } else {

                        return _Vetalk_calcSafeDistance_RearVehicleStopedFirst(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

                }

           }
      }
}

float Vetalk_calcAVWWarningDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0;
    float   min_safety_distance = 0.0;    
    float   rearvehicle_lonaccel = 0.0;
	float 	Tr = 3.2;
	float 	Ts = 0.4;    

    readiness_time = Tr + Ts;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000;
    } 

}

/*
 * Vetalk_calcAVWMajorDistance()
 * 
 * 计算警告级别的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 *
 * return
 * 警告级别的AVW安全距离
 */
float Vetalk_calcAVWMajorDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Tr = 1.8f;
	float 	Ts = 0.4f;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000.0;
    } 
}

/*
 * Vetalk_calcAVWEmergencyDistance()
 * 
 * 计算严重警告级别的AVW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @frontvehicle_speed: 前车速度
 * @rearvehicle_speed: 后车速度
 * @frontvehicle_lonaccel: 前车加速度
 *
 * return
 * 严重警告级别的AVW安全距离
 */
float Vetalk_calcAVWEmergencyDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   readiness_time = 0.0f;
    float   min_safety_distance = 0.0f;    
    float   rearvehicle_lonaccel = 0.0f;
	float 	Ts = 0.4f;    
	float 	Tr = 0.6f;    

    readiness_time = Ts + Tr;
    min_safety_distance = 2;
    rearvehicle_lonaccel = -3;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return 1000;
    } 
    
}

float Vetalk_calcFCWSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float   readiness_time;
    float   min_safety_distance;

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;

    min_safety_distance = 2;

    /* 前车速度大于后车，安全 */
    if (frontvehicle_speed > rearvehicle_speed) {
        return -1;
    } else {

        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    }
}

float Vetalk_calcFCWWarningDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   warning_readiness_time;
    float   follow_readiness_time;
    float   min_safety_distance;
    float   follow_frontvehicle_lonaccel;
    float   rearvehicle_lonaccel;
    float   d_follow;
    float   d_warning;
	float 	Ts;


	Ts = 0.4;   
    warning_readiness_time = 1.2 + Ts;     // FCW_warning_reaction_time_s
    follow_readiness_time = 0.5 + Ts;      // FCW_follow_reaction_time_s
    min_safety_distance = 2;               // FCW_minsafety_distance_m
    follow_frontvehicle_lonaccel = -6;     // FCW_mindecelerate_mps2
    rearvehicle_lonaccel = -6;             // FCW_mindecelerate_mps2

    d_follow = _Vetalk_calcSafeDistance(follow_readiness_time, frontvehicle_speed, rearvehicle_speed, follow_frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    d_warning = _Vetalk_calcSafeDistance(warning_readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

    
    if (frontvehicle_speed <= rearvehicle_speed) {
        if (rearvehicle_speed >= 60/3.6 && (rearvehicle_speed - frontvehicle_speed) < 5/3.6) {
            /* 返回跟随距离和soft距离较大的一个 */
            return (d_follow > d_warning ? d_follow : d_warning);
        } else {
            return d_warning;
        }
    } else {    
        /* 后车速度很快，及时小于前车也有危险 */
        if (rearvehicle_speed >= 60/3.6 && rearvehicle_speed + 5/3.6 > frontvehicle_speed) {
            return d_follow;
        } else {
            return -1;
        }
    } 
    return -1;
}


float Vetalk_calcFCWMajorDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   readiness_time;
    float   min_safety_distance;    
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

	Tr = 0.5;                  // FCW_major_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 2;   // FCW_minsafety_distance_m;
    rearvehicle_lonaccel = -6; // FCW_mindecelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return -1;
    } 

}

float Vetalk_calcFCWEmergencyDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    float   readiness_time;
    float   min_safety_distance;    
    float   rearvehicle_lonaccel;
	float 	Ts;    
	float 	Tr;

	Ts = 0.4;
    Tr = 0.3;                  // FCW_emergency_reaction_time_s
    readiness_time = Ts + Tr;
    min_safety_distance = 2;   // FCW_minsafety_distance_m;
    rearvehicle_lonaccel = -6; // FCW_mindecelerate_mps2;

    if (frontvehicle_speed < rearvehicle_speed) {
        return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
    } else {
        return -1;
    } 
    
}

float Vetalk_calcFCWWarningFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWWarningDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed));
}

float Vetalk_calcFCWMajorFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWMajorDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed)); 
}

float Vetalk_calcFCWEmergencyFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed)
{
    return (float)(1.0f + 5.0 / 100.0f) * (Vetalk_calcFCWEmergencyDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed));   
}

void TA_EvaluateThreatFCW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float d_warning;
    float d_major;
    float d_emergency;
    float d_slowed = 0;

    float d_warning_Flexible = 0.0f;
    float d_major_Flexible = 0.0f;
    float d_emergency_Flexible = 0.0f;

    /* 车辆已刹车，并且减速度达到一定程度，不考虑反映时间，使用已减速公式 */
    if (rearvehicle_lonaccel < -3) {
        /* The vehicle has slowed down */
        d_slowed = Vetalk_calcFCWSlowedDistance(frontvehicle_speed, 
                                                rearvehicle_speed, 
                                                frontvehicle_lonaccel, 
                                                rearvehicle_lonaccel);
    } 

    d_warning = Vetalk_calcFCWWarningDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    d_major = Vetalk_calcFCWMajorDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    d_emergency = Vetalk_calcFCWEmergencyDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    // d_warning_Flexible = Vetalk_calcFCWWarningFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_major_Flexible = Vetalk_calcFCWMajorFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_emergency_Flexible = Vetalk_calcFCWEmergencyFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    printf("<FCW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f, d_slowed:%4.2f\n",d_warning, d_major, d_emergency, d_slowed);
    // printf("d_warning_Flexible:%4.2f, d_major_Flexible:%4.2f, d_emergency_Flexible:%4.2f\n",d_warning_Flexible, d_major_Flexible, d_emergency_Flexible);
    
    return;
}

float Vetalk_calcEEBLSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float   readiness_time;
    float   min_safety_distance;
    
    readiness_time = 0.0f;

    min_safety_distance = 2; // EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

float Vetalk_calcEEBLWarningDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
	float 	Tr;
	float 	Ts;    

	Tr = 2.9; // EBW_warning_reaction_time_s;
    
	Ts = 0.4;

    rearvehicle_lonaccel = -3;   // EBW_decelreate_value_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 2.0;   // EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

float Vetalk_calcEEBLMajorDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
    float   Tr;
    float   Ts;    

    Tr = 1.8;  //EBW_major_reaction_time_s
    Ts = 0.4;

    rearvehicle_lonaccel = -3;   // EBW_decelreate_value_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 2;     //EBW_min_safetydistance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);

}


float Vetalk_calcEEBLEmergencyDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel)
{
    float   min_safety_distance;
    float   rearvehicle_lonaccel;    
    float   readiness_time;
    float   Ts;    
    float   Tr;

    Ts = 0.4;
    Tr = 0.6;                   // EBW_emergency_reaction_time_s;
    rearvehicle_lonaccel = -3;  // Min_Brake_Deceleration_mps2;
    readiness_time = Tr + Ts;
    min_safety_distance = 4;    // Min_Safety_Distance_m;

    return _Vetalk_calcSafeDistance(readiness_time, frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel, rearvehicle_lonaccel, min_safety_distance);
}

void TA_EvaluateThreatEBW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel)
{
    float d_warning;
    float d_major;
    float d_emergency;
    float d_slowed = 0;

    float d_warning_Flexible = 0.0f;
    float d_major_Flexible = 0.0f;
    float d_emergency_Flexible = 0.0f;

    /* 车辆已刹车，并且减速度达到一定程度，不考虑反映时间，使用已减速公式 */
    if (rearvehicle_lonaccel < -3) {
        /* The vehicle has slowed down */
        d_slowed = Vetalk_calcEEBLSlowedDistance(frontvehicle_speed, 
                                                rearvehicle_speed, 
                                                frontvehicle_lonaccel, 
                                                rearvehicle_lonaccel);
    } 

    d_warning = Vetalk_calcEEBLWarningDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
    d_major = Vetalk_calcEEBLMajorDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);
    d_emergency = Vetalk_calcEEBLEmergencyDistance(frontvehicle_speed, rearvehicle_speed, frontvehicle_lonaccel);

    // d_warning_Flexible = Vetalk_calcFCWWarningFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_major_Flexible = Vetalk_calcFCWMajorFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);
    // d_emergency_Flexible = Vetalk_calcFCWEmergencyFlexibleDistance(frontvehicle_speed, frontvehicle_lonaccel, rearvehicle_speed);

    printf("<EBW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f, d_slowed:%4.2f\n",d_warning, d_major, d_emergency, d_slowed);
    // printf("d_warning_Flexible:%4.2f, d_major_Flexible:%4.2f, d_emergency_Flexible:%4.2f\n",d_warning_Flexible, d_major_Flexible, d_emergency_Flexible);
    
    return;
}

float Vetalk_calcICWWarningDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;

	Tr = 2.9;  // ICW_warning_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time * 1.5, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

/*
 * Vetalk_calcICWMajorDistance()
 * 
 * 计算警告级别的ICW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @local_speed: 车的速度
 *
 * return
 * float，警告级别的ICW安全距离
 */

float Vetalk_calcICWMajorDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;    

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;
	Tr = 1.8; // ICW_major_reaction_time_s;
	Ts = 0.4;

    readiness_time = Tr + Ts;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

/*
 * Vetalk_calcICWEmergencyDistance()
 * 
 * 计算严重警告级别的ICW安全距离
 * 
 * @pTA: 指针，指向结构体tTA, 代表TA全局变量
 * @local_speed: 车的速度
 *
 * return
 * float，严重警告级别的ICW安全距离
 */

float Vetalk_calcICWEmergencyDistance(float local_speed)
{
    float   readiness_time;
    float   min_safety_distance;
    float   rearvehicle_lonaccel;
	float 	Tr;
	float 	Ts;

    min_safety_distance = 0.0f;
    readiness_time = 0.0f;
    rearvehicle_lonaccel = 0.0f;
    Tr = 0.6; // ICW_major_reaction_time_s;
	Ts = 0.4;
    
    readiness_time = Tr + Ts; // ICW_emergency_reaction_time_s;
    min_safety_distance = 4;   // ICW_minsafety_distance_m;
    rearvehicle_lonaccel = -2; // ICW_decelerate_value_mps2;

    return _Vetalk_calcSafeDistance(readiness_time, 0.0f, local_speed, 0.0f, rearvehicle_lonaccel, min_safety_distance);
}

void TA_EvaluateThreatICW(float local_speed)
{    
    float d_warning;
    float d_major;
    float d_emergency;

    d_warning = 0.0f;
    d_major = 0.0f;
    d_emergency = 0.0f;

    d_warning = Vetalk_calcICWWarningDistance(local_speed);
    d_major = Vetalk_calcICWMajorDistance(local_speed);
    d_emergency = Vetalk_calcICWEmergencyDistance(local_speed);

    printf("<ICW> d_warning:%4.2f, d_major:%4.2f, d_emergency:%4.2f\n",d_warning, d_major, d_emergency);
}

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