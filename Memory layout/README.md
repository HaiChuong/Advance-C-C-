
# Memory layout

A brief description of what this project does and who it's for


## Khái niệm
Khi chạy các file main.exe và main.hex (lưu ở bộ nhớ SSD hoặc FLASH) thì các chương trình này sẽ được copy vào bộ nhớ RAM để thực thi. Memory layout mô tả cách hệ điều hành phân bổ không gian bộ nhớ cho các thành phần.

Memory layout gồm 5 phần chính: Text segment, Data segment, Bss segment, Heap, Stack.

## Text segment
Chứa mã máy của chương trình.

Thường chỉ có quyền đọc và thực thi, không có quyền ghi để bảo vệ mã không bị ghi đè.

Các biến hằng số toàn cục và các chuỗi hằng được lưu ở Text segment nếu hệ điều hành là MacOS.
## Data segment
*Initialized Data Segment (Dữ liệu Đã Khởi Tạo)*

Các biến hằng số toàn cục và các chuỗi hằng được lưu ở rdata trong data segment. (hệ điều hành window)

Chứa các biến toàn cục, biến static (global + local) được khởi tạo với giá trị khác 0.

Có thể đọc và thay đổi giá trị của các biến.

Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.

Có thể mở file.s để kiểm tra vùng nhớ của biến (gcc -S -o main.s main.c)
```
int a = 5;
const int b = 10;
void *ptr = &a;
```
![m1](https://github.com/user-attachments/assets/689448e3-c65f-43ec-acb1-d53bf2229fe3)

## Bss segment
*Uninitialized Data Segment (Dữ liệu Chưa Khởi Tạo)*

Các biến hằng số toàn cục bằng 0 hoặc chưa khởi tạo giá trị được lưu ở rdata trong data segment. (hệ điều hành window)

Chứa các biến toàn cục, biến static (global + local) bằng 0 hoặc chưa khởi tạo giá trị.

Có thể đọc và thay đổi giá trị của các biến.

Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.

Có thể mở file.s để kiểm tra vùng nhớ của biến (gcc -S -o main.s main.c)
## Stack
Dùng để lưu trữ thông tin về các hàm đang được gọi.

Chứa các biến cục bộ, tham số truyền vào.

Có thể đọc và thay đổi giá trị.

Sau khi ra khỏi hàm, sẽ thu hồi vùng nhớ.

Các biến hằng số cục bộ sẽ được lưu ở Stack và có thể thay đổi giá trị của biến thông qua con trỏ.

Bộ nhớ Stack là **cố định** nên nếu ta sử dụng quá nhiều bộ nhớ vượt quá khả năng lưu trữ của Stack sẽ gây tràn bộ nhớ (quá nhiều biến cục bộ, hàm đệ quy vô hạn)
```
void *ptr = NULL;
void test(){
    const int c = 5;    //lưu ở stack
    ptr = &c;
    *ptr = 10;
    printf("c = %d", c);
}
```


## Heap
Heap được sử dụng để cấp phát bộ nhớ động trong quá trình thực thi của chương trình. Cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu của dữ liệu.

Các hàm như malloc(), calloc(), realloc(), và free() được sử dụng để cấp phát và giải phóng bộ nhớ trên heap.

**malloc(size)**: Trả về con trỏ void và cấp phát cho biến size byte vùng nhớ heap.
```
int *ptr = NULL;
int size = 10;
ptr = (int*)malloc(size*sizeof(int)); 
//cấp phát 40 ô địa chỉ heap cho con trỏ ptr
```
**calloc(num,size)**: Trả về con trỏ void và cấp phát num*size byte vùng nhớ heap. Tất cả các phần tử được khởi tạo đều có giá trị bằng 0. Dùng để tạo 1 mảng các phần tử được khởi tại giá trị 0.
```
int *ptr = NULL;
int num = 10;
ptr = (int*)calloc(num, sizeof(int));
```
**realloc(ptr,newSize)**: Trả về con trỏ void và sử dụng để thay đổi kích thước của 1 khối bộ nhớ đã được cấp phát trước đó bằng hàm malloc() hoặc calloc(). Cho phép ta tăng hoặc giảm kích thước bộ nhớ mà không phần cấp phát 1 bộ nhớ và sao chép dữ liệu.
```
ptr = (int*)realloc(ptr, size);
```
**free(ptr)**: Dùng để giải phóng bộ nhớ đã được cấp phát trước đó bằng hàm malloc(), calloc(), realloc(). Trả lại bộ nhớ cho hệ điều hành, giúp sử dụng bộ nhớ hiệu quả hơn.
```
free(ptr);
```
Nếu ta liên tục cấp phát vùng nhớ mà không giải phóng sẽ gây lỗi tràn vùng nhớ Heap. Nếu khởi tạo 1 vùng nhớ quá lớn mà Heap ko thể lưu trữ được sẽ bị lỗi khởi tạo vùng nhớ thất bại. Giá trị lớn nhất Heap có thể chứa là 2^63-1.
```
int *A = (int *)malloc(18446744073709551615);
---------------------------------------------
warning: argument 1 value '18446744073709551615' exceeds maximum object size 9223372036854775807 [-Walloc-size-larger-than=]
```


## Khái niệm
Khi chạy các file main.exe và main.hex (lưu ở bộ nhớ SSD hoặc FLASH) thì các chương trình này sẽ được copy vào bộ nhớ RAM để thực thi. Memory layout mô tả cách hệ điều hành phân bổ không gian bộ nhớ cho các thành phần.

Memory layout gồm 5 phần chính: Text segment, Data segment, Bss segment, Heap, Stack.

## Bảng so sánh malloc, calloc, realloc
|  | malloc | calloc| realloc |
|:--------------:|:-------:|:------:|:-------:|
| Chức năng | Cấp phát vùng nhớ có kích thước cụ thể | Cấp phát vùng nhớ, khởi tạo tất cả các giá trị bằng 0 | Thay đổi kích thước của vùng nhớ đã được cấp phát trước đó |
| Giá trị khởi tạo | Không khởi tạo | Khởi tạo tất cả các giá trị bằng 0 | Không thay đổi giá trị các phần tử sẵn có |
| Kích thước | Chỉ định tổng kích thước | Chỉ định số lượng phần tử và kích thước mỗi phần tử | Chỉ định kích thước mới mong muốn |
|Công dụng|Sử dụng khi cần 1 vùng nhớ linh hoạt|Sử dụng khi cần 1 mảng các phần tử được khởi tạo bằng 0|Sử dụng khi cần thay đổi kích thước bộ nhớ đã tồn tại|

## So sánh Stack và Heap
**Stack** được sử dụng để lưu trữ các biến cục bộ, tham số hàm và các thông tin cần thiết cho việc gọi hàm.

Kích thước cố định và thường nhỏ hơn Heap. Tốc độ truy cập nhanh hơn Heap.

Do hệ thống quản lý và tự động giải phóng bộ nhớ sau khi thực thi xong hàm nên ít xảy ra rò rỉ bộ nhớ hơn.

**Heap** được sử dụng để lưu trữ các đối tượng, mảng lớn và các dữ liệu có kích thước không xác định trước. 

Kích thước lớn hơn Stack, linh hoạt hơn nhưng tốc độ truy cập chậm hơn.

Do lập trình viên tự quản lý bộ nhớ nên dữ liệu sẽ không bị huỷ khi hàm thực thi xong. Phải lưu ý giải phóng bộ nhớ để tránh tràn và rò rỉ bộ nhớ. 

