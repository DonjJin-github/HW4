#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //����� �����ϴ� �Լ�
void print_matrix(int** matrix, int row, int col);// ����� ����ϴ� �Լ�
int free_matrix(int** matrix, int row, int col); //�����Ҵ��� �迭�� �����ϴ� �Լ�
int fill_data(int** matrix, int row, int col); //��Ŀ� ���� �Է��ϴ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //������� ���ϴ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);//������� ���� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //����� ��ġ����� ���ϴ� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //����� ���� �����ϴ� �Լ�

int main()
{

    char command; //command ���� ����
    printf("[----- [�ֵ���]  [2019038016] -----]\n"); 

    int row, col; //���� row,col����
    srand(time(NULL));//srand�� �����Ͽ� �������� �� �׻� ���ο� ���� ���� ���� �� �ֵ��� �Ѵ�

    printf("Input row and col : "); 
    scanf("%d %d", &row, &col); //����ڿ��� row,col�� �Է¹޴´�
    int** matrix_a = create_matrix(row, col); //2�������� matrix_a�� create_matrix�Լ��� �̿��Ͽ� �����Ҵ�
    int** matrix_b = create_matrix(row, col); //2�������� matrix_b�� create_matrix�Լ��� �̿��Ͽ� �����Ҵ�
    int** matrix_a_t = create_matrix(col, row); //2�������� matrix_a_t�� create_matrix�Լ��� �̿��Ͽ� �����Ҵ�


    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } //matrix_a��NULL�̰ų� matrix_b�� NULL�϶� return -1

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
        scanf(" %c", &command); //����ڿ��� command�� �Է¹޴´�

        switch (command) { //command�� ���� ���� ������ ������ ������ �ݺ��� ����
        case 'z': case 'Z': //command�� z,Z�϶�
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);  //Fill_data�Լ��� ȣ���Ͽ� matrix_a�� ������ 0~19�� �� ���� 
            fill_data(matrix_b, row, col); //Fill_data�Լ��� ȣ���Ͽ� matrix_b�� ������ 0~19�� �� ���� 
            break;
        case 'p': case 'P': //command�� p,P�϶�
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //print_matrix�� ȣ���Ͽ� matrix_a�� ���
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //print_matrix�� ȣ���Ͽ� matrix_b�� ���
            break;
        case 'a': case 'A': //command�� a,A�϶�
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //addition_matrix�Լ��� ȣ��
            break;
        case 's': case 'S': //command�� s,S�϶�
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //subtraction_matrix�Լ��� ȣ��
            break;
        case 't': case 'T': //command�� t,T�϶�
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix �Լ��� ȣ���Ͽ� matrix_a�� ��ġ����� ���Ѵ�
            print_matrix(matrix_a_t, col, row); //print_matrix�Լ��� ȣ���Ͽ� matrix_a_t���
            break;
        case 'm': case 'M': //command�� m,M�϶�
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix �Լ��� ȣ���Ͽ� matrix_a�� ��ġ����� ���Ѵ�
            multiply_matrix(matrix_a, matrix_a_t, row, col); //multiply_matrix �Լ��� ȣ���Ͽ� matrix_a��t�� ���� ���Ѵ�
            break;
        case 'q': case 'Q': //command�� q,Q�϶�
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix_a_t �����Ҵ�� �޸� ����
            free_matrix(matrix_a, row, col); //matrix_a �����Ҵ�� �޸� ����
            free_matrix(matrix_b, row, col); //matrix_b �����Ҵ�� �޸� ����
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');//command�� q��Q�϶� �ݺ��� ����

    return 1;
}

int** create_matrix(int row, int col)//���������͸� ���� �޸� �Ҵ��� �ϴ� �Լ�
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	}
    int** matrix;//���������� matrix ����
    matrix = malloc(sizeof(int*) * row); //matrix�� �����޸� �Ҵ�
    for (int i = 0; i < row; i++)
        matrix[i] = malloc(sizeof(int) * col);//matrix[i]�� �����޸� �Ҵ�
    /* Check post conditions */
	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	}
    return matrix; //matrix�� ����
}

void print_matrix(int** matrix, int row, int col) //����� ����ϴ� �Լ�
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
	}
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%d\t", matrix[i][j]); //�ݺ����� �̿��Ͽ� **matrix�� ����Ѵ�
        printf("\n");

    }
    /* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
	}

}


int free_matrix(int** matrix, int row, int col) //�����Ҵ�� �޸𸮸� �����ϴ� �Լ�
{
/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < col; i++)
        free(matrix[i]);//�ݺ����� �̿��Ͽ� matrix[i] �޸� ����
    free(matrix); //matrix �޸� ����
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
            matrix[i][j] = rand() % 20; //�ݺ����� �̿��Ͽ� matirx[i][j]�� ������ 0~19�ǰ� ����
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) //�� ����� ���� ���ϴ� �Լ�
{
    int** matrix_sum= create_matrix(row, col); //**matrix_sum�� �����޸� �Ҵ�
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; //�ݺ����� �̿��Ͽ� matrix_sum�� matrix_a,b�� �� ����
    /* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

    print_matrix(matrix_sum, row, col);//print_matrix �Լ��� ȣ���Ͽ� matrix_sum ���
	free_matrix(matrix_sum, row, col);//free_matrix �Լ��� ȣ���Ͽ� matrix_sum�޸� ����
	return 1;
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) //�� ����� ���� ���ϴ� �Լ�
{
    int** matrix_sub = create_matrix(row, col); //**matrix_sub�� �����޸� �Ҵ�
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];//�ݺ����� �̿��Ͽ� matrix_sub�� matrix_a,b�� �� ����
    /* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);//print_matrix �Լ��� ȣ���Ͽ� matrix_sub���
	free_matrix(matrix_sub, row, col);//free_matrix �Լ��� ȣ���Ͽ� matrix_sub�޸� ����
	return 1;
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col) //��ġ����� ���ϴ� �Լ�
{
    /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_t[i][j] = matrix[j][i]; //�ݺ����� �̿��Ͽ� ��ġ����� ���Ѵ�
    /* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)//����� ���� ���ϴ� �Լ�
{
   int** matrix_axt = create_matrix(row, row); //**matrix_axt�� �����޸� �Ҵ�
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix_axt[i][j] = 0;//�ݺ����� �̿��Ͽ� matrix_axt�� ������ 0���� �ʱ�ȭ
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
            for (int k = 0; k < col; k++)
                matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];// matrix_axt�� ���ϴ� �ݺ���
   /* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);//print_matrix �Լ��� ȣ���Ͽ� matrix_axt���
	free_matrix(matrix_axt, row, row);//free_matrix �Լ��� ȣ���Ͽ� matrix_axt�޸� ����
	return 1;
}


