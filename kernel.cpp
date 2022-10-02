
//  页面置换算法
//	支持功能：
//	完成时间： 2022年1月10日；

void initial(int memory[][20]);
int check(int j, int memory[][20],int large);
int Thesame(int j, int memory[][20], int x,int large);
void testoutput(int memory[][20], int num[],int len,int large);

void OPT(int num[], int memory[][20],int len, int large,bool show_way); 
void FIFO(int num[], int memory[][20],int len, int large,bool show_way);
void LRU(int num[], int memory[][20],int len, int large,bool show_way);
void LFU(int num[], int memory[][20],int len, int large,bool show_way);

void OPTchange(int i, int j, int memory[][20], int num[],int large);
void FIFOchange(int i, int j, int memory[][20], int num[],int large);
void LRUchange(int i, int j, int memory[][20], int num[],int large);
void LFUchange(int i, int j, int memory[][20], int num[],int large);

int switch_counter = 0;
int lost_counter = 0;


int n, m;		//物理块个数、作业页面个数 



int page[20];	//需要访问的页面 

struct Mem {	//内存		
	int pnum;	//页面号
	int visit;	//访问位
}mem[10];

int idx = 1;	//内存指针
int lack_cnt;	//缺页次数



//输入一个页面号，返回内存中的位置，返回-1则没有 
int find(int x) { 
	for(int i = 1; i <= n; i++) {
		if(mem[i].pnum == x) return i;
	}
	return -1;
}




int clockChange(int i )
{
	//判断是否在内存中
		int j = find(page[i]);
		if(j == -1) 
		{	//如果内存没有
			lack_cnt++;	//缺页次数++ 
		while(1) 
		{
			//遇到访问位为1,置0 
			if(mem[idx].visit == 1) 
			{ 
				mem[idx].visit = 0;
			}
			else 
			{	//访问位为0，置换页面
				mem[idx].pnum = page[i];
				mem[idx].visit = 1;
				break;
			}
			//指针循环遍历 
			idx++;
			if(idx == n + 1) 
				idx = 1;
		}
		}
		else
		{	//内存中有，引用置1，指针定位
			idx = j;
			mem[idx].visit = 1;
		}

		idx++;
		if(idx == n + 1) idx = 1;
		return lack_cnt;
}




void initial(int memory[][20])                   //初始化二位数组
{
	int i, j; 
	for(i = 0; i < 10; i++)  
		for(j = 0; j < 20; j++)
			memory[i][j] = -1;
}



// 遍历large次，判断memory中是否存全是 -1 ，都不是-1，则内存初始化完毕
int check(int j, int memory[][20] ,int large)              //判断是否有‘初始化’的值，有则返回其行数
{
	int i = -1;
	do{
		i++; 
	} while((memory[i][j] != -1) && (i < large));  //按行判断
	if(i == large)                            //若i=large，说明该列中的三个页面都不是空闲物理块，将i依旧置为-1 
		i = -1;   
	return i;
}


//memory 保存着置换的结果
int Thesame(int j, int memory[][20], int x, int large)   //判断要进入的新页面x是否与当前列的物理块中的页面有相同的 
{
	int flag = 0;                        // 作判断结果的标记 
	int i = 0;
	for(i = 0; i < large; i++)                   //按行进行判断 
	{
		if(memory[i][j] == x)              // 若有相同的则将标记置为1 
			flag = 1;
	}	
	return flag;
}


//四种算法 
void OPT(int num[], int memory[][20],int len, int large)        //考虑三种情况：相同、置换、初始化
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                   			//遍历len次
	{
		int k = 0;
		if(Thesame(j, memory, num[j] , large))       //找‘相同’ 
		{                                            //调用Thesame（）若有相同页面则当前列的页面不发生置换 
			for(r = 0; (r < large ) && (j + 1) < 20; r++) //并将当前列中的页面存放到下一列 
			{
				memory[r][j + 1] = memory[r][j];     // memory 记录了内存中的历史状态
			}
		}

		else if((k = check(j, memory,large)) != -1)  //找‘初始化’即：找空闲物理块，发生中断
		{                                            //调用check（），把check（）的返回值赋给k，若k!=-1则说明有空闲物理块
													 //要发生中断 ，且k就是当前列中将发生中断的那行 
			memory[k][j] = num[j];                   //将新页面进入该空闲物理块 
			for(r = 0; r < large && (j + 1) < 20; r++)
			{
				memory[r][j + 1] = memory[r][j];    //并将当前列中的所有页面存放到下一列 
			}
			lost_counter++;                         //缺页中断次数加1 
		}

		else
		{                                       //前两种皆不满足则将发生置换 
			OPTchange(r, j, memory, num, large);           //调用OPT的置换函数 
			for(r = 0; (r < large) && (j + 1 < 20); r++)      //本列数据检查完后，将本列数据送给下一列 		
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                      //置换次数加1 
			lost_counter++;	                       //缺页中断次数加1 
		}	
		
	}  
}



// OPT的核心置换算法
void OPTchange(int i, int j, int memory[][20], int num[] ,int large)
{
	int a[10], b[10], m, n, x = 0;
	

	 //算出当前列中的large行页面在多久以后才被使用 
	for(m = 0; m < large; m++)                             
	{
		x = j;             
		do{                                            //即将当前列的三个页面和当前列以后所有会出现的页面比较，当找到相同的页面退出do-while 
			x++;                                       //退出时，x即表示所计算出的不久以后该行页面出现的列数 
		}while((memory[m][j] != num[x]) && (x < 20)); 
		
		a[m] = x - j;                                 //将当前列中三个页面在多久以后会出现的‘时间’ 记录下来 
	}
	n = 0;
	for(m = 0; m < large; m++)                            //查找最久以后才被使用的页面在当前列的第几行 
	{
		if(a[m] > n)       
		{
			n= a[m];                                  //n作中间变量，用于存放三者中的最大值 
			x = m;                                    //把最久以后才会用到的页面的行数赋给x 
		}
	}	
	memory[x][j] = num[j];                           //将新页面进入，置换掉最久以后才会用到的页面 
}






void FIFO(int num[], int memory[][20],int len ,int large)              //FIFO算法，考虑3中情况 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                         //按列进行 
	{
		int k = 0;
		if(Thesame(j, memory, num[j], large)){             //判断是否有相同的值,有则当前页面不发生置换 

			for(r = 0; (r < large ) && (j + 1) < len; r++)			
				memory[r][j + 1] = memory[r][j];    //把当前列存放在下一列中	

		}

		
		else if((k = check(j, memory, large)) != -1)           //找‘初始化’即：找空闲物理块，发生中断 
		{
			memory[k][j] = num[j];                  //将新页面进入物理块 
			for(r = 0; r < large && (j + 1) < len; r++)       //将当前列的页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                         //缺页中断次数加1 
		
		}


		else                                       //不满足前两者则发生置换 
		{
			FIFOchange(r, j, memory, num, large);          //调用FIFO的置换函数 
			for(r = 0; (r < large) && (j + 1 < len); r++)      //当前列页面完成置换后，将三个页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                       //置换次数加1 
			lost_counter++;	                        //缺页中断次数加1 
		}	
	}  


}


// FIFO, 在二维数组向前遍历，找到连续存放在该页面中的次数
void FIFOchange(int i, int j, int memory[][20], int num[],int large)  //FIFO的置换算法 
{
	int a[10], b[10], m, n, x = 0;	
	
	for(m = 0; m < large; m++)                                  //计算当前列中三个页面连续在物理块中存放的次数 
	{
		x = j;                                              //把当前的列数赋给x 
		do{
			x--;
		}while((memory[m][j] == memory[m][x]) && (x > 0));  //在二维数组中查找 
		a[m] = j-x;                                         //当前的列数减去该页面连续存放在当前物理块中的开始的那列的列数，即为该页面连续存放在当前物理块中的时间 
	}
	
	n = 0;
	for(m = 0; m < large; m++)                                  //查找使用最久的页面在第几行 
	{
		if(a[m] > n)
		{
			 n = a[m];                                     //n作为中间变量用于存放最久的连续‘时间’ 
			 x = m;                                        //将最久的那个页面的行数赋给x 
		}
	}	
	memory[x][j] = num[j];                                //新页面将存放最久的那个页面置换掉 
}




void LRU(int num[], int memory[][20], int len, int large)                    //LRU算法 ，3种情况 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                              //按列进行 
	{

		int k = 0;          
		if(Thesame(j, memory, num[j],large))
		{                                        //判断是否有相同的页面,有则不发生置换 
		
			for(r = 0; (r < large ) && (j + 1) < len; r++)    //将当前列存放在二维数组的下一列 
				memory[r][j + 1] = memory[r][j];	

		}


		else if((k = check(j, memory,large)) != -1)            //找‘初始化’即：找空闲物理块，发生中断
		{
			
			memory[k][j] = num[j];                   //将新页面进入物理块 
			for(r = 0; r < large && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];       //将当前列的页面存放在下一列 
		 	lost_counter++;                          //缺页中断次数加1 
		
		}

		else{
		
			LRUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)          //本列页面检查完后，将本列页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                          //置换次数加1 
			lost_counter++;	                          //缺页中断次数加1 

		}	
	}  
}


void LRUchange(int i, int j, int memory[][20], int num[], int large)
{
	int a[10], b[10], m, n, x = 0;
	
	for(m = 0; m < large; m++)                            //算出同列各行数据多久才被使用 
	{
		x = j;
		do{
			x--;
		}while((memory[m][j] != num[x]) && (x > 0));  //在一维数组中查找，即计算之前已经进入的物理块
		                                             //且还存在于物理块中的这三个页面最后一次进入物理块的那列的列数 
		a[m] = j - x;                                //当前的列数减去该页面最后一次进入物理块的那列的列数，即为该页面距离当前即将进入物理块的距离
	}
	
	n = 0;
	for(m = 0; m < large; m++)                           //n作中间变量存放距离即将进入物理块的页面的距离的最大值
	{
		if(a[m] > n)
		{
			n= a[m];
			x = m;                                   // 将该有最大距离的页面的行号赋给x 
		}
	}
	memory[x][j] = num[j];                           //新页面将距离它自己最远的那个页面置换掉 
}






void LFU(int num[], int memory[][20],int len, int large)                //LFU算法 ，3种情况 
{		
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)
	{	
		int k = 0;

		if(Thesame(j, memory, num[j],large)){             //判断是否有相同的页面,有则不发生置换 

			for(r = 0; (r < large ) && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];	
	
		}


		else if((k = check(j, memory,large)) != -1)           //找‘初始化’即：找空闲物理块，发生中断
		{

			memory[k][j] = num[j];                 //将新页面进入物理块
			for(r = 0; r < large && (j + 1) < len; r++)      //将当前列的页面存放在下一列
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                        //缺页中断次数加1 

		}

		else{

			LFUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)       //本列页面检查完后，将本列页面存放在下一列
				memory[r][j + 1] = memory[r][j];	
			switch_counter++;                       //置换次数加1 
			lost_counter++;	                       //缺页中断次数加1 

		}	
	}  		
}


void LFUchange(int i, int j, int memory[][20], int num[], int large)   //LFU的置换算法 
{
	int a[10], m, n, x = 0;
	
	for(m = 0; m < large; m++)                                  //计算当前列各行页面在之前使用过的次数 
	{
		x = 0;
		for(n = 0; n < j; n++)                                 //从第0行开始查找 
		{
			if(num[n] == memory[m][j])                     //若查找到的页面等于当前的这行的页面则将它使用的次数加1 
				x++;
		} 
		a[m] = x;                                         //将计算的每行的页面使用次数赋给a[m] 
	}
	

	n = 20;
	x = 0; 
	for(m = 0; m < large; m++)                                //查找使用次数最少的页面在第几行 
	{
		if(a[m] < n)                                      //n作中间变量用于存放使用次数最少的页面的行号 
		{
			n = a[m];    
			x = m;
		}
	}
	memory[x][j] = num[j];                                 //新页面将之前使用频率最小的那个页面置换掉 
}






