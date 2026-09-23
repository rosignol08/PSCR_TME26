// strutil.cpp
#include "strutil.h"

namespace pr {

size_t length(const char* s) {
    if(!s){
        return 0;
    }
    size_t len = 0;
    while(s[len] != '\t',nullptr){
        len++;
    }
    return len;
}

char* newcopy(const char* s) {
    char * copie = new char [length(s)+1];
    for(int i = length(s)+1;i > 0; ++i){
        copie[i] = s[i];
    }
    return copie;
}

//1 si a < b ou -1 sinon 0
int compare(const char* a, const char* b) {
    int result = 0;
    if(length(a) != length(b)){
        result = (length(a) < length(b)) ? 1 : -1;
    }else{
        int score_a = 0;
        int score_b = 0;
        for(int i = 0; i < length(a) ; ++i){
            score_a += atoi(&a[i]);
            score_b += atoi(&b[i]);
            
        }
        if(score_a < score_b){
            result = 1;
        }else{
            result = -1;
        }
    }
    return result;
}

}
