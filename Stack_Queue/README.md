
# Stack - Queue




## Stack
Stack là một cấu trúc dữ liệu tuân theo nguyên tắc LIFO (Last In, First Out). Nghĩa là phần tử cuối cùng được đưa vào sẽ là phần tử đầu tiên được lấy ra.

Các thao tác cơ bản trên Stack:
- Push: Thêm một phần tử vào đỉnh của stack. (push -> top++)
- Pop: Xóa phần tử ở đỉnh của stack và trả về giá trị của nó. (pop -> top--)
- Top: Trả về giá trị của phần tử ở đỉnh của stack mà không xóa nó. (top(max) = size - 1)
- IsEmpty: Kiểm tra xem stack có rỗng hay không.
- IsFull: Kiểm tra xem stack đã đầy chưa.

Hàm khởi tạo thành phần và khởi tạo 1 stack
```
typedef struct Stack {
    int* items;
    int size;
    int top;
} Stack;

void initialize( Stack *stack, int size) {
    stack->items = (int*) malloc(sizeof(int) * size);
    stack->size = size;
    stack->top = -1;
}
```
Mỗi Stack bao gồm 3 thành phần chính items (giá trị của phần tử), size (kích cỡ của stack), top (phần tử nằm trên đỉnh stack hiện tại).

Khởi tạo Stack sẽ tạo 1 vùng nhớ tương ứng với kích cỡ của stack và kiểu dữ liệu. Giá trị top ban đầu và khi stack rỗng được mặc định là -1.

Hàm kiểm tra Stack rỗng hoặc đầy
```
int is_empty( Stack stack) {
    return stack.top == -1;
}

int is_full( Stack stack) {
    return stack.top == stack.size - 1;
}
```
Các hàm tương tác với dữ liệu của Stack

**Push** : Thêm 1 phần tử vào đỉnh Stack (tăng top lên và gán giá trị cần truyền vào top hiện tại nếu stack chưa đầy)
```
void push( Stack *stack, int value) {
    if (!is_full(*stack)) {
        stack->items[++stack->top] = value;
    } else {
        printf("Stack overflow\n");
    }
}
```
**Pop** : Xóa phần tử ở đỉnh của stack và trả về giá trị của nó (trả về giá trị hiện tại của top và giảm top nếu stack không rỗng)
```
int pop( Stack *stack) {
    if (!is_empty(*stack)) {
        return stack->items[stack->top--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}
```
**Top** : Trả về giá trị của phần tử ở đỉnh của stack mà không xóa nó (trả về giá trị hiện tại của top nếu chuỗi không rỗng)
```
int top( Stack stack) {
    if (!is_empty(stack)) {
        return stack.items[stack.top];
    } else {
        printf("Stack is empty\n");
        return -1;
    }
}
```


## Queue
Queue là một cấu trúc dữ liệu tuân theo nguyên tắc FIFO (First In, First Out). Nghĩa là phần tử đầu tiên được đưa vào sẽ là phần tử đầu tiên được lấy ra. Có 2 cách triển khai với Queue: Linear Queue và Circular Queue.

*Linear Queue*: Không thể thêm phần tử mới khi rear đã đạt tới cuối mảng.

*Circular Queue*: Triển khai phức tạp hơn Linear Queue, khi rear đạt đến cuối mảng nó sẽ quay lại đầu mảng.

Các thao tác cơ bản trên Queue:
- Enqueue: Thêm một phần tử vào cuối hàng đợi.
- Dequeue: Xóa phần tử ở đầu hàng đợi và trả về giá trị của nó.
- Front: Để lấy giá trị của phần tử đứng đầu hàng đợi.
- Rear: Để lấy giá trị của phần tử đứng cuối hàng đợi.
- IsEmpty: Kiểm tra xem hàng đợi có rỗng hay không.
- IsFull: Kiểm tra xem hàng đợi đã đầy chưa.

Hàm khởi tạo thành phần và khởi tạo 1 Queue
```
typedef struct{
    int *items;
    int front;
    int rear;
    int size;
} Queue;

Queue *initialize(int size){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
    return queue;
}
```
Mỗi Queue gồm 4 thành phần chính items (giá trị của phần tử), size (kích thước của Queue), rear (phần tử nằm ở cuối hàng đợi), front(phần tử nằm ở đầu hàng đợi).

Khởi tạo Stack sẽ tạo 1 vùng nhớ tương ứng với kích cỡ của Queue và kiểu dữ liệu. Giá trị front-rear ban đầu và khi Queue rỗng được mặc định là -1.


Các hàm tương tác với dữ liệu của **Linear Queue**
Hàm kiểm tra Queue rỗng hoặc đầy
```
int isFull(Queue queue){
    return queue.rear == queue.size - 1;
}

int isEmpty(Queue queue){
    return (queue.front == -1);
}
```

**Front**: Lấy giá trị của phần tử đứng đầu hàng đợi.
```
int front(Queue queue) {
    if (!is_empty(queue)) {
        return queue.items[queue.front];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}
```
**Rear**: Lấy giá trị của phần tử đứng cuối hàng đợi.
```
int rear(Queue queue) {
    if (!isEmpty(queue)) {
        return queue.items[queue.rear];
    } else {
        printf("Queue is empty\n");
        return -1;
    }
}
```
**Enqueue**: Thêm một phần tử vào cuối hàng đợi. (Nếu Queue đang rỗng, front và rear đều tăng lên 0 và gán dữ liệu vào rear. Nếu Queue không rỗng và không đầy, tăng rear và gán dữ liệu vào rear)
```
void enqueue(Queue *queue, int data){
    if (isFull(*queue)){
        printf("Queue is full! Cannot add more elements.\n");
    } 
    else{
        if (isEmpty(*queue)){
            queue->front = queue->rear = 0;
        }
        else{
            queue->rear++;
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}
```
**Dequeue**: Xóa phần tử ở đầu hàng đợi và trả về giá trị của nó. (Nếu Queue không rỗng, trả về giá trị hiện tại của front và tăng front. Nếu front = rear -> Queue chỉ còn 1 phần tử -> set front và rear về -1 và chuỗi rỗng).
```
int dequeue(Queue *queue){
    if (isEmpty(*queue)){
        printf("Queue is empty! Cannot dequeue.\n");
        return -1;
    } 
    else{
        int value = queue->items[queue->front];
        if (queue->front == queue->rear){
            queue->front = queue->rear = -1;
        }
        else{
            queue->front++;
        }
        return value;
    }
}
```
Các hàm tương tác với dữ liệu của **Circular Queue**. Hàm front và rear tương tự Linear Queue.
Hàm kiểm tra Queue rỗng hoặc đầy
```
int is_empty(Queue queue) {
    return queue.front == -1;
}

int is_full(Queue queue) {
    return (queue.rear + 1) % queue.size == queue.front;
}
```

**Enqueue**: Tương tự như Linear Queue nhưng do triển khai theo vòng tròn nên phải chia lấy dư với size của Queue để trả về rear đúng thứ tự và trong giới hạn của size.
```
void enqueue(Queue *queue, int value) {
    if (!is_full(*queue)) {
        if (is_empty(*queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % queue->size;
        }
        queue->items[queue->rear] = value;
    } else {
        printf("Queue overflow\n");
    }
}
```
**Dequeue**: Tương tự như Linear Queue. Tác động đến front nên phải chia lấy dư với size của Queue để trả về front đúng thứ tự và trong giới hạn của size.
```
int dequeue(Queue *queue) {
    if (!is_empty(*queue)) {
        int dequeued_value = queue->items[queue->front];
        if (queue->front == queue->rear) {
            queue->front = queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeued_value;
    } else {
        printf("Queue underflow\n");
        return -1;
    }
}
```

