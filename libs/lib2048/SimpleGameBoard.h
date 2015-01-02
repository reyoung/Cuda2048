#pragma  once
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>


class SimpleGameBoardPrivate;

class SimpleGameBoard : public boost::noncopyable {
public:
    enum MoveDirection {
        MD_LEFT = 0,
        MD_RIGHT,
        MD_UP,
        MD_DOWN
    };

    enum MoveResult {
        MR_OK = 0,
        MR_DIE,
        MR_BADACTION
    };

    SimpleGameBoard(int N);

    virtual ~SimpleGameBoard();

    virtual int getSize()const;

    virtual const int * getMap()const;

    virtual void initGame();

    virtual MoveResult move(MoveDirection direction);

    virtual bool canMove(MoveDirection direction)const;

    virtual bool canMove()const;

    virtual int score(boost::function<int(int)> score_map = defaultScoreEvaluator ) const;
private:
    static int defaultScoreEvaluator(int m);
private:
    SimpleGameBoardPrivate * m;
};