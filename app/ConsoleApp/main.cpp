#include <iostream>
#include <2048.h>



int main(){
    using namespace std;
    SimpleGameBoard board(4);
    board.initGame();
    cout<<board.score();
    return 0;
}