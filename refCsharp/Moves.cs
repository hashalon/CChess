public class Move : System.ICloneable
{
    // PROPERTIES
    private IntVector position;
    private Direction rotation;

    // GETTERS
    public IntVector Position { get { return position; } }
    public Direction Rotation { get { return rotation; } }

    // CONSTRUCTORS
    public Move(IntVector position, Direction rotation )
    {
        this.position = position;
        this.rotation = rotation;
    }

    // METHODS
    public virtual void Apply(BaseBoard board, BasePiece piece)
    {
        board.lastMove = this;
        board.Remove(piece);              // remove from old position
        piece.MoveTo(position, rotation); // move to new position
        board.Remove(piece);              // remove other piece at position
        board.Add   (piece);              // put piece at position
    }

    // OVERRIDES
    public override bool Equals(object o)
    {
        if (o is IntVector)      return position == (IntVector)o;
        else if (o is BasePiece) return position == ((BasePiece)o).Position;
        else if (o is Move)      return position == ((Move)o)     .Position;
        return false;
    }
    public virtual object Clone()
    { return new Move(position, rotation); }
    public override int GetHashCode()
    { return position.GetHashCode(); }
    public override string ToString()
    {
        return GetType().Name 
            + "| position: " + position
            + "; rotation: " + _RotationString(rotation);
    }

    // OPERATORS
    public static bool operator ==(Move move, IntVector position)
    { return move.position == position; }
    public static bool operator !=(Move move, IntVector position)
    { return move.position != position; }
    public static bool operator ==(Move move1, Move move2)
    {
        return move1.position == move2.Position
            && move1.rotation == move2.rotation;
    }
    public static bool operator !=(Move move1, Move move2)
    { return !(move1 == move2); }

    // HELPERS
    protected static string _RotationString(Direction rotation)
    {
        switch (rotation)
        {
            case Direction.Deg90 : return " 90 deg";
            case Direction.Deg180: return "180 deg";
            case Direction.Deg270: return "-90 deg";
        }
        return "  0 deg";
    }
}

// Specific move objects

public class EnPassant : Move
{
    // PROPERTIES
    private BasePiece pawn;   // pawn that did the move
    // GETTERS
    public BasePiece Pawn { get { return pawn; } }
    // CONSTRUCTORS
    public EnPassant(IntVector position, Direction rotation,
        BasePiece pawn) : base(position, rotation)
    { this.pawn = pawn; }
    // METHODS
    public override void Apply(BaseBoard board, BasePiece piece)
    {
        base.Apply(board, piece);
        board.Remove(pawn);
    }
    // OVERRIDES
    public override object Clone()
    { return new EnPassant(Position, Rotation, pawn); }
    public override string ToString()
    { return base.ToString() + "; pawn: " + pawn; }
}

public class LongMove : Move
{
    // PROPERTIES
    private BasePiece pawn;
    private IntVector jumped; // position jumped
    // GETTERS
    public BasePiece Pawn   { get { return pawn; } }
    public IntVector Jumped { get { return jumped; } }
    // CONSTRUCTORS
    public LongMove(IntVector position, Direction rotation,
        BasePiece pawn, IntVector jumped) : base(position, rotation)
    {
        this.pawn   = pawn;
        this.jumped = jumped;
    }
    // OVERRIDES
    public override object Clone()
    { return new LongMove(Position, Rotation, Pawn, jumped); }
    public override string ToString()
    { return base.ToString() + "; pawn: " + pawn + "; jump: " + jumped; }
}

public class Castling : Move
{
    // PROPERTIES
    private IntVector castlerTarget;   // targeted castler
    private IntVector castlerPosition; // position of the castler
    private Direction castlerRotation; // rotation of the castler
    // GETTERS
    public IntVector CastlerTarget   { get { return castlerTarget; } }
    public IntVector CastlerPosition { get { return castlerPosition; } }
    public Direction CastlerRotation { get { return castlerRotation; } }
    // CONSTRUCTORS
    public Castling(IntVector position, Direction rotation,
        IntVector castlerTarget, IntVector castlerPosition,
        Direction castlerRotation) : base(position, rotation)
    {
        this.castlerTarget  = castlerTarget;
        this.castlerPosition = castlerPosition;
        this.castlerRotation = castlerRotation;
    }
    // METHODS
    public override void Apply(BaseBoard board, BasePiece piece)
    {
        base.Apply(board, piece);
        BasePiece castler = board.FindPiece(castlerTarget);
        board  .Remove(castler);
        castler.MoveTo(castlerPosition, castlerRotation);
        board  .Remove(castler);
        board  .Add   (castler);
    }
    // OVERRIDES
    public override object Clone()
    {
        return new Castling(Position, Rotation, 
            castlerTarget, castlerPosition, castlerRotation);
    }
    public override string ToString()
    {
        return base.ToString()
            + "; target castler: "   + castlerTarget
            + "; castler position: " + castlerPosition
            + "; castler rotation: " + _RotationString(castlerRotation);
    }
}