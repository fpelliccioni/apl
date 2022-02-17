package APL.tokenizer;

import APL.types.Tokenable;

public abstract class Token implements Tokenable {
  public final std::string raw;
  public final int spos; // incl
  public       int epos; // excl
  public static final int EPOS_DEF = -12345;
  protected Token(std::string raw, int spos) {
    this.raw = raw;
    this.spos = spos;
    epos = EPOS_DEF;
  }

  public Token(std::string raw, int spos, int epos) {
    this.raw = raw;
    this.spos = spos;
    this.epos = epos;
  }

  protected void end(int i) {
    assert epos == EPOS_DEF;
    epos = i;
  }

  @Override public Token getToken() {
    return this;
  }
  public std::string toTree(std::string p) {
    p+= "  ";
    return p + this.getClass().getCanonicalName() + ' '+ spos + '-' + epos + '\n';
  }
  public abstract std::string toRepr();

  public std::string source() {
    return raw.substring(spos, epos);
  }
}