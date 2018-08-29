#include<stdio.h>
#include<malloc.h>

int zuheshu(float s[],int n); // 组合数的函数
float zuhe[4]={0}; // 暂时存放组合
int sum=0; // 用于计数
// 动态分配n个float变量的数组
float * fsz(int n)
{
	return (float *)malloc(sizeof(float)*n);
}

int zuhefu(); //符号组合
int yunsuan(float s[],char p[],int k0[],int k1[]); // 算式组合
float qiujie(float suanshi[],int n); // 算式求解

int hefa(float suanshi[],int r); // 算式正确性检查
float jianjie(float suanshi[],int r); // 算式简洁性检查

int fuhe=0; // 计数符合算式数

void main()
{
	// 输入四个数
	/*float shu[4]={0};
	printf("请输入4个数字(1~10):\n");
	scanf("%f",&shu[0]);
	scanf("%f",&shu[1]);
	scanf("%f",&shu[2]);
	scanf("%f",&shu[3]);
	//float shu[4]={1,2,3,4};
	printf("输入的4个数字依此是: %.0f %.0f %.0f %.0f\n",shu[0],shu[1],shu[2],shu[3]);*/
	float s[4]={3,3,3,3},shu[4]={0};
	printf("请输入四个数(0-9):\n");
	for(int i=0;i<4;i++)
	{
		scanf("%f",&s[i]);
		for(int j=i;j>0;j--)
		{
			if(s[j]<=s[j-1])
			{
				float s0=s[j-1];
				s[j-1]=s[j];
				s[j]=s0;
			}
		}
	}
	/*printf("四个数是:");
	for(i=0;i<4;i++)
	{
		printf("%.0f ",s[i]);
	}
	printf("\n");*/
	zuheshu(s,4);
	
	printf("有%d个算式符合\n",fuhe);
}

// 组合数，并调用yunsuan
int zuheshu(float s[],int n)
{
	if(n==1)
	{
		zuhe[4-n]=s[0];
		zuhefu();
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		if(i==0)
		{
			// 直接填入s[0],数组和候选数中去除该数,递归
			zuhe[4-n]=s[i];//n=4
			float *p=fsz(n-1);
			int o=0;
			for(int k=0;k<n;k++)
			{
				if(k!=i)
					p[o++]=s[k];
			}
			zuheshu(p,n-1);
			free(p);
		}
		else if(s[i]!=s[i-1])
		{
			// 直接填入s[0],数组和候选数中去除该数,递归
			zuhe[4-n]=s[i];
			float *p=fsz(n-1);
			int o=0;
			for(int k=0;k<n;k++)
			{
				if(k!=i)
					p[o++]=s[k];
			}
			zuheshu(p,n-1);
			//free(p);
		}
	}
}

// 组合运算符号,并调用yunsuan
int zuhefu()
{
	// 对操作符'+','—','*','/'组合
	char opter[4]={'+','-','*','/'};
	for(int h=0;h<4;h++) // 第一个操作符
	{
		for(int i=0;i<4;i++) // 第二个操作符
		{
			for(int j=0;j<4;j++) // 第三个操作符
			{
				char op[3]; // 放置操作符
				op[0]=opter[h];
				op[1]=opter[i];
				op[2]=opter[j];
				// 对括号组合
				/* 0 1 1 1 2 2 2 3*/
				int khzh[8][3]={{0,0,0},{0,0,1},{0,1,0},{1,0,0},{0,1,1},{1,0,1},{1,1,0},{1,1,1}}; // 正或反括号
				for(int k=0;k<=3;k++)
				{
					switch(k)
					{
					case 0: // 有0个括号
						{
							yunsuan(zuhe,op,khzh[0],khzh[0]);
						}
						break;
					case 1: // 有1个括号
						{
							for(int m=1;m<=3;m++) // 正括号
							{
								for(int n=1;n<=3;n++) //反括号
								{//代码将算式组合，并判断正确性;其中(括号)010和100为错误组合,010和010无错误组合,001和100为错误组合,同时100和001可视做无括号应过滤（即正括号后接操作数,操作符,不能是操作数,反括号）
									//正确组合有六组
									if((m==2&&n==3)||(m==1&&n==2)||(m==3&&n==1)||(m==1&&n==3))
										continue;
									yunsuan(zuhe,op,khzh[m],khzh[n]);
								}
							}
						}
						break;
					case 2: // 有2个括号
						{
							//代码将算式组合，并判断正确性;其中(括号)*1*和1**为错误组合，**1和*1*为错误组合，应过滤（即正括号后接操作数，操作符，不能是操作数，反括号）同时出现1**和**1也应视为0**和**0
							//正确括法只有一种即101和101
							yunsuan(zuhe,op,khzh[5],khzh[5]);
						}
						break;
					case 3: //有3个括号,不可能
						//利用khzu[7]代码将算式组合，并判断正确性(不正确)
						break;
					}
				}
			}
		}
	}
	return 1;
} 

// 对s[]中的四个数按照p[]和k[]中的运算符进行组合并调用qiujie()函数运算判断结果是否为24
int yunsuan(float s[],char p[],int k0[],int k1[])
{
	float suanshi0[13]={'0'}; // 合成等式
	int r=0; // 等式的长度
	// 组合等式
	for(int q=0;q<13;q++)
	{
		switch(q)
		{
		case 0:
			{
				if(k0[0]==1)
					suanshi0[r++]='(';
			}
			break;
		case 1:
			{
				suanshi0[r++]=s[0];
			}
			break;
		case 2:
			{
				suanshi0[r++]=p[0];
			}
			break;
		case 3:
			{
				if(k0[1]==1)
					suanshi0[r++]='(';
				
			}
			break;
		case 4:
			{
				suanshi0[r++]=s[1];
			}
			break;
		case 5:
			{
				if(k1[0]==1)
					suanshi0[r++]=')';
			}
			break;
		case 6:
			{
				suanshi0[r++]=p[1];
			}
			break;
		case 7:
			{
				if(k0[2]==1)
					suanshi0[r++]='(';
			}
			break;
		case 8:
			{
				suanshi0[r++]=s[2]; 
			}
			break;
		case 9:
			{
				if(k1[1]==1)
					suanshi0[r++]=')';
			}
			break;
		case 10:
			{
				suanshi0[r++]=p[2];
			}
			break;
		case 11:
			{
				suanshi0[r++]=s[3];
			}
			break;
		case 12:
			{
				if(k1[2]==1)
					suanshi0[r++]=')';
			}
			break;
		}
	}
	
	float * suanshi=fsz(r); // 动态空间申请
	for(int i=0;i<r;i++)
	{
		suanshi[i]=suanshi0[i];
	}
	// 组合算式的正确性检查
	/*float f=hefa(suanshi,r);
	if(f==0)
	{
		return 0;
	}
	// 组合算式的简洁性检查
	//f=jianjie(suanshi,r);
	if(f==0)
	{
		return 0;
	}*/
	// 调用函数求解结果为24则输出等式
	float sum0=qiujie(suanshi,r);
	if(sum0==24)
	{
		fuhe++;
		for(int t=0;t<r;t++)
		{
			if(suanshi[t]>10)
				printf("%c",char(suanshi[t]));
			else
				printf("%0.0f",suanshi[t]);
		}
		printf("=%0.0f",sum0);
		printf("\n");
	}
	free(suanshi);
	return 1;
}

// 算式正确性检查
int hefa(float suanshi[],int r)
{
	float * p=&suanshi[0]; // 为当前指针
	float * q=&suanshi[1]; // 为下一指针
	int flag=1; // 等式正确标记
	while(1)
	{
		if(*p==40) // 判断是否为'('
		{
			if((*q>=0)&&(*q<=9))
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if((*p>=0)&&(*p<=9)) // 判断是否为数
		{
			if((p-suanshi)>=(r-1))
			{
				break;
			}
			if(*q==')'||((*q>41)&&(*q<48))) // '+','-','*','/'在次范围内
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if(*p==41) // 判断是否为')'
		{
			if((p-suanshi)>=(r-1))
			{
				break;
			}
			if((*q>41)&&(*q<48)) // '+','-','*','/'在次范围内
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
		if((*p>41)&&(*p<48)) // // 判断是否为符号
		{
			if(*q==40||((*q>=0)&&(*q<=9)))
			{
				p++;
				q++;
			}
			else
			{
				flag=0;
				break;
			}
		}
	}
	return flag;
}

// 算式简洁性检查
float jianjie(float suanshi[],int r)
{
	float re=1; // 是否括号不影响算式求解
	float *p=&re,*q=&re;
	int k=0; // 括号数目
	int k1=0; // 运算符的个数
	float r0=0; // '('前的运算符优先级
	float r2=1; // 算式运算符优先级
	float r1=0; // ')'后的运算符优先级
	int r3=0;
	for(int i=0;i<r;i++)
	{
		if(suanshi[i]=='(')
		{
			k++;
			if(*p!='('||k==1)
			{
				p=&suanshi[i];
				if(i!=0)
				{
					if(*(p-1)=='+'||*(p-1)=='-')
					{
						r0=1;
					}
					else if(*(p-1)=='*'||*(p-1)=='/')
					{
						r0=2;
					}
					if(*(p-1)=='-')
					{
						r0+=100;
					}
					else if(*(p-1)=='/')
					{
						r0+=1000;
					}
				}
			}
		}
		else if(suanshi[i]==')')
		{
			if(k--==1)
			{
				q=&suanshi[i];
				if(i!=r-1)
				{
					if(*(q+1)=='+'||*(q+1)=='-')
					{
						r1=1;
					}
					else if(*(q+1)=='*'||*(q+1)=='/')
					{
						r1=2;
					}
				}
				//递归
				re=jianjie(p+1,q-p-1); // 返回括号内的优先级
				if(int(r0/100)>=1) // 括号'('外出现减号或除号
				{
					if((int(r0/100))==1&&(int(re/100))==1) // 括号'('外出现减号,括号内出现+或-
					{
						continue;
					}
					else if((int(r0/1000))==1&&(int(re/1000))==1) // 括号'('外出现除号,括号内出现*或/
					{
						continue;
					}
				}
				if(int(re/100)==1)
					re-=100;
				if(int(re/1000)==1)
					re-=1000;
				if(int(r0/100)==1)
					r0-=100;
				else if(int(r0/1000)==1)
					r0-=1000;
				if(re==0)
					return 0;
				if(re>=r0&&re>=r1)
					return 0;
			}
		}
		else if(k==0)
		{
			if(suanshi[i]=='+'||suanshi[i]=='-')
			{
				r2=((r2*k1)+1)/(++k1);
				r3=r3/10+1;
			}
			else if(suanshi[i]=='*'||suanshi[i]=='/')
			{
				r2=(r2*k1+2)/(++k1);
				r3=r3%10+10;
			}
		}
	}
	if(r3%10==1)
		r2+=100;
	if(r3/10==1)
		r2+=1000;
	return r2;
}

// 调用函数求解结果为24则输出等式
float qiujie(float suanshi[],int n)
{
	if(n==3)
	{
		float a=0;
		switch(char(suanshi[1]))
		{
		case '+':
			return (suanshi[0]+suanshi[2]);
		case '-':
			return (suanshi[0]-suanshi[2]);
		case '*':
			return (suanshi[0]*suanshi[2]);
		case '/':
			return (suanshi[0]/suanshi[2]);
		}
	}
	// 过滤掉括号项
	float pq='0';
	float * p=&pq; // 指向算式的第一个正括号
	float * q=&pq; // 指向算式的与第一个正括号配对的反括号
	int k=0;
	float suanshi1[7]={'0'}; // 除去括号后的算式
	int s=0; // 用来记录suanshi1数组的长度
	float sum=0; // 算式的值
	for(int m=0;m<n;m++)
	{
		if(suanshi[m]=='(')
		{
			k++;
			if((*p)!='(')
			{
				p=&suanshi[m];
			}
			continue;
		}
		if(suanshi[m]==')')
		{
			if(k--==1)
			{
				q=&suanshi[m];
				suanshi1[s++]=qiujie(p+1,q-p-1);
				p=&pq;
				q=&pq;
			}
			continue;
		}
		if(k==0)
		{
			suanshi1[s++]=suanshi[m];
			continue;
		}
	}
	if(s==3)
	{
		sum=qiujie(suanshi1,s);
	}
	else
	{
		p=&suanshi1[0]; // 指向第一个数
		q=&suanshi1[2]; // 只想第二个数
		for(m=0;m<(s-1)/2;m++)
		{
			switch(char(suanshi1[2*m+1]))
			{
			case '+':
				if((s-1)/2!=1&&(suanshi1[2*(m+1)+1]=='*'||suanshi1[2*(m+1)+1]=='/'))
				{
					*q=qiujie(p+2,3);
					int ws=&suanshi1[s-1]-&suanshi1[2*(m+1)];
					for(int w=1;w<=ws;w++)
					{
						if(((q+w+2)-(q+ws))>0)
						{
							*(q+w)=-1;
						}
						else
						{
							*(q+w)=*(q+w+2);
						}
					}
					s=s-2;
					m--;
				}
				else
				{
					if(m==0)
					{
						sum+=*p+*q;
					}
					else
					{
						sum+=*q;
					}
					p=p+2;
					q=q+2;
				}
				break;
			case '-':
				if((s-1)/2!=1&&(suanshi1[2*(m+1)+1]=='*'||suanshi1[2*(m+1)+1]=='/'))
				{
					*q=qiujie(p+2,3);
					int ws=&suanshi1[s-1]-&suanshi1[2*(m+1)];
					for(int w=1;w<=ws;w++)
					{
						if(((q+w+2)-(q+ws))>0)
						{
							*(q+w)=-1;
						}
						else
						{
							*(q+w)=*(q+w+2);
						}
					}
					s=s-2;
					m=-1;
				}
				else
				{
					if(m==0)
						sum+=*p-*q;
					else
						sum-=*q;
					p=p+2;
					q=q+2;
				}
				break;
			case '*':
				if(m==0)
					sum+=(*p)*(*q);
				else
					sum*=*q;
				p=p+2;
				q=q+2;
				break;
			case '/':
				if(m==0)
				{
					sum+=(*p)/(*q);
				}
				else
				{
					sum/=*q;
				}
				p=p+2;
				q=q+2;
				break;
			}
		}
	}
	return sum;
}
