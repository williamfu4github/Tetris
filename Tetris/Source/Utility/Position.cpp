#include "Utility/Position.hpp"

Position::Position() {
}

Position::Position(int row, int column):
    row(row),
    column(column) {
}

Position::~Position() {
}

bool Position::operator ==(const Position& other) const {
    return ((row == other.row) && (column == other.column));
}

bool Position::operator !=(const Position& other) const {
    return !(*this == other);
}
