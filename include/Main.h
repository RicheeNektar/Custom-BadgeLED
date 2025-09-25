#ifndef MAIN_H
#define MAIN_H

#include <FreeRTOS.h> // required for task.h
#include <task.h>

void setupPins();
void loadConfigs();
void setupTasks();
void setup();

void loop();

#endif //MAIN_H
