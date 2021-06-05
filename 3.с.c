#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void createField(int * q,int * **arr, int *sizeOfX, int *sizeOfY);
void fillWithBombzEz(int **arr1, int sizeOfX, int sizeOfY, int *countOfBomb);
bool openCells(int **field, int sizeOfX, int sizeOfY, int posi, int posj);
void showField(int **arr1, int sizeOfX, int sizeOfY);
int checkNearCells(int **field, int sizeOfX, int sizeOfY, int posi, int posj);
void setFlag(int **field, int posi, int posj);
bool condOfWin(int **field, int sizeOfX, int sizeOfY, int countOfBomb);

bool openCells(int **field, int sizeOfX, int sizeOfY, int posi, int posj)
{
	if (field[posi][posj] == -1) 
	{
		field[posi][posj] = checkNearCells(field, sizeOfX, sizeOfY, posi, posj);
		if (checkNearCells(field, sizeOfX, sizeOfY, posi, posj) == 0) 
		{
			if ((posi - 1 > 0) && (checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj) == 0)) openCells(field, sizeOfX, sizeOfY, posi-1, posj);
			else if (posi - 1 > 0) field[posi-1][posj] = checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj);
			if ((posi - 1 > 0) && (posj + 1 < sizeOfX - 1) && (checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj+1) == 0)) openCells(field, sizeOfX, sizeOfY, posi-1, posj+1);
			else if ((posi - 1 > 0) && (posj + 1 < sizeOfX - 1)) field[posi-1][posj+1] = checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj+1);
			if ((posj + 1 < sizeOfX - 1) && (checkNearCells(field, sizeOfX, sizeOfY, posi, posj+1) == 0)) openCells(field, sizeOfX, sizeOfY, posi, posj+1);
			else if (posj + 1 < sizeOfX - 1) field[posi][posj+1] = checkNearCells(field, sizeOfX, sizeOfY, posi, posj+1);
			if ((posi + 1 < sizeOfY - 1) && (posj + 1 < sizeOfX - 1) && (checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj+1) == 0)) openCells(field, sizeOfX, sizeOfY, posi+1, posj+1);
			else if ((posi + 1 < sizeOfY - 1) && (posj + 1 < sizeOfX - 1)) field[posi+1][posj+1] = checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj+1);
			if ((posi + 1 < sizeOfY - 1) && (checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj) == 0)) openCells(field, sizeOfX, sizeOfY, posi+1, posj);
			else if (posi + 1 < sizeOfY - 1) field[posi+1][posj] = checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj);
			if ((posj - 1 > 0) && (posi + 1 < sizeOfY - 1) && (checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj-1) == 0)) openCells(field, sizeOfX, sizeOfY, posi+1, posj-1);
			else if ((posj - 1 > 0) && (posi + 1 < sizeOfY - 1)) field[posi+1][posj-1] = checkNearCells(field, sizeOfX, sizeOfY, posi+1, posj-1);
			if ((posj - 1 > 0) && (checkNearCells(field, sizeOfX, sizeOfY, posi, posj-1) == 0)) openCells(field, sizeOfX, sizeOfY, posi, posj-1);
			else if (posj - 1 > 0) field[posi][posj-1] = checkNearCells(field, sizeOfX, sizeOfY, posi, posj-1);
			if ((posi - 1 > 0) && (posj - 1 > 0) && (checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj-1) == 0)) openCells(field, sizeOfX, sizeOfY, posi-1, posj-1);
			else if ((posi - 1 > 0) && (posj - 1 > 0)) field[posi-1][posj-1] = checkNearCells(field, sizeOfX, sizeOfY, posi-1, posj-1); 
		}
	}
	else if(field[posi][posj] == -2)
	{		
		printf("Вы проиграли!");
		return true;
	}
	return false;	
}


void createField(int * q,int * **arr, int *sizeOfX, int *sizeOfY)
{
	
	int i, j;
	
	printf("Введите размер поля (х/у): ");
	scanf("%d %d", sizeOfX, sizeOfY);
	
	* arr =(int **)malloc(*sizeOfY*sizeof(int *));
	for (i = 0; i < *sizeOfY; i++)
	{
		(*arr)[i] = (int *)malloc(*sizeOfX * sizeof(int));
		for (j = 0; j < *sizeOfX; j++) 
		{
			if ((i == 0) || (j == 0) || (i == *sizeOfY - 1) || (j == *sizeOfX - 1)) (*arr)[i][j] = -10;
			else (*arr)[i][j] = -1;
		}
	}
}

void fillWithBombzEz(int **arr1, int sizeOfX, int sizeOfY, int *countOfBomb)
{
	int x,y, i;
	do {
		printf("Введите количество бомб: ");
		scanf("%d", countOfBomb);
		if ((*countOfBomb < 0) || (*countOfBomb > sizeOfX * sizeOfY - 1)) printf("\nНедопустимое кол-во бомб\n");
	} while ((*countOfBomb < 0) || (*countOfBomb > sizeOfX * sizeOfY - 1));
	for (i = 1; i <= *countOfBomb; i++)
	{
		do {
			x = 1 + rand() % (sizeOfX - 2);
			y = 1 + rand() % (sizeOfY - 2);
		} while (arr1[y][x] == -2);
		arr1[y][x] = -2;
	}
}
	

int main()
{
	srand(time(NULL));
	int **field, i, j,q, sizeOfX, sizeOfY, posi, posj, choiseKey, countOfBomb;
	bool lose = false;
	createField(&q, &field, &sizeOfX, &sizeOfY);
	fillWithBombzEz(field, sizeOfX, sizeOfY, &countOfBomb);
	showField(field, sizeOfX, sizeOfY);	
	
	do {
		do {
			printf("Возможные варианты действий: \n1) Открыть клетку 2) Поставить флажок\n Выберите действие: ");
			scanf("%d", &choiseKey);
			if ((choiseKey < 1) || (choiseKey > 2)) printf("\nНекорректный ввод\n");
		} while ((choiseKey < 1) || (choiseKey > 2));
		do {
			do {
				printf("Введите координаты клетки: ");
				scanf("%d %d", &posi, &posj);
				if ((posi < 1) || (posi > sizeOfY - 2) || (posj < 1) || (posj > sizeOfX - 2)) printf("\nНекорректный ввод\n");
			} while ((posi < 1) || (posi > sizeOfY - 2) || (posj < 1) || (posj > sizeOfX - 2));
			if ((choiseKey == 2) && (field[posi][posj] >= 0)) printf("Вы не можете поставить сюда флажок\n");
		} while ((choiseKey == 2) && (field[posi][posj] >= 0));
		(choiseKey == 1)? lose = openCells(field, sizeOfX, sizeOfY, posi, posj): setFlag(field, posi, posj);
		showField(field, sizeOfX, sizeOfY);
	} while ((lose == false) && (condOfWin(field, sizeOfX, sizeOfY, countOfBomb) == false));
}
	
	
void showField(int **arr1, int sizeOfX, int sizeOfY)
{
	int i, j;
	for (i = 0; i < sizeOfY * 2 + 1; i++)
	{	
		if (i == 0)
		{
			for (j = 0; j < sizeOfX; j++) 
			{
				if (j == 0) printf("    %d", j);
				else if (j > 10) printf(" %d", j); 
				else printf ("  %d", j);
			}
			printf("\n");
		}
		for (j = 0; j < sizeOfX; j++)
		{
			if ((i % 2 == 0) && (j == 0)) printf("   ---");
			else if (i % 2 == 0) printf("---");
			else if ((i % 2 == 1) && (j == 0))
			{
				if (i/2 < 10) printf(" %d", i/2);
				else printf("%d", i/2);
				if (arr1[i/2][j] == -1) printf(" |  ");
				else if (arr1[i/2][j] == -2) printf(" |  ");
				else if ((arr1[i/2][j] == -3) || (arr1[i/2][j] == -4)) printf(" | P");
				else if (arr1[i/2][j] == -10) printf(" |XX");
				else printf(" | %d", arr1[i/2][j]);
			}
			else 
			{
				if (arr1[i/2][j] == -1) printf("|  ");
				else if (arr1[i/2][j] == -2) printf("|  "); 
				else if ((arr1[i/2][j] == -3) || (arr1[i/2][j] == -4)) printf("| P");
				else if (arr1[i/2][j] == -10) printf("|XX");
				else printf("| %d", arr1[i/2][j]);
			}
		}
		((i == 0) || (i == sizeOfY * 2))? printf("-\n"): printf("|\n");
	}
	printf("\n");
}
	
int checkNearCells(int **field, int sizeOfX, int sizeOfY, int posi, int posj)
{
	int count = 0;
	if ((posi - 1 > 0) && ((field[posi-1][posj] == -2) || (field[posi-1][posj] == -4))) count++;
	if ((posi - 1 > 0) && (posj + 1 < sizeOfX - 1) && ((field[posi-1][posj+1] == -2) || (field[posi-1][posj+1] == -4))) count++;
	if ((posj + 1 < sizeOfX - 1) && ((field[posi][posj+1] == -2) || (field[posi][posj+1] == -4))) count++;
	if ((posi + 1 < sizeOfY - 1) && (posj + 1 < sizeOfX - 1) && ((field[posi+1][posj+1] == -2) || (field[posi+1][posj+1] == -4))) count++;
	if ((posi + 1 < sizeOfY - 1) && ((field[posi+1][posj] == -2) ||(field[posi+1][posj] == -4))) count++;
	if ((posj - 1 > 0) && (posi + 1 < sizeOfY - 1) && ((field[posi+1][posj-1] == -2) || (field[posi+1][posj-1] == -4))) count++;
	if ((posj - 1 > 0) && ((field[posi][posj-1] == -2) || (field[posi][posj-1] == -4))) count++;
	if ((posi - 1 > 0) && (posj - 1 > 0) && ((field[posi-1][posj-1] == -2) || (field[posi-1][posj-1] == -4))) count++;
	return count;
}

void setFlag(int **field, int posi, int posj)
{
	if (field[posi][posj] == -1) field[posi][posj] = -3;
	else if (field[posi][posj] == -2) field[posi][posj] = -4;
	else if (field[posi][posj] == -3) field[posi][posj] = -1;
	else if (field[posi][posj] == -4) field[posi][posj] = -2;
}

bool condOfWin(int **field, int sizeOfX, int sizeOfY, int countOfBomb)
{
	int i, j, localCountOfBomb = 0, countOfFlag = 0;
	for (i = 0; i < sizeOfY; i++)
	{
		for (j = 0; j < sizeOfX; j++)
		{
			if ((field[i][j] == -3) || (field[i][j] == -4)) countOfFlag++;
			else if (field[i][j] == -2) localCountOfBomb++;
		}
	}
	if ((countOfFlag == countOfBomb) && (localCountOfBomb == 0)) return true;
	else return false;
}