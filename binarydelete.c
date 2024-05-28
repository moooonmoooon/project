#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50        //배열의 사이즈 정의

int scan(int a[], int size);  //배열 입력함수
int printarr(int a[]);           //배열 출력함수    
int makeBST(int ba[], int result[], int size, int numofdata);  // 이진 트리를 만드는 함수
int delete(int a[], int size);                                //배열애 있는 수를 삭제하는 함수
int SerchDeleteDataIndex(int a[], int remnum);       //배열안에서 삭제하고 싶은 수를 찾는 함수
int NoChildDelete(int a[], int remnum);             //자식노드가 없을때 삭제하는 함수
int OneChildDelete(int a[], int size, int index);     //자식 노드가 하나만 있을때 삭제하는 함수
int rearrange(int a[], int size, int initial);         //배열을 재배열하는 함수


int main() {
    //a 배열 생성후 -1로 초기화
    int a[MAX_SIZE];          
    memset(a, -1, sizeof(a)); 

    //a 배열에 숫자 삽입
    int numofdata = scan(a, MAX_SIZE);

    //bst 배열 생성 후 -1로 초기화
    int bstarr[MAX_SIZE];
    memset(bstarr, -1, sizeof(bstarr));

    //a배열 값들 출력
    printf("\n입력받은 배열\n");
    printarr(a);

    //이진트리로 정렬하는 함수
    makeBST(a, bstarr, MAX_SIZE, numofdata);

    //이진트리 출력
    printf("\n이진트리 배열\n");
    printarr(bstarr);

    //이진트리의 수 삭제
    delete(bstarr, MAX_SIZE);
    
    //삭제 후 이진트리 출력
    printf("\n삭제 후 이진트리 배열\n");
    printarr(bstarr);


    return 0;
}


int scan(int a[], int size) { //출력값은 int 정수.
    char k = 'y';   //수 입력 여부를 받는 변수
    int i = 0;      //수 입력횟수 출력

    //
    while (k != 'n' && i < size) {
        //배열에 수 입력여부 넣기
        printf("배열에 수를 입력하고 싶으면 y, 아니면 n: ");
        scanf_s(" %c", &k);
        if (k == 'y') {
            printf("입력하고 싶은 수를 쓰시오: ");
            scanf_s("%d", &a[i]);
            i++;
        }
    }

    //배열을 몇번째까지 사용했는지 return
    return i; 
}

int printarr(int a[]) {
    for (int i = 0; i < MAX_SIZE; i++) { //bstarr의 유효 숫자가 있는 numofdata 까지 출력.
        printf("%d ", a[i]);
    }

    return 0;
}

int makeBST(int ba[], int bstarr[], int size, int numofdata) {  //이진트리를 만드는 함수
    //int t = -1;         //배열의 몇 번째까지 사용했는지 저장하는 변수
    int index = 0;
    //bst와 그냥 배열 인데스 1번 초기화 //result[0] 아님 주의
    bstarr[1] = ba[0];

    //ba는 인덱스 0값은 넣어줬으니까, 인덱스 1번 부터 / numofdata 번 반복.
    for (int a = 1; a <= numofdata; a++) { //넣어주는 횟수만큼 반복. 

        int i = 1; //이진 탐색 트리 인덱스가 1부터 시작해야 0부터 시작하면 자리값이 계속 0이 나옴.

        while (bstarr[i] != -1) {//-1값이 아니면 다음 자리값 찾기 위해 계속 반복. //배열 안의 값이 -1이라면 while반복문 끝내고 배열 값 저장.

            if (bstarr[i] > ba[a]) {//입력값이 기존 값보다 작다.
                i = 2 * i;
            }
            else if (bstarr[i] < ba[a]) {
                i = 2 * i + 1;
            }
            else break;
        }
        //배열 안의 값이 -1이 아니라면, 현재 i자리 값에 현재 넣어야할 입력배열 값 넣어주기.
        bstarr[i] = ba[a];
        index = i;//index 값은 계속 i값으로 초기화 됨.
    }//여기까지 for 반복문

    return index;//유효숫자 인덱스는 반환이 된 후 numofdata2 에 넣어주기 
}

int delete(int a[], int size) {
    int remnum;      //삭제하고 싶은 수를 입력받는 매개변수
      
    int i = 1;      //k가 배열의 몇번째에 위치했는지 알려주는 매개변수

    //삭제 시키고 싶은 수 입력받기
    printf("\n배열 중 삭제하고 싶은 수를 입력해주세요\n"); 
    scanf_s("%d", &remnum);

    //삭제하고 싶은 수의 위치 찾기
    int remnumi = SerchDeleteDataIndex(a,remnum);
    
     
     //데이터 삭제하기 
    if (a[remnumi * 2 + 1] == -1 && a[2 * remnumi] == -1) {//자식이 없는 경우
        NoChildDelete(a, remnumi);
    }
    else if (a[remnumi * 2 + 1] == -1 || a[2 * remnumi] == -1) {    //자식이 한쪽에만 있는 경우
        OneChildDelete(a, size, remnumi);
    }
    else {  //양쪽에 있는 경우
        
    }
    
    return 0;
}

int SerchDeleteDataIndex(int a[], int remnum) {
    int i=1;
    while (a[i] != remnum) {

        if (a[i] > remnum) {     //왼쪽 자식으로 이동
            i = 2 * i;
        }
        else if (a[i] < remnum) {    //오른쪽 자식으로 이동
            i = 2 * i + 1;
        }
        else if (a[i] == -1) {   //배열에 수가 존재하지 않는 경우
            printf("\n배열 중 입력하신 수가 존재하지 않습니다. 아래배열을 보시고 다시 입력하여주세요.\n");
            printarr(a);
            delete(a, MAX_SIZE);
        }
        else break;     //같은 수를 찾은 경우
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
        a[parent] = a[rchild];     //부모로 자식을 옮겨준다
        a[rchild] = -1;             //옮긴 값을 널값으로바꾼다
        rearrange(a, size, rchild); 
    }
    else {
        a[parent] = a[lchild];     //부모로 자식을 옮겨준다
        a[lchild] = -1;            //옮긴 값을 널값으로바꾼다
        rearrange(a, size, lchild);
        
    }
   
    return 0;
}

int rearrange(int a[], int size, int initial) {
    int leftchild = 2 * initial;        //왼쪽 자식
    int rightchild = 2 * initial + 1;   //오른쪽 자식

    //왼쪽 자식 재배열
    if (leftchild <= size && a[leftchild] != -1) {
        a[initial] = a[leftchild];
        a[leftchild] = -1;
        rearrange(a, size, leftchild);
   }
    //오른쪽 자식 재배열
    if (rightchild <= size && a[rightchild] != -1) {
        a[initial] = a[rightchild];
        a[rightchild] = -1;
        rearrange(a, size, rightchild);
    }
    return 0;

}