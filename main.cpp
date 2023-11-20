/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
DigitalOut led(LED1);  // 使用MBED OS的DigitalOut类，控制板上的LED
DigitalIn button(BUTTON1);
namespace {
#define PERIOD_MS 2000ms
}

int main()
{
printf("MBED OS Template Code\r\n");
  
    while (1) {
        // 读取按钮状态
        if (button == 0) {
            // 按钮被按下，点亮LED
            led = 1;
            printf("Button pressed\r\n");
        } else {
            // 按钮未被按下，熄灭LED
            led = 0;
        }

        // 在这里可以添加其他代码，实现你的功能

        // MBED OS的主循环中会处理一些系统任务
        ThisThread::sleep_for(10ms);  // 休眠，避免循环过于频繁
    }
}
