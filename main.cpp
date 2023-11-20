/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
/*DigitalOut led(LED1);  // 使用MBED OS的DigitalOut类，控制板上的LED
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
            led = 0;
            printf("Button pressed\r\n");
        } else {
            // 按钮未被按下，熄灭LED
            led = 1;
        }

        // 在这里可以添加其他代码，实现你的功能

        // MBED OS的主循环中会处理一些系统任务
        ThisThread::sleep_for(10ms);  // 休眠，避免循环过于频繁
    }
}*/
/*
#include "platform/mbed_wait_api.h"

DigitalIn button(BUTTON1);
DigitalOut led(LED1);

Timer buttonTimer;
Ticker ticker;

bool buttonPressed = false;

void buttonIRQ() {
    if (button.read() == 0) {
        buttonTimer.start();
    } else {
        buttonTimer.stop();
        printf("Durée d'appui sur le bouton : %lld microsecondes\n", buttonTimer.elapsed_time().count()); 
        buttonTimer.reset();
        buttonPressed = !buttonPressed;
    }
}

void toggleLED() {
    led = !led;
}

int main() {
    button.rise(callback(buttonIRQ));  // Configuration de l'interruption sur la baisse du bouton
    ticker.attach(&toggleLED, 1s);  // Configuration du ticker avec une fréquence de 1 Hz

    while (true) {
    if (button == 0 && !buttonPressed) {
        // Détecter le front montant du bouton
        buttonPressed = true;
        buttonTimer.start();
        printf("Bouton pressé\n");
    } else if (button == 1 && buttonPressed) {
        // Détecter le front descendant du bouton
        buttonPressed = false;
        buttonTimer.stop();
        printf("Durée d'appui sur le bouton : %lld microsecondes\n", buttonTimer.elapsed_time().count());
        buttonTimer.reset();
    }
    wait(0.1);  // Délai de 100 ms pour éviter le polling excessif
}
}*/
#include "mbed.h"

// Déclaration des objets représentant le bouton, la LED et le timer
InterruptIn button(BUTTON1);
DigitalOut led(LED1);
Timer buttonTimer;

// Variable pour stocker le temps d'appui sur le bouton
float buttonPressDuration = 0.0f;

// Fonction appelée lorsqu'une interruption est déclenchée par le bouton
void buttonPressed() {
    if (button) {
        // Bouton relâché, arrêter le timer et afficher la durée d'appui
        buttonTimer.stop();
        buttonPressDuration = buttonTimer.elapsed_time().count();
        printf("Bouton relâché. Durée d'appui : %.2f secondes\n", buttonPressDuration);
    } else {
        // Bouton appuyé, démarrer le timer
        buttonTimer.reset();
        buttonTimer.start();
        printf("Bouton appuyé\n");
    }
}

    void blinkLed() {
        led = !led;
    }

int main() {
    // Attacher la fonction d'interruption au front descendant (le bouton est actif à l'état bas)
    button.fall(&buttonPressed);

    // Ticker pour faire clignoter la LED
    Ticker ledTicker;
    float blinkFrequency = 1.0f; // Fréquence initiale en Hz

    // Fonction appelée périodiquement pour faire clignoter la LED

    // Attacher la fonction de clignotement au ticker
    ledTicker.attach(&blinkLed, 1.0 / blinkFrequency);

    // Boucle principale
    while (1) {
        // Attendre jusqu'à ce que le bouton soit appuyé pour changer la fréquence
        if (button) {
            // Changer la fréquence à chaque appui
            blinkFrequency += 0.5f;
            printf("Fréquence de clignotement changée à %.2f Hz\n", blinkFrequency);
            ledTicker.detach();
            ledTicker.attach(&blinkLed, 1.0 / blinkFrequency);     
        }
        ThisThread :: sleep_for(200ms);
    }
}

