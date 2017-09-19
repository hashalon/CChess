// FAIRY PIECES

// KIRIN
// (2,0;1,1)-leaper
public class Kirin : BasePiece
{
    // CONSTRUCTORS
    public Kirin(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(2, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Kirin(Position, Team, Orientation, HasMoved); }
}

// PHOENIX
// (1,0;2,2)-leaper
public class Phoenix : BasePiece
{
    // CONSTRUCTORS
    public Phoenix(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(2, 2));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Phoenix(Position, Team, Orientation, HasMoved); }
}


// ROOK-LIKE

// WAZIR
// (1,0)-leaper
public class Wazir : BasePiece
{
    // CONSTRUCTORS
    public Wazir(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(1, 0)); }

    // OVERRIDES
    public override object Clone()
    { return new Wazir(Position, Team, Orientation, HasMoved); }
}

// DABBABA
// (2,0)-leaper
public class Dabbaba : BasePiece
{
    // CONSTRUCTORS
    public Dabbaba(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(2, 0)); }

    // OVERRIDES
    public override object Clone()
    { return new Dabbaba(Position, Team, Orientation, HasMoved); }
}

// THREELEAPER
// (3,0)-leaper
public class Threeleaper : BasePiece
{
    // CONSTRUCTORS
    public Threeleaper(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(3, 0)); }

    // OVERRIDES
    public override object Clone()
    { return new Threeleaper(Position, Team, Orientation, HasMoved); }
}

// BISHOP-LIKE

// FERZ
// (1,1)-leaper
public class Ferz : BasePiece
{
    // CONSTRUCTORS
    public Ferz(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(1, 1)); }

    // OVERRIDES
    public override object Clone()
    { return new Ferz(Position, Team, Orientation, HasMoved); }
}

// ALFIL
// (2,2)-leaper
public class Alfil : BasePiece
{
    // CONSTRUCTORS
    public Alfil(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(2, 2)); }

    // OVERRIDES
    public override object Clone()
    { return new Alfil(Position, Team, Orientation, HasMoved); }
}

// TRIPPER
// (3,3)-leaper
public class Tripper : BasePiece
{
    // CONSTRUCTORS
    public Tripper(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return LeaperMoves(new MoveSet(), zone, new IntVector(3, 3)); }

    // OVERRIDES
    public override object Clone()
    { return new Tripper(Position, Team, Orientation, HasMoved); }
}


// KNIGHT-LIKE

// CAMEL
// (1,3)-leaper
public class Camel : BasePiece
{
    // CONSTRUCTORS
    public Camel(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 3));
        LeaperMoves(moves, zone, new IntVector(3, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Camel(Position, Team, Orientation, HasMoved); }
}

// ZEBRA
// (2,3)-leaper
public class Zebra : BasePiece
{
    // CONSTRUCTORS
    public Zebra(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(2, 3));
        LeaperMoves(moves, zone, new IntVector(3, 2));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Zebra(Position, Team, Orientation, HasMoved); }
}

// GIRAFFE
// (1,4)-leaper
public class Giraffe : BasePiece
{
    // CONSTRUCTORS
    public Giraffe(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 4));
        LeaperMoves(moves, zone, new IntVector(4, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Giraffe(Position, Team, Orientation, HasMoved); }
}


// KING-LIKE

// MANN
// (1,0;1,1;1,2)-leaper
public class Mann : BasePiece
{
    // CONSTRUCTORS
    public Mann(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Mann(Position, Team, Orientation, HasMoved); }
}

// CENTAUR
// (1,0;1,1;1,2)-leaper
public class Centaur : BasePiece
{
    // CONSTRUCTORS
    public Centaur(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));
        LeaperMoves(moves, zone, new IntVector(1, 2));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Centaur(Position, Team, Orientation, HasMoved); }
}