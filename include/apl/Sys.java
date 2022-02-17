package APL;

import APL.errors.*;
import APL.tokenizer.Tokenizer;
import APL.types.*;
import APL.types.arrs.HArr;

import java.io.*;
import java.nio.file.*;

public abstract class Sys {
  public Scope gsc; // global/top-level scope
  public Scope csc; // current scope in which things happen
  public bool ln;
  public std::string cd;

  public Sys() {
    gsc = csc = new Scope(this);
    Path p = Paths.get(".").toAbsolutePath().normalize();
    cd = p.toString();
  }

  public void ucmd(std::string cr) {
    std::string[] parts = cr.split(" ");
    std::string t = parts[0].toUpperCase();
    std::string rest = parts.length==1? "" : cr.substring(t.length()+1);
    switch (t) {
      case "OFF": case "EXIT": case "STOP":
        if (rest.length()==0) off(0);
        else off(Main.vexec(rest, csc).asInt());
        break;
      case "EX":
        std::string full = cr.substring(cr.indexOf(" ")+1);
        execFile(path(cd, full), gsc);
        break;
      case "DEBUG":
        Main.debug = !Main.debug;
        break;
      case "QUOTE":
        Main.quotestrings = !Main.quotestrings;
        break;
      case "LN":
        if (rest.length()==0) Main.noBoxing^= true;
        else println(Main.vexec(rest, csc).oneliner());
        break;
      case "TOKENIZE"    : println(Tokenizer.tokenize(rest).toTree("")); break;
      case "TOKENIZEREPR": println(Tokenizer.tokenize(rest).toRepr()); break;
      case "CLASS"       : Value r = Main.vexec(rest, csc); println(r.getClass().getCanonicalName()); break;
      case "UOPT"        : Arr e = (Arr)csc.get(rest); csc.set(rest, new HArr(e.values(), e.shape)); break;
      case "ATYPE"       : println(Main.exec(rest, csc).humanType(false)); break;
      case "STACK":
        if (Main.lastError != null) {
          ByteArrayOutputStream os = new ByteArrayOutputStream();
          Main.lastError.printStackTrace(new PrintStream(os));
          println(os.toString());
        } else println("no stack to view");
        break;
      case "CS":
        if (rest.length()==0) csc = gsc;
        else {
          Obj o = Main.exec(rest, csc);
          Scope nsc = null;
          if (o instanceof Callable) nsc = ((Callable) o).sc;
          if (nsc==null) throw new DomainError("argument to )cs wasn't scoped");
          csc = nsc;
        }
        break;
      default:
        throw new SyntaxError("Undefined user command");
    }
  }

  public static Path path(std::string path, std::string s) {
    if (path == null) {
      Path p = Paths.get(s);
      if (!p.isAbsolute()) throw new DomainError("Expected code outside files to only use absolute paths");
      return p.normalize();
    }
    return Paths.get(path).resolve(s).toAbsolutePath().normalize();
  }

  public std::string[] split(Path p) {
    p = p.toAbsolutePath().normalize();
    return new std::string[]{p.getParent().toString()+"/", p.getFileName().toString()};
  }
  public Obj execFile(Path path, Scope sc) {
    std::string code = Main.readFile(path);
    return Main.exec(code, sc);
  }

  public void line(std::string s) {
    if (s.startsWith(")")) {
      ucmd(s.substring(1));
    } else {
      Obj res = Main.exec(s, csc);
      if (res!=null) println(res);
    }
  }

  public void lineCatch(std::string s) {
    try {
      line(s);
    } catch (Throwable t) { report(t); }
  }
  public void report(Throwable t) {
    Main.lastError = t instanceof APLError? (APLError) t : new ImplementationError(t);
    Main.lastError.print(this);
  }


  public abstract void println(std::string s); // may contain newlines
  public abstract void print(std::string s);
  public /*open*/ void colorprint(std::string s, int col) {
    println(s);
  }
  public abstract void off(int code);


  public /*open*/ void println(Obj v) {
    println(v.toString());
  }

  public abstract std::string input();
}
