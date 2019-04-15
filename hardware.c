/*
 * hardware.c
 *
 *  Created on: Jan 14, 2019
 *      Author: colli
 */
#include "msp.h"
#include "globals.h"
#include "hardware.h"
#include "pinout.h"



void LFXT_Init ()
{
    /* Pin setup for LFXT power and read*/
    PJ->SEL0 &=~ 0x03;
    PJ->SEL1 &=~ 0x03;

    PJ->SEL0 |=  0x01;
    PJ->SEL1 |=  0x01;

}
//================================================================
void LedOutput_Init()
{
  //  P1->SEL0 &=~ 0x01;
 //   P1->SEL1 &=~ 0x01;
   // P1->DIR  |=  0x01;
  //  P1->OUT  &=~ 0x01;

    P2->SEL0 &=~ 2;
    P2->SEL1 &=~ 2;
    P2->DIR |= 2;
    P2->OUT &=~ 2;


}
//================================================================
void Input_Init()
{
    //Set up buttons on MSP for interface
    P1->SEL0 &=~ 0x12;
    P1->SEL1 &=~ 0x12;
    P1->DIR  &=~ 0x12;
    P1->REN  |=  0x12;
    P1->OUT  |=  0x12;
}
//================================================================
void TimerA1_Init()
{
    TIMER_A1->CTL &=~ 0x3F7;  //Set TACTL to 0
    TIMER_A1->CTL |=  0x01D6;  //PG 132 in book
    TIMER_A1->EX0 = 0; //1:1
    TIMER_A1->CCR[0] = 4095;
    TIMER_A1->CCTL[0] |= 0x10;
    TIMER_A1->CTL |= TACLR;

    NVIC_SetPriority(TA1_0_IRQn, 3);
    NVIC_EnableIRQ(TA1_0_IRQn);
}
//================================================================
void TimerA2_Init()
{
    TIMER_A2->CTL &=~ 0x3F7;  //Set TACTL to 0
    TIMER_A2->CTL |=  0x01D6;  //PG 132 in book
    TIMER_A2->EX0 = 0; //1:1

}
//================================================================
void TimerA2_Delay(uint16_t ms) //with 32000 aclk 4.096 ticks = 1 ms.  Basic delay that keeps msp busy
{
    if (ms*4096 < 65535)
    {
        TIMER_A2->CCR[0] = ms*40;
        while ((TIMER_A2->CCTL[0]&1)==0);
        TIMER_A2->CCTL[0]&= ~1; //clears int flag

    }

}
//================================================================
void Raspi_Init()
{
    CAM_EN;
    //Setup P2.3 as an output for Raspi 2wire com
    P2->SEL0 &=~ BIT3;
    P2->SEL1 &=~ BIT3;
    P2->DIR  |=  BIT3;
    P2->OUT  &=~ BIT3;

    //Setup P2.2 as an input for Raspi 2wire com
    P2->SEL0 &=~ BIT2;
    P2->SEL1 &=~ BIT2;
    P2->DIR  &=~ BIT2;
    //P2->REN  |=  BIT2;
    P2->OUT  &=~ BIT2;


}
//================================================================
//uint32_t BPM-to-Ticks(int )


