using System.Collections.Generic;

public class MoveSet
{
    // PROPERTIES
    private HashSet<Move> moves;

    // GETTERS
    public HashSet<Move> Moves { get { return moves; } }

    // CONSTRUCTORS
    public MoveSet()
    { moves = new HashSet<Move>(); }

    // METHODS
    public bool Add(Move move)
    { return moves.Add(move); }
    public bool IsEmpty()
    { return moves.Count == 0; }
    public Move GetMoveForPosition(IntVector position)
    {
        foreach (Move move in moves)
        {
            if (move == position) return move;
        }
        return null;
    }
    public void Purge(BaseBoard board, BasePiece piece)
    {
        // we must use an iterator because we are removing elements
        Purger predicate = new Purger(board, piece);
        moves.RemoveWhere(predicate.Purge);
    }

    // OVERRIDES
    public override string ToString()
    { return "MoveSet: " + moves.Count; }

    // OPERATORS
    public static bool operator +(MoveSet moves, Move move)
    { return moves.Add(move); }
    public static bool operator ~(MoveSet moves)
    { return moves.IsEmpty(); }

    // HELPERS
}

// class to remove elements while iterating
public struct Purger
{
    private BaseBoard board;
    private BasePiece piece;

    public Purger(BaseBoard board, BasePiece piece)
    {
        this.board = board;
        this.piece = piece;
    }

    public System.Predicate<Move> Purge { get { return _Test; } }

    private bool _Test(Move move)
    {
        BaseBoard tempBoard = (BaseBoard)board.Clone();
        BasePiece tempPiece = (BasePiece)piece.Clone();
        move.Apply(tempBoard, tempPiece);
        if (tempBoard.SingleKing && tempBoard.ThreatenKing(tempPiece.Team))
            return true;
        else
        {
            uint count;
            HashSet<BasePiece> kings = 
                tempBoard.ThreatenKings(tempPiece.Team, out count);
            if (kings.Count == count) return true;
        }
        return false;
    }
}