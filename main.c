#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "remote.h"   
//ALIENTEK Mini STM32开发板范例代码22
//红外遥控实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

 void initGame(); //声明自定义函数

 typedef struct
{
		u8 x;
		u8 y;
		u8 number;
		u8 isDefault; //是否是默认数字，如是则不可更改
		u16 bgColor; // 格子色和字的背景色
}cell; 

cell cells[9][9];
//////////////////////////////////////////////////////////////////////////////
int main(void)
 { 
	u8 key;
	u8 t=0;	
	u8 *str=0; 	
	delay_init();	    	 //延时函数初始?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	Remote_Init();			//红外接收初始化	
	
	initGame();
	 
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,280,200,16,16,"Result:");	
	LCD_ShowString(60,300,200,16,16,"hh");
	
	 
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 
			LCD_ShowNum(116,130,key,3,16);		//显示键值
			LCD_ShowNum(116,150,RmtCnt,3,16);	//显示按键次数		  
			switch(key)
			{
				case 0:str="ERROR";break;			   
				case 162:str="POWER";LED1=1;break;	    
				case 98:str="UP";LED1=0;break;	    
				case 2:str="PLAY";break;		 
				case 226:str="ALIENTEK";break;		  
				case 194:str="RIGHT";break;	   
				case 34:str="LEFT";break;		  
				case 224:str="VOL-";break;		  
				case 168:str="DOWN";break;		   
				case 144:str="VOL+";break;		    
				case 104:str="1";break;		  
				case 152:str="2";break;	   
				case 176:str="3";break;	    
				case 48:str="4";break;		    
				case 24:str="5";break;		    
				case 122:str="6";break;		  
				case 16:str="7";break;			   					
				case 56:str="8";break;	 
				case 90:str="9";break;
				case 66:str="0";break;
				case 82:str="DELETE";break;		 
			}
			LCD_Fill(116,170,116+8*8,170+16,WHITE);	//清除之前的显示
			LCD_ShowString(116,170,200,16,16,str);	//显示SYMBOL
		}else delay_ms(10);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
void initGame(){
	u8 x = 2;
	u8 y = 2;
	u8 count;
	u8 size = lcddev.width/9;

	//画格子
	for(count = 10; count > 0; count --){
			LCD_DrawLine(2,y,size * 9 + 1,y);
			y = y + size;
	}
	
	for(count = 10; count > 0; count --){
			LCD_DrawLine(x,2,x,size * 9 + 1);
			x = x + size;
	}

	//初始化cell
	for(x = 0; x < 9; x++)
	{		
		for(y = 0; y < 9; y++)
		{
			cells[x][y].x = 2+size*y+size/3;
			cells[x][y].y = 1+size*x+ size/3;
			cells[x][y].bgColor = WHITE;
			cells[x][y].number = 0;
			cells[x][y].isDefault = 0;
		}	
	}

	///////////////////初始化默认格子///////////////////////
	cells[0][0].number = 6;
	cells[0][2].number = 5;
	cells[1][1].number = 8;
	cells[2][1].number = 3;

	cells[1][3].number = 9;
	cells[1][5].number = 1;
	cells[2][3].number = 7;
	cells[2][5].number = 6;
	
	cells[0][6].number = 3;
	cells[0][8].number = 9;
	cells[1][7].number = 2;
	cells[2][7].number = 4;

	cells[3][0].number = 1;
	cells[3][2].number = 4;
	cells[5][0].number = 3;
	cells[5][2].number = 8;
	
	cells[4][4].number = 8;

	cells[3][6].number = 7;
	cells[3][8].number = 5;
	cells[5][6].number = 2;
	cells[5][8].number = 4;
	
	cells[6][1].number = 5;
	cells[7][1].number = 6;
	cells[8][0].number = 7;
	cells[8][2].number = 9;
	
	cells[6][3].number = 4;
	cells[6][5].number = 3;
	cells[7][3].number = 1;
	cells[7][5].number = 8;
	
	cells[6][7].number = 9;
	cells[7][7].number = 5;
	cells[8][6].number = 8;
	cells[8][8].number = 1;
	
	for(x = 0; x < 9; x++){		
		for(y = 0; y < 9; y++){
			if(cells[x][y].number != 0){
				cells[x][y].isDefault = 1;
				cells[x][y].bgColor = GRAY;
				LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
			}
		}
	}
	/////////////画数字//////////////////////
	POINT_COLOR=BLACK;
	for(x = 0; x < 9; x++){		
		for(y = 0; y < 9; y++){		
			if(cells[x][y].number != 0){
				BACK_COLOR = cells[x][y].bgColor;
				LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
			}
		}	
	}

	/////////////////初始化当前格子/////////////////
	LCD_Fill(3 + size*4, 3 + size*4,1 + size*5 , 1 + size*5 , LIGHTBLUE);
	BACK_COLOR = LIGHTBLUE;
	LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
}