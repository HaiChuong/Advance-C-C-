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
```
Khi nhập 1 chuỗi dữ liệu vào cần thêm ký hiệu /" để đánh dấu mở đầu và kết thúc chuỗi.
```
 const char* json_str = "{"
                        "\"1001\":{"
                          "\"SoPhong\":3,"
                          "\"NguoiThue\":{"
                            "\"Ten\":\"Nguyen Van A\","
                            "\"CCCD\":\"1920517781\","
                            "\"Tuoi\":26,"
                            "\"ThuongTru\":{"
                              "\"Duong\":\"73 Ba Huyen Thanh Quan\","
                              "\"Phuong_Xa\":\"Phuong 6\","
                              "\"Tinh_TP\":\"Ho Chi Minh\""
                            "}"
                          "},"
                          "\"SoNguoiO\":{"
                            "\"1\":\"Nguyen Van A\","
                            "\"2\":\"Nguyen Van B\","
                            "\"3\":\"Nguyen Van C\""
                          "},"
                          "\"TienDien\": [24, 56, 98],"
                          "\"TienNuoc\":30.000"
                        "}"
```

## Parse JSON
Sau khi có chuỗi được nhập vào ta bắt đầu phân tích dữ liệu từ chuỗi thành các phần tử với các kiểu dữ liệu và giá trị phù hợp.

Tạo hàm phân tích toàn bộ chuỗi chính thành các phần tử thích hợp.

*Toàn bộ hàm parse_ đều sử dụng tham số truyền vào là con trỏ cấp 2 để có thể thay đổi được vùng nhớ của chuỗi dữ liệu là kiểu char** *, tránh bị stack thu hồi lại vùng nhớ khi kết thúc hàm.*
```
JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++;
    }



    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:
            if (isdigit(**json) || **json == '-') {
                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}
```
Phân tích các phần tử kiểu object
```
JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;



        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_string(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}
```
Phân tích phần tử kiểu array
```
JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json); 
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}
```
Phân tích phần tử kiểu string
```
JsonValue *parse_string(const char **json) {
    skip_whitespace(json);


    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start; // 3
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';


            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}
```
Phân tích phần tử kiểu number
```
JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;


    double num = strtod(*json, &end);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}
```
Phân tích phần tử kiểu boolean
```
JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}
```
Phân tích phần tử kiểu NULL
```
JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}
```
Các hàm phụ trợ đọc chuỗi
```
// hàm skip_whitespace bỏ qua các khoảng trắng trước dữ liệu
static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}

// hàm free_json_value giải phóng vùng nhớ động được cấp bởi heap để phân tích chuỗi , do array và object có nhiều phần tử bên trong 
nên để giải phóng từng lệnh sẽ mất thời gian nên tạo 1 hàm free để giải phóng bộ nhớ dùng chung cho kiểu dữ liệu này.
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}

// hàm test để đọc chuỗi được chọn thành các phần tử 
void test(JsonValue* json_value){
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        //size_t num_fields2 = json_value->value.object.values->value.object.count;
        for (size_t i = 0; i < num_fields; ++i) {

            char* key = json_value->value.object.keys[i];
            JsonValue* value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);


            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }

            if(type == JSON_NUMBER){
                printf("%s: %f\n", key, value->value.number);
            }

            if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }

            if(type == JSON_OBJECT){
                printf("%s: \n", key);
                test(value);
            }

            if(type == JSON_ARRAY){
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++)
                {
                   test(value->value.array.values + i);
                } 
                printf("\n");
            }

  
        }

     
    }
    else 
    {
            if(json_value->type == JSON_STRING){
                printf("%s ", json_value->value.string);
            }

            if(json_value->type == JSON_NUMBER){
                printf("%f ", json_value->value.number);
            }

            if(json_value->type == JSON_BOOLEAN){
                printf("%s ", json_value->value.boolean ? "True":"False");
            }

            if(json_value->type == JSON_OBJECT){
                printf("%s: \n", json_value->value.object.keys);
                test(json_value->value.object.values);
                           
            }
    }

}
```
Thực hiện đọc chuỗi
```
int main(){
  const char* json_str = "...."                   // nhập chuỗi cần đọc
  JsonValue* json_value = parse_json(&json_str);  // Phân tích chuỗi thành chuỗi JSON
  test(json_value);                               // Đọc chuỗi JSON 
  free_json_value(json_value);                    // Giải phóng bộ nhớ được cấp
  return 0;
}

