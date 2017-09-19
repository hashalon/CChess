package chess

// Zone interface for boards and special zones
type Zone interface {
	CheckPos(pos Vec2) bool
	RetargetMove(move Move) Move
	RetargetPos(pos Vec2, rot int8) (Vec2, int8)
	FindPiece(pos Vec2) (Piece, bool)
}

// Board game board, contains pieces
type Board struct {
	nbTurns uint
	nbTeams, currTeam uint8
	singleKing bool
	pieces   map[uint]Piece
	moveSets map[uint]MoveSet
	// used for en passant move
	lastMoved Piece
	jumped    Vec2
}

// MakeBoard create a new board (with an invalid lastMove)
func MakeBoard(nbTeams uint8) Board {
	return Board{ 0,  nbTeams, 0, true,
		make(map[uint]Piece),
		make(map[uint]MoveSet),
		Piece{ pType: 0 }, Vec2{ -128, -128 } }
}

// Clone deep clone the board
func (board Board) Clone() Board {
	clone := board
	clone.pieces   = make(map[uint]Piece)
	clone.moveSets = make(map[uint]MoveSet)
	for id, piece := range board.pieces {
		clone.pieces[id] = piece
	}
	/*for id, moveset := range board.moveSets {
		clone.moveSets[id] = moveset.Clone()
	}*/
	return clone
}

// CheckPos return true if the position is inside of the board
func (board Board) CheckPos(pos Vec2) bool {
	return -1 < pos.x && pos.x < 8 && -1 < pos.y && pos.y < 8
}

// RetargetMove apply modification to the move so that it remains in the board
func (board Board) RetargetMove(move Move) Move {
	return move
}

// RetargetPos apply modification to position and rotation so that they remain in the board
func (board Board) RetargetPos(pos Vec2, rot int8) (Vec2, int8) {
	return pos, rot
}

// Add add a piece to the board
func (board Board) Add(piece Piece) {
	board.pieces[piece.ID()] = piece
}
// Remove remove piece from board based on its ID
func (board Board) Remove(piece Piece) {
	delete(board.pieces, piece.ID())
}

func (board Board) addID(id uint, piece Piece) {
	board.pieces[id] = piece
}
func (board Board) remID(id uint) {
	delete(board.pieces, id)
}

// FindPiece return the piece at the position (or false if not found)
func (board Board) FindPiece(pos Vec2) (Piece, bool) {
	return board.findID(pos.ID())
}
func (board Board) findID(id uint) (Piece, bool) {
	piece, ok := board.pieces[id]
	return piece, ok
}

// GetMoves return the moveset associated to the piece (a new computed moveset if not found)
func (board Board) GetMoves(piece Piece) MoveSet {
	id := piece.ID()
	set, ok := board.moveSets[id]
	if !ok {
		set = piece.GetMoves(board)
		board.moveSets[id] = set
		set.Purge(board, piece)
	}
	return set
}

// ThreatenKing return true if one king of the team is threaten
func (board Board) ThreatenKing(team uint8) bool {
	// cycle through enemy pieces
	for id, enemy := range board.pieces {
		if enemy.team != team {
			set := enemy.GetMoves(board)
			// cycle through the moves of the enemy piece
			for id2, move := range set.moves {
				king, ok := board.findID(id2)
				if ok && king.team == team && king.isKing { return true }
			}
		}
	}
	return false
}

// ThreatenKings return set of kings that are threaten and the total count of king of the team
func (board Board) ThreatenKings(team uint8) (map[uint]Piece, uint) {
	kings := make(map[uint]Piece) // gather threaten kings
	var count uint // count number of kings of the team
	// cycle through enemy pieces
	for id, enemy := range board.pieces { 
		if enemy.team != team {
			set := enemy.GetMoves(board)
			// cycle through the moves of the enemy piece
			for id2, move := range set.moves {
				king, ok := board.findID(id2)
				if ok && king.team == team && king.isKing { kings[id2] = king }
			}
		} else if enemy.isKing { count++ }
	}
	return kings, count
}

// IsInCheckMate return true if the team is in checkmate and have lost
func (board Board) IsInCheckMate(team uint8) bool {
	atLeastOne := false // do we have at least one king
	for id, piece := range board.pieces {
		if piece.team == team && piece.isKing {
			atLeastOne = true
			break
		}
	}
	if !atLeastOne { return true } // no more kings -> checkmate
	for id, piece := range board.pieces {
		if piece.team == team {
			set := board.GetMoves(piece)
			if set.IsEmpty() { return true }
		}
	}
	return false
}

// EndTurn change current team, reset movesets and increment turn
func (board Board) EndTurn() {
	board.currTeam = (board.currTeam + 1) % board.nbTeams
	board.moveSets = make(map[uint]MoveSet)
	if board.currTeam == 0 { board.nbTurns++ }
}