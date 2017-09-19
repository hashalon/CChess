// XIANGQI PIECES

// GENERAL
// (1,0)-leaper
public class General : BasePiece
{
    // CONSTRUCTORS
    public General(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, true, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(1, 0)); }

    // OVERRIDES
    public override object Clone()
    { return new General(Position, Team, Orientation, HasMoved); }
}

// ADVISOR
// (1,1)-leaper
public class Advisor : BasePiece
{
    // CONSTRUCTORS
    public Advisor(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(1, 1)); }

    // OVERRIDES
    public override object Clone()
    { return new Advisor(Position, Team, Orientation, HasMoved); }
}

// ELEPHANT
// (2,2)-leaper
public class Elephant : BasePiece
{
    // CONSTRUCTORS
    public Elephant(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(2, 2)); }

    // OVERRIDES
    public override object Clone()
    { return new Elephant(Position, Team, Orientation, HasMoved); }
}

// HORSE
// (1,2)-leaper /!\ blocked by pieces
public class Horse : BasePiece
{
    // CONSTRUCTORS
    public Horse(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        // TODO check for blocks
        LeaperMoves(moves, zone, new IntVector(1, 2));
        LeaperMoves(moves, zone, new IntVector(2, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Horse(Position, Team, Orientation, HasMoved); }
}

// CHARIOT (ROOK)
// (1,0)-rider

// CANNON
// (1,0)-hopper
public class Cannon : BasePiece
{
    // CONSTRUCTORS
    public Cannon(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO not the same thing as grasshopper
        return HopperMoves(new MoveSet(), zone, new IntVector(1, 0));
    }

    // OVERRIDES
    public override object Clone()
    { return new Cannon(Position, Team, Orientation, HasMoved); }
}

// SOLDIER
// (1,0)-leaper
public class Soldier : BasePiece
{
    // CONSTRUCTORS
    public Soldier(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        // TODO only forward or sideway in second zone
        return LeaperMoves(new MoveSet(), zone, new IntVector(1, 0));
    }

    // OVERRIDES
    public override object Clone()
    { return new Soldier(Position, Team, Orientation, HasMoved); }
}