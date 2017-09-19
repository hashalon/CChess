package chess

// Piece game piece on the 2D board
type Piece struct {
	Vec2 // position on the board
	orient int8
	pType, team uint8
	hasMoved, isKing, isCastler bool
}

/*
	piece types:
	0: none   |  7: 
	1: pawn   |  8: 
	2: rook   |  9: 
	3: knight | 10: 
	4: bishop | 11: 
	5: queen  | 12: 
	6: king   | 13: 
*/

// MakePiece make a new piece with the specified parameters
func MakePiece(x, y, orient int8, pType, team uint8) Piece {
	var (
		isKing    = false
		isCastler = false
	)
	switch pType {
	case 2: isCastler = true
	case 6: isKing    = true
	}
	return Piece{Vec2{x, y}, orient, pType, team, false, isKing, isCastler}
}

// MoveTo move the piece to the new location with given rotation
func (piece Piece) MoveTo(pos Vec2, rot int8) {
	piece.x = pos.x
	piece.y = pos.y
	piece.orient = ((piece.orient + rot) % 4 + 4) % 4
	piece.hasMoved = true
}

// GetMoves return moveset for the piece
func (piece Piece) GetMoves(zone Zone) MoveSet {
	set := MakeMoveSet()

	return set
}

// leaperMoves moves for knight, king
func (piece Piece) leaperMoves() {

}

// riderMoves moves for knight, king
func (piece Piece) riderMoves() {
	
}

// hopperMoves moves for knight, king
func (piece Piece) hopperMoves() {
	
}