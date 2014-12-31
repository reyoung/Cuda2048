#include "SimpleGameBoard.h"
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <boost/random.hpp>

using namespace std;
struct SimpleGameBoardPrivate {
    SimpleGameBoardPrivate(int N):n(N), rng(time(0)), dist(0, N*N-1){
        map = new int[n*n];
        memset(map, 0, sizeof(int)*n*n);
    }

    ~SimpleGameBoardPrivate(){
        delete [] map;
    }

    void init(){
        // Set Map to 0
        memset(map, 0, sizeof(int)*n*n);
        // Random 2 position set to 1;
        int x = dist.operator()(rng);
        int y = 0;
        do{
            y = dist.operator()(rng);
        }while(x==y);
        ++map[x];
        ++map[y];
    }

    int n;

    int * map;

    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> dist;
};

SimpleGameBoard::SimpleGameBoard(int N)
    :m(new SimpleGameBoardPrivate(N))
{
}


SimpleGameBoard::~SimpleGameBoard() {
    if(m){
        delete m;
    }
}

int SimpleGameBoard::getSize() const {
    return m->n;
}

const int * SimpleGameBoard::getMap() const {
    return m->map;
}


void SimpleGameBoard::initGame() {
    m->init();
}

SimpleGameBoard::MoveResult SimpleGameBoard::move(SimpleGameBoard::MoveDirection direction) {

}

int SimpleGameBoard::score(boost::function<int(int)> score_map)const {
    int score = 0;
    for(int i=0;i<m->n*m->n; ++i){
//        cout<<m->map[i]<<endl;
        score += score_map(m->map[i]);
    }
    return score;
}

int SimpleGameBoard::defaultScoreEvaluator(int m) {
    if(m==0){
        return 0;
    } else {
        return 1<<m;
    }
}