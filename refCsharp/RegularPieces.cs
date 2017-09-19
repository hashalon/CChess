// REGULAR PIECES

// ROOK
// (1,0)-rider
public class Rook : BasePiece
{
    // CONSTRUCTORS
    public Rook(IntVector position, uint team, 
        Direction orientation = Direction.North, bool hasMoved = false) 
        : base(position, team, orientation, hasMoved, false, true) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return RiderMoves(new MoveSet(), zone, new IntVector(1, 0)); }

    // OVERRIDES
    public override object Clone()
    { return new Rook(Position, Team, Orientation, HasMoved); }
}

// KNIGHT
// (1,2)-leaper
public class Knight : BasePiece
{
    // CONSTRUCTORS
    public Knight(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(2, 1));
        LeaperMoves(moves, zone, new IntVector(1, 2));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Knight(Position, Team, Orientation, HasMoved); }
}

// BISHOP
// (1,1)-rider
public class Bishop : BasePiece
{
    // CONSTRUCTORS
    public Bishop(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    { return RiderMoves(new MoveSet(), zone, new IntVector(1, 1)); }

    // OVERRIDES
    public override object Clone()
    { return new Bishop(Position, Team, Orientation, HasMoved); }
}

// QUEEN
// (1,0;1,1)-rider
public class Queen : BasePiece
{
    // CONSTRUCTORS
    public Queen(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, false, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        RiderMoves(moves, zone, new IntVector(1, 0));
        RiderMoves(moves, zone, new IntVector(1, 1));
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new Queen(Position, Team, Orientation, HasMoved); }
}

// KING
// (1,0;1,1)-leaper
public class King : BasePiece
{
    // CONSTRUCTORS
    public King(IntVector position, uint team,
        Direction orientation = Direction.North, bool hasMoved = false)
        : base(position, team, orientation, hasMoved, true, false) { }

    // METHODS
    public override MoveSet GetMoves(Zone zone)
    {
        MoveSet moves = new MoveSet();
        LeaperMoves(moves, zone, new IntVector(1, 0));
        LeaperMoves(moves, zone, new IntVector(1, 1));

        // check for castling
        if (!HasMoved)
        {
            IntVector trajectory = new IntVector(1, 0);
            for (uint i = 0; i < 4; ++i)
            {
                FindCastler(moves, zone, trajectory);
                trajectory <<= 1; // rotate
            }
        }
        return moves;
    }

    // OVERRIDES
    public override object Clone()
    { return new King(Position, Team, Orientation, HasMoved); }

    // HELPERS
    private void FindCastler(
        MoveSet moves, Zone zone, IntVector trajectory)
    {
        Direction rotation;
        IntVector position = zone.Retarget(
            Position + trajectory, out rotation);
        IntVector traject = trajectory << (int)rotation;

        // look for pieces between king and castler
        while (zone.CheckPosition(position))
        {
            BasePiece piece = zone.FindPiece(position);
            if ((System.Object)piece != null)
            {
                // we need an ally castler that hasn't moved yet
                if (Team == piece.Team && piece.IsCastler && !piece.HasMoved)
                {
                    // compute castling move
                    Direction rotation1, rotation2;
                    IntVector
                        position1 = zone.Retarget(Position + trajectory * 2,
                        out rotation1),
                        position2 = zone.Retarget(Position + trajectory,
                        out rotation2);
                    // castling permitted if both stay in the board
                    if (   zone.CheckPosition(position1) 
                        && zone.CheckPosition(position2))
                        moves.Add(new Castling(position1, rotation1, 
                            piece.Position, position2, rotation2));
                }
                break; // found an other piece -> stop the loop
            }
            position = zone.Retarget(position + traject, out rotation);
            traject <<= (int)rotation;
        }
    }
}