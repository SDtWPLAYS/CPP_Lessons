#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;



int main (){
    for(auto y = 0; y < 256; y++){
        if(y % 64 < 32){
            for(auto x = 0; x < 256; x++){
                if(st::pow(32, 2) < st::pow(x, 2) + st::pow(y, 2) && st::pow(48, 2) > st::pow(x, 2) + st::pow(y, 2)){
                    if(x % 64 < 32){
                        st::cout << 'L';
                    }
                    else{
                        st::cout << 'N';
                    }
                }
                else if(x % 64 < 32){
                    st::cout << ' ';
                }
                else{
                    st::cout << 'L';
                }
            }
        }
        else{
            for(auto x = 0; x < 256; x++){
                if(st::pow(32, 2) < st::pow(x, 2) + st::pow(y, 2) && st::pow(48, 2) > st::pow(x, 2) + st::pow(y, 2)){
                    if(x % 64 < 16){
                        st::cout << 'N';
                    }
                    else{
                        st::cout << 'L';
                    }
                }
                else if(x % 64 < 16){
                    st::cout << 'L';
                }
                else{
                    st::cout << ' ';
                }
            }
        }
        st::cout << '\n';
    }
    return 0;
}