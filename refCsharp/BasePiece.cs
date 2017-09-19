public abstract class BasePiece : System.ICloneable
{
    // PROPERTIES
    private IntVector position;
    private Direction orientation;
    private uint team;
    private bool
        hasMoved  = false,
        isKing    = false,
        isCastler = false;

    // GETTERS
    public IntVector Position    { get { return position; } }
    public Direction Orientation { get { return orientation; } }
    public uint Team      { get { return team; } }
    public bool HasMoved  { get { return hasMoved; } }
    public bool IsKing    { get { return isKing; } }
    public bool IsCastler { get { return isCastler; } }


    // CONSTRUCTORS
    public BasePiece(IntVector position, uint team, Direction orientation,
        bool hasMoved, bool isKing, bool isCastler)
    {
        this.position    = position;
        this.orientation = orientation;
        this.team      = team;
        this.hasMoved  = hasMoved;
        this.isKing    = isKing;
        this.isCastler = isCastler;
    }

    // TO IMPLEMENT
    public abstract MoveSet GetMoves(Zone zone);

    // METHODS
    public void MoveTo(IntVector position, Direction rotation)
    {
        this.position = position;
        int v = (int)(orientation) + (int)(rotation);
        orientation = (Direction)((v % 4 + 4) % 4);
        hasMoved = true;
    }
    // OVERRIDES
    public override bool Equals(object o)
    {
        if (o is IntVector)      return position == (IntVector)o;
        else if (o is BasePiece) return position == ((BasePiece)o).Position;
        else if (o is Move)      return position == ((Move)o)     .Position;
        return false;
    }
    public abstract object Clone();
    public override int GetHashCode()
    { return position.GetHashCode(); }
    public override string ToString()
    {
        return GetType().Name 
            + "| team: "        + team 
            + "; position: "    + position 
            + "; orientation: " + orientation;
    }

    // OPERATORS
    public static bool operator ==(BasePiece piece, IntVector position)
    { return piece.position == position; }
    public static bool operator !=(BasePiece piece, IntVector position)
    { return piece.position != position; }
    public static bool operator ==(BasePiece piece, Move move)
    { return piece.position == move.Position; }
    public static bool operator !=(BasePiece piece, Move move)
    { return piece.position != move.Position; }
    public static bool operator ==(BasePiece piece1, BasePiece piece2)
    {
        return piece1.position    == piece2.Position 
            && piece1.orientation == piece2.orientation
            && piece1.team        == piece2.team;
    }
    public static bool operator !=(BasePiece piece1, BasePiece piece2)
    { return !(piece1 == piece2); }

    // HELPERS
    protected MoveSet LeaperMoves(
        MoveSet moves, Zone zone, IntVector trajectory)
    {
        for (uint i = 0; i < 4; ++i)
        {
            // position and rotation of the move
            Direction rotation;
            IntVector position = zone.Retarget(
                this.position + trajectory, out rotation);

            if (zone.CheckPosition(position))
            {
                BasePiece piece = zone.FindPiece(position);
                if (((System.Object)piece == null) || (team != piece.team))
                    moves.Add(new Move(position, rotation));
            }
            trajectory <<= 1; // rotate
        }
        return moves;
    }
    protected MoveSet RiderMoves(
        MoveSet moves, Zone zone, IntVector trajectory)
    {
        for (uint i = 0; i < 4; ++i)
        {
            // position and rotation of the move
            Direction rotation;
            IntVector position = zone.Retarget(
                this.position + trajectory, out rotation);

            // the trajectory the piece will follow
            IntVector traject = trajectory << (int)rotation;

            while (zone.CheckPosition(position))
            {
                BasePiece piece = zone.FindPiece(position);
                position = zone.Retarget(position + traject, out rotation);
                traject <<= (int)rotation;
                if ((System.Object)piece == null)
                    moves.Add(new Move(position, rotation));
                else
                {
                    if (team != piece.team)
                        moves.Add(new Move(position, rotation));
                    break; // Enemy or Ally -> stop loop
                }
            }
            trajectory <<= 1; // rotate
        }
        return moves;
    }
    protected MoveSet HopperMoves(
        MoveSet moves, Zone zone, IntVector trajectory)
    {
        for (uint i = 0; i < 4; ++i)
        {
            // position and rotation of the move
            Direction rotation;
            IntVector position = zone.Retarget(
                this.position + trajectory, out rotation);

            // the trajectory the piece will follow
            IntVector traject = trajectory << (int)rotation;

            while (zone.CheckPosition(position))
            {
                BasePiece piece = zone.FindPiece(position);
                position = zone.Retarget(position + traject, out rotation);
                traject <<= (int)rotation;
                if ((System.Object)piece != null) break;
            }
            if (zone.CheckPosition(position))
            {
                BasePiece piece = zone.FindPiece(position);
                if ((System.Object)piece == null || Team != piece.Team)
                    moves.Add(new Move(position, rotation));
            }

        }
        return moves;
    }
}
