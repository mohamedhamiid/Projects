//#include "util/delay.h"
//#include "../../INCLUDE/MCAL/DIO/DIO.h"
//#include "../../INCLUDE/MCAL/ADC/ADC.h"
//#include "../../INCLUDE/MCAL/TIMER/TIMER.h"
//#include "../../INCLUDE/MCAL/UART/UART.h"
//#include "../../INCLUDE/MCAL/ADC/ADC_priv.h"
//#include "../../INCLUDE/MCAL/UART/UART_priv.h"
//#include "../../INCLUDE/MCAL/TIMER/TIMER_priv.h"
//#include "../../INCLUDE/MCAL/ADC/ADC_cfg.h"
//#include "../../INCLUDE/MCAL/DIO/DIO_priv.h"
//#include "../../SERVICES/bit_utilies.h"
//#include "../../INCLUDE/HAL/Led/Led.h"
//#include "../../INCLUDE/HAL/seg_7/seg_7.h"
//#include "../../INCLUDE/HAL/Button/Button.h"
//#include "../../INCLUDE/HAL/Lcd/Lcd.h"
//#include "../../INCLUDE/HAL/Keypad/Keypad.h"
//#include "../../INCLUDE/MCAL/EXTINT/EXTINT.h"
//#include "../../INCLUDE/MCAL/GIE/GIE.h"
//#include "../../INCLUDE/HAL/STEPPER/STEPPER.h"
//#include "avr/interrupt.h"
//
////////////////////////////////////////////////////////////////////
///************************IMT PROJECT*****************************/
//u8 EnterMessageLine1[]="1) New User";
//u8 EnterMessageLine2[]="2) Old User";
//
//u8 NewUserNewPass[]="New Password";
//u8 NewUserNewPassConfirm[]="Confirm Password";
//
//u8 NewOldUserPass[]="Enter Password";
//
//u8 NewIncorrectPass[]="Incorrect Password";
//u8 NewcorrectPass[]="correct Password";
//
//u8 NewPass[6];
//u8 ConfPass[6];
//u8 EnterPass[6];
//
//u8 correct = 1;
//int main(){
//		Lcd_tstrucCfg Lcd1={
//				.DataPortId=DIO_u8_PORTB,
//				.CtrlPortId=DIO_u8_PORTA,
//				.RS_Pin=0,
//				.RW_Pin=1,
//				.EN_Pin=2
//		};
//		Keypad_tstrucCfg Keypad1={
//				.DataPortId=DIO_u8_PORTC
//		};
//
//		Lcd_vidInit(&Lcd1);
//		Keypad_vidInit(&Keypad1);
////		UART_structCfg uart={
////				.UART_u8BaudRate=UART_BAUD_RATE_9600,
////				.UART_u8CharSize=UART_CHARACTER_SIZE_8_BIT,
////				.UART_u8Parity=UART_PARITY_DISABLED,
////				.UART_u8Mode=UART_MODE_ASYNCHRONOUS,
////				.UART_u8StopBit=UART_STOP_BIT_SELECT_1_BIT,
////				.UART_u8EnableTXorRX=UART_ENABLE_TX_RX,
////		};
////		UART_voidInit(&uart);
/////////////////////////////////////////////////////////
//		UART_structCfg uart={
//					.UART_u8BaudRate=UART_BAUD_RATE_9600,
//					.UART_u8CharSize=UART_CHARACTER_SIZE_8_BIT,
//					.UART_u8Parity=UART_PARITY_EVEN,
//					.UART_u8Mode=UART_MODE_ASYNCHRONOUS,
//					.UART_u8StopBit=UART_STOP_BIT_SELECT_1_BIT,
//					.UART_u8EnableTXorRX=UART_ENABLE_RX,
//			};
//			Led_tCfg Led1 = {
//				.Led_NestStruct.Port = DIO_u8_PORTD ,
//				.Pin  = DIO_u8_PIN2 ,
//				.Led_NestStruct.Active_Status = Led_Active_High ,
//				.Led_NestStruct.Current_Status= Led_Active_High_High
//			};
//		//	Led_vidLedInit(&Led1);
//		Led_vidLedInit(&Led1);
//		UART_voidInit(&uart);
////		u8 Loc_u8UARTReturnData;
////		while(1){
////			Loc_u8UARTReturnData = UART_u8GetChar();
////			if(Loc_u8UARTReturnData=='1')
////				Led_vidOn(&Led1);
////			else if(Loc_u8UARTReturnData=='2')
////				Led_vidOff(&Led1);
////		}
/////////////////////////////////////////////////////////
//while (1){
//	    Lcd_GotoPosition(&Lcd1,LCD_LINE1,0);
//		Lcd_WriteString(&Lcd1,EnterMessageLine1);
//		Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
//		Lcd_WriteString(&Lcd1,EnterMessageLine2);
//		UCSRB=0b00010000;
//u8 main1=0;
//main1 = UART_u8GetChar();
////main1=Keypad_u8GetPressedKey(&Keypad1);
//if (main1=='1'){
//	Lcd_CLR(&Lcd1);
//	Lcd_WriteString(&Lcd1,NewUserNewPass);
//	Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
//
//	for(u8 passCounter = 0 ; passCounter<6 ;passCounter++){
//		u8 ch=0;
//		UCSRB=0b00010000;
//		do{
//			_delay_ms(200);
//			ch=UART_u8GetChar();
//			_delay_ms(100);
//		}while(ch >= '9' || ch <= '0');
//		UCSRB=0b00000000;
//		NewPass[passCounter] = ch;
//		Lcd_GotoPosition(&Lcd1,LCD_LINE2,passCounter);
////		u8 ch = NewPass[passCounter];
//		Lcd_WriteLetter(&Lcd1,&ch);
//		_delay_ms(500);
//
//	}
//
//	Lcd_CLR(&Lcd1);
//	Lcd_WriteString(&Lcd1,NewUserNewPassConfirm);
//	Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
//
//	for(u8 passCounter = 0 ; passCounter<6 ;passCounter++){
//		u8 ch=0;
//		UCSRB=0b00010000;
//		do{
//			_delay_ms(200);
//			ch=UART_u8GetChar();
//			_delay_ms(100);
//		}while(ch >= '9' || ch <= '0');
//		UCSRB=0b00000000;
//		ConfPass[passCounter] = ch;
//		Lcd_GotoPosition(&Lcd1,LCD_LINE2,passCounter);
////		ch = ConfPass[passCounter];
//		Lcd_WriteLetter(&Lcd1,&ch);
//		_delay_ms(500);
//	}
//
//			Lcd_CLR(&Lcd1);
//	for(u8 passCounter = 0 ; passCounter<6 ;passCounter++){
//		if (NewPass[passCounter] != ConfPass[passCounter])
//			correct=0;}
//
//		if(correct){
//			Lcd_WriteString(&Lcd1,NewcorrectPass);
//			_delay_ms(1000);
//		}
//		else {
//			Lcd_WriteString(&Lcd1,NewIncorrectPass);
//						_delay_ms(500);
//		}
//		UCSRB=0b00010000;
//	}
//else if(main1=='2'){
//	Lcd_CLR(&Lcd1);
//	Lcd_WriteString(&Lcd1,NewOldUserPass);
//	Lcd_GotoPosition(&Lcd1,LCD_LINE2,0);
//	for(u8 passCounter = 0 ; passCounter<6 ;passCounter++){
//		u8 ch;
//		UCSRB=0b00010000;
//				do{
//					_delay_ms(200);
//					ch=UART_u8GetChar();
//					_delay_ms(100);
//				}while(ch >= '9' || ch <= '0');
//				UCSRB=0b00000000;
//			EnterPass[passCounter] = ch;
//	//		Lcd_GotoPosition(&Lcd1,LCD_LINE2,passCounter);
//	//		u8 ch = NewPass[passCounter];
//			Lcd_WriteLetter(&Lcd1,&ch);
//			_delay_ms(1000);
//	}
//	Lcd_CLR(&Lcd1);
//		for(u8 passCounter = 0 ; passCounter<6 ;passCounter++){
//			if (EnterPass[passCounter] != NewPass[passCounter])
//				correct=0;}
//
//		   if(correct){
//				Lcd_WriteString(&Lcd1,NewcorrectPass);
//				_delay_ms(1000);
//			}
//			else {
//				Lcd_WriteString(&Lcd1,NewIncorrectPass);
//							_delay_ms(1000);
//			}
//
//
//}
//}
//}
///*****************************End of project**************************/
//
//
