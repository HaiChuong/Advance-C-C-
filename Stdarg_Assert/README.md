
# Stdarg - Assert




## Stdarg
Là thư viện cung cấp phương thức làm việc với hàm có lượng tham số input không cố định

va_list: Sử dụng để làm việc với số lượng đối số hàm thay đổi. Cho phép tạo các hàm có số lượng đối số không xác định. Bằng với kiểu dữ liệu "char *variable".

va_start: Khởi tạo biến và đối số cuối cùng KHÔNG phải đối số của hàm.

va_arg: Truy cập giá trị đối số tiếp theo trong danh sách và trả về kiểu dữ liệu mong muốn.

va_end: Giải phóng bộ nhớ va_list khởi tạo.

Ví dụ: 
```
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
typedef struct 
{
    int x;
    int y;
}moi;

int tong(int fi,...){
    va_list chuoi; //char *chuoi;
    va_start(chuoi, fi);
    int tong = 0;
    for (size_t i = 0; i < fi; i++)
    {
        moi tmp = va_arg(chuoi, moi);
        tong = tong + tmp.x + tmp.y;
    }
    va_end(chuoi);
    return tong;
} 
int main(){
    printf("tong: %d", tong(3, (moi){3,4}, (moi){6,7}, (moi){11,1}));

}
```
## Thư viện Assert
Là thư viện cung cấp macro Assert để kiểm tra điều kiện, sử dụng tương tự if. Nếu thoả điều kiện hàm sẽ chạy bình thường, không thoả hàm sẽ dừng chương trình ko tiếp tục thực hiện các lệnh bên dưới.

Ví dụ:
```
#include<stdio.h>
#include<assert.h>

int main(){
    int i = 3;
    assert( i == 5 );
    printf("hello");
}
```
Hàm sẽ báo lỗi không cho chương trình chạy cho đến khi thoả điều kiện.

Có thể kết hợp với macro để thực hiện
```
#include<stdio.h>
#include<assert.h>

int i = 3;
#define must assert(i == 5)

int main(){
    must;
    printf("hello");
}
```
## Macro
Macro là 1 đoạn mã được đặt tên, để thay thế cho 1 tác vụ ta sử dụng nhiều lần. Macro được thực hiện trong giai đoạn Preprocessor.

Khai báo:
```
#define name name_is_replaced
```
Có thể sử dụng macro cho nhiều dòng bằng ký tự "\\".
```
#define d(a,b) printf("tich = %d\n", a*b );\
        printf("thuong = %d", a/b);
```