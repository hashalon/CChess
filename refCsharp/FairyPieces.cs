// FAIRY PIECES

// GRASSHOPPER
// (1,0;1,1)-hopper
public class Grasshopper : BasePiece
{
    // CONSTRUCTORS
    public Grasshopper(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        HopperMoves(moves, zone, new IntVector(1, 0));
        HopperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Grasshopper(Position, Team, Orientation, HasMoved); }
}