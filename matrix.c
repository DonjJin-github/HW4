#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //행렬을 생성하는 함수
void print_matrix(int** matrix, int row, int col);// 행렬을 출력하는 함수
int free_matrix(int** matrix, int row, int col); //동적할당한 배열을 해제하는 함수
int fill_data(int** matrix, int row, int col); //행렬에 값을 입력하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //두행렬을 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//두행렬을 빼는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //행렬의 전치행렬을 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //행렬의 곱을 시행하는 함수

int main()
{

    char command; //command 변수 선언
    printf("[----- [최동진]  [2019038016] -----]\n"); 

    int row, col; //변수 row,col선언
    srand(time(NULL));//srand를 선언하여 난수생성 시 항상 새로운 난수 값을 받을 수 있도록 한다

    printf("Input row and col : "); 
    scanf("%d %d", &row, &col); //사용자에게 row,col을 입력받는다
    int** matrix_a = create_matrix(row, col); //2중포인터 matrix_a를 create_matrix함수를 이용하여 동적할당
    int** matrix_b = create_matrix(row, col); //2중포인터 matrix_b를 create_matrix함수를 이용하여 동적할당
    int** matrix_a_t = create_matrix(col, row); //2중포인터 matrix_a_t를 create_matrix함수를 이용하여 동적할당


    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } //matrix_a가NULL이거나 matrix_b가 NULL일때 return -1

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //사용자에게 command를 입력받는다

        switch (command) { //command의 값에 따라 조건이 만족될 때까지 반복문 실행
        case 'z': case 'Z': //command가 z,Z일때
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);  //Fill_data함수를 호출하여 matrix_a에 임의의 0~19의 값 저장 
            fill_data(matrix_b, row, col); //Fill_data함수를 호출하여 matrix_b에 임의의 0~19의 값 저장 
            break;
        case 'p': case 'P': //command가 p,P일때
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //print_matrix를 호출하여 matrix_a를 출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //print_matrix를 호출하여 matrix_b를 출력
            break;
        case 'a': case 'A': //command가 a,A일때
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //addition_matrix함수를 호출
            break;
        case 's': case 'S': //command가 s,S일때
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //subtraction_matrix함수를 호출
            break;
        case 't': case 'T': //command가 t,T일때
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix 함수를 호출하여 matrix_a의 전치행렬을 구한다
            print_matrix(matrix_a_t, col, row); //print_matrix함수를 호출하여 matrix_a_t출력
            break;
        case 'm': case 'M': //command가 m,M일때
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix 함수를 호출하여 matrix_a의 전치행렬을 구한다
            multiply_matrix(matrix_a, matrix_a_t, row, col); //multiply_matrix 함수를 호출하여 matrix_a와t의 곱을 구한다
            break;
        case 'q': case 'Q': //command가 q,Q일때
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix_a_t 동적할당된 메모리 해제
            free_matrix(matrix_a, row, col); //matrix_a 동적할당된 메모리 해제
            free_matrix(matrix_b, row, col); //matrix_b 동적할당된 메모리 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');//command가 q와Q일때 반복문 종료

    return 1;
}

int** create_matrix(int row, int col)//이중포인터를 동적 메모리 할당을 하는 함수
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	}
    int** matrix;//이중포인터 matrix 선언
    matrix = malloc(sizeof(int*) * row); //matrix를 동적메모리 할당
    for (int i = 0; i < row; i++)
        matrix[i] = malloc(sizeof(int) * col);//matrix[i]를 동적메모리 할당
    /* Check post conditions */
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}
    return matrix; //matrix로 리턴
}

void print_matrix(int** matrix, int row, int col) //행렬을 출력하는 함수
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
	}
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%d\t", matrix[i][j]); //반복문을 이용하여 **matrix를 출력한다
        printf("\n");

    }
    /* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
	}

}


int free_matrix(int** matrix, int row, int col) //동적할당된 메모리를 해제하는 함수
{
/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < col; i++)
        free(matrix[i]);//반복문을 이용하여 matrix[i] 메모리 해제
    free(matrix); //matrix 메모리 해제
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = rand() % 20; //반복문을 이용하여 matirx[i][j]에 임의의 0~19의값 저장
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //두 행렬의 합을 구하는 함수
{
    int** matrix_sum= create_matrix(row, col); //**matrix_sum을 동적메모리 할당
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //반복문을 이용하여 matrix_sum에 matrix_a,b의 합 저장
    /* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(matrix_sum, row, col);//print_matrix 함수를 호출하여 matrix_sum 출력
	free_matrix(matrix_sum, row, col);//free_matrix 함수를 호출하여 matrix_sum메모리 해제
	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //두 행렬의 차를 구하는 함수
{
    int** matrix_sub = create_matrix(row, col); //**matrix_sub를 동적메모리 할당
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];//반복문을 이용하여 matrix_sub에 matrix_a,b의 차 저장
    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);//print_matrix 함수를 호출하여 matrix_sub출력
	free_matrix(matrix_sub, row, col);//free_matrix 함수를 호출하여 matrix_sub메모리 해제
	return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //전치행렬을 구하는 함수
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i]; //반복문을 이용하여 전치행렬을 구한다
    /* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//행렬의 곱을 구하는 함수
{
   int** matrix_axt = create_matrix(row, row); //**matrix_axt를 동적메모리 할당
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_axt[i][j] = 0;//반복문을 이용하여 matrix_axt의 값들을 0으로 초기화
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
            for (int k = 0; k < col; k++)
                matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];// matrix_axt를 구하는 반복문
   /* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);//print_matrix 함수를 호출하여 matrix_axt출력
	free_matrix(matrix_axt, row, row);//free_matrix 함수를 호출하여 matrix_axt메모리 해제
	return 1;
}


