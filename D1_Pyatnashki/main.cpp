//
//пятнашки пункт а
//

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
struct Position{
    Position() = default;
    Position& operator = (const Position& x1);
    Position(const Position& x);
    Position(std::vector<int>Square, int digit): Square(Square), digit(digit){}
    void GetNeighbour(std::vector<Position>&Neighbour, std::vector<std::string>&Side);
    std::vector<int> Square;
    int evrist = 0;
    int evrist_2 = 0;
    void Evrist_();
private:
    int digit = 0;
    std::vector<int> GetL();
    std::vector<int> GetR();
    std::vector<int> GetU();
    std::vector<int> GetD();
    int G();
    int Corner_conflict();
    int Linear_conflict();
    int ManhattanDistance();
    bool operator () (const Position& x, const Position& y) const;
};

Position::Position(const Position& x)
{
    this->Square = x.Square;
    this->digit = x.digit;
    this->evrist = x.evrist;
}

Position& Position::operator = (const Position& x1)
{
    if(&x1 == this)
    {
        return *this;
    }
    this -> Square = x1.Square;
    this -> digit = x1.digit;
    this -> evrist = x1.evrist;
    return *this;
}

const bool operator < (const Position& x, const Position& y)
{
    if(x.evrist < y.evrist)
    {
        return false;
    }
    else if(x.evrist == y.evrist && x.evrist_2 < y.evrist_2)
    {
        return false;
    }
    else if(x.evrist == y.evrist && x.evrist_2 < y.evrist_2 && x.Square < y.Square)
    {
        return false;
    }
    return true;
}

bool Position::operator () (const Position& x, const Position& y) const
{
    return x < y;
}

std::vector<int> Position::GetL()                   //сдвиг влево
{
    std::vector<int>Square_ = Square;
    std::swap(Square_[digit], Square_[digit - 1]);
    return Square_;
}

std::vector<int> Position::GetR()                    //сдвиг вправо
{
    std::vector<int>Square_ = Square;
    std::swap(Square_[digit], Square_[digit + 1]);
    return Square_;
}

std::vector<int> Position::GetU()                   //сдвиг вверх
{
    std::vector<int>Square_ = Square;
    std::swap(Square_[digit], Square_[digit - 4]);
    return Square_;
}

std::vector<int> Position::GetD()                   //сдвиг вниз
{
    std::vector<int>Square_ = Square;
    std::swap(Square_[digit], Square_[digit + 4]);
    return Square_;
}

void Position::GetNeighbour(std::vector<Position>&Neighbour, std::vector<std::string>&Side)
{                                               //находим соседние положения
    if(digit % 4 != 0)
    {
        std::vector<int> LNeighb = GetL();
        Position LN(LNeighb, digit - 1);
        LN.Evrist_();
        Neighbour.push_back(LN);
        Side.push_back("R");
    }
    if(digit % 4 != 3)
    {
        std::vector<int> LNeighb = GetR();
        Position RN(LNeighb, digit + 1);
        RN.Evrist_();
        Neighbour.push_back(RN);
        Side.push_back("L");
    }
    if(digit > 3)
    {
        std::vector<int> UNeighb = GetU();
        Position UN(UNeighb, digit - 4);
        UN.Evrist_();
        Neighbour.push_back(UN);
        Side.push_back("D");
    }
    if(digit < 12)
    {
        std::vector<int> DNeighb = GetD();
        Position DN(DNeighb, digit + 4);
        DN.Evrist_();
        Neighbour.push_back(DN);
        Side.push_back("U");
    }
}

int Position::ManhattanDistance()       //считает манхеттенское расстояние
{
    int evrist = 0;
    for(int i = 0; i < 16; ++i)
    {
        if(Square[i] != 15)
        {
            int real_x = Square[i] / 4;
            int real_y = Square[i] % 4;
            int x = i / 4;
            int y = i % 4;
            evrist += abs(real_x - x) + abs(real_y - y);
        }
    }
    return evrist;
}

int Position::Linear_conflict()         //считает линейный конфликт
{
    int evrist = 0;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = i * 4; j < (i + 1) * 4; ++j)
        {
            if(Square[j] != 15 && Square[j]/4 == j/4)
            {
                for(int p = j % 4 + 1; p < 4; ++p)
                {
                    if(Square[4 * i + p]/4 == j/4 && Square[j] > Square[4 * i + p])
                    {
                        evrist += 2;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 4; ++i)
    {
        for(int j = i; j < 16; j += 4)
        {
            if(Square[j] != 15 && Square[j] % 4 == j % 4)
            {
                for(int p = j + 4; p < 16; p += 4)
                {
                    if(Square[p] % 4 == p % 4 && Square[j] > Square[p ])
                    {
                        evrist += 2;
                    }
                }
            }
        }
    }
    return evrist;
}

int Position::Corner_conflict()                         //считает угловой конфликт
{
    int evrist = 0;
    if(Square[1] == 1 && Square[4] == 4 && Square[0] != 0)
    {
        evrist += 2;
    }
    if(Square[2] == 2 && Square[7] == 7 && Square[3] != 3)
    {
        evrist += 2;
    }
    if(Square[8] == 8 && Square[13] == 13 && Square[12] != 12)
    {
        evrist += 2;
    }
    if(Square[11] == 11 && Square[14] == 14 && Square[15] != 15)
    {
        evrist += 2;
    }
    return evrist;
}

int Position::G()                                       //считает количество фишек не стоящих на месте
{
    int evrist_2 = 0;
    for(int i = 0; i < 16; ++i)
    {
        if(Square[i] != 15 && Square[i] != i)
        {
            ++evrist_2;
        }
    }
    return evrist_2;
}

void Position::Evrist_()                            //подсчёт эвристики
{
    evrist = ManhattanDistance() + Corner_conflict() + Linear_conflict();
    evrist_2 = G();
}

std::stack<std::string> AStar (Position start)        //сам алгоритм
{
    std::stack<std::string>Sequence;                    //тут будет ответ
    std::priority_queue<Position>Queue;                 //очередь для АСтара
    std::set<std::vector<int>>Used;                     //пройденные позиции
    std::map<std::vector<int>, Position>Father;         //сюда запоминаем предка
    std::map<std::vector<int>, std::string>Side;        //сюда запоминаем как мы двигались чтобы прийти в данное положение
    std::vector<int> standard = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Used.insert(start.Square);                          //помечаем начальное положение как пройденное
    Queue.push(start);                                  //добавляем начальное положениее
    Father[start.Square] = start;
    while (!Queue.empty())
    {
        Position regular = Queue.top();                 //берем вершину с самой маленькой эвристикой
        Queue.pop();
        std::vector<Position>Children;
        std::vector<std::string>Side_;
        regular.GetNeighbour(Children, Side_);          //находим соседние положения
        for(int i = 0; i < Children.size(); ++i)        //рассматриваем их
        {
            if(Used.count(Children[i].Square) == 0)     //если ещё не used то кидаем в очередь и т д
            {
                Queue.push(Children[i]);
                Used.insert(Children[i].Square);
                Father[Children[i].Square] = regular;
                Side[Children[i].Square] = Side_[i];
            }
            if(Children[i].Square == standard)          //если это конечное положение востанавливаем путь
            {
                Side[Children[i].Square] = Side_[i];
                Sequence.push(Side[Children[i].Square]);
                //std::cout << Side_[i];
                while (regular.Square != start.Square)
                {
                    //std::cout << Side_[i];
                    //std::cout << Side[regular.Square];
                    Sequence.push(Side[regular.Square]);
                    regular = Father[regular.Square];
                }
                return Sequence;
            }
        }
    }
    return Sequence;
}

int main()
{
    int digit = 0;
    std::vector<int>A_;
    std::vector<int>chenge;
    for(int i = 0; i < 16; ++i)                 //считываем
    {
        int cell = 0;
        std::cin >> cell;
        if(cell == 0)
        {
            digit = i;
        }
        A_.push_back((cell + 15) % 16);         //сразу делаем удобным для обработки
        if(cell != 0)
        {
            chenge.push_back(cell);
        }
    }
    Position A(A_, digit);
    int chen = 0;
    for(int i = 0; i < 15; ++i)                 //считаем перестановки
    {
        for(int j = i + 1; j < 15; ++j)
        {
            if(chenge[i] > chenge[j])
            {
                ++chen;
            }
        }
    }
    if((chen + digit/4 + 1) % 2 == 1)          //смотрим решаемы ли восьминашки
    {
        std::cout << -1;
    }
    else
    {
        A.Evrist_();
        std::stack<std::string> answer = AStar (A);
        std::cout << answer.size()<< std::endl;
        while(!answer.empty())
        {
            std::cout << answer.top();              //формируем и выводим ответ
            answer.pop();
        }
    }
    return 0;
}

