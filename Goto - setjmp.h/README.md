
# Goto - setjmp.h




## Goto
Goto là 1 lệnh cho phép ta nhảy đến 1 label đã được đặt trước trong phạm vi hàm (có thể sử dụng thoát khỏi các vòng lặp...).

Khai báo:
```
Goto label;

label:
```


## Setjmp.h
Setjmp.h là thư viện cung cấp cho ta 2 hàm chính setjmp và longjmp.
Có tác dụng nhảy lệnh theo vị trí đặt trước như goto nhưng có thể sử dụng ở ngoài hàm và set giá trị cho biến jmp_buf.

Thường được sử dụng để quản lý ngoại lệ.
```
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
#define TRY if ((exception_code = setjmp(buf)) == 0) 
#define CATCH(x) else if (exception_code == (x)) 
#define THROW(x) longjmp(buf, (x))
```
Giá trị mặc định khởi tạo cho exception_code là 0, longjmp sẽ nhảy về dòng lệnh setjmp và set giá trị exception_code thành x
