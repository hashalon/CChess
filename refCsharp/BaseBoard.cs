using System.Collections.Generic;

public interface Zone
{
    // check that the position is inside the limits of the board
    bool CheckPosition(IntVector position);
    // rotate and move the object in the board
    Move      Retarget (Move      move);
    IntVector Retarget (IntVector position, out Direction rotation);
    BasePiece FindPiece(IntVector position);
}

public abstract class BaseBoard : System.ICloneable, Zone
{
    // PROPERTIES
    private uint numberOfTurns = 0;
    private uint numberOfTeams;
    private uint turnOfTeam = 0;
    private bool singleKing = true;
    private HashSet   <BasePiece> pieces;
    private Dictionary<BasePiece, MoveSet> moveSets;

    // reference to last move to manage EnPassant
    public Move lastMove = null;

    // GETTERS
    public uint NumberOfTurns { get { return numberOfTurns; } }
    public uint NumberOfTeams { get { return numberOfTeams; } }
    public uint TurnOfTeam    { get { return turnOfTeam; } }
    public bool SingleKing    { get { return singleKing; } }

    // CONSTRUCTORS
    public BaseBoard(uint numberOfTeams)
    {
        this.numberOfTeams = numberOfTeams;
        pieces   = new HashSet<BasePiece>();
        moveSets = new Dictionary<BasePiece, MoveSet>();
    }

    // TO IMPLEMENT
    // check that the position is inside the limits of the board
    public abstract bool CheckPosition(IntVector position);
    // rotate and move the object in the board
    public virtual Move      Retarget(Move move) { return move; }
    public virtual IntVector Retarget(
        IntVector position, out Direction rotation)
    {
        rotation = Direction.Deg0;
        return position;
    }

    // METHODS
    public bool Add   (BasePiece piece) { return pieces.Add   (piece); }
    public bool Remove(BasePiece piece) { return pieces.Remove(piece); }
    // find the piece at the given position
    public BasePiece FindPiece(IntVector position)
    {
        foreach (BasePiece piece in pieces)
            if (piece == position) return piece;
        return null;
    }
    public HashSet<BasePiece> FindPiecesOfTeam(uint team)
    {
        HashSet<BasePiece> pieces = new HashSet<BasePiece>();
        foreach (BasePiece piece in this.pieces)
            if (piece.Team == team) pieces.Add(piece);
        return pieces;
    }
    // return the purged moves of the piece
    public MoveSet GetMovesForPiece(BasePiece piece)
    {
        MoveSet moves;
        bool found = moveSets.TryGetValue(piece, out moves);
        if (!found)
        {
            moves = piece.GetMoves(this);
            moveSets.Add(piece, moves); // reuse computed moves
            // TODO purge
        }
        return moves;
    }
    // true if one king is threathen aka. in check
    public bool ThreatenKing(uint team)
    {
        foreach (BasePiece enemy in pieces)
        {
            if (enemy.Team != team) // enemy piece
            {
                MoveSet moves = enemy.GetMoves(this);
                foreach (Move move in moves.Moves)
                {
                    // king are only threaten through regular moves
                    BasePiece king = FindPiece(move.Position);
                    if (((System.Object)king != null) 
                        && king.Team == team && king.IsKing)
                        return true;
                }
            }
        }
        return false;
    }
    // return all kings that are threathen aka. in check
    public HashSet<BasePiece> ThreatenKings(uint team, out uint count)
    {
        count = 0;
        HashSet<BasePiece> kings = new HashSet<BasePiece>();
        foreach (BasePiece enemy in pieces)
        {
            if (enemy.Team != team) // enemy piece
            {
                MoveSet moves = enemy.GetMoves(this);
                foreach (Move move in moves.Moves)
                {
                    // king are only threaten through regular moves
                    BasePiece king = FindPiece(move.Position);
                    if (((System.Object)king != null) 
                        && king.Team == team && king.IsKing)
                        kings.Add(king);
                }
            }
            else if (enemy.IsKing) ++count;
        }
        return kings;
    }
    // true if the player is in checkmate
    public bool IsInCheckMate()
    {
        // do we have atleast one king left ?
        bool atLeastOneKing = false;
        foreach (BasePiece piece in pieces)
        {
            if (piece.Team == turnOfTeam && piece.IsKing)
                atLeastOneKing = true;
        }
        // no more kings -> loose
        if (!atLeastOneKing) return true;
        // see if team can still performs moves
        // compute movesets and purge to see if empty
        foreach (BasePiece piece in pieces)
        {
            if (piece.Team == turnOfTeam)
            {
                MoveSet moves = GetMovesForPiece(piece);
                // if atleast one move set is not empty, we can save the king
                if (!moves.IsEmpty()) return true;
            }
        }
        return false;
    }
    // prepare next turn
    public void EndTurn()
    {
        turnOfTeam = (turnOfTeam + 1) % numberOfTeams;
        moveSets = new Dictionary<BasePiece, MoveSet>();
        if (turnOfTeam == 0) ++numberOfTurns;
    }
    // replace a piece by an other
    public void Replace(BasePiece newPiece)
    {
        //BasePiece oldPiece = FindPiece(newPiece.Position);
        pieces.Remove(newPiece);
        pieces.Add   (newPiece);
    }

    // OVERRIDES
    public abstract object Clone();
    public override string ToString()
    {
        return GetType().Name
            + "| pieces: " + pieces.Count
            + "; teams: "  + numberOfTeams 
            + "; turns: "  + numberOfTurns;
    }

    // OPERATORS
    public static bool operator +(BaseBoard board, BasePiece piece)
    { return board.Add(piece); }
    public static bool operator -(BaseBoard board, BasePiece piece)
    { return board.Remove(piece); }

    // HELPERS
    protected static bool InBound(int min, int value, int max)
    { return min <= value && value <= max; }
}