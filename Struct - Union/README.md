
# Struct - Union




## Struct
Struct là 1 cấu trúc dữ liệu cho phép ta tự định nghĩa 1 kiểu dữ liệu mới gồm nhiều kiểu dữ liệu khác nhau. Cho phép ta tạo kiểu dữ liệu phức tạp hơn để mô tả được chính xác đối tượng cần khởi tạo.

Khai báo: 
```
struct ten_struct {
    kieu_du_lieu ten_bien1;
    kieu_du_lieu ten_bien2;
    // ...
};
```
Khai báo biến:
```
struct ten_struct name1;
struct ten_struct *name2;
```
Truy cập thành phần của Struct:
```
name1.ten_bien1 = 1;
name2->tenbien1 = 1;
```
Hoặc khai báo bằng typedef:
```
typedef struct {
    kieu_du_lieu ten_bien1;
    kieu_du_lieu ten_bien2;
    // ...
}ten_struct;

ten_struct name1;
```
Kích thước của struct:
```
struct Example {
    uint8_t a;  // 1 byte  
    uint16_t b; // 2 byte
    uint32_t c; // 4 byte
}; // Kích thước: 12
```
Mỗi biến có kích thước tính theo biến có kích thước to nhất
![struct](https://github.com/user-attachments/assets/142d9414-a59b-41a5-9480-3c2f3ff703b9)

Các biến có kích thước nhỏ hơn sẽ được bù vào bằng các byte trống (padding) cho phù hợp với yêu cầu căn chỉnh của cpu.
```
struct Example {
    uint8_t var1[9];  // 1 byte   = 4 + 4 + 1 + 3(padding)
    uint32_t var2[2]; // 4 byte   = 4 + 4 
    uint16_t var3[10]; // 2 byte  = 4 + 4 + 4 + 4 + 4
}; // Kích thước: 40
```
Ví dụ vùng nhớ của var1[9] (1 byte):
![struct1](https://github.com/user-attachments/assets/29d6dbaf-571e-42da-8906-2dd49696a92e)


## Union
Union là kiểu dữ liệu tương tự struct cho phép ta tạo 1 kiểu dữ liệu mới gồm nhiều kiểu dữ liệu khác nhau. Nhưng sử dụng chung 1 địa chỉ trong bộ nhớ, ta chỉ có thể tương tác với 1 thành phần trong cùng 1 thời điểm (Tiết kiệm bộ nhớ hơn struct nhưng vẫn có thể sử dụng nhiều kiểu thành phần).

Khai báo và sử dụng tương tự struct.
```
union ten_union {
    kieu_du_lieu ten_thanh_phan1;
    kieu_du_lieu ten_thanh_phan2;
    // ...
};
```
Kích thước của union:
```
union Data {
    uint8_t a;  // 1 byte
    uint16_t b; // 2 byte
    uint32_t c; // 4 byte
};// Kích thước : 4 byte
```
Kích thước của union phụ thuộc vào thành phần có kích thước lớn nhất.
```
union Data {
    uint8_t var1[3];  // 1 byte     3 byte + 1 (padding)
    uint16_t var2[10]; // 2 byte    4 + 4 + 4 + 4 + 4
    uint32_t var3[4]; // 4 byte     4 + 4 + 4 + 4
};// Kích thước : 20 byte
```
Nếu ta gán giá trị quá lớn so với kiểu dữ liệu biến sẽ đọc dữ liệu của byte đầu tiên trong địa chỉ để ghi vào
```
union Data {
    uint8_t var1;  // 1 byte     
    uint32_t var2; // 4 byte
    uint16_t var3; 
};
```
![union](https://github.com/user-attachments/assets/460de316-5177-49fb-9706-843b28d731dd)
![union1](https://github.com/user-attachments/assets/090d08b5-f80c-487f-bf90-ce05380a9150)
Hệ thống sẽ gán giá trị byte đầu tiên giá trị 11111010 vào var1 kiểu uint8_t.