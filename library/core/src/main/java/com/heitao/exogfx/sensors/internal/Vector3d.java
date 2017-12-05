package com.google.vrtoolkit.cardboard.sensors.internal;

public class Vector3d {
    public float x;
    public float y;
    public float z;
    
    public Vector3d() {
        super();
    }
    
    public Vector3d(final float xx, final float yy, final float zz) {
        super();
        this.set(xx, yy, zz);
    }
    
    public void set(final float xx, final float yy, final float zz) {
        this.x = xx;
        this.y = yy;
        this.z = zz;
    }
    
    public void setComponent(final int i, final float val) {
        if (i == 0) {
            this.x = val;
        }
        else if (i == 1) {
            this.y = val;
        }
        else {
            this.z = val;
        }
    }
    
    public void setZero() {
        final float x = 0.0f;
        this.z = x;
        this.y = x;
        this.x = x;
    }
    
    public void set(final Vector3d other) {
        this.x = other.x;
        this.y = other.y;
        this.z = other.z;
    }
    
    public void scale(final float s) {
        this.x *= s;
        this.y *= s;
        this.z *= s;
    }
    
    public void normalize() {
        final float d = this.length();
        if (d != 0.0) {
            this.scale(1.0f / d);
        }
    }
    
    public static float dot(final Vector3d a, final Vector3d b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    
    public float length() {
        return (float)Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
    }
    
    public boolean sameValues(final Vector3d other) {
        return this.x == other.x && this.y == other.y && this.z == other.z;
    }
    
    public static void add(final Vector3d a, final Vector3d b, final Vector3d result) {
        result.set(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    
    public static void sub(final Vector3d a, final Vector3d b, final Vector3d result) {
        result.set(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    
    public static void cross(final Vector3d a, final Vector3d b, final Vector3d result) {
        result.set(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }
    
    public static void ortho(final Vector3d v, final Vector3d result) {
        int k = largestAbsComponent(v) - 1;
        if (k < 0) {
            k = 2;
        }
        result.setZero();
        result.setComponent(k, 1.0f);
        cross(v, result, result);
        result.normalize();
    }
    
    public static int largestAbsComponent(final Vector3d v) {
        final float xAbs = Math.abs(v.x);
        final float yAbs = Math.abs(v.y);
        final float zAbs = Math.abs(v.z);
        if (xAbs > yAbs) {
            if (xAbs > zAbs) {
                return 0;
            }
            return 2;
        }
        else {
            if (yAbs > zAbs) {
                return 1;
            }
            return 2;
        }
    }

    @Override
    public String toString() {
        final StringBuilder builder = new StringBuilder().append("{ ");
        builder.append(Float.toString(this.x));
        builder.append(", ");
        builder.append(Float.toString(this.y));
        builder.append(", ");
        builder.append(Float.toString(this.z));
        builder.append(" }");
        return builder.toString();
    }
}
