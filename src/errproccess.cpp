#include <errproccess.h>

void Err::errCheck(bool flag, std::string s){
    if(flag){
        printf("%s\n", s.c_str());
        exit(EXIT_FAILURE);
    }
}