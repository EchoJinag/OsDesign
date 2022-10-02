#include <iostream>
using namespace std;
#include<random>
#include<fstream>
#include<queue>
#include<string>
#include <iomanip>
#include "kernel.cpp"   // 静态库
#include<Windows.h>

queue <int> q;

// 请微调代码



//输出当前内存的情况_1
void myprint() {
	for(int i = 1; i <= n; i++)
		//printf("|", "%d","|","%d","|",mem[i].pnum, mem[i].visit);
		cout << '|' << mem[i].pnum << "|" << mem[i].visit << '|' << '\t';
	printf("\n");
}



void testoutput(int memory[][20], int num[],int len ,int large)  //测试输出
{
	int i, j;
	for(i = 0; i < len; i++)                   //输出产生的页面 
		cout << num[i] << "  ";
	cout << endl << endl; 	     
	for(i = 0; i < large; i++)                   //按列输出物理块中的页面置换过程 
	{
		for(j = 0; j < len; j++)
		{
			if(memory[i][j] != -1)
				cout << memory[i][j] << "  ";//物理块中有页面存在，将其输出 
			else
				cout << "   ";               //物理块空闲，输出空格 
		}
		cout << endl; 
	}

	cout << "缺页次数：" << lost_counter <<endl;
	cout << "置换次数：" << switch_counter<<endl;
	cout << "缺页率：" << lost_counter << "/" << len << endl; 
	double a = lost_counter;
	double b = len;
	cout << "缺页率：" << setprecision(3)<<a/b<<endl; 
	system("pause");
}





//五种算法 
void print_OPT(int num[], int memory[][20],int len,int large,bool show_way)        //OPT算法考虑3中情况 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                   //按列进行 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;
		if(Thesame(j, memory, num[j] , large))       //找‘相同’ 
		{                                 //调用Thesame（）若有相同页面则当前列的页面不发生置换 
			cout << "相同 " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < 20; r++) //并将当前列中的页面存放到下一列 
			{
				memory[r][j + 1] = memory[r][j];
			}

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;

		}

		else if((k = check(j, memory,large)) != -1)  //找‘初始化’即：找空闲物理块，发生中断
		{                                            //调用check（），把check（）的返回值赋给k，若k!=-1则说明有空闲物理块，要发生中断 ，且k就是当前列中将发生中断的那行 
			cout << "换初始化 " << num[j] <<endl;
			memory[k][j] = num[j];                   //将新页面进入该空闲物理块 
			for(r = 0; r < large && (j + 1) < 20; r++)
			{
				memory[r][j + 1] = memory[r][j];    //并将当前列中的所有页面存放到下一列 
			}
			lost_counter++;                         //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}

		else
		{                                       //前两种皆不满足则将发生置换 
			cout << "置换 " << num[j] << endl;
			OPTchange(r, j, memory, num, large);           //调用OPT的置换函数 
			for(r = 0; (r < large) && (j + 1 < 20); r++)      //本列数据检查完后，将本列数据送给下一列 		
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                      //置换次数加1 
			lost_counter++;	                       //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
		
	}  

}






void print_FIFO(int num[], int memory[][20],int len ,int large,bool show_way)              //FIFO算法，考虑3中情况 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                         //按列进行 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;
		if(Thesame(j, memory, num[j], large)){             //判断是否有相同的值,有则当前页面不发生置换 
			cout << "相同 " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)			
				memory[r][j + 1] = memory[r][j];    //把当前列存放在下一列中	

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;	
		}

		
		else if((k = check(j, memory,large)) != -1)           //找‘初始化’即：找空闲物理块，发生中断 
		{
			cout << "换初始化 " << num[j] <<endl;
			memory[k][j] = num[j];                  //将新页面进入物理块 
			for(r = 0; r < large && (j + 1) < len; r++)       //将当前列的页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                         //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}


		else                                       //不满足前两者则发生置换 
		{
			cout << "置换 " << num[j] << endl;
			FIFOchange(r, j, memory, num, large);          //调用FIFO的置换函数 
			for(r = 0; (r < large) && (j + 1 < len); r++)      //当前列页面完成置换后，将三个页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                       //置换次数加1 
			lost_counter++;	                        //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  


}



void print_LRU(int num[], int memory[][20], int len, int large,bool show_way)                    //LRU算法 ，3种情况 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                              //按列进行 
	{
	    if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;          
		if(Thesame(j, memory, num[j],large))
		{                                        //判断是否有相同的页面,有则不发生置换 
			cout << "相同 " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)    //将当前列存放在二维数组的下一列 
				memory[r][j + 1] = memory[r][j];	

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;	
		}


		else if((k = check(j, memory,large)) != -1)            //找‘初始化’即：找空闲物理块，发生中断
		{
			cout << "换初始化 " << num[j] <<endl;
			memory[k][j] = num[j];                   //将新页面进入物理块 
			for(r = 0; r < large && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];       //将当前列的页面存放在下一列 
		 	lost_counter++;                          //缺页中断次数加1 
			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}




		else{
			cout << "置换 " << num[j] << endl;
			LRUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)          //本列页面检查完后，将本列页面存放在下一列 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                          //置换次数加1 
			lost_counter++;	                          //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  
}



void print_LFU(int num[], int memory[][20],int len, int large,bool show_way)                //LFU算法 ，3种情况 
{		
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)
	{	
		int k = 0;
		if (show_way)
			system("pause");
		else
			Sleep(500);
		if(Thesame(j, memory, num[j],large)){             //判断是否有相同的页面,有则不发生置换 
			cout << "相同 " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];	

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;		
		}



		else if((k = check(j, memory,large)) != -1)           //找‘初始化’即：找空闲物理块，发生中断
		{
			cout << "换初始化 " << num[j] <<endl;
			memory[k][j] = num[j];                 //将新页面进入物理块
			for(r = 0; r < large && (j + 1) < len; r++)      //将当前列的页面存放在下一列
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                        //缺页中断次数加1 


			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}



		else{
			cout << "置换 " << num[j] << endl;
			LFUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)       //本列页面检查完后，将本列页面存放在下一列
				memory[r][j + 1] = memory[r][j];	
			switch_counter++;                       //置换次数加1 
			lost_counter++;	                       //缺页中断次数加1 

			cout<<"内存空间:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  		
}





void clock(int len, int large, int page[],bool show_way) {

	// cout << "请输入物理块的个数" << endl;
	// cin >> n;
	// cout << "请输入页面个数" << endl;
	// cin >> m;
	// cout << "请依次输入作业的页面走向" << endl;
	// for(int i = 1; i <= m; i++) cin >> page[i];
	// cout << endl;
	
	n = large;
	m = len;
	//遍历页面
	for(int i = 0; i < m; i++) 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		
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
		cout << "当前页面" << page[i] << endl;
		myprint();
	}

	cout << endl;
	cout << "缺页次数:" << lack_cnt << '\t' << "缺页率:" << lack_cnt << '/' << m << endl;
    system("pause");

}




void test()
{
	int choose = 9;                                        //switch中的算法选择变量 
	int num[20], memory[10][20];                            //一位数组用于产生页面，二维数组用于保存物理块中页面置换的过程 
	int i, j;
	int len;
	int large;
	bool show_way;
	int choice;
	int temp[100];
	// 	                                     //用-1初始化二维数组 
	// cout << "--------------------------------------------------"<< endl;
	// cout << "-----------课程设计：页面置换算法---------"<< endl; 

	do {
		initial(memory);
		system("cls");
		cout << "--------------------------------------------------" << endl;
		cout << "-----------课程设计：页面置换算法---------" << endl;


		cout << "请选择进程产生方式:[1] 手动输入 [2] 自动生成 [3]文件读取" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "请输入物理块大小" << endl;
			cin >> large;
			cout << "请输入待访问页面数量" << endl;
			cin >> len;
			cout << "请依次输入访问页号次序" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> num[i];
			}
		}

		else if (choice == 2)
		{
			srand(time(0));
			large = (rand() % 4) + 2;// 随机生成2到5以内整数
			len = (rand() % 11) + 10;

			for (int i = 0; i < len; i++)
				num[i] = (rand() % 10);
			cout << "已经为您随机生成" << large << "个物理块,共" << len << "个页面！";
			cout << "具体走向为：		" << endl;
			cout << num[0];
			for (int i = 1; i < len; i++)
				cout << "->" << num[i];
			cout << endl << endl;

		}





		else if (choice == 3)
		{

			ifstream in;//test
			string filename = "data.txt";//test
			in.open(filename);//test
			if (!in)//test
			{
				cerr << "打开文件出错。" << endl;//test
				exit;//test
			}
			string s;//用于保存读入的数据//test
			in.seekg(0, ios::beg);//tes
			getline(in, s, ' ');//test
			large = stoi(s);//test
			getline(in, s, ' ');//test
			len = stoi(s);//test
			for (int i = 0; i < len; i++)
			{
				getline(in, s, ' ');//test
				num[i] = stoi(s);//test
			}

			cout << "读取文件成功，共有" << large << "个物理块,共" << len << "个页面！";
			cout << "具体走向为：		" << endl;
			cout << num[0];
			for (int i = 1; i < len; i++)
				cout << "->" << num[i];
			cout << endl << endl;

		}


		else
		{
			cout << "输入错误！" << endl;
		}


		cout << "请输入选择：1.OPT  2.FIFO  3.LRU  4.LFU  5.CLOCK  0.退出->" << endl;
		cin >> choose;


		cout << "请选择计时方式:[1] 按键盘 [0] 响应WIN_TIMER " << endl;
		cin >> show_way;

		switch (choose)
		{
			//算法选择 
		case 1://OPT

			print_OPT(num, memory, len, large, show_way);
			testoutput(memory, num, len, large);                  //输出opt算法的页面置换过程 
			lost_counter = 0;                         //将缺页中断次数重置为0 
			switch_counter = 0;                       //将置换次数重置为0 
			break;

		case 2://FIFO

			print_FIFO(num, memory, len, large, show_way);
			testoutput(memory, num, len, large);
			lost_counter = 0;
			switch_counter = 0;
			break;

		case 3://LRU

			print_LRU(num, memory, len, large, show_way);
			testoutput(memory, num, len, large);
			lost_counter = 0;
			switch_counter = 0;

			break;

		case 4://LFU	


			print_LFU(num, memory, len, large, show_way);
			testoutput(memory, num, len, large);
			lost_counter = 0;
			switch_counter = 0;
			break;

		case 5://LFU			
			clock(len, large, num, show_way);
			break;
		case 0:
			cout << "拜拜 !" << endl;
			break;
		default:
			cout << "输入有误，请重新输入:" << endl;
		}

	} while (choose != 0);


}
//3 20 1 0 1 0 5 4 0 3 4 3 0 3 2 1 3 0 1 7 0 5

int main()
{

	test();
	return 0;
}

