package chess

// MoveSet set of possible moves for a piece
type MoveSet struct {
	moves map[uint]Move
}

// MakeMoveSet create a new moveset
func MakeMoveSet() MoveSet {
	return MoveSet{ make(map[uint]Move) }
}

// Clone deep clone the move set
func (set MoveSet) Clone() MoveSet {
	clone := MoveSet{ make(map[uint]Move) }
	for id, move := range set.moves {
		clone.moves[id] = move
	}
	return clone
}

// Add add the move to the moveset
func (set MoveSet) Add(move Move) {
	set.moves[move.ID()] = move
}
func (set MoveSet) addID(id uint, move Move) {
	set.moves[id] = move
}

// IsEmpty return true if the moveset is empty
func (set MoveSet) IsEmpty() bool {
	return len(set.moves) == 0
}

// GetMove return a move based on the position (false if no move found)
func (set MoveSet) GetMove(pos Vec2) (Move, bool) {
	return set.getID(pos.ID())
}
func (set MoveSet) getID(id uint) (Move, bool) {
	move, ok := set.moves[id]
	return move, ok
}

// Purge remove all invalid moves from the moveset
func (set MoveSet) Purge(board Board, piece Piece) {
	for id, move := range set.moves {
		tempBoard := board.Clone()
		tempPiece := piece
		move.Apply(tempBoard, tempPiece)

	}
}