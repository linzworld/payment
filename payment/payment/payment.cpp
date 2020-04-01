#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define M 155

//函数声明
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
	int id;//支出记录id
	float money;//金额
	int year;//年
	int month;//月
	int day;//日
	int usage;//四种用途,1是学习，2是餐饮，3是服装，4是娱乐
	float percent;//每笔支出所占比例
}payment[M];//一维数组存储信息


const char fileName[] = "d:\\list.txt";//文件存储路径
int currentMaxId ;//当前文件中的最大id
int n;///当前文件中记录的数目

float totalMoney = 0;//金额总数

float studyMoney = 0;//学习的金额总额
float cateringMoney = 0;//餐饮的金额总额
float clothesMoney = 0;//服装的金额总额
float recreationMoney = 0;//娱乐的金额总额


//将文本中的信息移动到结构体数组里
void readData()
{
	FILE* fp;///定义文件指针
	///调用fopen函数，以只读模式打开d:\list.txt文件，并验证返回值是否为空
	if ((fp = fopen(fileName, "r")) == NULL)
	{
		fp = fopen(fileName, "w");
	}
	else
	{
		/**feof是输入输出函数，检查文件是否结束，如结束，则返回非零值，
			否则返回0 .函数原型为：int feof(FILE *fp)**/
		for (n = 0; !feof(fp); n++)
		{
			fscanf(fp, "%d %f %d %d %d %d\n", &payment[n].id, &payment[n].money, &payment[n].year, &payment[n].month, &payment[n].day, &payment[n].usage);///将结构体里的信息写入文本
		} ///保存文件数据到结构体
		if (n == 0)//当文件里面没有记录的时候
			currentMaxId = 0;
		else
			currentMaxId = payment[n - 1].id;//获取当前最大记录的id
	}
	fclose(fp);//关闭文件
}



///菜单选项
void menu()
{
	int flag = 1;//中断程序的标志
	while (flag)
	{
		readData();//重新加载文本数据
		allMoneyCount();//计算当前金额总数
		system("cls");//清屏操作
		int selectOPS;//用户选择的操作
		cout << "          欢迎进入个人财务管理系统                \n" << endl;
		cout << "           *************************               \n" << endl;
		cout << "  \t\t1.记录每笔支出费用     \n" << endl;
		cout << "  \t\t2.查看自己的每笔支出   \n" << endl;
		cout << "  \t\t3.按照类别查看支出   \n" << endl;
		cout << "  \t\t4.统计支出比例         \n" << endl;
		cout << "  \t\t5.退出系统             \n" << endl;
		cout << "           *************************               \n" << endl;

		printf("请选择(1-5):[ ]\b\b");
		selectOPS = numberJudge();
		if (selectOPS < 1 || selectOPS>5)///错误输入，重新获取输入
		{
			printf("您输入的选项不在我们服务范围之内,请确定好您要选择的服务，重新输入！！！\n");
			system("pause");
			menu();
		}
		else///正确输入
			switch (selectOPS)///根据输入实现相应函数调用
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

///查看每笔支出的记录
void detail()
{
	
	printf("\t\t 当前所有的支出记录：\n");
	printf("记录编号   支出金额\t具体日期\t类别\t百分比\n");
	for (int  i = 0; i < n; i++)
	{
		printfSinglePayment(i);
	}
	system("pause");
}

//打印出单个支出信息
void printfSinglePayment(int i) {
	printf("%d\t%8.2f\t", payment[i].id, payment[i].money );
	printf("%d-%d-%d\t", payment[i].year, payment[i].month, payment[i].day);
	const char *usage = "学习";
	switch (payment[i].usage)
	{
		case 1:
			usage = "学习";
			break;
		case 2:
			usage = "餐饮";
			break;
		case 3:
			usage = "服装";
			break;
		case 4:
			usage = "娱乐";
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
	printf("记录编号   支出金额\t具体日期\t类别\t比例\n");
	for (int i = 0; i < n; i++)
	{
		if (payment[i].usage == selectUsage)
		{
			
			printfSinglePayment(i);
		}
	}
	system("pause");
	
}

//在选择类别的时候，将总金额换成相对应的类别的总金额
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


///录入一条信息
void add()
{
	printf("请填写您要录入的支出的信息：金额 年份 月份 日期 用途（请以空格隔开每个数据）\n");

	printf(" 请输入金额: ");
		scanf(" %f", &payment[n].money);
	printf(" 请输入年份: ");
		payment[n].year = numberJudge();
	printf(" 请输入月份(1-12):[] \b\b");
		payment[n].month = numberJudge();
		if (payment[n].month <1 || payment[n].month >12)
		{
			printf("\n\t月份输入有误，请重新输入1-12范围内的数字！");
			payment[n].month = numberJudge();
		}

	printf("请输入日期(1-31):[] \b\b");
		payment[n].day = numberJudge();
		if (payment[n].day < 1 || payment[n].day >31)
		{
			printf("\n\t日期输入有误，请重新输入1-31范围内的数字！");
			payment[n].day = numberJudge();
		}
	
		payment[n].usage = usageJudge();


	currentMaxId = payment[n - 1].id;
	payment[n].id = currentMaxId + 1;
	FILE* fp;///定义文件指针
	printf("该条记录正在写入文件 list.txt...\n");
	fp = fopen(fileName, "a");///参数"a"意思是说将新添加的数据接着文本里的数据写，不会覆盖文本里的内容
	if (currentMaxId == 0)//第一条记录之前不用加换行
		fprintf(fp, "%d\t%8.2f\t%d\t%d\t%d\t%d", payment[n].id, payment[n].money, payment[n].year, payment[n].month, payment[n].day, payment[n].usage);///将结构体里的信息写入文本
	else
		fprintf(fp, "\n%d\t%8.2f\t%d\t%d\t%d\t%d", payment[n].id, payment[n].money, payment[n].year, payment[n].month, payment[n].day, payment[n].usage);///将结构体里的信息写入文本

	fclose(fp);///关闭文件
	printf("\n该条记录已经写入文件 list.txt，请前往查看！\n");
	n++;
	system("pause");
}

//计算支出总金额
void allMoneyCount() {
	totalMoney = 0;//初始化
	studyMoney = 0;//学习的金额总额
	cateringMoney = 0;//餐饮的金额总额
	clothesMoney = 0;//服装的金额总额
	recreationMoney = 0;//娱乐的金额总额
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

//计算不同类别的支出所占比例
void paymentPercent() {
	printf("请输入选择查看的支出类别(1代表学习，2代表餐饮，3代表服装，4代表娱乐)：\n");
	printf("类别\t百分比\n");
	printf("学习\t%5.2f\n", (studyMoney / totalMoney) * 100);
	printf("餐饮\t%5.2f\n", (cateringMoney / totalMoney) * 100);
	printf("服装\t%5.2f\n", (clothesMoney / totalMoney) * 100);
	printf("娱乐\t%5.2f\n", (recreationMoney / totalMoney) * 100);
	system("pause");
}

//对输入的类别进行判断，只能输入1-4
int usageJudge() {
	int usage= 0;
	printf("请输入支出的类别(1代表学习，2代表餐饮，3代表服装，4代表娱乐)：\n");
	printf("请选择(1-4):[ ]\b\b");
	usage = numberJudge();
	if (usage < 1 ||  usage >4)
	{
		printf("\n\t类别输入有误，请重新输入1-4范围内的数字！");
		usage = numberJudge();
	}
	return usage;
}

//对输入的数字进行分析，判断格式是否相符
int numberJudge() {
	int num;
	int sign = 0;
	int retur;
	do {
		sign = 0;
		retur = scanf(" %d", &num);//如果输入的n是十进制数字，则返回1（符合条件的参数）
		if (retur == 0) {
			printf("\n非法输入，请重新输入十进制数字！\n");
			for (; getchar() != '\n';);
				sign = -1;
		}
	} while (sign == -1);
	return num;
}


int main()
{
	readData();///读取文件数据
	menu();///显示主菜单
}
