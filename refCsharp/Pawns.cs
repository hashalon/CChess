public abstract class BasePawn : BasePiece
{
    // CONSTRUCTORS
    public BasePawn(IntVector position, uint team, 
        Direction orientation, bool hasMoved) 
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    protected MoveSet GetMoves(Zone zone, 
        IntVector[] movements, IntVector[] captures)
    {
        MoveSet   moves = new MoveSet();
        Direction rotation;
        BasePiece piece;

        // check movements
        for (uint i=0; i<movements.Length; ++i)
        {
            // regular move
            IntVector position = zone.Retarget(Position 
                + (movements[i] << (int)Orientation), out rotation);
            if (zone.CheckPosition(position))
            {
                piece = zone.FindPiece(position);
                if ((System.Object)piece == null)
                {
                    moves.Add(new Move(position, rotation));
                    if (HasMoved) continue;
                }
            }
            else continue;

            // long move
            IntVector position2 = zone.Retarget(Position 
                + (movements[i] << (int)Orientation) * 2, out rotation);
            if (zone.CheckPosition(position2))
            {
                piece = zone.FindPiece(position2);
                if ((System.Object)piece == null) moves.Add(
                    new LongMove(position2, rotation, this, position));
            }
        }

        // check captures
        for (uint i=0; i<captures.Length; ++i)
        {
            IntVector position = zone.Retarget(Position
                + (captures[i] << (int)Orientation), out rotation);
            if (!zone.CheckPosition(position)) continue;
            piece = zone.FindPiece(position);
            if ((System.Object)piece == null)
            {
                if (Team != piece.Team)
                    moves.Add(new Move(position, rotation));
            }
            else if (zone is BaseBoard)
            {
                BaseBoard board = (BaseBoard)zone;
                if (board.lastMove != null && board.lastMove is LongMove)
                {
                    LongMove move2 = (LongMove)board.lastMove;
                    if (Team != move2.Pawn.Team && move2.Jumped == position)
                        moves.Add(new EnPassant(
                            position, rotation, move2.Pawn));
                }
            }
        }
        return moves;
    }

    // HELPERS
    // trajectories are defined as facing EAST
    protected static IntVector[] forward  = { new IntVector(1, 0) };
    protected static IntVector[] sideways =
    {
        new IntVector( 1,-1), // SOUTH/EAST
        new IntVector( 1, 1)  // NORTH/EAST
    };
}

// PAWNS TYPES

// REGULAR PAWN
// move forward, capture sideways
public class Pawn : BasePawn
{
    // CONSTRUCTORS
    public Pawn(IntVector position, uint team, 
        Direction orientation, bool hasMoved = false) 
        : base(position, team, orientation, hasMoved) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return GetMoves(zone, forward, sideways); }

    // OVERRIDES
    public override object Clone()
    { return new Pawn(Position, Team, Orientation); }
}

// BEROLINA PAWN
// move sideways, capture forward
public class Berolina : BasePawn
{
    // CONSTRUCTORS
    public Berolina(IntVector position, uint team, 
        Direction orientation, bool hasMoved = false) 
        : base(position, team, orientation, hasMoved) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return GetMoves(zone, sideways, forward); }

    // OVERRIDES
    public override object Clone()
    { return new Berolina(Position, Team, Orientation); }
}