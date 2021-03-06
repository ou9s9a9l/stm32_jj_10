

//道岔
const unsigned short dat0[][11]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
{461,449,457},            //14/16,4/6,10/12
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
{462,478},            //(14/16),[20],(22/24),[4/6]
{462,477},              //(14/16),22/24,[4/6]
{461,449,457},            //14/16,4/6,10/12
{449,461,458},                    //4/6，14/16，(10/12)
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
{477,461,449,387},              //22/24,14/16,4/6,IG_R
{457,450},            //10/12,(4/6),[14/16]
{478,461,449},            //(22/24),14/16,4/6
//大连方面XN发车-----------------------------------------------
{389},                            //无道岔，IIG_R
//大连方面X接车-----------------------------------------------
{513},                       //13/15
//大连方面X通过-----------------------------------------------
{513,477,461,449},      //13/15,22/24,14/16,4/6
//大连北方面XB接车----------------------------------------------
{458,450},       //(10/12), [14/16],(4/6)
};
const unsigned short dat1[][1]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
{0},            //14/16,4/6,10/12
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
{0},            //(14/16),[20],(22/24),[4/6]
{0},              //(14/16),22/24,[4/6]
{0},            //14/16,4/6,10/12
{0},                    //4/6，14/16，(10/12)
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
{0},              //22/24,14/16,4/6,IG_R
{0},            //10/12,(4/6),[14/16]
{0},            //(22/24),14/16,4/6
//大连方面XN发车-----------------------------------------------
{0},                            //无道岔，IIG_R
//大连方面X接车-----------------------------------------------
{0},                       //13/15
//大连方面X通过-----------------------------------------------
{0},      //13/15,22/24,14/16,4/6
//大连北方面XB接车----------------------------------------------
{0},       //(10/12), [14/16],(4/6)
};
//轨道
const unsigned short dat2[][13]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
{362,336,390,366},            //ⅡBG,6-14DG,ⅡG,ⅡAG 
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
{362,336,334,340,342,392},             //ⅡBG,6-14DG,4-16DG,22DG,24DG,3G
{362,336,334,340,388},             //ⅡBG,6-14DG,4-16DG,22DG,IG
{362,336,390},            //ⅡBG,6-14DG,ⅡG
{362,336,332,418,420},          //ⅡBG,6-14DG,2DG,10DG,12DG
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
{340,334,360},              //22DG,4-16DG,IBG
{336,334,360},            //6-14DG,4-16DG,IBG
{342,340,334,360},            //24DG,22DG,4-16DG,IBG
//大连方面XN发车-----------------------------------------------
{366},                            //ⅡAG
//大连方面X接车-----------------------------------------------
{356,388},                       //15DG,IG
//大连方面X通过-----------------------------------------------
{356,388,340,334,360},      //15DG,IG,22DG,4-16DG,IBG
//大连东方面XB接车----------------------------------------------
{336,334,360,420,418},       //6-14DG,4-16DG,IBG,12DG,10DG
};

//信号机X-L X-LU/XI-L XI-LU XI-U  
unsigned short dat5[][2][3]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
{{1,6},{141,144,146}},      //{{S-L,S-LU},{SII-L,SII-U,SII-LU}},
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
{{7}},                   //{{S-UU}},
{{7}},                   //{{S-UU}},
{{4}},                    //{{S-U}},
{{7}},                   //{{S-UU}},
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
{{77,80,82}},           //{{XI-L,XI-U,XI-LU}},
{{93,96,98}},         //{{XII-L,XII-U,XII-LU}},
{{109,112,114}},           //{{X3-L,X3-U,X3-LU}},
//大连方面XN发车-----------------------------------------------
{{141,144,146}},           //{{SII-L,SII-U,SII-LU}},
//大连方面X接车-----------------------------------------------
{{50}},                  //{{X-U}},
//大连方面X通过-----------------------------------------------
{{47,52},{77,80,82}},  	  //{{X-L,X-LU},{XI-L,XI-U,XI-LU}},
//大连东方面XB接车----------------------------------------------
{{22}},                //{{XB-UU}},
};

//方向
//沈阳方面接车1  大连方面接车2  沈阳方面发车3 大连方面发车4 大连东方面接车5 大连东方面发车6 
unsigned short dat4[][2]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
{1,4},
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
{1},
{1},
{1},
{1},
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
{3},
{3},
{3},
//大连方面XN发车-----------------------------------------------
{4},
//大连方面X接车-----------------------------------------------
{2},
//大连方面X通过-----------------------------------------------
{2,3},
//大连东方面XB接车----------------------------------------------
{5},
};

//语音播报 txt 行数   
unsigned short dat3[]={
//沈阳方面S通过++++++++++++++++++++++++++++++++++++++++++++++
142,               //上行二道通过信号开放
//沈阳方面S接车++++++++++++++++++++++++++++++++++++++++++++++
123,              //上行3道接车信号开放
121,               //上行1道接车信号开放
122,		   //上行2道接车信号开放
220,		   //上行大连东方向接车信号开放
//沈阳方面SN发车+++++++++++++++++++++++++++++++++++++++++++++
1,               //下行1道发车信号开放
2,               //下行2道发车信号开放
3,               //下行3道发车信号开放
//大连方面XN发车-----------------------------------------------
102,               //上行2道发车信号开放
//大连方面X接车-----------------------------------------------
21,               //下行一道接车信号开放
//大连方面X通过-----------------------------------------------
41,               //下行一道通过信号开放
//大连东方面XB接车----------------------------------------------
221,               //下行大连东发车信号开放
};



#define CON_LENGTH 12             //[3]counter 4[daocha]  LENGTH修改，一般不变
unsigned short	conditon[CON_LENGTH][5]={
	{407,201,2,0,355},//x1jg-h
	{409,202,2},//x2jg
	{411,203,2},//x3jg
	{355,204,2},//15DG-H          X进站第一个区段 15DG
	{401,205},//x1lq
	{397,206},//x2lq
	{403,211,1,0,361},//s1jg
	{405,212,1},//s2jg
	{399,213,1},//s3jg
	{361,214,1},//IIBG-H       S进站第一个区段  IIBG
	{415,215},//s1lq
	{413,216},//s2lq
};
 unsigned short factor[7][4]={
	 {0},
	 {0,0,356},//xjz-b  X进站第一个区段15DG-B
	 {0,0,362},//sjz-b  S进站第一个区段IIBG-B
	 {0,0,360},//IBG-b   X出站最后一个区段（SN前一个区段） IBG-B
	 {0,0,366},//IIAG-b  S出站最后一个区段（XN前一个区段） IIAG_B
	 {0,0,362},//sjz-b  S???????IIBG-B
	 {0,0,360},//IBG-b   X????????(SN?????) IBG-B
	 };


const unsigned char s[2][30] =  {
	"沙河口",
"大连东",};

unsigned short	conditon_can[][6]={
	//  id  packnum charnum posnum   xinhaoji
	//par
	//id 1-13
	//pacnum  0,1
	//charnum  conditon_can[num][2] 1/2/3/4/5/6/7
	//posnum   conditon_can[num][3] 0/1/2/3/4/5/6/7
	//xinhaoji  eg:1344  2311 811
	
	{0x0d,00,5,0,2206,0x10},//30ag
	


};




