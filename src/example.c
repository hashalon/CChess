#include <stdio.h>
#include <stdlib.h>

struct Board {
    short pieces[32]; // we have a maximum of 32 pieces on the board
    char
        length, // the current number of piece in the board
        turn;   // the team of the current player
} m_board; // we create the main board

struct Moves {
    char
        from,   // position of the piece we want to move
        length; // length of the list
    char to[28]; // list of all the valid destination for said piece
    // 28 is the maximum number of movement possible for the queen
};

struct Turn {
    char length; // length of the list
    struct Moves moves[16]; // list of all the piece that can be moved
    // each player has a maximum of 16 piece that can be moved
};

struct Vector { char x, y; };

// directions used by different pieces
struct Vector D_ortho[4] = { {1,0},  {0,1},  {-1,0}, {0,-1} }; // rook
struct Vector D_diago[4] = { {1,1}, {-1,1}, {-1,-1}, {1,-1} }; // bishop
struct Vector D_octo [8] = { {1,0},  {0,1}, {-1,0},  {0,-1}, {1,1}, {-1,1}, {-1,-1},  {1,-1} }; // queen and king
struct Vector D_jump [8] = { {2,1}, {-2,1}, {2,-1}, {-2,-1}, {1,2}, {-1,2},  {1,-2}, {-1,-2} }; // knight

/* bits definition per piece:
       0-2 : x-axis
       3-5 : y-axis
         6 : team
       7-9 : piece type
        10 : has moved
        -- if potential is necessary, that require changing shorts into ints
        11 : potentialy destroyed
        12 : potentialy moved
     13-15 : x-axis potentialy moved
     16-18 : y-axis potentialy moved
*/

// team
const char
    F_white  = 0 << 6,
    F_black  = 1 << 6,
    M_pos    =     63, //   111 111 : mask to get the position of a piece
    M_team   = 1 << 6; // 1 000 000 : mask to get the team of a piece
// piece type
const short
    M_type   = 7 << 7, //   111 0 000 000 : mask to get the type of the piece
    M_moved  = 1 << 8, // 1 000 0 000 000 : mask to get the hasMoved value of the piece 
    F_pawn   = 0 << 7,
    F_rook   = 1 << 7,
    F_knight = 2 << 7,
    F_bishop = 3 << 7,
    F_queen  = 4 << 7,
    F_king   = 5 << 7;

/* PROTOTYPES */
// allow to reset the game
void initBoard( struct Board &board );
// check if the given position is a valid position within the board
char isValidPos( char pos );
// add the values of the vector to the given position
char addVectorToPos( struct Vector &vector, char pos );
// at piece at the given position
// remove any other piece if there was an other one at the given position, return 1
// append the new piece at the end of the list if the position is free and valid, return 0
// doesn't add the piece if the position is invalid or there is too much pieces already, return -1
char addPiece( struct Board &board, short piece );

// get all valid moves for this turn
struct Turn getTurn( struct Board &board, char checkNext );
// return the piece at the given position,
// return -1 if there was none,
// return -2 if the position is outside of the board boundaries
short getPieceAtPos( struct Board &board, char pos );
// move the piece from position to position
void movePiece( struct Board &board, char from, char to );
// return a struct with all the moves the piece can perform within the specified board
// if board == m_board, check moves for next turn
struct Moves getMoves( struct Board &board, short piece, char checkNext );
// function to add moves to the structure
void addToMoves( struct Board &board, struct Moves &moves, char move, char checkNext );
// recursive function to add movevement to the set of possible movement
void addMovesLinear( struct Board &board, struct Moves &moves, short piece, char pos, struct Vector &dir, char checkNext );

// print the given board to the console
void printBoard( struct Board &board );

int main()
{
    /* INIT THE GAME */
    printf("\n    << 1K  CHESS >>\n"); // we print a title
    initBoard (m_board); // we init the board
    char
        i, j,    // loop increments
        x, y,    // values for printing possible moves
        move,    // the move studied
        end = 0; // has the game ended ?
    // as long as the game hasn't ended
    while( !end )
    {
        printBoard(m_board); // we print the board
        struct Turn turn = getTurn( m_board, 1 );
        for(i=0; i<turn.length; ++i)
        {
            struct Moves* moves = &turn.moves[i];
            move = moves->from;
            x = (move  & 7) + 'a', // we recover y as a letter
            y = (move >> 3) +  1;  // we recover x as a number
            printf("\n%c%d > ", x, y );
            for(j=0; j<moves->length; ++j)
            {
                move = moves->to[j];
                x = (move  & 7) + 'a', // we recover y as a letter
                y = (move >> 3) +  1;  // we recover x as a number
                printf("%c%d,%d; ", x, y, move );
            }
        }
        end = 1;
    }


    // when the game ends, we pause the program so the players can see who won
    system("pause");
    return 0;
}

void initBoard( struct Board &board )
{
    board.length = 0, // the list is empty
    board.turn   = 0; // white start first

    char
        y_b1 = 7 << 3, // pieces
        y_b2 = 6 << 3, // pawns
        // empty space
        y_w2 = 1 << 3, // pawns
        y_w1 = 0 << 3, // pieces
        i;
    // we create the pieces for each team
    /* WHITE TEAM */
    addPiece( board, F_rook   | F_white | y_w1 | 0 );
    addPiece( board, F_knight | F_white | y_w1 | 1 );
    addPiece( board, F_bishop | F_white | y_w1 | 2 );
    addPiece( board, F_queen  | F_white | y_w1 | 3 );
    addPiece( board, F_king   | F_white | y_w1 | 4 );
    addPiece( board, F_bishop | F_white | y_w1 | 5 );
    addPiece( board, F_knight | F_white | y_w1 | 6 );
    addPiece( board, F_rook   | F_white | y_w1 | 7 );
    /* BLACK TEAM */
    addPiece( board, F_rook   | F_black | y_b1 | 0 );
    addPiece( board, F_knight | F_black | y_b1 | 1 );
    addPiece( board, F_bishop | F_black | y_b1 | 2 );
    addPiece( board, F_queen  | F_black | y_b1 | 3 );
    addPiece( board, F_king   | F_black | y_b1 | 4 );
    addPiece( board, F_bishop | F_black | y_b1 | 5 );
    addPiece( board, F_knight | F_black | y_b1 | 6 );
    addPiece( board, F_rook   | F_black | y_b1 | 7 );
    // we create the pawns for both team
    for(i=0; i<8; ++i)
    {
        // we add pawn for both black and white
        addPiece( board, F_pawn | F_white | y_w2 | i );
        addPiece( board, F_pawn | F_black | y_b2 | i );
    }
    // at that point m_board.length should have a value of 32
}
char isValidPos( char pos )
{
    // we extract the coordinates from the position
    unsigned char
        x = pos & 7,        // first     3 bits
        y = (pos >> 3) & 7; // following 3 bits
    // unsigned char cannot be negative, we only check the upper value
    return ( x < 8 && y < 8 );
}
char addVectorToPos( struct Vector &vector, char pos )
{
    // we extract the coordinates from the position
    char
        x = pos  & 7, // first     3 bits
        y = pos >> 3; // following 3 bits
        x += vector.x;
        y += vector.y;
    // we concat the values back into one variable
    return ((y & 7) << 3) | (x & 7);
}
char addPiece( struct Board &board, short piece )
{
    char pos = piece & M_pos;
    // if the position is within the range of valid positions
    if( isValidPos(pos) )
    {
        // for each piece present in the board
        char i;
        for(i=0; i<board.length; ++i)
        {
            // if there is already a piece at the given position
            if( (board.pieces[i] & M_pos) == pos )
            {
                // we replace the old piece by the new one
                board.pieces[i] = piece;
                return 1; // we destroyed a other piece
            }
        }
        // we check each pieces, none of them was occupying the position
        if( board.length < 32 ) // if we access board[32] the program will crash
        {
            // we put a piece at the end of the list
            board.pieces[board.length++] = piece;
            // then we increment the length of the list
            return 0; // we appended the piece at the end of the list
        }
    }
    return -1; // the piece couldn't be added to the board
}

struct Turn getTurn( struct Board &board, char checkNext )
{
    char  i;
    short piece;

    struct Turn turn;
    turn.length = 0;

    for(i=0; i<board.length; ++i)
    {
        piece = board.pieces[i];
        // as long as the team of the piece is the same as the one of the player
        // and we don't go over 16 pieces
        // if team==1 000 000 -> !!team==1
        if( (!!(piece & M_team) == board.turn) && turn.length < 16 )
        {
            // we can add the moves to the list
            turn.moves[turn.length++] = getMoves( board, piece, checkNext );
            // we increase the length of the list
        }
    }
    // we've filled the turn with valid moves
    return turn;
}
short getPieceAtPos( struct Board &board, char pos )
{
    // as long as the position is within the boundaries of the board
    if( isValidPos(pos) )
    {
        // for each piece of the board
        char i;
        for(i=0; i<board.length; ++i)
        {
            // if there is a piece at the given position
            if( (board.pieces[i] & M_pos) == pos )
            {
                // we return it
                return board.pieces[i];
            }
        }
        return -1; // we haven't found a piece at the given position
    }
    return -2; // the position we want to access is outside of the board
}
void movePiece( struct Board &board, char from, char to )
{
    char i, pos, index = -1; // index of the piece to replace in the list
    // for each piece on the board
    for(i=0; i<board.length; ++i)
    {
        // we recover the piece at the current position
        pos = board.pieces[i] & M_pos;
        // if there is a piece at the destination
        if( pos == to ) index = i;
        // if we found the piece we want to move
        else if( pos == from )
        {
            // we replace the position of the current piece and
            // we mark that the piece has moved
            board.pieces[i] = M_moved | (board.pieces[i] & ~M_pos) | pos;
        }
    }
    // if we found a piece at the destination
    if( index != -1 )
    {
        // the last piece take the place of the piece that has been removed
        board.pieces[index] = board.pieces[--board.length];
        // and we reduce the number of pieces
    }
}
struct Moves getMoves( struct Board &board, short piece, char checkNext )
{
    char 
        pos  = piece & M_pos,  // we extract the position of the piece
        team = piece & M_team, // we extract the team of the piece
        move,                  // the move we're executing
        i;                     // increment value for for-loops
    short
        type  = piece & M_type,  // we extract the type of the piece
        moved = piece & M_moved, // we extract the hasMoved value of the piece
        other;                   // the other piece

    struct Moves moves; // will contains the calculated move possible
    // we init the values of the moves
    moves.length = 0;
    moves.from   = pos;

    struct Vector* dirs; // direction of movement for the pieces

    // based on the type of the piece we run different move functions
    switch( type )
    {
        // pawn movements
        case F_pawn :
        {
            struct Vector dir;
            dir.y = team ? -1 : 1; // if black we go down, if white we go up
            // we repeat twice : once on the left and then on the right
            for( dir.x = -1; dir.x < 2; dir.x += 2 ) // (v.x = -1 then v.x = 1)
            {
                move  = addVectorToPos(dir, pos);
                other = getPieceAtPos(board, move);
                // if there is a piece on the left/right, and it is one of the opposed team
                if( other > -1 && ((other ^ piece) & M_team) )
                {
                    // the pawn can move to that position
                    addToMoves(board, moves, move, checkNext);
                }
            }
            // we check for movements forward
            dir.x = 0;
            move = addVectorToPos(dir, pos);
            // if there is no piece in front of the piece,
            // but we're not outside of the boundaries of the board
            if( getPieceAtPos(board, move) == -1 )
            {
                addToMoves(board, moves, move, checkNext); // the move is valid
                if( !moved ) // if the piece hasn't moved yet
                {
                    // we check if we can make a "En passant" move
                    dir.y *= 2;
                    move = addVectorToPos(dir, pos);
                    // if the position is empty
                    if( getPieceAtPos(board, move) == -1 )
                    {
                        // we add the move to the list
                        addToMoves(board, moves, move, checkNext);
                    }
                }
            }
        }
        break;
        // linear movements
        case F_rook   :
        case F_bishop :
        case F_queen  :
        {
            // we recover the type of movement we want based on the piece type
            char dlength = 4;
            switch( type )
            {
                case F_rook   : dirs = D_ortho; break;
                case F_bishop : dirs = D_diago; break;
                case F_queen  : dirs = D_octo;  dlength = 8; break;
            }
            // for each movement
            for(i=0; i<dlength; ++i)
            {
                // we search recursively for possible movement in the direction
                addMovesLinear(board, moves, piece, pos, dirs[i], checkNext);
            }
        }
        break;
        // jump movements
        case F_knight :
        case F_king   :
        {
            // if the piece is a king, he can perform a cast
            if( type == F_king )
            {
                dirs = D_octo; // king move in every 8 directions
                if( !moved ) // if the king hasn't moved until now
                {
                    // if team black y = top else y = bottom
                    char
                    ypos = team ? (111 << 3) : (0 << 3),
                    rpos,  // rook position               0 or 7
                    start, // start of the loop           1 or 5
                    max,   // maximum value of the loop   4 or 7
                    cast;  // position of the cast either 2 or 6
                    // this loop is repeated twice, once for the left castling then for the right castling
                    for( rpos=0, start=1, max=4, cast=2; rpos<8; rpos+=7, start=5, max=7, cast=6 )
                    {
                        // we check the left clastling
                        other = getPieceAtPos( board, ypos & rpos );
                        // if the piece at position 0 is a rook of the same team as the king that has moved yet
                        if( (other & M_type) == F_rook && !((other ^ piece) & M_team) && !(other & M_moved))
                        {
                            // we check that each postion between rook and king is empty
                            for(i=start; i<max; ++i )
                            {
                                other = getPieceAtPos( board, ypos | i );
                                // atleast one position is not empty
                                if( other != -1 ) cast = 0; // castling is not possible
                            }
                            // if we have checked that castling was possible
                            if( cast )
                            {
                                // cast = 2 or 6
                                move = ypos | cast;
                                addToMoves(board, moves, move, checkNext);
                            }
                        }
                    }
                }
            }
            else{
                dirs = D_jump; // knight move by jumping
            } 
            
            // for each movement
            for(i=0; i<8; ++i)
            {
                move  = addVectorToPos(dirs[i], pos);
                other = getPieceAtPos(board, move);
                // if the position is free or is an enemy
                if( other == -1 || ((other ^ piece) & M_team) )
                {
                    // we can add the move to the list
                    addToMoves(board, moves, move, checkNext);
                }
            }
        }
        break;
    }
    return moves; // we've collected al of the moves possible'
}
void addMovesLinear( struct Board &board, struct Moves &moves,
    short piece, char pos, struct Vector &dir, char checkNext )
{
    char  move  = addVectorToPos(dir, pos);
    short other = getPieceAtPos(board, move);
    // if the position is free or enemy piece
    if( other == -1 || ((other ^ piece) & M_team) )
    {
        addToMoves(board, moves, move, checkNext); // the move is a valid one
        // if the position is free, 
        if( other == -1 )
        {
            // we can check for the next position in the same direction
            addMovesLinear(board, moves, piece, move, dir, checkNext);
        }
    }
}
void addToMoves( struct Board &board, struct Moves &moves, char move, char checkNext )
{
    // as long as the position is valid and we haven't excedeed the length of 27
    if( isValidPos(move) && moves.length < 27 )
    {
        // if we make that move, would the king be in check
        char kingCheck = 0; // we assume no
        // if we need to check for the next turn
        if( checkNext )
        {
            char i, j;
            short other; // the piece we are studing
            // we make a copy of the board
            struct Board nextBoard = board;
            // we suppose we're on the next turn
            nextBoard.turn = !board.turn;
            // and we have made the move
            movePiece(nextBoard, moves.from, move);

            // we recover the possible move of the enemy player for the next turn
            struct Turn nextTurn = getTurn( nextBoard, 0 );
            // for each piece we can move
            for(i=0; i<nextTurn.length; ++i)
            {
                // we recover the next moves for one piece
                struct Moves* nextMoves = &nextTurn.moves[i];
                // for each destination of said move, as long as the king is not in check
                for(j=0; j<nextMoves->length && !kingCheck; ++j)
                {
                    // we recover the piece at the destination
                    other = getPieceAtPos(nextBoard, nextMoves->to[j]);
                    // if the piece is a piece of the current team and a king
                    if( other > -1 && !!(other & M_team) == board.turn && (other & M_type) == F_king )
                    {
                        // then performing the move would put the king in check
                        kingCheck = 1;
                    }
                }
                // the king is not in check if we make the move
            }
        }
        // if the king wouldn't be in check
        if( !kingCheck )
        {
            // we can make the move
            moves.to[moves.length++] = move;
            // we increment the length of the list
        }
    }
}

void printBoard( struct Board &board )
{
    const char* label = board.turn ? "BLACK" : "WHITE";
    // we print info about the state of the game
    printf("\n    --%s--TURN--\n", label);
    short piece;
    char  x, y, c;
    // we need to print the board from top to bottom, left to right
    for(y=7; y>-1; --y)
    {
        printf("\n %d  ", y+1); // we print the line number
        for(x=0; x<8; ++x)
        {
            // we recover the piece we need
            piece = getPieceAtPos(board, (y << 3) | x);
            if( piece > -1 )
            {
                switch( piece & M_type )
                {
                    case F_pawn   : c = 'P'; break;
                    case F_rook   : c = 'R'; break;
                    case F_knight : c = 'N'; break;
                    case F_bishop : c = 'B'; break;
                    case F_queen  : c = 'Q'; break;
                    case F_king   : c = 'K'; break;
                }
                // if the piece is of team black
                if( piece & M_team ) c += 32; // we switch to lower case
            }
            else c = '.'; // empty square
            printf("%c ",c);
        }
    }
    printf("\n\n    ");
    // then we print the column identifier
    for(c='a'; c<'i'; ++c) printf("%c ",c);
    printf("\n\n");
}