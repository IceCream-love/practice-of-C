#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define SETTIME  strftime(stock[numtime].mytime,sizeof(stock[numtime].mytime),"%x%A%X",localtime(&t))

struct STOCK  //��Ʊ
{
	char mytime[50],advice[100];
	int flag,stocknum;
	double orihand,handmon,income,incomerate;
	double ori,stock_ave;
	double cur,last;
};
int BUY[1000],b,c;

int main()
{
	FILE *save,*data;
	STOCK stock[500];
	int numtime=0;
	time_t t=time(NULL);
	
	save=fopen("save.txt","a");  //�򿪴浵
	fprintf(save,"%s %s %d %d %f %f %f %f %f %f %f %f %d %d\n",NULL,NULL,0,0,  0,0,  0,0,   0,0,  0,0,  0,0);
	for(int i=0;i<1000;i++)
		fprintf(save,"%d ",0);
	fprintf(save,"\n");
	fclose(save);

	save=fopen("save.txt","r");
	fscanf(save,"%s %s %d %d %lf %lf %lf %lf %lf %lf %lf %lf %d %d",stock[numtime].mytime,stock[numtime].advice,&stock[numtime].flag,\
		&stock[numtime].stocknum,&stock[numtime].orihand,&stock[numtime].handmon,&stock[numtime].income,&stock[numtime].incomerate,\
		&stock[numtime].ori,&stock[numtime].stock_ave,&stock[numtime].cur,&stock[numtime].last,&b,&c);
	fclose(save);                 //�浵��ȡ���

	data=fopen("data.txt","a");   //������

	while(1)
	{
		if(stock[numtime].last==0)  //�¿�����
		{
			SETTIME;
			printf("%s\n",stock[numtime].mytime);
			fprintf(data,"%s\n",stock[numtime].mytime);
			printf("��������ҪͶ����е��ʽ�,��ò�С������\n");
			fprintf(data,"��������ҪͶ����е��ʽ�,��ò�С������\n");
			scanf("%lf",&stock[numtime].orihand);
			printf("����������Ҫ�����Ʊ�ĳ�ʼ�۸�\n");
			fprintf(data,"����������Ҫ�����Ʊ�ĳ�ʼ�۸�\n");
			scanf("%lf",&stock[numtime].ori);
			stock[numtime].handmon=stock[numtime].orihand;
			stock[numtime].cur=stock[numtime].ori;
			stock[numtime+1].last=stock[numtime].last;
			stock[numtime+1].orihand=stock[numtime].orihand;
			stock[numtime+1].handmon=stock[numtime].handmon;
			stock[numtime+1].ori=stock[numtime].ori;
			stock[numtime+1].stock_ave=stock[numtime].stock_ave;
			stock[numtime+1].stocknum=stock[numtime].stocknum;
			BUY[b]=(int)floor(stock[numtime].orihand*0.1/stock[numtime].cur/100)*100;
			if(BUY[b]>0) 
			{
				sprintf(stock[numtime].advice,"���������������%dֻ��,Ȼ��",BUY[b]);
				stock[numtime].stock_ave=(BUY[b]*stock[numtime].cur+stock[numtime].stocknum*stock[numtime].stock_ave)/(stock[numtime].stocknum+BUY[b]);
				stock[numtime+1].stock_ave=stock[numtime].stock_ave;
				stock[numtime].handmon-=BUY[b]*stock[numtime].cur;
				stock[numtime].stocknum+=BUY[b];
				stock[numtime+1].stocknum=stock[numtime].stocknum;
				stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
				stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
				stock[numtime+1].handmon=stock[numtime].handmon;
				stock[numtime+1].last=stock[numtime].cur;
				b++;
			}

		}             //�¿����׽���

		else            // �Ӵ浵�ж�ȡ���ݻ���������
		{
			SETTIME;
			printf("%s\n",stock[numtime].mytime);
			fprintf(data,"%s\n",stock[numtime].mytime);
			printf("������չɼ�\n");
			fprintf(data,"������չɼ�\n");
			scanf("%lf",&stock[numtime].cur);
			stock[numtime+1].orihand=stock[numtime].orihand;
			stock[numtime+1].ori=stock[numtime].ori;
			stock[numtime+1].last=stock[numtime].last;
			stock[numtime+1].stock_ave=stock[numtime].stock_ave;
			stock[numtime+1].stocknum=stock[numtime].stocknum;
			stock[numtime+1].handmon=stock[numtime].handmon;
			if(stock[numtime].cur>stock[numtime].ori*1.2)
			{
				sprintf(stock[numtime].advice,"���������������%dֻ��,Ȼ��",stock[numtime].stocknum);
				stock[numtime].handmon+=stock[numtime].stocknum*stock[numtime].cur;
				stock[numtime].stocknum=0;
				stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
				stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
				stock[numtime+1].last=stock[numtime].cur;
				stock[numtime+1].stocknum=stock[numtime].stocknum;
				stock[numtime+1].handmon=stock[numtime].handmon;
				c=b;
			}
			else if(stock[numtime].last-stock[numtime].cur>0.0618*0.66*stock[numtime].ori)    //�� 
			{
				BUY[b]=(int)floor(stock[numtime].orihand*0.1/stock[numtime].cur/100)*100;
				if(BUY[b]>0&& stock[numtime].handmon-BUY[b]*stock[numtime].cur>0)  //��Ǯ��
				{
					sprintf(stock[numtime].advice,"���������������%dֻ��,Ȼ��",BUY[b]);
					stock[numtime].stock_ave=(BUY[b]*stock[numtime].cur+stock[numtime].stocknum*stock[numtime].stock_ave)/(stock[numtime].stocknum+BUY[b]);
					stock[numtime+1].stock_ave=stock[numtime].stock_ave;
					stock[numtime].handmon-=BUY[b]*stock[numtime].cur;
					stock[numtime].stocknum+=BUY[b];
					stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
					stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
					stock[numtime].flag=1;
					stock[numtime+1].last=stock[numtime].cur;
					stock[numtime+1].stocknum=stock[numtime].stocknum;
					stock[numtime+1].handmon=stock[numtime].handmon;
					b++;
				}
				else         //ûǮ��
				{
					sprintf(stock[numtime].advice,"���������������",BUY[b]);
					stock[numtime].stock_ave=stock[numtime-1].stock_ave;
					stock[numtime].handmon=stock[numtime-1].handmon;
					stock[numtime].stocknum=stock[numtime-1].stocknum;
					stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
					stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
					stock[numtime].flag=0;
				}
			}
			else if(stock[numtime].cur-stock[numtime].last>0.0618*1.26*stock[numtime].ori)    //�� 
			{
				sprintf(stock[numtime].advice,"���������������%dֻ��,Ȼ��",BUY[c]);
				stock[numtime].handmon+=BUY[c]*stock[numtime].cur;
				stock[numtime].stocknum-=BUY[c];
				stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
				stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
				stock[numtime].flag=2;
				stock[numtime+1].last=stock[numtime].cur;
				stock[numtime+1].stocknum=stock[numtime].stocknum;
				stock[numtime+1].handmon=stock[numtime].handmon;
				c++;
			}
			else                                    //���ǲ���
			{
				sprintf(stock[numtime].advice,"���������������");
				stock[numtime].stock_ave=stock[numtime-1].stock_ave;
				stock[numtime].handmon=stock[numtime-1].handmon;
				stock[numtime].stocknum=stock[numtime-1].stocknum;
				stock[numtime].income=stock[numtime].handmon+stock[numtime].stocknum*stock[numtime].cur-stock[numtime].orihand;
				stock[numtime].incomerate=stock[numtime].income/stock[numtime].orihand*100;
				stock[numtime].flag=0;
			}
		}        // �Ӵ浵�ж�ȡ���ݻ��������̽���

		printf("%s\n",stock[numtime].advice);
		fprintf(data,"%s\n",stock[numtime].advice);
		printf("�������ֽ�Ϊ%.0fԪ\n",stock[numtime].handmon);
		fprintf(data,"�������ֽ�Ϊ%.0fԪ\n",stock[numtime].handmon);
		printf("�����й�Ʊ��Ϊ%d��\n",stock[numtime].stocknum);
		fprintf(data,"�����й�Ʊ��Ϊ%d��\n",stock[numtime].stocknum);
		printf("��Щ��Ʊ����Ϊ%.2fԪ\n",stock[numtime].stock_ave);
		fprintf(data,"��Щ��Ʊ����Ϊ%.2fԪ\n",stock[numtime].stock_ave);
		printf("��������Ϊ%.0fԪ\n",stock[numtime].income);
		fprintf(data,"��������Ϊ%.0fԪ\n",stock[numtime].income);
		printf("����������Ϊ�ٷ�֮%.2f\n",stock[numtime].incomerate);
		fprintf(data,"����������Ϊ�ٷ�֮%.2f\n",stock[numtime].incomerate);
		if(b==c)
		{
			printf("���׽���\n");
			fprintf(data,"���׽���\n");
			fclose(data);
			remove("save.txt");
			system("PAUSE");
			return 0;
		}

		save=fopen("save.txt","w");  //�浵
		fprintf(save,"%s %s %d %d %f %f %f %f %f %f %f %f  %d %d \n",stock[numtime].mytime,stock[numtime].advice,stock[numtime].flag,\
			stock[numtime].stocknum, stock[numtime].orihand,stock[numtime].handmon,stock[numtime].income,stock[numtime].incomerate,\
			stock[numtime].ori,stock[numtime].stock_ave,stock[numtime].cur,stock[numtime].last,b,c);
		for(int i=0;i<1000;i++)
			fprintf(save,"%d ",BUY[i]);
		fprintf(save,"\n");
		fclose(save);                
		
		
		printf("*************************************\n");  
		fprintf(data,"*************************************\n");
		fclose(data);
		data=fopen("data.txt","a");//�浵��ȡ���

		numtime++;
	}
}
