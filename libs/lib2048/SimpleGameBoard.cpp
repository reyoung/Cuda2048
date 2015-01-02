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


//    SimpleGameBoardRow getRow(int idx, SimpleGameBoard::MoveDirection direction) {
//        return SimpleGameBoardRow(*this, direction, idx);
//    }

    int n;

    int * map;

    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> dist;
};


class SimpleGameBoardRow{
public:
    SimpleGameBoardRow(SimpleGameBoardPrivate& m, SimpleGameBoard::MoveDirection d, int n)
            :m(m), n(n), d(d)
    {

    }

    int size()const {
        return m.n;
    }

    int & operator[] (int idx) {
        int * begin;
        switch (d){
            case SimpleGameBoard::MD_LEFT:
                begin = n*m.n + m.map;
                return begin[idx];
            case SimpleGameBoard::MD_RIGHT:
                begin = n*m.n + m.n -1 + m.map;
                return *(begin - 1);
            case SimpleGameBoard::MD_UP:
                begin = m.map + m.n;
                return *(begin + m.n*idx);
            case SimpleGameBoard::MD_DOWN:
                begin = m.map + m.n*(m.n-1)+n;
                return *(begin - m.n*idx);
        }
    }

    bool canMove(){
        SimpleGameBoardRow& r = *this;
        bool z_not_zero = r[0];
        for(int i=1;i<r.size();++i){
            if(r[i]==0 && z_not_zero){
                z_not_zero = false;
            } else if(!z_not_zero && r[i]){
                return true;
            }
        }

        for(int i=0;i<r.size()-1;++i){
            if(r[i]==r[i+1] && r[i]){
                return true;
            }
        }
        return false;
    }

    SimpleGameBoard::MoveDirection  d;
    int n;
    SimpleGameBoardPrivate& m;
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

bool SimpleGameBoard::canMove(SimpleGameBoard::MoveDirection direction) const {
    SimpleGameBoard* self = const_cast<SimpleGameBoard*>(this);
    int len = self->m->n;
    bool canMove = false;
    for(int i=0;i<len;++i){
        SimpleGameBoardRow row(*self->m, direction, i);
        canMove =canMove || row.canMove();
    }
    return canMove;
}

bool SimpleGameBoard::canMove() const {
    bool canMove = false;
    for(int i=0;i<4;++i){
        canMove = canMove || this->canMove((SimpleGameBoard::MoveDirection)i);
    }
    return canMove;
}