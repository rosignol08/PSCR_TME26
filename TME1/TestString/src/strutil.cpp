// strutil.cpp
#include "strutil.h"
#include <iostream>

namespace pr {

size_t length(const char* s) {
    if(!s){
        return 0;
    }
    size_t len = 0;
    while(s[len] != '\0'){
        len++;
    }
    return len;
}

char* newcopy(const char* s) {
    char * copie = new char [length(s)];
    for(u_int i = 0; i<=length(s); ++i){
        copie[i] = s[i];
    }
    return copie;
}

//1 si a > b ou -1 sinon 0
int compare(const char* a, const char* b) {
    int result = 0;
    if(length(a) != length(b)){
        //std::cout << length(a) << " " << length(b) << std::endl;
        if(length(a) > length(b)){
            result = 1;
        }else{
            result = -1;
        }
        //result = (length(a) < length(b)) ? 1 : -1;
    }else{
        int score_a = 0;
        int score_b = 0;
        for(int i = 0; i < length(a) ; ++i){
            score_a += a[i] -'0';
            score_b += b[i] -'0';
            
        }
        //std::cout << "score A : " << score_a << std::endl;
        //std::cout << "score B : " << score_b << std::endl;
        if(score_a < score_b){
            result = -1;
        }else if(score_a == score_b){
            result = 0;
        }else{
            result = 1;
        }
    }
    //std::cout << " resultat : " << result << std::endl;
    return result;
}

}
