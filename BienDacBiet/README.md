
# Extern - Static - Volatile - Register


## Extern
Để sử dụng các biến và các hàm đã được khai báo ở các file khác mà không cần phải sử dụng #include (sử dụng #include nhiều sẽ dư thừa dữ liệu, khiến máy đọc các lệnh không cần thiết gây lãng phí).

Để sử dụng các biến và các hàm cần thiết ta chỉ cần liên kết các file và sử dụng Extern để tránh gây dư thừa dữ liệu.

Câu lệnh liên kết các file và chạy file:
```
gcc file1.c file2.c file3.c -o main
./main
```
Khai báo Extern:
```
Extern int a;
Extern void display(); // void display();
```

## Static local variables
Khi sử dụng Static local máy tính sẽ không thu hồi địa chỉ đã cấp khi gọi hàm và giữ phạm vi của biến đó trong phạm vi hàm đó.

Ví dụ:
```
#include <stdio.h>

void cong(){
    static int a = 3;
    printf("a = %d\n", ++a);
}
int main(){
    cong();
    cong();
    cong();
}
```
## Static global variables
Khi sử dụng Static global nó sẽ giới hạn phạm vi của biến trong file hiện tại.
```
#include <stdio.h>
Static int a;
int main()
```
## Volatile
Sử dụng nhiều trong vi điều khiển, dùng để báo hiệu một biến có thể thay đổi ngẫu nhiên, ngoài kiểm soát của chương trình. Tránh để máy tối ưu hoá biến khi giá trị của biến không đổi qua nhiều lần chạy.
```
Volatile int a = 0;
```
## Register
Khi khai báo 1 biến và 1 phép toán, các đối tượng sẽ được lưu trên RAM(int a = 5;++a) sau đó chuyển sang Register (R1 = 5,  ADD R1,1)
và chuyển đến ALU để tính toán và trả giá trị về Register sau đó là RAM và ta nhận kết quả.

Sử dụng Register để ghi thẳng giá trị vào thanh ghi giảm bớt các bước tương tác với RAM để tăng tốc độ xử lý (lưu ý dung lượng thanh ghi có hạn không lạm dụng).

Code chạy trên vi điều khiển:
```
#include <stdio.h>
#include <time.h>

int main() {
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    int i;
    (// so sánh với Register int i;)

    // Đoạn mã của chương trình
    for (i = 0; i < 2000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);

    return 0;
}
```