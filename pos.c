#include <stdio.h>

#define MAX_MENU_NUM 7
#define MAX_TABLE_NUM 10

typedef struct MENU {
	char *menu_name; // 메뉴이름
	int price; // 가격
	int sale_num; //판매량
	int table_sale_num[MAX_TABLE_NUM]; // 테이블별 판매량
}MENU;

typedef struct TABLE {
	int table_num; // 테이블번호
	MENU *detail; // 주문내역
	int table_price; // 총액
}TABLE;

void Calculration(TABLE *table, MENU *menu, int table_num, int menu_num) // 계산하기
{
	printf("%d번 테이블 판매액 : %d\n", table_num, table[table_num - 1].table_price);

	if (menu_num == MAX_MENU_NUM + 1) { // 현금계산
		int i;
		printf("받은 금액 : ");
		scanf("%d", &i);
		printf("거스름돈 : %d\n", i - table[table_num - 1].table_price);
		printf("---계산 완료 ---\n");
	}

	if (menu_num == MAX_MENU_NUM + 2) { // 카드계산
		printf("---카드 결제 ---\n");
		printf("---계산 완료 ---\n");
	}

	for (int i = 0; i < MAX_TABLE_NUM; i++)
		table[table_num - 1].detail[i].table_sale_num[table_num - 1] = 0;
	table[table_num - 1].table_price = 0;
}

void Bill(TABLE *table, MENU *menu, int table_num, int menu_num) // 영수증발급
{
	if (menu_num == MAX_MENU_NUM + 3) { // 총액만 영수증
		printf("-table%d 주문정보\n", table[table_num - 1].table_num); // 테이블별 주문내역

		printf("        총액 : %d원\n\n", table[table_num - 1].table_price);
	}

	if (menu_num == MAX_MENU_NUM + 4) { // 판매내역과 영수증
		printf("-table%d 주문정보\n", table[table_num - 1].table_num); // 테이블별 주문내역
		for (int i = 0; i < MAX_MENU_NUM; i++)
			if (table[table_num - 1].detail[i].table_sale_num[table_num - 1] != 0)
				printf("%12s : %2d\n", table[table_num - 1].detail[i].menu_name, table[table_num - 1].detail[i].table_sale_num[table_num - 1]);
		printf("        총액 : %d원\n\n", table[table_num - 1].table_price);
	}
}

void Sales(MENU *menu) // 매출확인
{
	int total_price = 0;

	for (int i = 0; i < MAX_MENU_NUM; i++)
		total_price += menu[i].sale_num * menu[i].price;
	printf("전체 매출액 : %d\n", total_price);

	printf("메뉴별 판매량 및 판매액\n");
	for (int i = 0; i < MAX_MENU_NUM; i++)
		printf("%d. %12s : %2d %6d\n", i + 1, menu[i].menu_name, menu[i].sale_num, menu[i].sale_num * menu[i].price);




}




void Table(TABLE *table, MENU *menu, int table_num)
{
	int menu_num = 0;

	while (menu_num != MAX_MENU_NUM + 5) {
		printf("-table%d 주문정보\n", table[table_num - 1].table_num); // 테이블별 주문내역
		for (int i = 0; i < MAX_MENU_NUM; i++)
			if (table[table_num - 1].detail[i].table_sale_num[table_num - 1] != 0)
				printf("%12s : %2d\n", table[table_num - 1].detail[i].menu_name, table[table_num - 1].detail[i].table_sale_num[table_num - 1]);
		printf("        총액 : %d원\n\n", table[table_num - 1].table_price);

		for (int i = 0; i < MAX_MENU_NUM; i++)
			printf("%d. %12s : %5d\n", i + 1, menu[i].menu_name, menu[i].price);
		printf("%d. 현금계산\n", MAX_MENU_NUM + 1);
		printf("%d. 카드계산\n", MAX_MENU_NUM + 2);
		printf("%d. 영수증발급(가격)\n", MAX_MENU_NUM + 3);
		printf("%d. 영수증발급(내역+가격)\n", MAX_MENU_NUM + 4);
		printf("%d. 주문종료\n", MAX_MENU_NUM + 5);
		printf("***************************\n");
		printf("*********선택 : ");
		scanf("%d", &menu_num);
		printf("***************************\n");

		if (menu_num <= MAX_MENU_NUM) {
			table[table_num - 1].detail[menu_num - 1].table_sale_num[table_num - 1]++; // 그메뉴 테이블 주문 갯수
			table[table_num - 1].table_price += menu[menu_num - 1].price; // 테이블 판매액
			menu[menu_num - 1].sale_num++; // 그메뉴 총 주문갯수
		}
		else if (menu_num == MAX_MENU_NUM + 1 || menu_num == MAX_MENU_NUM + 2) { // 계산관련
			Calculration(table, menu, table_num, menu_num);
			menu_num = MAX_MENU_NUM + 5;
		}
		else if (menu_num == MAX_MENU_NUM + 3 || menu_num == MAX_MENU_NUM + 4) { // 영수증발급
			Bill(table, menu, table_num, menu_num);
			menu_num = MAX_MENU_NUM + 5;
		}
		else
			menu_num = MAX_MENU_NUM + 5;
	}
}

void main()
{
	int table_num = 0;

	MENU menu[MAX_MENU_NUM] = { //메뉴판
		{ "후라이드치킨", 16000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "양념치킨", 17000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "간장치킨", 17000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "불고기피자", 13000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "포테이토피자", 13000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "맥주", 5000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ "음료수", 2000, 0,{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }
	};

	TABLE table[MAX_TABLE_NUM] = { // 테이블정보정리
		{ 1, &menu[0], 0 },
		{ 2, &menu[0], 0 },
		{ 3, &menu[0], 0 },
		{ 4, &menu[0], 0 },
		{ 5, &menu[0], 0 },
		{ 6, &menu[0], 0 },
		{ 7, &menu[0], 0 },
		{ 8, &menu[0], 0 },
		{ 9, &menu[0], 0 },
		{ 10, &menu[0], 0 },
	};

	while (table_num != MAX_TABLE_NUM + 2) {
		for (int i = 1; i <= 10; i++)
			printf("%d. table%d\n", i, i);
		printf("%d. 매출확인\n", MAX_TABLE_NUM + 1);
		printf("%d. POS종료\n", MAX_TABLE_NUM + 2);
		printf("***************************\n");
		printf("*********선택 : ");
		scanf("%d", &table_num);
		printf("***************************\n");
		if (table_num <= MAX_TABLE_NUM)
			Table(&table, &menu, table_num);
		else if (table_num == MAX_TABLE_NUM + 1) { // 매출확인
			Sales(&menu);
		}
		else
			table_num = MAX_TABLE_NUM + 2;
	}
}
