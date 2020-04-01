#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define M 155

//��������
void readData();
void detail();
void printfSinglePayment(int i);
void add();
void menu();
void selectPaymentByUsage();
void allMoneyCount();
void paymentPercent();
void changeTotalMoneyTOSelect(int usage);
int numberJudge();
int usageJudge();

struct payment {
	int id;//֧����¼id
	float money;//���
	int year;//��
	int month;//��
	int day;//��
	int usage;//������;,1��ѧϰ��2�ǲ�����3�Ƿ�װ��4������
	float percent;//ÿ��֧����ռ����
}payment[M];//һά����洢��Ϣ


const char fileName[] = "d:\\list.txt";//�ļ��洢·��
int currentMaxId ;//��ǰ�ļ��е����id
int n;///��ǰ�ļ��м�¼����Ŀ

float totalMoney = 0;//�������

float studyMoney = 0;//ѧϰ�Ľ���ܶ�
float cateringMoney = 0;//�����Ľ���ܶ�
float clothesMoney = 0;//��װ�Ľ���ܶ�
float recreationMoney = 0;//���ֵĽ���ܶ�


//���ı��е���Ϣ�ƶ����ṹ��������
void readData()
{
	FILE* fp;///�����ļ�ָ��
	///����fopen��������ֻ��ģʽ��d:\list.txt�ļ�������֤����ֵ�Ƿ�Ϊ��
	if ((fp = fopen(fileName, "r")) == NULL)
	{
		fp = fopen(fileName, "w");
	}
	else
	{
		/**feof�������������������ļ��Ƿ��������������򷵻ط���ֵ��
			���򷵻�0 .����ԭ��Ϊ��int feof(FILE *fp)**/
		for (n = 0; !feof(fp); n++)
		{
			fscanf(fp, "%d %f %d %d %d %d\n", &payment[n].id, &payment[n].money, &payment[n].year, &payment[n].month, &payment[n].day, &payment[n].usage);///���ṹ�������Ϣд���ı�
		} ///�����ļ����ݵ��ṹ��
		if (n == 0)//���ļ�����û�м�¼��ʱ��
			currentMaxId = 0;
		else
			currentMaxId = payment[n - 1].id;//��ȡ��ǰ����¼��id
	}
	fclose(fp);//�ر��ļ�
}



///�˵�ѡ��
void menu()
{
	int flag = 1;//�жϳ���ı�־
	while (flag)
	{
		readData();//���¼����ı�����
		allMoneyCount();//���㵱ǰ�������
		system("cls");//��������
		int selectOPS;//�û�ѡ��Ĳ���
		cout << "          ��ӭ������˲������ϵͳ                \n" << endl;
		cout << "           *************************               \n" << endl;
		cout << "  \t\t1.��¼ÿ��֧������     \n" << endl;
		cout << "  \t\t2.�鿴�Լ���ÿ��֧��   \n" << endl;
		cout << "  \t\t3.�������鿴֧��   \n" << endl;
		cout << "  \t\t4.ͳ��֧������         \n" << endl;
		cout << "  \t\t5.�˳�ϵͳ             \n" << endl;
		cout << "           *************************               \n" << endl;

		printf("��ѡ��(1-5):[ ]\b\b");
		selectOPS = numberJudge();
		if (selectOPS < 1 || selectOPS>5)///�������룬���»�ȡ����
		{
			printf("�������ѡ������Ƿ���Χ֮��,��ȷ������Ҫѡ��ķ����������룡����\n");
			system("pause");
			menu();
		}
		else///��ȷ����
			switch (selectOPS)///��������ʵ����Ӧ��������
			{
			case 1: add();
				break;

			case 2:detail();
				break;

			case 3:selectPaymentByUsage();
				break;

			case 4:paymentPercent();
				break;

			case 5:flag = 0;
				break;
			}
	}
	
}

///�鿴ÿ��֧���ļ�¼
void detail()
{
	
	printf("\t\t ��ǰ���е�֧����¼��\n");
	printf("��¼���   ֧�����\t��������\t���\t�ٷֱ�\n");
	for (int  i = 0; i < n; i++)
	{
		printfSinglePayment(i);
	}
	system("pause");
}

//��ӡ������֧����Ϣ
void printfSinglePayment(int i) {
	printf("%d\t%8.2f\t", payment[i].id, payment[i].money );
	printf("%d-%d-%d\t", payment[i].year, payment[i].month, payment[i].day);
	const char *usage = "ѧϰ";
	switch (payment[i].usage)
	{
		case 1:
			usage = "ѧϰ";
			break;
		case 2:
			usage = "����";
			break;
		case 3:
			usage = "��װ";
			break;
		case 4:
			usage = "����";
			break;
		default:
			break;
	}
	printf("%s\t", usage);
	printf("%5.2f\n", (payment[i].money / totalMoney)*100);
}



void selectPaymentByUsage() {
	int selectUsage = usageJudge();
	changeTotalMoneyTOSelect(selectUsage);
	printf("��¼���   ֧�����\t��������\t���\t����\n");
	for (int i = 0; i < n; i++)
	{
		if (payment[i].usage == selectUsage)
		{
			
			printfSinglePayment(i);
		}
	}
	system("pause");
	
}

//��ѡ������ʱ�򣬽��ܽ������Ӧ�������ܽ��
void changeTotalMoneyTOSelect(int usage){
	switch (usage)
	{
		case 1:
			totalMoney =  studyMoney;
			break;
		case 2:
			totalMoney = cateringMoney ;
			break;
		case 3:
			totalMoney = clothesMoney ;
			break;
		case 4:
			totalMoney = recreationMoney ;
			break;
	}
}


///¼��һ����Ϣ
void add()
{
	printf("����д��Ҫ¼���֧������Ϣ����� ��� �·� ���� ��;�����Կո����ÿ�����ݣ�\n");

	printf(" ��������: ");
		scanf(" %f", &payment[n].money);
	printf(" ���������: ");
		payment[n].year = numberJudge();
	printf(" �������·�(1-12):[] \b\b");
		payment[n].month = numberJudge();
		if (payment[n].month <1 || payment[n].month >12)
		{
			printf("\n\t�·�������������������1-12��Χ�ڵ����֣�");
			payment[n].month = numberJudge();
		}

	printf("����������(1-31):[] \b\b");
		payment[n].day = numberJudge();
		if (payment[n].day < 1 || payment[n].day >31)
		{
			printf("\n\t����������������������1-31��Χ�ڵ����֣�");
			payment[n].day = numberJudge();
		}
	
		payment[n].usage = usageJudge();


	currentMaxId = payment[n - 1].id;
	payment[n].id = currentMaxId + 1;
	FILE* fp;///�����ļ�ָ��
	printf("������¼����д���ļ� list.txt...\n");
	fp = fopen(fileName, "a");///����"a"��˼��˵������ӵ����ݽ����ı��������д�����Ḳ���ı��������
	if (currentMaxId == 0)//��һ����¼֮ǰ���üӻ���
		fprintf(fp, "%d\t%8.2f\t%d\t%d\t%d\t%d", payment[n].id, payment[n].money, payment[n].year, payment[n].month, payment[n].day, payment[n].usage);///���ṹ�������Ϣд���ı�
	else
		fprintf(fp, "\n%d\t%8.2f\t%d\t%d\t%d\t%d", payment[n].id, payment[n].money, payment[n].year, payment[n].month, payment[n].day, payment[n].usage);///���ṹ�������Ϣд���ı�

	fclose(fp);///�ر��ļ�
	printf("\n������¼�Ѿ�д���ļ� list.txt����ǰ���鿴��\n");
	n++;
	system("pause");
}

//����֧���ܽ��
void allMoneyCount() {
	totalMoney = 0;//��ʼ��
	studyMoney = 0;//ѧϰ�Ľ���ܶ�
	cateringMoney = 0;//�����Ľ���ܶ�
	clothesMoney = 0;//��װ�Ľ���ܶ�
	recreationMoney = 0;//���ֵĽ���ܶ�
	for (int  i = 0; i < n; i++)
	{
		totalMoney += payment[i].money;
		switch (payment[i].usage)
		{
			case 1 :
				studyMoney += payment[i].money;
				break; 
			case 2:
				cateringMoney += payment[i].money;
				break;		
			case 3:
				clothesMoney += payment[i].money;
				break;		
			case 4:
				recreationMoney += payment[i].money;
				break;
		}
	}

}

//���㲻ͬ����֧����ռ����
void paymentPercent() {
	printf("������ѡ��鿴��֧�����(1����ѧϰ��2���������3�����װ��4��������)��\n");
	printf("���\t�ٷֱ�\n");
	printf("ѧϰ\t%5.2f\n", (studyMoney / totalMoney) * 100);
	printf("����\t%5.2f\n", (cateringMoney / totalMoney) * 100);
	printf("��װ\t%5.2f\n", (clothesMoney / totalMoney) * 100);
	printf("����\t%5.2f\n", (recreationMoney / totalMoney) * 100);
	system("pause");
}

//��������������жϣ�ֻ������1-4
int usageJudge() {
	int usage= 0;
	printf("������֧�������(1����ѧϰ��2���������3�����װ��4��������)��\n");
	printf("��ѡ��(1-4):[ ]\b\b");
	usage = numberJudge();
	if (usage < 1 ||  usage >4)
	{
		printf("\n\t���������������������1-4��Χ�ڵ����֣�");
		usage = numberJudge();
	}
	return usage;
}

//����������ֽ��з������жϸ�ʽ�Ƿ����
int numberJudge() {
	int num;
	int sign = 0;
	int retur;
	do {
		sign = 0;
		retur = scanf(" %d", &num);//��������n��ʮ�������֣��򷵻�1�����������Ĳ�����
		if (retur == 0) {
			printf("\n�Ƿ����룬����������ʮ�������֣�\n");
			for (; getchar() != '\n';);
				sign = -1;
		}
	} while (sign == -1);
	return num;
}


int main()
{
	readData();///��ȡ�ļ�����
	menu();///��ʾ���˵�
}
