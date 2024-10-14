
# Pointer

Ôn tập Pointer



## Khái niệm

Pointer là 1 biến chứa địa chỉ bộ nhớ của 1 biến khác, giúp ta thao tác trên bộ nhớ linh hoạt hơn.

Khai báo:

    int a = 7;
    int *ptr = &a;

Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch (64bit là 8byte, 32bit là 4byte)
## Void Pointer

Kiểu con trỏ sử dụng để trỏ đến ô nhớ của các biến có nhiều kiểu dữ liệu

Ví dụ:
```
#include <stdio.h>
int main(){
    int a = 5;
    double b = 7;
    char c = 'C';
    char arr[]="ABabAb";
    void *ptr = NULL;
    ptr = &a;
    printf("dia chi ptr: %p, gia tri a = %d\n", ptr, *(int*)ptr);

    ptr = &b;
    printf("dia chi ptr: %p, gia tri b = %f\n", ptr, *(double*)ptr);

    ptr = &c;
    printf("dia chi ptr: %p, gia tri c = %c\n", ptr, *(char*)ptr);   
}
```


## Function Pointer
Kiểu con trỏ sử dụng để trỏ đến ô nhớ của 1 hàm. 

Các đối số phải cùng kiểu dữ liệu và cùng kiểu dữ liệu trả về để gọi được hàm. Từ đó 1 con trỏ hàm có thể gọi được nhiều hàm có cùng đối số và kiểu trả về.

Ví dụ:
```
#include <stdio.h>

void tong(int a, int b){
    printf("tong = %d\n", a+b);
}

void hieu(int a, int b){ 
    printf("hieu = %d\n", a-b);
}

void tich(int a, int b){
    printf("tich = %d\n", a*b);
}

void tinhToan(void (*ptr)(int,int),int a,int b){
    ptr(a,b);
}

int main(){
    int a =10;
    int b = 5;
    tich(a,b);
    tinhToan(hieu,a,b);
    tinhToan(tich,a,b);
    tinhToan(tong,a,b);
}
```

## Pointer to Constant , Constant to Pointer
Con trỏ hằng là con trỏ không thể thay đổi giá trị trong ô nhớ mà nó trỏ tới bằng con trỏ. Có thể thay đổi giá trị thông qua biến.
```
#include <stdio.h>

int main(){
    int a = 10;
    const int *ptr = &a;
    a = 15;
    printf("a = %d", *ptr);
}
```
Hằng con trỏ là con trỏ không thể thay đổi địa chỉ khi được khởi tạo (Phải đặt kiểu dữ liệu trước *const).

```
#include <stdio.h>

int main(){
    int a = 10;
    int *const ptr = &a;
    printf("a = %d", *ptr);
}
```
## Pointer to Pointer
Là con trỏ cấp 2 sử dụng để trỏ tới địa chỉ của 1 con trỏ khác, có thể xuất giá trị của con trỏ cấp 1 đang trỏ tới.
```
#include<stdio.h>

int main(){
    int a = 7;
    int *ptr = &a;
    int **ptr2 = &ptr;
    printf("a = %d\n", *ptr);
    printf("dia chi cua a: %p\n", ptr);
    printf("gia tri cua ptr: %p\n", *ptr2);
    printf("check a = %d\n", **ptr2);
}
```

## NULL Pointer
Con trỏ null là con trỏ không trỏ đến đối tượng hay vùng nhớ nào, được sử dụng cho các con trỏ được khai báo nhưng chưa sử dụng, gán giá trị.
```
int *ptr = NULL;
```