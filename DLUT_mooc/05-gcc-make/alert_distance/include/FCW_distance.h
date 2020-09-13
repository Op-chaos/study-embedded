

float Vetalk_calcFCWSlowedDistance(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel);

float Vetalk_calcFCWWarningDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

float Vetalk_calcFCWMajorDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

float Vetalk_calcFCWEmergencyDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

float Vetalk_calcFCWWarningFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

float Vetalk_calcFCWMajorFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

float Vetalk_calcFCWEmergencyFlexibleDistance(float frontvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_speed);

void TA_EvaluateThreatFCW(float frontvehicle_speed, float rearvehicle_speed, float frontvehicle_lonaccel, float rearvehicle_lonaccel);














