#include "Watchy_7_SEG.h"

#define DARKMODE true

const unsigned char *numbers [10] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};

void Watchy7SEG::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    drawDate();
    drawSteps();
    drawWeather();
    drawBattery();
    display.drawBitmap(121, 143, WIFI_CONFIGURED ? wifi : wifioff, 26, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    if(BLE_CONFIGURED){
        display.drawBitmap(85, 170, bluetooth, 13, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
}

void Watchy7SEG::drawTime(){
    //Heures
    display.drawBitmap(17, 12, numbers[currentTime.Hour/10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    display.drawBitmap(51, 12, numbers[currentTime.Hour%10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //second digit
    //separe
    display.drawBitmap(85, 12, colon, 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    //Minute
    display.drawBitmap(119, 12, numbers[currentTime.Minute/10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    display.drawBitmap(153, 12, numbers[currentTime.Minute%10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //second digit
    //ok farfadet46
}

void Watchy7SEG::drawDate(){
    //jour
    display.drawBitmap(17, 76, numbers[currentTime.Day/10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    display.drawBitmap(51, 76, numbers[currentTime.Day%10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //second digit
    //separateur
    display.drawBitmap(85, 76, separe, 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //separator
    //mois
    display.drawBitmap(119, 76, numbers[currentTime.Month/10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    display.drawBitmap(153, 76, numbers[currentTime.Month%10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //second digit
    //ok farfadet46
}
void Watchy7SEG::drawSteps(){
    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0){
      sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    display.drawBitmap(109, 170, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(132, 174);
    display.setFont(&DSEG7_Classic_Regular_15);
    display.println(stepCount);
    //ok farfadet46
}
void Watchy7SEG::drawBattery(){
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1){
        //batteryLevel = 3;
        display.drawBitmap(155, 142, bat3, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if(VBAT > 3.95 && VBAT <= 4.1){
        //batteryLevel = 2;
        display.drawBitmap(155, 142, bat2, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if(VBAT > 3.80 && VBAT <= 3.95){
        //batteryLevel = 1;
        display.drawBitmap(155, 142, bat1, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if(VBAT <= 3.80){
        //batteryLevel = 0;
        display.drawBitmap(155, 142, bat0, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    //ok farfadet46
}

void Watchy7SEG::drawWeather(){

    weatherData currentWeather = getWeatherData();

    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;

    display.drawBitmap(5, 145, numbers[temperature/10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //first digit
    display.drawBitmap(38, 145, numbers[temperature%10], 30, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK); //second digit
    //display.println(temperature);
    display.drawBitmap(71, 145, celsius, 26, 20, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}
