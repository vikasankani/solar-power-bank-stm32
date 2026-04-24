#include "main.h"
#include <stdio.h>

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

// ---------- FUNCTIONS ----------

// Read ADC channel
uint32_t readADC(uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    return HAL_ADC_GetValue(&hadc1);
}

// Convert ADC → voltage
float adcToVoltage(uint32_t adc_val) {
    float v = (adc_val * 3.3) / 4095.0;
    return v;
}

// Apply voltage divider (adjust factor!)
float scaleVoltage(float v_adc, float factor) {
    return v_adc * factor;
}

// Set PWM duty (0–100)
void setPWM(uint8_t duty) {
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, duty * 10); 
    // assuming ARR = 1000
}

// ---------- MAIN ----------

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_ADC1_Init();
    MX_TIM2_Init();

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

    float solar_v, battery_v;

    while (1)
    {
        // Read ADC
        uint32_t solar_adc = readADC(ADC_CHANNEL_1);
        uint32_t battery_adc = readADC(ADC_CHANNEL_0);

        // Convert to voltage
        float solar_adc_v = adcToVoltage(solar_adc);
        float battery_adc_v = adcToVoltage(battery_adc);

        // Scale (IMPORTANT: adjust based on your divider)
        solar_v = scaleVoltage(solar_adc_v, 6.0);   // for 18V panel
        battery_v = scaleVoltage(battery_adc_v, 2.0); // for battery

        // -------- CONTROL LOGIC --------

        if (solar_v > battery_v + 0.5) {
            // Allow charging
            setPWM(80); // 80% duty
        }
        else {
            // Stop charging
            setPWM(0);
        }

        // -------- DEBUG --------
        printf("Solar: %.2f V | Battery: %.2f V\n", solar_v, battery_v);

        HAL_Delay(1000);
    }
}
