#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50        //�迭�� ������ ����

int scan(int a[], int size);  //�迭 �Է��Լ�
int printarr(int a[]);           //�迭 ����Լ�    
int makeBST(int ba[], int result[], int size, int numofdata);  // ���� Ʈ���� ����� �Լ�
int delete(int a[], int size);                                //�迭�� �ִ� ���� �����ϴ� �Լ�
int SerchDeleteDataIndex(int a[], int remnum);       //�迭�ȿ��� �����ϰ� ���� ���� ã�� �Լ�
int NoChildDelete(int a[], int remnum);             //�ڽĳ�尡 ������ �����ϴ� �Լ�
int OneChildDelete(int a[], int size, int index);     //�ڽ� ��尡 �ϳ��� ������ �����ϴ� �Լ�
int rearrange(int a[], int size, int initial);         //�迭�� ��迭�ϴ� �Լ�


int main() {
    //a �迭 ������ -1�� �ʱ�ȭ
    int a[MAX_SIZE];          
    memset(a, -1, sizeof(a)); 

    //a �迭�� ���� ����
    int numofdata = scan(a, MAX_SIZE);

    //bst �迭 ���� �� -1�� �ʱ�ȭ
    int bstarr[MAX_SIZE];
    memset(bstarr, -1, sizeof(bstarr));

    //a�迭 ���� ���
    printf("\n�Է¹��� �迭\n");
    printarr(a);

    //����Ʈ���� �����ϴ� �Լ�
    makeBST(a, bstarr, MAX_SIZE, numofdata);

    //����Ʈ�� ���
    printf("\n����Ʈ�� �迭\n");
    printarr(bstarr);

    //����Ʈ���� �� ����
    delete(bstarr, MAX_SIZE);
    
    //���� �� ����Ʈ�� ���
    printf("\n���� �� ����Ʈ�� �迭\n");
    printarr(bstarr);


    return 0;
}


int scan(int a[], int size) { //��°��� int ����.
    char k = 'y';   //�� �Է� ���θ� �޴� ����
    int i = 0;      //�� �Է�Ƚ�� ���

    //
    while (k != 'n' && i < size) {
        //�迭�� �� �Է¿��� �ֱ�
        printf("�迭�� ���� �Է��ϰ� ������ y, �ƴϸ� n: ");
        scanf_s(" %c", &k);
        if (k == 'y') {
            printf("�Է��ϰ� ���� ���� ���ÿ�: ");
            scanf_s("%d", &a[i]);
            i++;
        }
    }

    //�迭�� ���°���� ����ߴ��� return
    return i; 
}

int printarr(int a[]) {
    for (int i = 0; i < MAX_SIZE; i++) { //bstarr�� ��ȿ ���ڰ� �ִ� numofdata ���� ���.
        printf("%d ", a[i]);
    }

    return 0;
}

int makeBST(int ba[], int bstarr[], int size, int numofdata) {  //����Ʈ���� ����� �Լ�
    //int t = -1;         //�迭�� �� ��°���� ����ߴ��� �����ϴ� ����
    int index = 0;
    //bst�� �׳� �迭 �ε��� 1�� �ʱ�ȭ //result[0] �ƴ� ����
    bstarr[1] = ba[0];

    //ba�� �ε��� 0���� �־������ϱ�, �ε��� 1�� ���� / numofdata �� �ݺ�.
    for (int a = 1; a <= numofdata; a++) { //�־��ִ� Ƚ����ŭ �ݺ�. 

        int i = 1; //���� Ž�� Ʈ�� �ε����� 1���� �����ؾ� 0���� �����ϸ� �ڸ����� ��� 0�� ����.

        while (bstarr[i] != -1) {//-1���� �ƴϸ� ���� �ڸ��� ã�� ���� ��� �ݺ�. //�迭 ���� ���� -1�̶�� while�ݺ��� ������ �迭 �� ����.

            if (bstarr[i] > ba[a]) {//�Է°��� ���� ������ �۴�.
                i = 2 * i;
            }
            else if (bstarr[i] < ba[a]) {
                i = 2 * i + 1;
            }
            else break;
        }
        //�迭 ���� ���� -1�� �ƴ϶��, ���� i�ڸ� ���� ���� �־���� �Է¹迭 �� �־��ֱ�.
        bstarr[i] = ba[a];
        index = i;//index ���� ��� i������ �ʱ�ȭ ��.
    }//������� for �ݺ���

    return index;//��ȿ���� �ε����� ��ȯ�� �� �� numofdata2 �� �־��ֱ� 
}

int delete(int a[], int size) {
    int remnum;      //�����ϰ� ���� ���� �Է¹޴� �Ű�����
      
    int i = 1;      //k�� �迭�� ���°�� ��ġ�ߴ��� �˷��ִ� �Ű�����

    //���� ��Ű�� ���� �� �Է¹ޱ�
    printf("\n�迭 �� �����ϰ� ���� ���� �Է����ּ���\n"); 
    scanf_s("%d", &remnum);

    //�����ϰ� ���� ���� ��ġ ã��
    int remnumi = SerchDeleteDataIndex(a,remnum);
    
     
     //������ �����ϱ� 
    if (a[remnumi * 2 + 1] == -1 && a[2 * remnumi] == -1) {//�ڽ��� ���� ���
        NoChildDelete(a, remnumi);
    }
    else if (a[remnumi * 2 + 1] == -1 || a[2 * remnumi] == -1) {    //�ڽ��� ���ʿ��� �ִ� ���
        OneChildDelete(a, size, remnumi);
    }
    else {  //���ʿ� �ִ� ���
        
    }
    
    return 0;
}

int SerchDeleteDataIndex(int a[], int remnum) {
    int i=1;
    while (a[i] != remnum) {

        if (a[i] > remnum) {     //���� �ڽ����� �̵�
            i = 2 * i;
        }
        else if (a[i] < remnum) {    //������ �ڽ����� �̵�
            i = 2 * i + 1;
        }
        else if (a[i] == -1) {   //�迭�� ���� �������� �ʴ� ���
            printf("\n�迭 �� �Է��Ͻ� ���� �������� �ʽ��ϴ�. �Ʒ��迭�� ���ð� �ٽ� �Է��Ͽ��ּ���.\n");
            printarr(a);
            delete(a, MAX_SIZE);
        }
        else break;     //���� ���� ã�� ���
    }
    
    return i;
}

int NoChildDelete(int a[], int remnum) {
    
    a[remnum] = -1;
    
    return 0;
}

int OneChildDelete(int a[], int size, int index) {
    
    int parent=index;
    int rchild=index*2+1;
    int lchild=index*2;

    if (a[rchild] != -1) {
        a[parent] = a[rchild];     //�θ�� �ڽ��� �Ű��ش�
        a[rchild] = -1;             //�ű� ���� �ΰ����ιٲ۴�
        rearrange(a, size, rchild); 
    }
    else {
        a[parent] = a[lchild];     //�θ�� �ڽ��� �Ű��ش�
        a[lchild] = -1;            //�ű� ���� �ΰ����ιٲ۴�
        rearrange(a, size, lchild);
        
    }
   
    return 0;
}

int rearrange(int a[], int size, int initial) {
    int leftchild = 2 * initial;        //���� �ڽ�
    int rightchild = 2 * initial + 1;   //������ �ڽ�

    //���� �ڽ� ��迭
    if (leftchild <= size && a[leftchild] != -1) {
        a[initial] = a[leftchild];
        a[leftchild] = -1;
        rearrange(a, size, leftchild);
   }
    //������ �ڽ� ��迭
    if (rightchild <= size && a[rightchild] != -1) {
        a[initial] = a[rightchild];
        a[rightchild] = -1;
        rearrange(a, size, rightchild);
    }
    return 0;

}