// JANGGI PIECES

// COUNSELOR (GENERAL)
// (1,0)-leaper + (1,1)-leaper when in center
public class Counselor : BasePiece
{
    // CONSTRUCTORS
    public Counselor(IntVector position, uint team,
        Direction orientation = Direction.North,
        bool hasMoved = false, bool isKing = false)
        : base(position, team, orientation, hasMoved, isKing, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO diagonal only in center
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Counselor(Position, Team, Orientation, HasMoved, IsKing); }
}

// ELEPHANT
// (2,3)-leaper
public class Syang : BasePiece
{
    // CONSTRUCTORS
    public Syang(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO block if other piece
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(2, 3));
        LeaperMoves(moves, zone, new IntVector(3, 2));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Syang(Position, Team, Orientation, HasMoved); }
}

// CHARIOT
// (1,0)-rider + (1,1)-leaper if in palace
public class Chariot : BasePiece
{
    // CONSTRUCTORS
    public Chariot(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO diagonal if in palace
        MoveSet moves = new MoveSet();
        RiderMoves (moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Chariot(Position, Team, Orientation, HasMoved); }
}

// CANNON
// (1,0)-hopper + (1,1)-hopper if in palace
public class Hpo : BasePiece
{
    // CONSTRUCTORS
    public Hpo(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO diagonal if in palace
        MoveSet moves = new MoveSet();
        HopperMoves(moves, zone, new IntVector(1, 0));
        HopperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Hpo(Position, Team, Orientation, HasMoved); }
}