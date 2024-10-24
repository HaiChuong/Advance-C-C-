
# JSON

JSON là chuỗi dữ liệu với các phần tử có nhiều kiểu dữ liệu khác nhau. Mỗi phần tử trong JSON là 1 đối tượng và cách nhau 1 dấu phẩy.

Một đối tượng JSON là một tập hợp các cặp key-value, được bao bọc bởi dấu ngoặc nhọn {}. 

Key: Là một chuỗi (string) duy nhất, đóng vai trò là tên của một thuộc tính hoặc một phần tử.

Value: Có thể là một trong các kiểu dữ liệu sau: Số, Chuỗi, Boolean, NULL, Mảng, Đối tượng.

Một mảng JSON là một danh sách các giá trị, được bao bọc bởi dấu ngoặc vuông [] (trong 1 mảng không nhất thiết phải cùng chung kiểu dữ liệu).



Ví dụ:
```
{ 
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "grades": [85, 90, 78]
}
```




## Các định dạng
Khởi tạo dữ liệu cho 1 JSON
```
typedef enum{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue{
    JSONType type;
    union{
        int     boolean; // 0 hoặc 1, 0 = false, 1 = true
        double  number;
        char    *string;
        struct{
            struct JSONValue *values;
            size_t count;
        } array;
        struct{
            char **keys; // ["key1", "key2", "key3"]
            struct JSONValue *values;
            size_t count;
        } object;
    } value;
} JSONValue;
```
Giả sử muốn tạo 1 JSON như sau:
```
"
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}
"
```
Ta cấp phát động bộ nhớ cho số đối tượng trong JSON và các đối tượng hoặc mảng trong value của các đối tượng.
```
int main(int argc, char const *argv[])
{
    JSONValue *json_str = (JSONValue*)malloc(sizeof(JSONValue));

    json_str->type = JSON_OBJECT;
    json_str->value.object.count = 5;

    json_str->value.object.keys = (char**)malloc(json_str->value.object.count*sizeof(char*));
    json_str->value.object.values = (JSONValue*)malloc(json_str->value.object.count*sizeof(JSONValue));
    //Cấp phát động bộ nhớ cho JSON json_str và 5 đối tượng của json_str
```
Sau đó tạo dữ liệu cho từng đối tượng của JSON
```
//key 1
    json_str->value.object.keys[0] = "name";
    json_str->value.object.values[0].type = JSON_STRING;
    json_str->value.object.values[0].value.string = "John Doe";

//key 2
    json_str->value.object.keys[1] = "age";
    json_str->value.object.values[1].type = JSON_NUMBER;
    json_str->value.object.values[1].value.number = 30.1234;

//key 3
    json_str->value.object.keys[2] = "city";
    json_str->value.object.values[2].type = JSON_STRING;
    json_str->value.object.values[2].value.string = "New York";

//key 4
    json_str->value.object.keys[3] = "isStudent";
    json_str->value.object.values[3].type = JSON_BOOLEAN;
    json_str->value.object.values[3].value.boolean = 1;

//key 5
    json_str->value.object.keys[4] = "grades";
    json_str->value.object.values[4].type = JSON_ARRAY;
    json_str->value.object.values[4].value.array.count = 3;
    json_str->value.object.values[4].value.array.values = (JSONValue*)malloc(json_str->value.object.values[4].value.array.count*sizeof(JSONValue));

    
    json_str->value.object.values[4].value.array.values[0].type = JSON_NUMBER;
    json_str->value.object.values[4].value.array.values[0].value.number = 85;

    json_str->value.object.values[4].value.array.values[1].type = JSON_NUMBER;
    json_str->value.object.values[4].value.array.values[1].value.number = 90;

    json_str->value.object.values[4].value.array.values[2].type = JSON_NUMBER;
    json_str->value.object.values[4].value.array.values[2].value.number = 78;

    return 0;
}