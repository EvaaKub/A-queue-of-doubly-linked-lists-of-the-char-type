// Курсач (с комментами).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>

const int NotUsed = system("color E1");


//----------------------------------------------------------------------------------Двусв. список------//
struct Zven
{
	char value;  //данные
	Zven* nextElement = NULL; //указатель на следующий элемент
	Zven* prevElement = NULL; //указатель на предыдущий элемент
};

struct Spisok 
{
	Zven* head;      //указатель на начало списка типа Zven
	Zven* current;   // указатель на текущий элемент Zven
	Zven* tail;      //указатель на конец списка типа Zven
};
//----------------------------------------------------------------------------------Двусв. список------//


//----------------------------------------------------------------------------------Очередь------//
struct Node
{
	Spisok data;     //данные типа Spisok
	struct Node* next;      // указатель на следующий узел
}*rear = NULL, *front = NULL; //указатели на конец и начало

//----------------------------------------------------------------------------------Очередь------//


void menu3(int e); //прототип


//----------------------------------------------------------------------------------Работа со списком------//
void PrintList(Spisok collection) { //вывод списка
	Zven* node = collection.head;
	while (1) {
		printf("%c", node->value);
		if (node == collection.current)   //если указатель указывает на данный элемент печатаем *
			printf("*");
		node = node->nextElement;  //Передвигаемся вперед
		if (node == NULL) {   //Если конец очереди завершаем цикл
			printf("\n");
			break;
		}
	}
}
void DeleteNext(Spisok* list) { //удалить элемент после указателя 
	if (list->current->nextElement->nextElement != NULL) {  //если это не последний элемент списка
		Zven* badNode = list->current->nextElement;
		list->current->nextElement = list->current->nextElement->nextElement;
		list->current->nextElement->prevElement = list->current;
		free(badNode); //Освобождаем память
	}
	else {  //если это последний элемент списка
		free(list->current->nextElement); //Освобождаем память
		list->current->nextElement = NULL;
		list->tail = list->current; //Меняем указатель на конец
	}
}
void DeletePrev(Spisok* list) {
	if (list->current->prevElement->prevElement != NULL) {//если это не первый элемент списка
		Zven* badNode = list->current->prevElement;
		list->current->prevElement = list->current->prevElement->prevElement;
		list->current->prevElement->nextElement = list->current;
		free(badNode); //Освобождаем память

	}
	else { //если это первый элемент списка
		free(list->current->prevElement); //Освобождаем память
		list->current->prevElement = NULL;
		list->head = list->current; //Меняем указатель на начало
	}
}
void DeleteAll(Spisok* list) { //очистить список
	Zven* node = list->head;
	Zven* badElement = node;
	while (node->nextElement != NULL) //пока не конец списка
	{
		badElement = node;
		node = node->nextElement; //двигаемся вперед
		free(badElement); //Освобождаем память
	}
	list->head = NULL;      
	list->current = NULL;   
	list->tail = NULL;      
}
Spisok StartWork() {  //начать работу со списком
	Spisok list;
	list.current = NULL;
	list.head = NULL;
	list.tail = NULL;
	return list;

}
int CheckEmpty(Spisok* list) {  //проверка на пустоту списка
	if (list->head == NULL) {
		printf("\n\tСписок пуст\n");
		return 1;
	}
	else {
		printf("\n\tСписок непуст\n");
		return 0;
	}
}
void CheckPointerOnEnd(Spisok* list) {   //проверка находится ли указатель в конце списка
	if (list->current->nextElement == NULL) {  //если это последний элемент
		printf("Да\n");
	}
	else printf("Нет\n"); //иначе
}
void CheckPointerOnStart(Spisok* list) {  //проверка находится ли указатель в начале списка
	if (list->current->prevElement == NULL) {  //если это первый элемент
		printf("Да\n");
	}
	else printf("Нет\n");
}
void MovePointerToStart(Spisok* list) {  //переместить указатель в начало списка
	list->current = list->head;
}
void MovePointerToEnd(Spisok* list) {   //переместить указатель в конец списка
	list->current = list->tail;
}



struct Node* newNode(Spisok collection)// Вспомогательная функция для выделения нового узла 
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));// выделяем новый узел в куче

	if (node != NULL) // проверяем выделилась ли память
	{
		// устанавливаем данные в выделенном узле и возвращаем их
		node->data = collection;
		node->next = NULL;
		return node;
	}
	else 
	{
		printf("\nError, NULL");
		exit(EXIT_FAILURE);
	}
}

void enq(Spisok collection)      //изменение первого элемента в очереди
{
	struct Node* node = newNode(collection);
	front->data = node->data; //меняем значение
		
}

void enqueue(Spisok collection)     // вставка в конце
{
	struct Node* node = newNode(collection); // выделяем новый узел в куче

	if (front == NULL)  // очередь пуста
	{
		// инициализируем и переднюю, и заднюю часть
		front = node;
		rear = node;
	}
	else 
	{

		rear->next = node; //обновить заднюю часть
		rear = node; //обновить заднюю часть
	}
}

void AddElement(Spisok* collection, char data, int directionFlag) { //добавить элемент в список
	struct Zven* current;
	current = (struct Zven*)malloc(sizeof(struct Zven)); //выделяем новый узел в куче
	if (current == NULL) { printf("Error, NULL\n"); exit(1); }
	current->value = data;   //присваеваем значение данного
	current->nextElement = NULL;
	current->prevElement = NULL;
	
	if (directionFlag == 1) //Если выбран Before
	{
		if (collection->head == NULL) {  //если первый элемент в списке
			collection->head = current;
			collection->current = current;
			collection->tail = current;
		}
		else if (collection->current->prevElement == NULL) { //если текущий указатель указывает на первый элемент в списке
			current->nextElement = collection->current;
			collection->current->prevElement = current;
			collection->head = current; //изменяем указатель на первый элемент
		}
		else {
			current->prevElement = collection->current->prevElement; //Иначе
			current->nextElement = collection->current;
			collection->current->prevElement->nextElement = current;
			collection->current->prevElement = current;
		}
	}
	
	else if (directionFlag == 2)  //Если выбран After
	{ 
		if (collection->head == NULL) { //если первый элемент в списке
			collection->head = current;
			collection->current = current;
			collection->tail = current;
		}
		else if (collection->current->nextElement == NULL) { //если текущий указатель указывает на последний элемент в списке
			current->prevElement = collection->current;
			collection->current->nextElement = current;
			collection->tail = current; //изменяем указатель на последний элемент
		}
		else { //Иначе
			current->nextElement = collection->current->nextElement;
			current->prevElement = collection->current;
			collection->current->nextElement->prevElement = current;
			collection->current->nextElement = current;
		}
	}
}
void MovePointerForvard(Spisok* list) { //передвинуть указатель вперёд
	list->current = list->current->nextElement;
}
void MovePointerBack(Spisok* list) { //передвинуть указатель назад
	list->current = list->current->prevElement;
}
void CheckNext(Spisok* list) {   //показать элемент после указателя 
	printf("Следующий элемент: %c\n", list->current->nextElement->value);
}
void CheckPrev(Spisok* list) {   //показать элемент до указателя 
	printf("Предыдущий элемент: %c\n", list->current->prevElement->value);
}
void ChangeNext(Spisok* list, char data) {  //изменить элемент после указателя 
	list->current->nextElement->value = data;
}
void ChangePrev(Spisok* list, char data) {    //изменить элемент до указателя 
	list->current->prevElement->value = data;
}
//----------------------------------------------------------------------------------Работа со списком------//


//----------------------------------------------------------------------------------Работа с очередью------//

int isEmpty() //Проверка на пустоту очереди
{
	return rear == NULL && front == NULL;
}

void Print(Spisok collection) //вывод элемента очереди
{
	Zven* node = collection.head;
	while (1) 
	{
		printf("%c", node->value);
		node = node->nextElement;  //двигаемся к следующему элементу
		
		if (node == NULL) //если конец очереди
		{
			break;
		}
	}
}

void PrintOhered()      //Печать очереди
{
	system("CLS");
	struct Node* temp = front;
	
	if (isEmpty()) //проверка на пустоту
	{
		printf("\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");

	}
	printf("* * * * * ОЧЕРЕДЬ * * * * *\n\n");
	while (1)
	{
		Print(temp->data); //вызов функции вывода элемента очереди
		printf("|");
		temp = temp->next;  //продвигаемся вперед к следующему узлу
		if (temp == 0) //если достигли конца завершаем цикл
			break;
	}
	printf("\n\n");
}

void PrintOh()     //Печать очереди (вспомогательная)
{
	struct Node* temp = front;
	printf("\n");
	while (1)
	{
		Print(temp->data);
		printf("|");
		temp = temp->next;
		if (temp == 0)
			break;
	}
	printf("\n\n");
}


int yd()        //удалить в начале
{
	if (front == NULL)  //Доп. проверка
	{
		printf("\nError");
		exit(EXIT_FAILURE);
	}

	struct Node* temp = front;
	front = front->next;   // продвигаемся вперед к следующему узлу

	if (front == NULL) //если очередь станет пустой
	{
		rear = NULL;  //меняем указатель на конец
	}

	free(temp);   // освобождаем память удаленного узла 
}


int ydvce()       //удалить всё (очистить очередь)
{
	if (front == NULL) //Доп. проверка
	{
		printf("\nError");
		exit(EXIT_FAILURE);
	}

	struct Node* temp = front;
	
	while(front != NULL) // пока очередь не станет пустой
	{
		temp = front;
		front = front->next; // продвигаемся вперед к следующему узлу
		free(temp);  //освобождаем память удаленного узла 
	}
	rear = NULL;
}


int vzat()        //взять из начала
{
	if (front == NULL)
	{
		printf("\nError");
		exit(EXIT_FAILURE);
	}
	struct Node* temp = front;
	Print(temp->data);
	front = front->next;   //продвигаемся вперед к следующему узлу

	if (front == NULL) //если станет пустым
	{
		rear = NULL;
	}
	free(temp);   //освобождаем память удаленного узла 
}

int pokaz()        //Показать элемент в начале
{
	if (front == NULL)
	{
		printf("\nError");
		exit(EXIT_FAILURE);
	}
	struct Node* temp = front;

	Print(temp->data);   

}

int Shet()       //Кол-во элементов в очереди
{
	int i = 0;
	struct Node* temp = front;

	while (temp != NULL) //пока не конец очереди
	{
		temp = temp->next; //продвигаемся вперед к следующему узлу
		i++; //счет
	}
	return i;  //возвращаем кол-во элементов
}

//----------------------------------------------------------------------------------Работа с очередью------//



//----------------------------------------------------------------------------------Менюшки------//

int menu2()  //меню очереди
{
	int Gran = 6;
	int poka = 0;
	int action = 0;
	int buffer, i;
	while (poka == 0)  //пока не выбран пункт 0
	{
		system("cls");
		printf("Меню (очередь | максимальная длина: 6 элементов)\n");
		printf("\n   1. Просмотр очереди"); 
		printf("\n   2. Удалить элемент в начале очереди");
		printf("\n   3. Добавить элемент в конец очереди");
		printf("\n   4. Изменить значение элемента в начале очереди"); 
		printf("\n   5. Показать значение элемента в начале очереди"); 
		printf("\n   6. Взять элемент из начала очереди"); 
		printf("\n   7. Очистить очередь");
		printf("\n   8. Проверка: очередь пуста?");
		printf("\n   0. Выход\n\n");
		printf("\nОчередь: \n");
		if (isEmpty())
		{
			printf("\n| Очередь пуста! |\n\n");
		}
		else{ PrintOh();}  //вызов печати очереди ()
		printf("\nВыберите пункт:\n");
		scanf_s("%d", &action);
		buffer = getchar();//мусор
		switch (action)
		{
		case 0:
			system("CLS");
			if (isEmpty()) //проверка на пустоту очереди
			{
				poka = 1;

			}
			else
			{
				ydvce();  //если очередь не пуста - очищаем
				poka = 1;
			}
			break;
		case 1:
			system("CLS");
			if (isEmpty()) //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");

			}
			else
			{
				PrintOhered();
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}

			system("CLS");
			break;


		case 2:
			system("CLS");
			if (isEmpty()) //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");
			}
			else
			{
				yd();
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;

		case 3:
			system("CLS");
			i = Shet();
			if (i < Gran)  //если очередь не заполнена 
			{
				menu3(0); //вызов меню списка
			}
			else  //иначе
			{
				printf("\n\t |   Переполнение очереди!   |\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;
			
		case 4:
			system("CLS");
			if (isEmpty())  //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");

			}
			else
			{
				menu3(1);
				buffer = getchar();
				system("CLS");
			}
			break;

		case 5:
			system("CLS");
			if (isEmpty())  //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");

			}
			else
			{
				pokaz();
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;

		case 6:
			system("CLS");
			if (isEmpty())  //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");

			}
			else
			{
				vzat();
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;

		case 7:
			system("CLS");
			if (isEmpty())  //проверка на пустоту очереди
			{
				printf("\n\t!!! ОЧЕРЕДЬ ПУСТА !!!\n\n");
				buffer = getchar();
				system("CLS");

			}
			else
			{
				ydvce();
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;

		case 8:
			system("CLS");
			if (isEmpty())  //проверка на пустоту очереди
			{
				printf("\n\t |      ДА      |\n\n");
				buffer = getchar();
				system("CLS");
			}
			else
			{
				printf("\n\t |      НЕТ     |\n\n");
				printf("\n\n... Выполнено успешно!\n\n");
				buffer = getchar();
				system("CLS");
			}
			break;
		}
	}
	return 0;
}



void menu3(int e)  //меню списка
{
	int G1 = 0;
	G1 = e;
	Spisok list;
	if (G1 == 1) {  list = front->data; }
	else
	{
		 list = StartWork();
	}
	int menuPointer = 0;
	int men2 = 0;
	int buffer;
	int G = 0;
	system("cls");
	while ((men2 == 0) && (G == 0))  //пока не был выбран и выполнен пункт 19 или 20
	{
		menuPointer = 0;
		int directionFlag = 0;
		system("cls");
		printf("Меню (список)\n");

		printf("\n1. Очистить список\n");
		printf("2. Проверка: список пуст?\n");
		printf("3. Установить указатель на начало\n");
		printf("4. Установить указатель на конец \n");
		printf("5. Проверка: указатель в конце списка?\n");
		printf("6. Проверка: указатель в начале списка?\n");
		printf("7. Сдвинуть указатель вперед\n");
		printf("8. Сдвинуть указатель назад\n");
		printf("9. Показать элемент за указателем\n");
		printf("10. Показать элемент до указателя\n");
		printf("11. Удалить следующий элемент\n");
		printf("12. Удалить предыдущий элемент\n");
		printf("13. Взять следующий элемент\n");
		printf("14. Взять предыдущий элемент\n");
		printf("15. Изменить следующий элемент\n");
		printf("16. Изменить предыдущий элемент\n");
		printf("17. Добавить элемент\n");
		printf("18. Распечатать\n");
		printf("19. Положить список в очередь\n");
		printf("20. Перейти к меню очереди\n");
		printf("\nСписок: \n");
		if (list.head != NULL)  //если список не пуст
			PrintList(list);
		else printf("| Список пуст! |\n\n");  //иначе
		printf("\nВыберите пункт:\n");
		scanf_s("%d", &menuPointer);
		buffer = getchar(); //мусор
		switch (menuPointer)
		{
		case 1:
			system("cls");
			if (list.head != NULL) {
				DeleteAll(&list);
			}
			printf("... Выполнено успешно!\n\n");
			buffer = getchar();
			break;
		case 2:
			system("cls");
			CheckEmpty(&list);
			printf("\n... Выполнено успешно!\n\n");
			buffer = getchar();
			break;
		case 3:
			system("cls");
			if (list.head != NULL)
			{
				MovePointerToStart(&list);
				printf("... Выполнено успешно!\n\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 4:
			system("cls");
			if (list.head != NULL)
			{
				MovePointerToEnd(&list);
				printf("... Выполнено успешно!\n\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 5:
			system("cls");
			if (list.head != NULL) {
				CheckPointerOnEnd(&list);
				printf("... Выполнено успешно!\n\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 6:
			system("cls");
			if (list.head != NULL) {
				CheckPointerOnStart(&list);
				printf("... Выполнено успешно!\n\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 7:
			system("cls");
			if (list.head != NULL) {
				if (list.current->nextElement != NULL) {
					MovePointerForvard(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Конец списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 8:
			system("cls");
			if (list.head != NULL) {
				if (list.current->prevElement != NULL) {
					MovePointerBack(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Начало списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 9:
			system("cls");
			if (list.head != NULL) {
				if (list.current->nextElement != NULL) {
					CheckNext(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Конец списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 10:
			system("cls");
			if (list.head != NULL) {
				if (list.current->prevElement != NULL) {
					CheckPrev(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Начало списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 11:
			system("cls");
			if (list.head != NULL) {
				if (list.current->nextElement != NULL) {
					DeleteNext(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Конец списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 12:
			system("cls");
			if (list.head != NULL) {
				if (list.current->prevElement != NULL) {
					DeletePrev(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Начало списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 13:
			system("cls");
			if (list.head != NULL) {
				if (list.current->nextElement != NULL) {
					CheckNext(&list);
					DeleteNext(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Конец списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 14:
			system("cls");
			if (list.head != NULL) {
				if (list.current->prevElement != NULL) {
					CheckPrev(&list);
					DeletePrev(&list);
					printf("... Выполнено успешно!\n\n");
				}
				else printf("Начало списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 15:
			system("cls");
			if (list.head != NULL) {
				if (list.current->nextElement != NULL) {
					char inputChangeElement;
					printf("Введите новый элемент:\n");
					buffer = scanf_s("%c", &inputChangeElement);
					ChangeNext(&list, inputChangeElement);
					printf("... Выполнено успешно!\n\n");
					buffer = getchar();
				}
				else
					printf("Конец списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 16:
			system("cls");
			if (list.head != NULL) {
				if (list.current->prevElement != NULL) {
					char inputChangeElement;
					printf("Введите новый элемент:\n");
					buffer = scanf_s("%c", &inputChangeElement);
					ChangePrev(&list, inputChangeElement);
					printf("... Выполнено успешно!\n\n");
					buffer = getchar();
				}
				else
					printf("Начало списка\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 17:
			system("cls");
			char inputElement;
			printf("До или после указателя?\n");
			printf("1. До\n");
			printf("2. После\n");
			scanf_s("%d", &directionFlag);
			buffer = getchar();
			if (directionFlag == 1 || directionFlag == 2) {
				printf("Введите элемент:\n");
				buffer = scanf_s("%c", &inputElement);
				AddElement(&list, inputElement, directionFlag);
				printf("... Выполнено успешно!\n\n");
				buffer = getchar();
				buffer = getchar();
			}
			else {
				printf("Неправильный ввод\n");
				buffer = getchar();
			}
			break;
		case 18:
			system("cls");
			if (list.head != NULL) {
				PrintList(list);
				printf("... Выполнено успешно!\n\n");
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;

		case 19:
			system("cls");
			if (list.head != NULL)
			{
				
				if (G1 == 0)
				{
					enqueue(list);     //Вызов функции, которая добавляет елементы списка в очередь 
					printf("... Выполнено успешно!\n\n");
					buffer = getchar();
				}

				if (G1 == 1)
				{
					enq(list);       //Вызов функции, которая изменяет елемент списка в начале очереди
					printf("... Выполнено успешно!\n\n");
					buffer = getchar();
				}
				G = 1;
			}
			else printf("\n| Список пуст! Добавьте элементы и выберите пункт повторно  |\n\n");
			buffer = getchar();
			break;
		case 20:
			system("cls");
			
			men2 = 1;
			buffer = getchar();
			break;

		default:
			system("cls");
			break;
		}
	}
}
//----------------------------------------------------------------------------------Менюшки------//

void main()
{
	setlocale(LC_ALL, "Russian");
	int menuPointer = 0;
	while (menuPointer != 2)
	{
		menuPointer = 0;
		printf("Меню\n");  //главное меню
		printf("\nВыберите пункт:\n");
		printf("1) Начать работу с кодом\n");
		printf("2) Выход\n");
		scanf_s("%d", &menuPointer);
		if (menuPointer == 1)
		{
			menu2();  //вызов меню очереди
		}
		else if (menuPointer == 2)
		{
			system("cls");
			printf("\n\t| Работа завершена, возвращайтесь скорее! :3 | \n");
			exit(0);
		}
		else printf("\n\t| Такого пункта нет! Выберите пункт повторно из предоставленного списка | \n");
		system("cls");
	}
}