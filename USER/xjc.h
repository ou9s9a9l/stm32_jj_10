
//道岔
#define DATLEN 200
//信号机X-L X-LU/XI-L XI-LU XI-U   ***
unsigned short dat5[DATLEN][2][3]={0

};
//北京接车1 九龙接车2 北京发车3 九龙发车4 贡家台接车5 贡家台发车6
unsigned short dat4[DATLEN][2]={0
};
//语音播报 txt 行数   ***
unsigned short dat3[DATLEN]={0
};

//***
#define CON_LENGTH 40             //[3]counter 4[daocha]  LENGTH修改，一般不变
unsigned short	conditon[CON_LENGTH][5]={0
};
 
unsigned short factor[9][4]={0
         };
 unsigned short   s[4][15] =  {0};

unsigned short	conditon_can[CON_LENGTH][6]={
	//  id  packnum charnum posnum   xinhaoji
	//par
	//id 1-13
	//pacnum  0,1
	//charnum  conditon_can[num][2] 1/2/3/4/5/6/7
	//posnum   conditon_can[num][3] 0/1/2/3/4/5/6/7
	//xinhaoji  eg:1344  2311 811
0
};
