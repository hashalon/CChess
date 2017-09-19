// FAIRY PIECES

// ROOK-LIKE

// EMPRESS
// (1,0)-rider + (1,2)-leaper
public class Empress : BasePiece
{
    // CONSTRUCTORS
    public Empress(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        RiderMoves (moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 2));
        LeaperMoves(moves, zone, new IntVector(2, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Empress(Position, Team, Orientation, HasMoved); }
}

// BISHOP-LIKE

// PRINCESS
// (1,1)-rider + (1,2)-leaper
public class Princess : BasePiece
{
    // CONSTRUCTORS
    public Princess(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        RiderMoves (moves, zone, new IntVector(1, 1));
        LeaperMoves(moves, zone, new IntVector(1, 2));
        LeaperMoves(moves, zone, new IntVector(2, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Princess(Position, Team, Orientation, HasMoved); }
}

// KNIGHT-LIKE

// NIGHTRIDER or UNICORN
// (1,2)-rider
public class Nightrider : BasePiece
{
    // CONSTRUCTORS
    public Nightrider(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        RiderMoves(moves, zone, new IntVector(1, 2));
        RiderMoves(moves, zone, new IntVector(2, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Nightrider(Position, Team, Orientation, HasMoved); }
}

// QUEEN-LIKE

// AMAZON
// (1,0;1,1)-rider + (1,2)-leaper
public class Amazon : BasePiece
{
    // CONSTRUCTORS
    public Amazon(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        RiderMoves (moves, zone, new IntVector(1, 0));
        RiderMoves (moves, zone, new IntVector(1, 1));
        LeaperMoves(moves, zone, new IntVector(1, 2));
        LeaperMoves(moves, zone, new IntVector(2, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Amazon(Position, Team, Orientation, HasMoved); }
}