package chess

// Move specify new position and orientation for a piece
type Move struct {
	mType uint8
	pos1, pos2, pos3 Vec2
	rot1, rot2 int8
}

/*
	move types:
	0: none
	1: basic
	2: long move
	3: en passant
	4: castling
*/

// MakeMove create new move
func MakeMove(pos Vec2, rot int8) Move {
	return Move{ mType: 1, pos1: pos, rot1: rot }
}
// MakeLongMove create new long move
func MakeLongMove(pos Vec2, rot int8, posJumped Vec2) Move {
	return Move{ mType: 2, pos1: pos, rot1: rot, pos2: posJumped }
}
// MakeEnPassant create new en passant move
func MakeEnPassant(pos Vec2, rot int8, posPawn Vec2) Move {
	return Move{ mType: 3, pos1: pos, rot1: rot, pos2: posPawn }
}
// MakeCastling create new castling move
func MakeCastling(
	pos Vec2, rot int8, posCast Vec2, rotCast int8, target Vec2) Move {
	return Move{ mType: 4, 
		pos1: pos,     rot1: rot, 
		pos2: posCast, rot2: rotCast, 
		pos3: target }
}


// Apply apply the move to the board and the piece
func (move Move) Apply(board Board, piece Piece) {
	board.lastMoved = Piece{ pType: 0 }
	if move.mType == 0 { return } // undefined
	// move the piece:
	board.Remove(piece)                // remove piece from board
	piece.MoveTo(move.pos1, move.rot1) // move piece
	board.Add(piece)                   // place piece in board
	if move.mType == 2 { /* long move */
		board.lastMoved = piece        // the pawn that was moved
		board.jumped    = move.pos2    // position which was jumped
	} else if move.mType == 3 { /* en passant */
		board.remID(board.lastMoved.ID()) // remove pawn
	} else if move.mType == 4 { /* castling */
		id := move.pos3.ID()
		castler, ok := board.findID(id) // find the castler
		board.remID(id)                 // remove it from the board
		if ok { // fine we found the castler
			castler.MoveTo(move.pos2, move.rot2) // move the castler
			board.Add(castler)                   // place it in the board
		} // else error
	}
}

