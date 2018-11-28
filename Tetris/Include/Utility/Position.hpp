#ifndef Position_hpp
#define Position_hpp

struct Position {
public:
    Position();
    Position(int row, int column);
    ~Position();
    bool operator ==(const Position& other) const;
    bool operator !=(const Position& other) const;
    
public:
    int row;
    int column;
};

#endif
