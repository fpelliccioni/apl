package APL.types;

import APL.Main;
import APL.types.arrs.ChrArr;


public class Char extends Primitive {
  public char chr;
  public static final Char[] ASCII;
  static {
    ASCII = new Char[128];
    for (int i = 0; i < 128; i++) {
      ASCII[i] = new Char((char) i);
    }
  }
  
  public static final Char SPACE = ASCII[' '];
  
  public Char(char c) {
    chr = c;
  }
  
  public static Char of(char c) {
    if (c < 128) return ASCII[c];
    return new Char(c);
  }
  
  public Char upper() {
    return Char.of(Character.toUpperCase(chr));
  }
  
  public Char lower() {
    return Char.of(Character.toLowerCase(chr));
  }
  
  public Char swap() {
    if (Character.isUpperCase(chr)) return lower();
    if (Character.isLowerCase(chr)) return upper();
    return Char.of(chr);
  }
  
  public int getCase() {
    return Character.isUpperCase(chr)? 1 : Character.isLowerCase(chr)? -1 : 0;
  }
  
  public String toString() {
    if (Main.quotestrings) return "'"+chr+"'";
    else return String.valueOf(chr);
  }
  public String oneliner(int[] ignored) {
    return "'"+chr+"'";
  }
  
  @Override
  public Value ofShape(int[] sh) {
    if (sh.length==0 && !Main.enclosePrimitives) return this;
    assert ia == Arr.prod(sh);
    return new ChrArr(Character.toString(chr), sh); // special because there's no quickCharArr
  }
  
  public int compareTo(Char v) {
    return Character.compare(chr, v.chr);
  }
  
  
  @Override public boolean equals(Obj c) {
    return c instanceof Char && chr == ((Char) c).chr;
  }
  
  public String asString() {
    return String.valueOf(chr);
  }
  
  @Override
  public int hashCode() {
    return chr;
  }
  
  public Value safePrototype() {
    return SPACE;
  }
}