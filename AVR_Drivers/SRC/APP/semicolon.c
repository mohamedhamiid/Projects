#include "util/delay.h"
#include "../../INCLUDE/MCAL/DIO/DIO.h"
#include "../../INCLUDE/MCAL/ADC/ADC.h"
#include "../../INCLUDE/MCAL/TIMER/TIMER.h"
#include "../../INCLUDE/MCAL/UART/UART.h"
#include "../../INCLUDE/MCAL/ADC/ADC_priv.h"
#include "../../INCLUDE/MCAL/UART/UART_priv.h"
#include "../../INCLUDE/MCAL/TIMER/TIMER_priv.h"
#include "../../INCLUDE/MCAL/ADC/ADC_cfg.h"
#include "../../INCLUDE/MCAL/DIO/DIO_priv.h"
#include "../../SERVICES/bit_utilies.h"
#include "../../INCLUDE/HAL/Led/Led.h"
#include "../../INCLUDE/HAL/seg_7/seg_7.h"
#include "../../INCLUDE/HAL/Button/Button.h"
#include "../../INCLUDE/HAL/Lcd/Lcd.h"
#include "../../INCLUDE/HAL/Keypad/Keypad.h"
#include "../../INCLUDE/MCAL/EXTINT/EXTINT.h"
#include "../../INCLUDE/MCAL/GIE/GIE.h"
#include "../../INCLUDE/HAL/STEPPER/STEPPER.h"
#include "avr/interrupt.h"
//////////////////////SEMICOLON/////////////////////////
#define DELAY_TO_PARALLEL_SEVSG   0.5

//void updata_TimeSecond(void);
void display_void_timeclock(void);
u8 GetSetting_Clock(u8 *capy_u16PtrArray,u8 capy_SizeArray);
void UpdataSetting_Clock(u8 *ptrcount_Second,u8 *ptrcount_Minutes,u8 *ptrcount_Hours,u8 *capy_u16PtrArray);
/*Global varible to set time clock */
volatile u8 Global_u8Seconds=0;
u8 Global_u8Hours=0,Global_u8Minutes=0;

ISR(TIMER1_COMPA_vect){
	Global_u8Seconds++;
	if(Global_u8Seconds==60)
		{
			Global_u8Seconds=0;
			Global_u8Minutes++;
		}
		if(Global_u8Minutes==60)
		{
			Global_u8Minutes=0;
			Global_u8Hours++;
		}
		if(Global_u8Hours==24)
		{
			Global_u8Seconds=0;
			Global_u8Hours=0;
		}
}

Lcd_tstrucCfg Lcd1={
		.DataPortId=DIO_u8_PORTA,
		.CtrlPortId=DIO_u8_PORTC,
		.RS_Pin=6,
		.EN_Pin=7,
		.RW_Pin=8
	};

	Keypad_tstrucCfg Keypad1={
		 .DataPortId=DIO_u8_PORTD
	};

	Seg_tCfg segments = { // Left
		 .Port = DIO_u8_PORTB ,
		 .Common_Type = Seg_CommCathode ,
	};
	u8 Intro_line1[]= "TO SET CLOCK ";
	u8 Intro_line2[]= "PRESS 0 ";

	u8 EnterHours[] = "Enter Hours= ";
	u8 EnterMin[]   = "Enter Min= ";
	u8 EnterSec[]   = "Enter Sec= ";
	u8 Confirm[]    = "Press = To confirm";
	u8 ThankYou[]   = "Thank U :) ";
	u8 WrongChoice[]   = " Wrong Choice ";
int main(void) {
	u8 Loc_u8pressedKey = Keypad_NotPressed;
	u8 Array[6]={'#','#','#','#','#','#'};

//	DIO_voidInit();
	GIE_voidGlobalInterruptEnable();
	/********************* Timer 0 *************************/
	Timer_structTimerCfg timer1={
			.Timer_u8TimerNo =TIMER_NO_TIMER1,
			.Timer_u8TimerForceOutputCompare=TIMER1_FOC_OFF,
			.Timer_u8WaveFormGenerationMode=TIMER1_MODE_CTC,
			.Timer_u8ClockSelect=TIMER1_CLOCK_PRESCALLING_1024,
//			.Timer_Interrupt=TIMER_INTERRUPT_ON
			.Timer1_u8Channel=TIMER1_CHANNEL_A
	};
	Timer_structTimerCfg timer1={
			.Timer_u8TimerNo =TIMER_NO_TIMER1,
			.Timer_u8TimerForceOutputCompare=TIMER1_FOC_OFF,
			.Timer_u8WaveFormGenerationMode=TIMER1_MODE_CTC,
			.Timer_u8ClockSelect=TIMER1_CLOCK_PRESCALLING_1024,
//			.Timer_Interrupt=TIMER_INTERRUPT_ON
			.Timer1_u8Channel=TIMER1_CHANNEL_A
	};
//	TCNT0 = 192 ;
	TIMER_voidCTCcfg(&timer1,976);
	TIMSK |= 0b00010000;
	TIMER_voidTimerInit(&timer1);

	/******************** 7 SEG   *************************/
	DIO_enuSetPortDirection(DIO_u8_PORTC,0b00111111); // 7SEG Power --> 0-5 Port C
	DIO_enuSetPortValue(DIO_u8_PORTC,0b00111111); // 7SEG Power --> 0-5 Port C
	Seg_vidInit(&segments);
	/********************** Lcd ****************************/
	Lcd_vidInit(&Lcd1);
//	Lcd_CLR(&Lcd1);
	/********************* KeyPad **************************/

	Keypad_vidInit(&Keypad1);


	/********************* Intro **************************/
	Lcd_WriteString(&Lcd1,Intro_line1);
	Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
	Lcd_WriteString(&Lcd1,Intro_line2);


	while (1) {
		Loc_u8pressedKey=Keypad_u8GetPressedKey(&Keypad1);
		if (Loc_u8pressedKey != Keypad_NotPressed) {
			if (Loc_u8pressedKey == '0') {
			    GetSetting_Clock(Array,6);
			    Lcd_CLR(&Lcd1);
			    Lcd_WriteString(&Lcd1,Intro_line1);
			    Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
			    Lcd_WriteString(&Lcd1,Intro_line2);
			    UpdataSetting_Clock(&Global_u8Seconds,&Global_u8Minutes,&Global_u8Hours,Array);
			} else {
				Lcd_CLR(&Lcd1);
				Lcd_GotoPosition(&Lcd1,LCD_LINE1,0);
				Lcd_WriteString(&Lcd1,WrongChoice);
				_delay_ms(500);
				Lcd_CLR(&Lcd1);
				Lcd_WriteString(&Lcd1,Intro_line1);
				Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
				Lcd_WriteString(&Lcd1,Intro_line2);
				_delay_ms(500);
			}
		}
		display_void_timeclock();
	}

	return 0;
}
/*call back function when ISR Happen */
//void updata_TimeSecond(void)
//{
//	count_Second++;
//}
void display_void_timeclock(void)
{
	for(int i=0;i<6;i++)
	{
		switch(i)
		{
		case 0:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
		    Seg_vidOn(&segments,Global_u8Seconds%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i, DIO_u8_HIGH);
			break;
		case 1:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
			Seg_vidOn(&segments,Global_u8Seconds/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i, DIO_u8_HIGH);
			break;
		case 2:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
			Seg_vidOn(&segments,Global_u8Minutes%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_HIGH);
			break;
		case 3:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
			Seg_vidOn(&segments,Global_u8Minutes/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_HIGH);
			break;
		case 4:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
			Seg_vidOn(&segments,Global_u8Hours%10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_HIGH);
			break;
		case 5:
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_LOW);
			Seg_vidOn(&segments,Global_u8Hours/10);
			_delay_ms(DELAY_TO_PARALLEL_SEVSG);
			DIO_enuSetPinValue(DIO_u8_PORTC, i , DIO_u8_HIGH);
			break;
		default:break;
		}
	}



}
u8 GetSetting_Clock(u8 *capy_u16PtrArray,u8 capy_SizeArray)
{
	u8 loc_counter=0;
	u8 loc_u8pressedKey=Keypad_NotPressed;
	Lcd_CLR(&Lcd1);
	Lcd_WriteString(&Lcd1,EnterHours);
	_delay_ms(100);
	while(loc_counter <=capy_SizeArray)
	{   /*recived clock from user */
		do{
			loc_u8pressedKey=Keypad_u8GetPressedKey(&Keypad1);
		}while (loc_u8pressedKey==Keypad_NotPressed);
		if((loc_u8pressedKey!=Keypad_NotPressed) && (loc_u8pressedKey!='c'))
		{
			capy_u16PtrArray[loc_counter]=loc_u8pressedKey;
			u8 letter = capy_u16PtrArray[loc_counter];
			Lcd_WriteLetter(&Lcd1,&letter);
			_delay_ms(100);
		}
		if(loc_counter==1)
		{
			Lcd_CLR(&Lcd1);
			Lcd_WriteString(&Lcd1,EnterMin);
			_delay_ms(100);
		}
		if(loc_counter==3)
		{
			Lcd_CLR(&Lcd1);
			Lcd_WriteString(&Lcd1,EnterSec);
			_delay_ms(100);
		}
		if(loc_counter==5)
		{
			Lcd_CLR(&Lcd1);
			Lcd_WriteString(&Lcd1,ThankYou);
			_delay_ms(100);
			return 0 ;
		}
		if(loc_u8pressedKey=='c')
		{
			Lcd_CLR(&Lcd1);
			Lcd_WriteString(&Lcd1,Intro_line1);
			Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
			Lcd_WriteString(&Lcd1,Intro_line2);
			_delay_ms(100);
			break ; /* to out from while loop */
		}
		loc_counter++;

	}
}
void UpdataSetting_Clock(u8 *ptrcount_Second,u8 *ptrcount_Minutes,u8 *ptrcount_Hours,u8 *capy_u16PtrArray)
{

   *ptrcount_Hours  = 10*(capy_u16PtrArray[0]-48)+(capy_u16PtrArray[1]-48);
   *ptrcount_Minutes= 10*(capy_u16PtrArray[2]-48)+(capy_u16PtrArray[3]-48);
   *ptrcount_Second = 10*(capy_u16PtrArray[4]-48)+(capy_u16PtrArray[5]-48);

}

///////////////////////////////////////////////////////////



