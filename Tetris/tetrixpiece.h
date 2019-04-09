#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H
/* Inspired by QtCreator, modified by Thomas Mion and Hugo Nicolle */
// Enum type containing all the shapes a piece can have
enum TetrixShape { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };


//Represents a piece
class TetrixPiece
{
public:
    TetrixPiece() { setShape(NoShape); }

    //Set the shape of a piece at random
    void setRandomShape();

    // Set the shape of piece to a defined one
    void setShape(TetrixShape shape);

    // Returns the shape of a piece
    TetrixShape shape() const { return pieceShape; }

    // Returns the x coordinates of the squares
    int x(int index) const { return coords[index][0]; }

    // Returns the y coordinates of the squares
    int y(int index) const { return coords[index][1]; }

    // Returns the min of the x coordinates of the squares
    int minX() const;

    // Returns the max of the x coordinates of the squares
    int maxX() const;

    // Returns the min of the y coordinates of the squares
    int minY() const;

    // Returns the max of the y coordinates of the squares
    int maxY() const;

    // Rotates a piece counter clockwise
    TetrixPiece rotatedLeft() const;

    // Rotates a piece clockwise
    TetrixPiece rotatedRight() const;

private:

    // Set the x coordinates of the squares
    void setX(int index, int x) { coords[index][0] = x; }

    // Set the y coordinates of the squares
    void setY(int index, int y) { coords[index][1] = y; }

    // The shape of the piece
    TetrixShape pieceShape;

    // Coordinates of the squares composing a piece
    int coords[4][2];
};


#endif
