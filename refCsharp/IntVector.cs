public enum Direction
{
    // orientation
    East   = 0,
    North  = 1,
    West   = 2,
    South  = 3,
    // rotation
    Deg0   = 0,
    Deg90  = 1,
    Deg180 = 2,
    Deg270 = 3
}

public struct IntVector
{
    // PROPERTIES
    public int x, y;

    // CONSTRUCTORS
    public IntVector(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    // METHODS
    public IntVector Inverse()
    { return new IntVector(-x, -y); }
    public IntVector Add(IntVector v)
    { return new IntVector(x + v.x, y + v.y); }
    public IntVector Add(int n)
    { return new IntVector(x + n, y + n); }
    public IntVector Subtract(IntVector v)
    { return new IntVector(x - v.x, y - v.y); }
    public IntVector Subtract(int n)
    { return Add(-n); }
    public IntVector Multiply(int n)
    { return new IntVector(x * n, y * n); }
    public IntVector Divide(int n)
    { return new IntVector(x / n, y / n); }
    public IntVector Modulo(int n)
    { return new IntVector(x % n, y % n); }
    public IntVector Rotate(Direction rot)
    { return Rotate((int) rot); }
    public IntVector Rotate(int rot)
    {
        rot = ((rot % 4) + 4) % 4;
        switch (rot)
        {
            case 1: return new IntVector(-y, x);
            case 2: return Inverse();
            case 3: return new IntVector(y, -x);
        }
        return this;
    }
    public IntVector MirrorX()
    { return new IntVector(-x, y); }
    public IntVector MirrorY()
    { return new IntVector(x, -y); }

    // OVERRIDES
    public override bool Equals(object o)
    {
        if (o is IntVector)
        {
            IntVector v = (IntVector)o;
            return x == v.x && y == v.y;
        }
        return false;
    }
    public override int GetHashCode()
    {
        short
            x = (short) this.x,
            y = (short) this.y;
        return (x & 0xffff) | ((y & 0xffff)<<16);
    }
    public override string ToString()
    { return "x: " + x + ", y: " + y; }

    // OPERATORS
    // equals ==
    public static bool operator ==(IntVector v1, IntVector v2)
    { return v1.Equals(v2); }
    public static bool operator !=(IntVector v1, IntVector v2)
    { return !v1.Equals(v2); }
    // plus +
    public static IntVector operator +(IntVector v)
    { return v; }
    public static IntVector operator +(IntVector v1, IntVector v2)
    { return v1.Add(v2); }
    public static IntVector operator +(IntVector v, int n)
    { return v.Add(n); }
    public static IntVector operator +(int n, IntVector v)
    { return v.Add(n); }
    // minus -
    public static IntVector operator -(IntVector v)
    { return v.Inverse(); }
    public static IntVector operator -(IntVector v1, IntVector v2)
    { return v1.Subtract(v2); }
    public static IntVector operator -(IntVector v, int n)
    { return v.Subtract(n); }
    public static IntVector operator -(int n, IntVector v)
    { return new IntVector(n - v.x, n - v.y); }
    // multiply *
    public static IntVector operator *(IntVector v, int n)
    { return v.Multiply(n); }
    public static IntVector operator /(IntVector v, int n)
    { return v.Divide(n); }
    public static IntVector operator %(IntVector v, int n)
    { return v.Modulo(n); }
    // shift << >>
    public static IntVector operator <<(IntVector v, int n)
    { return v.Rotate(n); }
    public static IntVector operator >>(IntVector v, int n)
    { return v.Rotate(-n); }
    // increment decrement ++ --
    public static IntVector operator ++(IntVector v)
    { return v.MirrorX(); }
    public static IntVector operator --(IntVector v)
    { return v.MirrorY(); }
}
