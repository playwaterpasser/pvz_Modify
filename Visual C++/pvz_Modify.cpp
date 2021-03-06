/*植物大战僵尸C语言修改器*/

//是否为调试版本
#define isDebug 0

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "mod.h"

//游戏进程名称
char processName[]="PlantsVsZombies.exe";
//命令
int command;
//定义进程PID
DWORD Pid;
//定义全局进程句柄
HANDLE hProcess=0;

//进程是否已经被打开
int isPro=0;
//是否后台运行标识
int backStage=1;
//是否重叠放置标识
int anyPosition=0;
//是否开启小僵尸特效标识
int little=0;

/*函数声明*/
int openPro();
int openMod();
void menu();
void upData();
void Choice();
void cheatMsg(int isSuccess,const char msg[]);
void noOperation();
void pause();
void showMiniGameList();
void cheatCode();
void showOpenCheat();
void color(int c);

/*主函数*/
int main(){
	//设置程序标题 
	SetConsoleTitle("【植物大战僵尸】 C语言修改器 v0.2");
	//检测游戏进程
	isPro=openPro();
	
	while(1){
		menu();
		color(14);
		printf("\n请按下按键选择选项：");
		command=getchar();
		Choice();
	}
	return 0;
}

//打开进程
int openPro(){
	color(14);
	printf("正在打开进程...\n");
	
	//寻找进程名称并返回pid
	if(FindProcessPid(processName,Pid)){
		printf("[%s][Pid：%d]\n",processName,Pid);
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if (hProcess!=0){
			color(10);
			printf("\n成功打开游戏进程[%s]！进程句柄：%d\n",processName,hProcess);
			//检测版本是否为英文原版和汉化一代二代
			if(readMemory(hProcess,0x42748E,4)==0xFF563DE8){
				return 1;
			}else{
				color(14);
				printf("\n不支持的游戏版本！目前仅支持英文原版和汉化一代/二代\n");
				return 0;
			}
		}else{
			color(12);
			printf("\n打开游戏进程[%s]失败\n",processName);
		}
	}else{
		color(14);
		printf("未找到游戏进程：%s\n",processName);
	}
	return 0;
}

//修改器是否已经读入游戏进程 
int openMod(){
	if(hProcess==0){
		color(14);
		printf("\n请先打开修改器搜索游戏句柄！\n");
		return 0;
	}
	return 1;
}

//主菜单 
void menu(){
	color(15);
	printf("\n————————————————————\n");
	printf("【植物大战僵尸】 C语言修改器\n\n");
	printf("O：重新打开/搜索进程[%s]\n",processName);
	if(isPro){
		#if isDebug
			printf("T：测试代码（Debug）\n");
		#endif
		printf("a：常规修改：\n");
		printf("1：修改阳光\n");
		printf("2：修改金钱\n");
		printf("3：卡牌全部无冷却时间\n");
		printf("4：允许后台运行（再开一次取消）\n");
		printf("5：修改卡槽格数\n");
		printf("6：自动收集资源\n");
		
		printf("\nb：关卡修改：\n");
		printf("1：冒险模式跳关\n");
		printf("2：小游戏跳关（混乱关卡）\n");
		
		printf("\nc：植物修改：\n");
		printf("1：激活重叠放置（再开一次取消）\n");
		printf("2：紫卡种植无限制\n");
		
		printf("\nd：僵尸修改：\n");
		printf("1：秒杀场上所有僵尸\n");
		printf("2：小僵尸特效（再开一次恢复正常大小）\n");
		
		printf("\ne：花园修改：\n");
		printf("1：修改智慧树高度\n");
		printf("2：巧克力数量修改\n");
		
		printf("\nf：其他修改：\n");
		printf("1：花瓶透视\n");
		printf("2：显示隐藏小游戏\n");
		
	}
	printf("\n特殊功能：\n");
	printf("~：查看修改器更新公告\n");
	printf("!：查看迷你小游戏、解密模式、生存模式关卡代码\n");
	printf("@：查看PVZ作弊码（彩蛋）大全\n");
	printf("#：查看目前已经开启的效果\n");
	printf("A：关于本修改器信息\n");
	printf("\nE：退出修改器");
	printf("\n————————————————————\n");
}

//更新公告
void upData(){
	color(9);
	printf("\n更新公告\n\n");
	printf("v0.1 [2019.3.4] 增加了最初的十个功能（1~0）\n");
	printf("v0.2 [2019.3.13] 新增以下功能：\n");
	printf("\t(1)自动收集资源\n\t(2)显示隐藏小游戏\n\t(3)重叠放置\n\t(4)巧克力修改\n\t(5)小僵尸特效\n\t(6)紫卡种植无限制\n");
	printf("修复/增强了以下功能：\n");
	printf("\t(1)花瓶透视不稳定性修复\n\t(2)秒杀僵尸不稳定性修复\n");
	
	pause();
}

//判断选择
void Choice(){
	color(13);
	//根据字符判断应该执行什么流程 
	switch(command){
		case 'O':
			isPro=openPro();
			pause();
			break;
		#if isDebug
		case 'T':
			if(openMod()){
				printf("\n当前值为：");
				
				/*
				int n;
				ReadProcessMemory(hProcess,(LPCVOID)getMemory_2(hProcess,0x006A9EC0,0x768,0xF4,4),&n,4,NULL);
				printf("\n当前值资源数量为%d：",n);
				writeMod_3(hProcess,0x006A9EC0,0x768,0xE4,0xD8+0x50,1,4);*/
			}
			break;
		#endif
		//常规修改
		case 'a':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						int Sun;
						printf("\n请输入要修改的阳光数量：");
						scanf("%d",&Sun);
						if(Sun<0)Sun=0;
						if(Sun>9990)Sun=9990;
						cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x768,0x5560,Sun,4),"阳光");
					}
					break;
				case '2':
					if(openMod()){
						int Money;
						printf("\n请输入要修改的金钱数量：");
						scanf("%d",&Money);
						if(Money<0)Money=0;
						if(Money>99999)Money=99999;
						cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x28,Money,4),"金钱");
					}
					break;
				case '3':
					if(openMod()){
						cheatMsg(writeMod(hProcess,0x00487296,0x1477,2),"卡牌无冷却");
					}
					break;
				case '4':
					if(openMod()){
						if(backStage==1){
							cheatMsg(writeMod(hProcess,0x0054EBEF,0xC3,1),"取消后台");
						}else{
							cheatMsg(writeMod(hProcess,0x0054EBEF,0x57,1),"恢复后台");
						}
						backStage=!backStage;
					}
					break;
				case '5':
					if(openMod()){
						int Card;
						printf("\n请输入要修改的卡槽格数（1~10）：");
						scanf("%d",&Card);
						if(Card<1)Card=1;
						if(Card>10)Card=10;
						cheatMsg(writeMod_3(hProcess,0x006A9EC0,0x768,0x144,0x24,Card,4),"卡槽格数");
					}
					break;
				case '6':
					if(openMod()){
						cheatMsg(writeMod(hProcess,0x0043158F,0xEB,1),"自动收集开启");
					}
					break;
				default :
					noOperation();
			}
			break;
		//关卡修改
		case 'b':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						int Checkpoint;
						printf("\n请输入要修改的冒险关卡（例如我要去4-3关卡，那么应该输入43）：");
						scanf("%d",&Checkpoint);
						if(Checkpoint<11)Checkpoint=11;
						Checkpoint-=10;
						cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x24,Checkpoint,4),"冒险模式关卡");
					}
					break;
				case '2':
					if(openMod()){
						int MiniGame;
						printf("\n需要先进入任意关卡然后点击菜单后（一定要这么做，否则会崩溃或者修改无效，此外重新开始会清除该模式下的存档，请注意备份存档），修改关卡代码然后点击重新开始，如果不重新开始的话将会产生混乱关卡的效果\n");
						printf("请输入要进入的迷你游戏ID（ID可通过查询【！】菜单的关卡代码（1~70））：");
						scanf("%d",&MiniGame);
						if(MiniGame<1)MiniGame=1;
						if(MiniGame>70)MiniGame=70;
						cheatMsg(writeMod_1(hProcess,0x006A9EC0,0x7F8,MiniGame,4),"小游戏跳关");
					}
					break;
				default :
					noOperation();
			}
			break;
		//植物修改
		case 'c':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						if(anyPosition==0){
							cheatMsg(writeMod(hProcess,0x0040FE30,0x81,1)&&writeMod(hProcess,0x00438E40,0xEB,1)&&writeMod(hProcess,0x0042A2D9,0x8D,1),"开启重叠放置");
						}else{
							cheatMsg(writeMod(hProcess,0x0040FE30,0x84,1)&&writeMod(hProcess,0x00438E40,0x74,1)&&writeMod(hProcess,0x0042A2D9,0x84,1),"取消重叠放置");
						}
						anyPosition=!anyPosition;
					}
					break;
				case '2':
					if(openMod()){
						cheatMsg(writeMod(hProcess,0x0041D7D0,0xC301B0,3)&&writeMod(hProcess,0x0040E477,0xEB,1),"紫卡种植无限制");
					}
					break;
				default :
					noOperation();
			}
			break;
		//僵尸修改
		case 'd':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						int z_i;
						int kill=0;
						int Z_Disappear;
						//pvz最大允许的僵尸数量是1024个，所以循环1024次就可以秒杀所有僵尸了
						for(z_i=0;z_i<1024;z_i++){
							Z_Disappear=readMemory_3(hProcess,0x006A9EC0,0x768,0x90,z_i*0x15C+0xEC,4);
							//printf("僵尸状态：%d",Z_Disappear);
							if(Z_Disappear==0)kill=writeMod_3(hProcess,0x006A9EC0,0x768,0x90,z_i*0x15C+0x28,3,4);
						}
						cheatMsg(kill,"秒杀全部僵尸");
					}
					break;
				case '2':
					if(openMod()){
						if(little==0){
							cheatMsg(writeMod(hProcess,0x00523ED5,0xEB,1),"开启小僵尸特效");
						}else{
							cheatMsg(writeMod(hProcess,0x00523ED5,0x74,1),"关闭小僵尸特效");
						}
						little=!little;
					}
					break;
				default :
					noOperation();
			}
			break;
		//花园修改
		case 'e':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						int Tree;
						printf("\n请输入要修改的智慧树高度：");
						scanf("%d",&Tree);
						if(Tree<0)Tree=0;
						cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0xF4,Tree,4),"智慧树高度");
					}
					break;
				case '2':
					if(openMod()){
						int Chocolates;
						printf("\n请输入要修改的巧克力数量：");
						scanf("%d",&Chocolates);
						if(Chocolates<0)Chocolates=0;
						if(Chocolates>999)Chocolates=999;
						Chocolates+=1000;
						cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x228,Chocolates,4),"巧克力数量");
					}
					break;
				default :
					noOperation();
			}
			break;
		//其他修改
		case 'f':
			getchar();
			color(14);
			printf("\n请选择子选项：");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openMod()){
						cheatMsg(writeMod(hProcess,0x0044E5CC,0x0033B866,4),"花瓶透视开启");
					}
					break;
				case '2':
					if(openMod()){
						cheatMsg(writeMod(hProcess,0x0042DF5D,0x38,1),"显示隐藏小游戏");
					}
					break;
				default :
					noOperation();
			}
			break;
		//~
		case '\x7E':
			upData();
			break;
		//!
		case '\x21':
			showMiniGameList();
			break;
		//@
		case '\x40':
			cheatCode();
			break;
		//#
		case '\x23':
			showOpenCheat();
			break;
		case 'A':
			printf("\n关于：本程序是植物大战僵尸（PlantsVsZombies）的修改器，使用Dev-C++开发编译\n修改器作者：流水“渺渺\n感谢大家的使用，有任何疑问和bug可以反馈给我。\n\n");
			pause();
			break;
		case 'E':
			exit(0);
			break;
		default :
			noOperation();
	}
	//暂缓输入
	getchar();
}

//修改信息
void cheatMsg(int isSuccess,const char msg[]){
	if(isSuccess){
		color(10);
		printf("\n修改【%s】成功！\n",msg);
	}else{
		color(12);
		printf("\n修改【%s】失败！\n",msg);
	}
	
	pause();
}

//找不到操作
void noOperation(){
	color(14);
	printf("\n找不到相关操作！请重新输入操作按键！\n");
	
	pause();
}

//暂停函数
void pause(){
	color(14);
	printf("\n按任意键继续……\n");
	getch();
}

//迷你游戏代码 
void showMiniGameList(){
	color(11);
	printf("\n小游戏代码（红色加“*”标志的关卡不能跳关/混乱，会造成崩溃退出）\n\n");
	const char *MiniGame[]={"生存模式：白天","生存模式：黑夜","生存模式：泳池","生存模式：浓雾","生存模式：屋顶",
							"生存模式：白天（困难）","生存模式：黑夜（困难）","生存模式：泳池（困难）","生存模式：浓雾（困难）","生存模式：屋顶（困难）",
							"生存模式：白天（无尽）","生存模式：黑夜（无尽）","生存模式：泳池（无尽）","生存模式：浓雾（无尽）","生存模式：屋顶（无尽）",
							"植物僵尸","坚果保龄球模式","老虎机","雨中种植物","宝石迷阵",
							"隐形食脑者","看星星","僵尸水族馆","宝石迷阵转转看","小僵尸大麻烦",
							"保护传送门","你看，他们像柱子一样","雪橇区","僵尸快跑","锤僵尸",
							"谁笑到最后","植物僵尸2","坚果保龄球2","跳跳舞会","僵王博士的复仇", 
							"坚果保龄球艺术锦标赛","晴天","无草皮之地（崩溃跳出，原因：少2道草皮）","重要时间","挑战种太阳花的艺术",
							"空袭","冰冻关卡","禅境花园（崩溃跳出）","超乎寻常的地心引力","坟墓模式",
							"你能把它挖出来吗","黑暗的暴风雨夜","蹦极闪电战","松鼠","智慧树（崩溃跳出）",
							"破罐者","全部留下","第三个罐子","连锁反应","M的意思是金属",
							"胆怯的制陶工","变戏法","另一个连锁反应","罐子王牌","无尽的试炼",
							"我是僵尸","我也是僵尸","你能铲了它么","完全傻了","死亡飞艇",
							"我烂了","僵尸摇摆","三连击","你的所有大脑都是属于我的","我是僵尸无尽版"
	};
	
	int gameLen=sizeof(MiniGame)/sizeof(MiniGame[0]);
	int i;
	for(i=0;i<gameLen;i++){
		//标记出错关卡
		if(i==37||i==42||i==49){
			color(12);
			printf("*");
		}else{
			color(11);
		}
		printf("%d.%s\n",i+1,MiniGame[i]);
	}
	
	pause();
}

//作弊码 
void cheatCode(){
	color(5);
	printf("\nPVZ作弊码大全（培养智慧树到一定高度智慧树会告诉你的）\n\n");
	printf("future ------ 僵尸戴上时尚太阳眼镜\n");
	printf("mustache ---- 僵尸戴上两撇胡子\n");
	printf("trickedout -- 剪草机统一变成机车剪草机\n");
	printf("daisies ----- 当僵尸被杀后掉下一些雏菊（需要智慧树达到100米）\n");
	printf("dance ------- 让僵尸摆动身体跳舞（动次打次 动次打次）（需要智慧树达到500米）\n");
	printf("sukhbir ----- 切换僵尸呼唤大脑时的叫声φ(>ω<*) \n");
	printf("pinata ------ 僵尸死后散落一地的糖果（需要智慧树达到1000米）\n");
	
	pause();
}

//显示启动的修改项目
void showOpenCheat(){
	color(11);
	printf("\n当前开启的修改项目\n\n");
	
	color(13);
	int sign=0;
	if(backStage==0){
		printf("取消后台功能已启用\n");
		sign=1;
	}
	if(anyPosition==1){
		printf("重叠放置功能已启用\n");
		sign=1;
	}
	if(little==1){
		printf("小僵尸特效已启用\n");
		sign=1;
	}
	
	if(sign==0)printf("目前没有修改项目正在启动\n");
	
	pause();
}

//更改文字颜色
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}