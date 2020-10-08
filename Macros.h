#pragma once
//开始界面相关参数**************************************************

//X与Y方向上的窗口偏移量
#define X_				(16)
#define Y_				(59)

//窗口的长与宽
#define WIDTH			(250)
#define HIGHT			(150)

//加上偏移量后的长宽最终值
#define W_X				(WIDTH+X_)
#define H_Y				(HIGHT+Y_)

//开始按钮的长宽值
#define START_W			(200)
#define START_H			(100)

//开始按钮位置
#define START_X			(25)
#define START_Y			(25)

//开始按钮初始化计时
#define STARTBUTTON_INITTICK (1)

//开始界面的画面刷新刻
#define STICK			(75)

//开始界面背景闪烁间隔
#define SBACKTICKS		(40)

//开始界面小蛇的节数
#define LITTLESNAKE		(8)

//开始界面循环音频延时
#define SSNDLOOPTICK	(8012)

//贪吃蛇相关数据*****************************************************

//定义方向句柄
#define UP				(0)
#define RIGHT			(1)
#define DOWN			(2)
#define LEFT			(3)

//定义地图边长
#define BORDER			(20)

//定义地图总格数
#define SUM				(BORDER*BORDER)

//每一节的边长
#define LENGTH			(25)

//贪吃蛇身体不见句柄
#define BODY			(0)
#define HEAD			(1)

//游戏界面相关参数***************************************************

//界面尺寸
#define THIGHT			(50)
#define FRAME			(25)
#define GWIDTH			(BORDER*LENGTH)
#define GHIGHT			(GWIDTH+THIGHT)
#define GW_F			(GWIDTH+FRAME*2)
#define GH_F			(GHIGHT+FRAME*2)

//游戏中的刷新刻
#define GTICK			(STICK)

//计时器刷新刻
#define TTICK			(1000)

//游戏中背景闪烁间隔
#define GBACKTICKS		(80)

//按键循环消息延时
#define KEYTICK			(1)

//是否无敌
//#define INVINCEBLE