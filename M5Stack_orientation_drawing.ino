/* Copyright 2024 Taisyu Shibata
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <M5Stack.h>
#include <Madgwick.h>
Madgwick MadgwickFilter;

int16_t ax, ay, az;//加速度　int16_tは2バイトの符号付き整数
int16_t gx, gy, gz;//角速度　同上
float ROLL, PITCH, YAW;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    delay(300);
    MadgwickFilter.begin(100);//フィルタのサンプリングを100Hzで
}

void loop()
{
    MadgwickFilter.updateIMU(gx / 131.0, gy / 131.0, gz / 131.0, ax / 16384.0, ay / 16384.0, az / 16384.0);
    ROLL = MadgwickFilter.getRoll();
    PITCH = MadgwickFilter.getPitch();
    YAW  = MadgwickFilter.getYaw();
    Serial.print(ROLL); Serial.print(",");
    Serial.print(PITCH); Serial.print(",");
    Serial.print(YAW);
    Serial.print("\n");
    delay(10);
}
