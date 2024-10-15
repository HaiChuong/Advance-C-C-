#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;
typedef enum { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR }ErrorCodes ;
char *error_code = "No error";
#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(cmd) else if (exception == cmd)
#define THROW(cmd,text)     \
        error_code = text;  \
        longjmp(buf,cmd);                                  
        

void readFile(int num){
    if(num != 1){
        printf("Doc file thanh cong\n");
    }else{
        THROW(FILE_ERROR,"Loi doc file! Sua loi readFile");
    }
}

void networkOperation(int net){
    if(net != 1){
        printf("Tao network thanh cong\n");
    }else{
        THROW(NETWORK_ERROR,"Loi network! Sua loi networkOperation");
    }
}

void calculateData(int cal){
    if(cal != 1){
        printf("Tinh toan thanh cong\n");
    }else{
        THROW(CALCULATION_ERROR,"Loi calculation! Sua loi calculateData");
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
        if(net != 1 && num != 1 && cal != 1)  {
            printf("%s\n", error_code);
            printf("Ket thuc chuong trinh");
        }               
             
    }CATCH(NETWORK_ERROR){
        printf("%s\n", error_code);
        goto continue1;
    }CATCH(FILE_ERROR){
        printf("%s\n", error_code);
        goto continue2;
    }CATCH(CALCULATION_ERROR){
        printf("%s\n", error_code);
        return 0;
    }
}