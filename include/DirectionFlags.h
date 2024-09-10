#ifndef DIRECTIONFLAGS_H
#define DIRECTIONFLAGS_H

#include <QFlags>
#include <QObject>

namespace DirectionFlags {
    Q_NAMESPACE

enum Direction {
    LEFT = 0x1,
    RIGHT = 0x2,
    TOP = 0x4,
    BOTTOM = 0x8
};

Q_ENUM_NS(Direction);

Q_DECLARE_FLAGS(Directions, Direction);
Q_DECLARE_OPERATORS_FOR_FLAGS(Directions)
}

#endif // DIRECTIONFLAGS_H
