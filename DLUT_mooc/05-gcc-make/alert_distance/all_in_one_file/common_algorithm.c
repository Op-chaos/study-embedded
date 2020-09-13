#include <stdio.h>
#include "common_algorithm.h"
float _Vetalk_calcSafeDistance_Oncoming(float readiness_time, float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed, float rearvehicle_lonaccel, float min_safety_distance)
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
float _Vetalk_calcSafeDistance_Inreadinesstime(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float min_safety_distance)
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

float _Vetalk_calcSafeDistance_RearVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
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
float _Vetalk_calcSafeDistance_FrontVehicleStopedFirst(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
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
float _Vetalk_calcSafeDistance(float readiness_time, float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel, float min_safety_distance)
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
