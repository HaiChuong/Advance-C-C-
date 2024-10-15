#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;
typedef enum { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR }ErrorCodes ;

#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(cmd) else if (exception == cmd)
#define THROW(cmd) for (ErrorCodes error = FILE_ERROR; error <= CALCULATION_ERROR; ++error) \
{                                                                                           \
    if(error == cmd)                                                                  \
    {longjmp(buf,cmd);}                                                              \
}

void readFile(int num){
    if(num != 1){
        printf("Doc file thanh cong\n");
    }else{
        THROW(FILE_ERROR);
    }
}

void networkOperation(int net){
    if(net != 10){
        printf("Tao network thanh cong\n");
    }else{
        THROW(NETWORK_ERROR);
    }
}

void calculateData(int cal){
    if(cal != 100){
        printf("tinh toan thanh cong\n");
    }else{
        THROW(CALCULATION_ERROR);
    }
}

int main(){
    int net = 0;
    int num = 0;
    int cal = 0;
    TRY{
        networkOperation(net);
        continue1: readFile(num);
        continue2:  calculateData(cal);
        if(net != 10 && num != 1 && cal != 100)  {
            printf("NO_ERROR\n");
            printf("Ket thuc chuong trinh");
        }               
             
    }CATCH(NETWORK_ERROR){
        printf("Loi network, sua loi network!\n");
        goto continue1;
    }CATCH(FILE_ERROR){
        printf("Loi doc file, sua loi file!\n");
        goto continue2;
    }CATCH(CALCULATION_ERROR){
        printf("Loi tinh toan, sua loi calculation!");
        return 0;
    }
}