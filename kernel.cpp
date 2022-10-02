
//  ҳ���û��㷨
//	֧�ֹ��ܣ�
//	���ʱ�䣺 2022��1��10�գ�

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


int n, m;		//������������ҵҳ����� 



int page[20];	//��Ҫ���ʵ�ҳ�� 

struct Mem {	//�ڴ�		
	int pnum;	//ҳ���
	int visit;	//����λ
}mem[10];

int idx = 1;	//�ڴ�ָ��
int lack_cnt;	//ȱҳ����



//����һ��ҳ��ţ������ڴ��е�λ�ã�����-1��û�� 
int find(int x) { 
	for(int i = 1; i <= n; i++) {
		if(mem[i].pnum == x) return i;
	}
	return -1;
}




int clockChange(int i )
{
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
		return lack_cnt;
}




void initial(int memory[][20])                   //��ʼ����λ����
{
	int i, j; 
	for(i = 0; i < 10; i++)  
		for(j = 0; j < 20; j++)
			memory[i][j] = -1;
}



// ����large�Σ��ж�memory���Ƿ��ȫ�� -1 ��������-1�����ڴ��ʼ�����
int check(int j, int memory[][20] ,int large)              //�ж��Ƿ��С���ʼ������ֵ�����򷵻�������
{
	int i = -1;
	do{
		i++; 
	} while((memory[i][j] != -1) && (i < large));  //�����ж�
	if(i == large)                            //��i=large��˵�������е�����ҳ�涼���ǿ�������飬��i������Ϊ-1 
		i = -1;   
	return i;
}


//memory �������û��Ľ��
int Thesame(int j, int memory[][20], int x, int large)   //�ж�Ҫ�������ҳ��x�Ƿ��뵱ǰ�е�������е�ҳ������ͬ�� 
{
	int flag = 0;                        // ���жϽ���ı�� 
	int i = 0;
	for(i = 0; i < large; i++)                   //���н����ж� 
	{
		if(memory[i][j] == x)              // ������ͬ���򽫱����Ϊ1 
			flag = 1;
	}	
	return flag;
}


//�����㷨 
void OPT(int num[], int memory[][20],int len, int large)        //���������������ͬ���û�����ʼ��
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                   			//����len��
	{
		int k = 0;
		if(Thesame(j, memory, num[j] , large))       //�ҡ���ͬ�� 
		{                                            //����Thesame����������ͬҳ����ǰ�е�ҳ�治�����û� 
			for(r = 0; (r < large ) && (j + 1) < 20; r++) //������ǰ���е�ҳ���ŵ���һ�� 
			{
				memory[r][j + 1] = memory[r][j];     // memory ��¼���ڴ��е���ʷ״̬
			}
		}

		else if((k = check(j, memory,large)) != -1)  //�ҡ���ʼ���������ҿ�������飬�����ж�
		{                                            //����check��������check�����ķ���ֵ����k����k!=-1��˵���п��������
													 //Ҫ�����ж� ����k���ǵ�ǰ���н������жϵ����� 
			memory[k][j] = num[j];                   //����ҳ�����ÿ�������� 
			for(r = 0; r < large && (j + 1) < 20; r++)
			{
				memory[r][j + 1] = memory[r][j];    //������ǰ���е�����ҳ���ŵ���һ�� 
			}
			lost_counter++;                         //ȱҳ�жϴ�����1 
		}

		else
		{                                       //ǰ���ֽԲ������򽫷����û� 
			OPTchange(r, j, memory, num, large);           //����OPT���û����� 
			for(r = 0; (r < large) && (j + 1 < 20); r++)      //�������ݼ����󣬽����������͸���һ�� 		
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                      //�û�������1 
			lost_counter++;	                       //ȱҳ�жϴ�����1 
		}	
		
	}  
}



// OPT�ĺ����û��㷨
void OPTchange(int i, int j, int memory[][20], int num[] ,int large)
{
	int a[10], b[10], m, n, x = 0;
	

	 //�����ǰ���е�large��ҳ���ڶ���Ժ�ű�ʹ�� 
	for(m = 0; m < large; m++)                             
	{
		x = j;             
		do{                                            //������ǰ�е�����ҳ��͵�ǰ���Ժ����л���ֵ�ҳ��Ƚϣ����ҵ���ͬ��ҳ���˳�do-while 
			x++;                                       //�˳�ʱ��x����ʾ��������Ĳ����Ժ����ҳ����ֵ����� 
		}while((memory[m][j] != num[x]) && (x < 20)); 
		
		a[m] = x - j;                                 //����ǰ��������ҳ���ڶ���Ժ����ֵġ�ʱ�䡯 ��¼���� 
	}
	n = 0;
	for(m = 0; m < large; m++)                            //��������Ժ�ű�ʹ�õ�ҳ���ڵ�ǰ�еĵڼ��� 
	{
		if(a[m] > n)       
		{
			n= a[m];                                  //n���м���������ڴ�������е����ֵ 
			x = m;                                    //������Ժ�Ż��õ���ҳ�����������x 
		}
	}	
	memory[x][j] = num[j];                           //����ҳ����룬�û�������Ժ�Ż��õ���ҳ�� 
}






void FIFO(int num[], int memory[][20],int len ,int large)              //FIFO�㷨������3����� 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                         //���н��� 
	{
		int k = 0;
		if(Thesame(j, memory, num[j], large)){             //�ж��Ƿ�����ͬ��ֵ,����ǰҳ�治�����û� 

			for(r = 0; (r < large ) && (j + 1) < len; r++)			
				memory[r][j + 1] = memory[r][j];    //�ѵ�ǰ�д������һ����	

		}

		
		else if((k = check(j, memory, large)) != -1)           //�ҡ���ʼ���������ҿ�������飬�����ж� 
		{
			memory[k][j] = num[j];                  //����ҳ���������� 
			for(r = 0; r < large && (j + 1) < len; r++)       //����ǰ�е�ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                         //ȱҳ�жϴ�����1 
		
		}


		else                                       //������ǰ���������û� 
		{
			FIFOchange(r, j, memory, num, large);          //����FIFO���û����� 
			for(r = 0; (r < large) && (j + 1 < len); r++)      //��ǰ��ҳ������û��󣬽�����ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                       //�û�������1 
			lost_counter++;	                        //ȱҳ�жϴ�����1 
		}	
	}  


}


// FIFO, �ڶ�ά������ǰ�������ҵ���������ڸ�ҳ���еĴ���
void FIFOchange(int i, int j, int memory[][20], int num[],int large)  //FIFO���û��㷨 
{
	int a[10], b[10], m, n, x = 0;	
	
	for(m = 0; m < large; m++)                                  //���㵱ǰ��������ҳ��������������д�ŵĴ��� 
	{
		x = j;                                              //�ѵ�ǰ����������x 
		do{
			x--;
		}while((memory[m][j] == memory[m][x]) && (x > 0));  //�ڶ�ά�����в��� 
		a[m] = j-x;                                         //��ǰ��������ȥ��ҳ����������ڵ�ǰ������еĿ�ʼ�����е���������Ϊ��ҳ����������ڵ�ǰ������е�ʱ�� 
	}
	
	n = 0;
	for(m = 0; m < large; m++)                                  //����ʹ����õ�ҳ���ڵڼ��� 
	{
		if(a[m] > n)
		{
			 n = a[m];                                     //n��Ϊ�м�������ڴ����õ�������ʱ�䡯 
			 x = m;                                        //����õ��Ǹ�ҳ�����������x 
		}
	}	
	memory[x][j] = num[j];                                //��ҳ�潫�����õ��Ǹ�ҳ���û��� 
}




void LRU(int num[], int memory[][20], int len, int large)                    //LRU�㷨 ��3����� 
{
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)                              //���н��� 
	{

		int k = 0;          
		if(Thesame(j, memory, num[j],large))
		{                                        //�ж��Ƿ�����ͬ��ҳ��,���򲻷����û� 
		
			for(r = 0; (r < large ) && (j + 1) < len; r++)    //����ǰ�д���ڶ�ά�������һ�� 
				memory[r][j + 1] = memory[r][j];	

		}


		else if((k = check(j, memory,large)) != -1)            //�ҡ���ʼ���������ҿ�������飬�����ж�
		{
			
			memory[k][j] = num[j];                   //����ҳ���������� 
			for(r = 0; r < large && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];       //����ǰ�е�ҳ��������һ�� 
		 	lost_counter++;                          //ȱҳ�жϴ�����1 
		
		}

		else{
		
			LRUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)          //����ҳ������󣬽�����ҳ��������һ�� 
				memory[r][j + 1] = memory[r][j];
			switch_counter++;                          //�û�������1 
			lost_counter++;	                          //ȱҳ�жϴ�����1 

		}	
	}  
}


void LRUchange(int i, int j, int memory[][20], int num[], int large)
{
	int a[10], b[10], m, n, x = 0;
	
	for(m = 0; m < large; m++)                            //���ͬ�и������ݶ�òű�ʹ�� 
	{
		x = j;
		do{
			x--;
		}while((memory[m][j] != num[x]) && (x > 0));  //��һά�����в��ң�������֮ǰ�Ѿ�����������
		                                             //�һ�������������е�������ҳ�����һ�ν������������е����� 
		a[m] = j - x;                                //��ǰ��������ȥ��ҳ�����һ�ν������������е���������Ϊ��ҳ����뵱ǰ�������������ľ���
	}
	
	n = 0;
	for(m = 0; m < large; m++)                           //n���м������ž��뼴������������ҳ��ľ�������ֵ
	{
		if(a[m] > n)
		{
			n= a[m];
			x = m;                                   // �������������ҳ����кŸ���x 
		}
	}
	memory[x][j] = num[j];                           //��ҳ�潫�������Լ���Զ���Ǹ�ҳ���û��� 
}






void LFU(int num[], int memory[][20],int len, int large)                //LFU�㷨 ��3����� 
{		
	int i = 0, j = 0, l = 0, r = 0;      
	for(j = 0; j < len; j++)
	{	
		int k = 0;

		if(Thesame(j, memory, num[j],large)){             //�ж��Ƿ�����ͬ��ҳ��,���򲻷����û� 

			for(r = 0; (r < large ) && (j + 1) < len; r++)
				memory[r][j + 1] = memory[r][j];	
	
		}


		else if((k = check(j, memory,large)) != -1)           //�ҡ���ʼ���������ҿ�������飬�����ж�
		{

			memory[k][j] = num[j];                 //����ҳ����������
			for(r = 0; r < large && (j + 1) < len; r++)      //����ǰ�е�ҳ��������һ��
				memory[r][j + 1] = memory[r][j];
			lost_counter++;                        //ȱҳ�жϴ�����1 

		}

		else{

			LFUchange(r, j, memory, num, large);
			for(r = 0; (r < large) && (j + 1 < len); r++)       //����ҳ������󣬽�����ҳ��������һ��
				memory[r][j + 1] = memory[r][j];	
			switch_counter++;                       //�û�������1 
			lost_counter++;	                       //ȱҳ�жϴ�����1 

		}	
	}  		
}


void LFUchange(int i, int j, int memory[][20], int num[], int large)   //LFU���û��㷨 
{
	int a[10], m, n, x = 0;
	
	for(m = 0; m < large; m++)                                  //���㵱ǰ�и���ҳ����֮ǰʹ�ù��Ĵ��� 
	{
		x = 0;
		for(n = 0; n < j; n++)                                 //�ӵ�0�п�ʼ���� 
		{
			if(num[n] == memory[m][j])                     //�����ҵ���ҳ����ڵ�ǰ�����е�ҳ������ʹ�õĴ�����1 
				x++;
		} 
		a[m] = x;                                         //�������ÿ�е�ҳ��ʹ�ô�������a[m] 
	}
	

	n = 20;
	x = 0; 
	for(m = 0; m < large; m++)                                //����ʹ�ô������ٵ�ҳ���ڵڼ��� 
	{
		if(a[m] < n)                                      //n���м�������ڴ��ʹ�ô������ٵ�ҳ����к� 
		{
			n = a[m];    
			x = m;
		}
	}
	memory[x][j] = num[j];                                 //��ҳ�潫֮ǰʹ��Ƶ����С���Ǹ�ҳ���û��� 
}






