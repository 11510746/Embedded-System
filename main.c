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

typedef struct
{
		u8 x;
		u8 y;
		u8 number;
		u8 isDefault; //1 is yes, 0 is no
		u16 bgColor; //cell back color
}cell;

cell cells[9][9];
void initGame();

 int main(void)
 { 
	u8 key;
	u8 t=0;	
	u8 x=4;
	u8 y=4; 
	u8 wall = 0;//through the border
	u8 size = lcddev.width/9;
	 
	delay_init();	    	 //延时函数初始?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	Remote_Init();			//红外接收初始化

	initGame();
	 
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,240,200,16,16,"Result:");	
	//LCD_ShowString(60,260,200,16,16,"hh");
	
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				    
				case 98:
					// str="UP";
					LED1=0;
				
					//check wall
					if(x == 0 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(x == 0)
						x = 8;
					else
						x -= 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					break;	    
			
				case 194:
					// str="RIGHT";
					//check wall
					if(y == 8 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(y == 8)
						y = 0;
					else
						y += 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					break;	   
				case 34:
					// str="LEFT";
					if(y == 0 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(y == 0)
						y = 8;
					else
						y -= 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
				
					break;		  
				// case 224:str="VOL-";break;		  
				case 168:
					// str="DOWN";
					if(x == 8 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(x == 8)
						x = 0;
					else
						x += 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
				
					break;		   
				// case 144:str="VOL+";break;		    
				case 104:
					//str="1";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 1;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					
					break;		  
				case 152:
					//str="2";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 2;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	   
				case 176:
					// str="3";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 3;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	    
				case 48:
					// str="4";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 4;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		    
				case 24:
					//str="5";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 5;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		    
				case 122:
					//str="6";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 6;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		  
				case 16:
					// str="7";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 7;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;			   					
				case 56:
					//str="8";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 8;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	 
				case 90:
					//str="9";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 9;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;
				case 66:
					//str="0";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 0;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		 
			}
	
		}else delay_ms(500);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}
 
void initGame()
{
	// draw grid
	u8 x = 2;
	u8 y = 2;
	u8 count;
	u8 size = lcddev.width/9;
	
	for(count = 10; count > 0; count --){
			LCD_DrawLine(2,y,size * 9 + 1,y);
			y = y + size;
	}
	
	for(count = 10; count > 0; count --){
			LCD_DrawLine(x,2,x,size * 9 + 1);
			x = x + size;
	}
	
	//init cells
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
	
	//init numbers
	cells[0][0].number = 6;
	cells[0][2].number = 5;
	cells[1][1].number = 8;
	cells[2][1].number = 3;
	
	cells[0][0].isDefault = 1;
	cells[0][2].isDefault = 1;
	cells[1][1].isDefault = 1;
	cells[2][1].isDefault = 1;
	
	cells[1][3].number = 9;
	cells[1][5].number = 1;
	cells[2][3].number = 7;
	cells[2][5].number = 6;
	
	cells[1][3].isDefault = 1;
	cells[1][5].isDefault = 1;
	cells[2][3].isDefault = 1;
	cells[2][5].isDefault = 1;
	
	cells[0][6].number = 3;
	cells[0][8].number = 9;
	cells[1][7].number = 2;
	cells[2][7].number = 4;
	
	cells[0][6].isDefault = 1;
	cells[0][8].isDefault = 1;
	cells[1][7].isDefault = 1;
	cells[2][7].isDefault = 1;
	
	cells[3][0].number = 1;
	cells[3][2].number = 4;
	cells[5][0].number = 3;
	cells[5][2].number = 8;
	
	cells[3][0].isDefault = 1;
	cells[3][2].isDefault = 1;
	cells[5][0].isDefault = 1;
	cells[5][2].isDefault = 1;
	
	cells[4][4].number = 8;
	cells[4][4].isDefault = 1;
	
	
	cells[3][6].number = 7;
	cells[3][8].number = 5;
	cells[5][6].number = 2;
	cells[5][8].number = 4;
	
	cells[3][6].isDefault = 1;
	cells[3][8].isDefault = 1;
	cells[5][6].isDefault = 1;
	cells[5][8].isDefault = 1;
	
	cells[6][1].number = 5;
	cells[7][1].number = 6;
	cells[8][0].number = 7;
	cells[8][2].number = 9;
	
	cells[6][1].isDefault = 1;
	cells[7][1].isDefault = 1;
	cells[8][0].isDefault = 1;
	cells[8][2].isDefault = 1;
	
	cells[6][3].number = 4;
	cells[6][5].number = 3;
	cells[7][3].number = 1;
	cells[7][5].number = 8;
	
	cells[6][3].isDefault = 1;
	cells[6][5].isDefault = 1;
	cells[7][3].isDefault = 1;
	cells[7][5].isDefault = 1;
	
	cells[6][7].number = 9;
	cells[7][7].number = 5;
	cells[8][6].number = 8;
	cells[8][8].number = 1;
	
	cells[6][7].isDefault = 1;
	cells[7][7].isDefault = 1;
	cells[8][6].isDefault = 1;
	cells[8][8].isDefault = 1;
	
	//init bgColor
	for(x=0; x < 3; x++)
		for(y = 0; y < 3; y++)
			cells[x][y].bgColor = YELLOW;
			
	for(x=0; x < 3; x++)
		for(y = 6; y < 9; y++)
			cells[x][y].bgColor = YELLOW;
			
	for(x=3; x < 6; x++)
		for(y = 3; y < 6; y++)
			cells[x][y].bgColor = YELLOW;
	
	for(x=6; x < 9; x++)
		for(y = 0; y < 3; y++)
			cells[x][y].bgColor = YELLOW;
	
	for(x=6; x < 9; x++)
		for(y = 6; y < 9; y++)
			cells[x][y].bgColor = YELLOW;
			
	//show numbers
	POINT_COLOR=BLACK;
	
	for(x = 0; x < 9; x++)
	{		
		for(y = 0; y < 9; y++)
		{
			if(cells[x][y].bgColor == YELLOW )
				LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
			
			if(cells[x][y].number >0 && cells[x][y].number < 10){
				BACK_COLOR = cells[x][y].bgColor;
				LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
			}
		}	
	}
	
	//init initial position
	LCD_Fill(3 + size*4, 3 + size*4,1 + size*5 , 1 + size*5 , LIGHTBLUE);
	BACK_COLOR = LIGHTBLUE;
	LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);

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

typedef struct
{
		u8 x;
		u8 y;
		u8 number;
		u8 isDefault; //1 is yes, 0 is no
		u16 bgColor; //cell back color
}cell;

cell cells[9][9];
void initGame();

 int main(void)
 { 
	u8 key;
	u8 t=0;	
	u8 x=4;
	u8 y=4; 
	u8 wall = 0;//through the border
	u8 size = lcddev.width/9;
	 
	delay_init();	    	 //延时函数初始?
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
	Remote_Init();			//红外接收初始化

	initGame();
	 
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,240,200,16,16,"Result:");	
	//LCD_ShowString(60,260,200,16,16,"hh");
	
	while(1)
	{
		key=Remote_Scan();	
		if(key)
		{	 	  
			switch(key)
			{
				    
				case 98:
					// str="UP";
					LED1=0;
				
					//check wall
					if(x == 0 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(x == 0)
						x = 8;
					else
						x -= 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					break;	    
			
				case 194:
					// str="RIGHT";
					//check wall
					if(y == 8 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(y == 8)
						y = 0;
					else
						y += 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					break;	   
				case 34:
					// str="LEFT";
					if(y == 0 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(y == 0)
						y = 8;
					else
						y -= 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
				
					break;		  
				// case 224:str="VOL-";break;		  
				case 168:
					// str="DOWN";
					if(x == 8 && wall == 1)
						break;
					
					//re-draw current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
					BACK_COLOR = cells[x][y].bgColor;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
					
					//move to new position
					if(x == 8)
						x = 0;
					else
						x += 1;
					
					//draw new current cell
					LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , LIGHTBLUE);
					BACK_COLOR = LIGHTBLUE;
					if(cells[x][y].number >0 && cells[x][y].number <10)
						LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
				
					break;		   
				// case 144:str="VOL+";break;		    
				case 104:
					//str="1";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 1;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					
					break;		  
				case 152:
					//str="2";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 2;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	   
				case 176:
					// str="3";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 3;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	    
				case 48:
					// str="4";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 4;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		    
				case 24:
					//str="5";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 5;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		    
				case 122:
					//str="6";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 6;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		  
				case 16:
					// str="7";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 7;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;			   					
				case 56:
					//str="8";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 8;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;	 
				case 90:
					//str="9";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 9;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;
				case 66:
					//str="0";
					if(cells[x][y].isDefault == 0)
					{
						cells[x][y].number = 0;
						LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);
					}
					break;		 
			}
	
		}else delay_ms(500);	  
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}
}
 
void initGame()
{
	// draw grid
	u8 x = 2;
	u8 y = 2;
	u8 count;
	u8 size = lcddev.width/9;
	
	for(count = 10; count > 0; count --){
			LCD_DrawLine(2,y,size * 9 + 1,y);
			y = y + size;
	}
	
	for(count = 10; count > 0; count --){
			LCD_DrawLine(x,2,x,size * 9 + 1);
			x = x + size;
	}
	
	//init cells
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
	
	//init numbers
	cells[0][0].number = 6;
	cells[0][2].number = 5;
	cells[1][1].number = 8;
	cells[2][1].number = 3;
	
	cells[0][0].isDefault = 1;
	cells[0][2].isDefault = 1;
	cells[1][1].isDefault = 1;
	cells[2][1].isDefault = 1;
	
	cells[1][3].number = 9;
	cells[1][5].number = 1;
	cells[2][3].number = 7;
	cells[2][5].number = 6;
	
	cells[1][3].isDefault = 1;
	cells[1][5].isDefault = 1;
	cells[2][3].isDefault = 1;
	cells[2][5].isDefault = 1;
	
	cells[0][6].number = 3;
	cells[0][8].number = 9;
	cells[1][7].number = 2;
	cells[2][7].number = 4;
	
	cells[0][6].isDefault = 1;
	cells[0][8].isDefault = 1;
	cells[1][7].isDefault = 1;
	cells[2][7].isDefault = 1;
	
	cells[3][0].number = 1;
	cells[3][2].number = 4;
	cells[5][0].number = 3;
	cells[5][2].number = 8;
	
	cells[3][0].isDefault = 1;
	cells[3][2].isDefault = 1;
	cells[5][0].isDefault = 1;
	cells[5][2].isDefault = 1;
	
	cells[4][4].number = 8;
	cells[4][4].isDefault = 1;
	
	
	cells[3][6].number = 7;
	cells[3][8].number = 5;
	cells[5][6].number = 2;
	cells[5][8].number = 4;
	
	cells[3][6].isDefault = 1;
	cells[3][8].isDefault = 1;
	cells[5][6].isDefault = 1;
	cells[5][8].isDefault = 1;
	
	cells[6][1].number = 5;
	cells[7][1].number = 6;
	cells[8][0].number = 7;
	cells[8][2].number = 9;
	
	cells[6][1].isDefault = 1;
	cells[7][1].isDefault = 1;
	cells[8][0].isDefault = 1;
	cells[8][2].isDefault = 1;
	
	cells[6][3].number = 4;
	cells[6][5].number = 3;
	cells[7][3].number = 1;
	cells[7][5].number = 8;
	
	cells[6][3].isDefault = 1;
	cells[6][5].isDefault = 1;
	cells[7][3].isDefault = 1;
	cells[7][5].isDefault = 1;
	
	cells[6][7].number = 9;
	cells[7][7].number = 5;
	cells[8][6].number = 8;
	cells[8][8].number = 1;
	
	cells[6][7].isDefault = 1;
	cells[7][7].isDefault = 1;
	cells[8][6].isDefault = 1;
	cells[8][8].isDefault = 1;
	
	//init bgColor
	for(x=0; x < 3; x++)
		for(y = 0; y < 3; y++)
			cells[x][y].bgColor = YELLOW;
			
	for(x=0; x < 3; x++)
		for(y = 6; y < 9; y++)
			cells[x][y].bgColor = YELLOW;
			
	for(x=3; x < 6; x++)
		for(y = 3; y < 6; y++)
			cells[x][y].bgColor = YELLOW;
	
	for(x=6; x < 9; x++)
		for(y = 0; y < 3; y++)
			cells[x][y].bgColor = YELLOW;
	
	for(x=6; x < 9; x++)
		for(y = 6; y < 9; y++)
			cells[x][y].bgColor = YELLOW;
			
	//show numbers
	POINT_COLOR=BLACK;
	
	for(x = 0; x < 9; x++)
	{		
		for(y = 0; y < 9; y++)
		{
			if(cells[x][y].bgColor == YELLOW )
				LCD_Fill(3 + size*y, 3 + size*x,1 + size*(y+1) , 1 + size*(x+1) , cells[x][y].bgColor);
			
			if(cells[x][y].number >0 && cells[x][y].number < 10){
				BACK_COLOR = cells[x][y].bgColor;
				LCD_ShowNum(cells[x][y].x,cells[x][y].y,cells[x][y].number,1,16);
			}
		}	
	}
	
	//init initial position
	LCD_Fill(3 + size*4, 3 + size*4,1 + size*5 , 1 + size*5 , LIGHTBLUE);
	BACK_COLOR = LIGHTBLUE;
	LCD_ShowNum(cells[4][4].x,cells[4][4].y,cells[4][4].number,1,16);

}
