#ifndef Position_hpp
#define Position_hpp

struct Position {
public:
    Position();
    Position(int row, int column);
    ~Position();
    
public:
    int row;
    int column;
};

#endif
