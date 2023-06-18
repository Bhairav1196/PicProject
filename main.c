/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F45K50
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"


uint16_t adcCal(){
    uint16_t convertedVal = 0;
    ADC_SelectChannel(channel_AN0);
    ADC_StartConversion();
    __delay_ms(1);
    
    if(ADC_IsConversionDone()==1){
        //printf("ADC_Done: ");
        return ADC_GetConversionResult();
    }
    else{
        return 0;
    }    
}

double convertValue(uint16_t *val){
    return ((*val) * 0.001526);  /*------returning val=((val/65535)*100)------*/
}

double adcMax(double *maxNo){
    for(int i=0;i<10;i++){ 
        //printf("NO:%f\r\n", *(maxNo+i));
        if(*maxNo < *(maxNo + i)){
            *maxNo = *(maxNo+i);
        } 
    }
    return *maxNo;
}
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    ADC_Initialize();
    EUSART1_Initialize();
    
    /*---variables--*/
    led = 0;
    uint16_t adcVal;
    uint16_t *adcPtr = &adcVal;
    double adcArray[10];
    double *arrayPtr = &adcArray;
    double convertedVal;
    double max;
    /*--------------*/
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    
    while (1)
    {
        /*---collecting array data---*/
        for(int i=0;i<10;i++){
            adcVal = adcCal(); 
            adcArray[i] = convertValue(&adcVal);
            __delay_ms(10);
        }
        /*--find max value in adc array--*/
        /*
        for(int i=0;i<10;i++){
            printf("adcArray[%d]: %0.3f \r\n", i, adcArray[i]);
        }*/
        
        double max = adcMax(&adcArray);
        printf("Maximum value: %.3f \r\n", max);
        __delay_ms(1000); 

        
        
#if 0
        if(EUSART1_is_rx_ready()){
            unsigned char rxData = EUSART1_Read();
            if( rxData == 1){
                PORTDbits.RD0 = 1;
            } 
            else{
                PORTDbits.RD0 = 0;
            }
        }
        if(EUSART1_is_tx_ready())
            {
                EUSART1_Write(count);
            }
#endif
        // Add your application code
#if 0
        if(count<1000){
            PORTDbits.RD0 = 1;
        }
        else{
            PORTDbits.RD0 = 0;
        }
#endif
#if 0
        
    
    
    //uint8_t val = convertedValue;
    EUSART1_Write("H");
    
    __delay_ms(100);
    
#endif
    
    
#if 0
    EUSART1_Write(1);
    __delay_ms(100);
            if(EUSART1_is_rx_ready()){
            unsigned char rxData = EUSART1_Read();
            if( rxData == 1){
                PORTDbits.RD0 = 1;
            } 
            else{
                PORTDbits.RD0 = 0;
            }
        }
#endif
        
        //__delay_ms(1000);
        
    }
}
/**
 End of File
*/