#include <iostream>
using namespace std;
#include<random>
#include<fstream>
#include<queue>
#include<string>
#include <iomanip>
#include "kernel.cpp"   // ��̬��
#include<Windows.h>

queue <int> q;

// ��΢������



//�����ǰ�ڴ�����_1
void myprint() {
	for(int i = 1; i <= n; i++)
		//printf("|", "%d","|","%d","|",mem[i].pnum, mem[i].visit);
		cout << '|' << mem[i].pnum << "|" << mem[i].visit << '|' << '\t';
	printf("\n");
}



void testoutput(int memory[][20], int num[],int len ,int large)  //�������
{
	int i, j;
	for(i = 0; i < len; i++)                   //���������ҳ�� 
		cout << num[i] << "  ";
	cout << endl << endl; 	     
	for(i = 0; i < large; i++)                   //�������������е�ҳ���û����� 
	{
		for(j = 0; j < len; j++)
		{
			if(memory[i][j] != -1)
				cout << memory[i][j] << "  ";//���������ҳ����ڣ�������� 
			else
				cout << "   ";               //�������У�����ո� 
		}
		cout << endl; 
	}

	cout << "ȱҳ������" << lost_counter <<endl;
	cout << "�û�������" << switch_counter<<endl;
	cout << "ȱҳ�ʣ�" << lost_counter << "/" << len << endl; 
	double a = lost_counter;
	double b = len;
	cout << "ȱҳ�ʣ�" << setprecision(3)<<a/b<<endl; 
	system("pause");
}





//�����㷨 
void print_OPT(int num[], int memory[][20],int len,int large,bool show_way)        //OPT�㷨����3����� 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                   //���н��� 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;
		if(Thesame(j, memory, num[j] , large))       //�ҡ���ͬ�� 
		{                                 //����Thesame����������ͬҳ����ǰ�е�ҳ�治�����û� 
			cout << "��ͬ " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < 20; r++) //������ǰ���е�ҳ���ŵ���һ�� 
			{
				memory[r][j + 1] = memory[r][j];
			}

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;

		}

		else if((k = check(j, memory,large)) != -1)  //�ҡ���ʼ���������ҿ�������飬�����ж�
		{                                            //����check��������check�����ķ���ֵ����k����k!=-1��˵���п�������飬Ҫ�����ж� ����k���ǵ�ǰ���н������жϵ����� 
			cout << "����ʼ�� " << num[j] <<endl;
			memory[k][j] = num[j];                   //����ҳ�����ÿ�������� 
			for(r = 0; r < large && (j + 1) < 20; r++)
			{
				memory[r][j + 1] = memory[r][j];    //������ǰ���е�����ҳ���ŵ���һ�� 
			}
			lost_counter++;                         //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}

		else
		{                                       //ǰ���ֽԲ������򽫷����û� 
			cout << "�û� " << num[j] << endl;
			OPTchange(r, j, memory, num, large);           //����OPT���û����� 
			for(r = 0; (r < large) && (j + 1 < 20); r++)      //�������ݼ����󣬽����������͸���һ�� 		
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                      //�û�������1 
			lost_counter++;	                       //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
		
	}  

}






void print_FIFO(int num[], int memory[][20],int len ,int large,bool show_way)              //FIFO�㷨������3����� 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                         //���н��� 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;
		if(Thesame(j, memory, num[j], large)){             //�ж��Ƿ�����ͬ��ֵ,����ǰҳ�治�����û� 
			cout << "��ͬ " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)			
				memory[r][j + 1] = memory[r][j];    //�ѵ�ǰ�д������һ����	

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;	
		}

		
		else if((k = check(j, memory,large)) != -1)           //�ҡ���ʼ���������ҿ�������飬�����ж� 
		{
			cout << "����ʼ�� " << num[j] <<endl;
			memory[k][j] = num[j];                  //����ҳ���������� 
			for(r = 0; r < large && (j + 1) < len; r++)       //����ǰ�е�ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                         //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}


		else                                       //������ǰ���������û� 
		{
			cout << "�û� " << num[j] << endl;
			FIFOchange(r, j, memory, num, large);          //����FIFO���û����� 
			for(r = 0; (r < large) && (j + 1 < len); r++)      //��ǰ��ҳ������û��󣬽�����ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                       //�û�������1 
			lost_counter++;	                        //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  


}



void print_LRU(int num[], int memory[][20], int len, int large,bool show_way)                    //LRU�㷨 ��3����� 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                              //���н��� 
	{
	    if (show_way)
			system("pause");
		else
			Sleep(500);
		int k = 0;          
		if(Thesame(j, memory, num[j],large))
		{                                        //�ж��Ƿ�����ͬ��ҳ��,���򲻷����û� 
			cout << "��ͬ " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)    //����ǰ�д���ڶ�ά�������һ�� 
				memory[r][j + 1] = memory[r][j];	

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;	
		}


		else if((k = check(j, memory,large)) != -1)            //�ҡ���ʼ���������ҿ�������飬�����ж�
		{
			cout << "����ʼ�� " << num[j] <<endl;
			memory[k][j] = num[j];                   //����ҳ���������� 
			for(r = 0; r < large && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];       //����ǰ�е�ҳ��������һ�� 
		 	lost_counter++;                          //ȱҳ�жϴ�����1 
			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}




		else{
			cout << "�û� " << num[j] << endl;
			LRUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)          //����ҳ������󣬽�����ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                          //�û�������1 
			lost_counter++;	                          //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  
}



void print_LFU(int num[], int memory[][20],int len, int large,bool show_way)                //LFU�㷨 ��3����� 
{		
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)
	{	
		int k = 0;
		if (show_way)
			system("pause");
		else
			Sleep(500);
		if(Thesame(j, memory, num[j],large)){             //�ж��Ƿ�����ͬ��ҳ��,���򲻷����û� 
			cout << "��ͬ " << num[j] << endl;
			for(r = 0; (r < large ) && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];	

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;		
		}



		else if((k = check(j, memory,large)) != -1)           //�ҡ���ʼ���������ҿ�������飬�����ж�
		{
			cout << "����ʼ�� " << num[j] <<endl;
			memory[k][j] = num[j];                 //����ҳ����������
			for(r = 0; r < large && (j + 1) < len; r++)      //����ǰ�е�ҳ��������һ��
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                        //ȱҳ�жϴ�����1 


			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}



		else{
			cout << "�û� " << num[j] << endl;
			LFUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)       //����ҳ������󣬽�����ҳ��������һ��
				memory[r][j + 1] = memory[r][j];	
			switch_counter++;                       //�û�������1 
			lost_counter++;	                       //ȱҳ�жϴ�����1 

			cout<<"�ڴ�ռ�:	";
			for ( int i =0 ; i < large; ++i )
			{
				cout<<"|"<<memory[i][j];
			}
			cout<<"|"<<endl;
		}	
	}  		
}





void clock(int len, int large, int page[],bool show_way) {

	// cout << "�����������ĸ���" << endl;
	// cin >> n;
	// cout << "������ҳ�����" << endl;
	// cin >> m;
	// cout << "������������ҵ��ҳ������" << endl;
	// for(int i = 1; i <= m; i++) cin >> page[i];
	// cout << endl;
	
	n = large;
	m = len;
	//����ҳ��
	for(int i = 0; i < m; i++) 
	{
		if (show_way)
			system("pause");
		else
			Sleep(500);
		
			//�ж��Ƿ����ڴ���
		int j = find(page[i]);
		if(j == -1) 
		{	//����ڴ�û��
			lack_cnt++;	//ȱҳ����++ 
		while(1) 
		{
			//��������λΪ1,��0 
			if(mem[idx].visit == 1) 
			{ 
				mem[idx].visit = 0;
			}
			else 
			{	//����λΪ0���û�ҳ��
				mem[idx].pnum = page[i];
				mem[idx].visit = 1;
				break;
			}
			//ָ��ѭ������ 
			idx++;
			if(idx == n + 1) 
				idx = 1;
		}
		}
		else
		{	//�ڴ����У�������1��ָ�붨λ
			idx = j;
			mem[idx].visit = 1;
		}

		idx++;
		if(idx == n + 1) idx = 1;
		cout << "��ǰҳ��" << page[i] << endl;
		myprint();
	}

	cout << endl;
	cout << "ȱҳ����:" << lack_cnt << '\t' << "ȱҳ��:" << lack_cnt << '/' << m << endl;
    system("pause");

}




void test()
{
	int choose = 9;                                        //switch�е��㷨ѡ����� 
	int num[20], memory[10][20];                            //һλ�������ڲ���ҳ�棬��ά�������ڱ����������ҳ���û��Ĺ��� 
	int i, j;
	int len;
	int large;
	bool show_way;
	int choice;
	int temp[100];
	// 	                                     //��-1��ʼ����ά���� 
	// cout << "--------------------------------------------------"<< endl;
	// cout << "-----------�γ���ƣ�ҳ���û��㷨---------"<< endl; 

	do {
		initial(memory);
		system("cls");
		cout << "--------------------------------------------------" << endl;
		cout << "-----------�γ���ƣ�ҳ���û��㷨---------" << endl;


		cout << "��ѡ����̲�����ʽ:[1] �ֶ����� [2] �Զ����� [3]�ļ���ȡ" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "������������С" << endl;
			cin >> large;
			cout << "�����������ҳ������" << endl;
			cin >> len;
			cout << "�������������ҳ�Ŵ���" << endl;
			for (int i = 0; i < len; i++)
			{
				cin >> num[i];
			}
		}

		else if (choice == 2)
		{
			srand(time(0));
			large = (rand() % 4) + 2;// �������2��5��������
			len = (rand() % 11) + 10;

			for (int i = 0; i < len; i++)
				num[i] = (rand() % 10);
			cout << "�Ѿ�Ϊ���������" << large << "�������,��" << len << "��ҳ�棡";
			cout << "��������Ϊ��		" << endl;
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
				cerr << "���ļ�����" << endl;//test
				exit;//test
			}
			string s;//���ڱ�����������//test
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

			cout << "��ȡ�ļ��ɹ�������" << large << "�������,��" << len << "��ҳ�棡";
			cout << "��������Ϊ��		" << endl;
			cout << num[0];
			for (int i = 1; i < len; i++)
				cout << "->" << num[i];
			cout << endl << endl;

		}


		else
		{
			cout << "�������" << endl;
		}


		cout << "������ѡ��1.OPT  2.FIFO  3.LRU  4.LFU  5.CLOCK  0.�˳�->" << endl;
		cin >> choose;


		cout << "��ѡ���ʱ��ʽ:[1] ������ [0] ��ӦWIN_TIMER " << endl;
		cin >> show_way;

		switch (choose)
		{
			//�㷨ѡ�� 
		case 1://OPT

			print_OPT(num, memory, len, large, show_way);
			testoutput(memory, num, len, large);                  //���opt�㷨��ҳ���û����� 
			lost_counter = 0;                         //��ȱҳ�жϴ�������Ϊ0 
			switch_counter = 0;                       //���û���������Ϊ0 
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
			cout << "�ݰ� !" << endl;
			break;
		default:
			cout << "������������������:" << endl;
		}

	} while (choose != 0);


}
//3 20 1 0 1 0 5 4 0 3 4 3 0 3 2 1 3 0 1 7 0 5

int main()
{

	test();
	return 0;
}

