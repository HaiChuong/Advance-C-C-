
# Bitmask

A brief description of what this project does and who it's for


## Khái niệm
Bitmask cho phép chúng ta thao tác với các bit riêng lẻ hoặc các nhóm bit trong một biến. Có thể sử dụng bitmask để đặt, xoá , kiểm tra trạng thái các bit cụ thể 
Các phép toán logic thường dùng:
```
// AND (&)
int result = num1 & num2;
// OR (|)
int result = num1 | num2;
// XOR (^)
int result = num1 ^ num2;
// NOT (~)
int result = ~num ;
// Dịch bit (<<)(>>)
int resultLeftShift = num << shiftAmount;
int resultRightShift = num >> shiftAmount;
```


## Các ứng dụng thường được sử dụng
```
// Giả sử ta có các tính năng
#define GENDER        1 << 0  // Bit 0: Giới tính (0 = Nữ, 1 = Nam)
#define TSHIRT        1 << 1  // Bit 1: Áo thun (0 = Không, 1 = Có)
#define HAT           1 << 2  // Bit 2: Nón (0 = Không, 1 = Có)
#define SHOES         1 << 3  // Bit 3: Giày (0 = Không, 1 = Có)
```
### Mở tính năng
Sử dụng phép OR để đặt trạng thái bit lên 1 và không ảnh hưởng đến các tính năng khác
```
void enableFeature(uint8_t *features, uint8_t feature) {
    *features |= feature;
}
```
### Tắt tính năng
Sử dụng kết hợp phép & với ~ feature để chỉ tắt 1 tính năng được chọn không ảnh hưởng các tính năng khác 
```
void disableFeature(uint8_t *features, uint8_t feature) {
    *features &= ~feature;
}
```
### Kiểm tra trạng thái
Sử dụng phép AND để kiểm tra tính năng có đang bật không, nếu có sẽ trả về kết quả 1
```
int isFeatureEnabled(uint8_t features, uint8_t feature) {
    return (features & feature) != 0;
}
```