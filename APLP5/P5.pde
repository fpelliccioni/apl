Fun setup, draw, scroll, scrollU, scrollD, kp, mp, kr, mr;
class P5 extends SimpleMap {
  MouseButton lm, mm, rm;
  void setv(String k, Obj v) {
    String s = k.toLowerCase();
    switch (s) {
      // callbacks
      case "setup": setup = (Fun) v; break;
      case "draw" :  draw = (Fun) v; break;
      case "scroll"         : case "sc" : scroll  = (Fun) v; break;
      case "scrollup"       : case "scu": scrollU = (Fun) v; break;
      case "scrolldown"     : case "scd": scrollD = (Fun) v; break;
      case "keypress"       : case "kp" : kp      = (Fun) v; break;
      case "modpress"       : case "mp" : mp      = (Fun) v; break;
      case "keyrelease"     : case "kr" : kr      = (Fun) v; break;
      case "modrelease"     : case "mr" : mr      = (Fun) v; break;
      // settings
      case "fps": case "framerate": frameRate(((Value) v).asInt());
      case "smooth": smooth(((Value)v).asInt()); return;
      case "size": {
        XY p = new XY(v);
        thisobj.size((int)p.x, (int)p.y);
        break;
      }
      
      case "cursor": {
        if (((Value) v).ia == 0) {
          noCursor();
        } else if (((Value) v).get(0) instanceof Char) {
          String name = ((Value) v).asString();
          switch (name.toLowerCase()) {
            case "cross": cursor(CROSS); break;
            case "hand": cursor(HAND); break;
            case "arrow": cursor(ARROW); break;
            case "move": cursor(MOVE); break;
            case "text": cursor(TEXT); break;
            case "wait": cursor(WAIT); break;
          }
        } else if (v instanceof APLImg) {
          cursor(((APLImg)v).img);
        } else throw new DomainError("Can't set cursor to "+v);
        break;
      }
      default: throw new DomainError("setting non-existing key "+s+" for PS");
    }
  }
  Obj getv(String k) {
    String s = k.toLowerCase();
    switch (s) {
      case "g": return mainGraphics;
      case "size": return arr(width, height);
      
      case "dispsize":      case "ds": return Main.toAPL(new int[]{displayWidth, displayHeight});
      case "displaywidth":  case "dw": return new Num(displayWidth);
      case "displayheight": case "dh": return new Num(displayHeight);
      
      case   "w": case   "width": return w;
      case   "h": case  "height": return h;
      case  "mx": case  "mousex": return mx;
      case  "my": case  "mousey": return my;
      case "pmx": case "pmousex": return new Num(pmouseX);
      case "pmy": case "pmousey": return new Num(pmouseY);
      
      case  "mpos": case "mousepos" : return mpos;
      case "pmpos": case "pmousepos": return arr(pmouseX, pmouseY);
      
      case  "lm": case "leftmouse"  : return lm;
      case  "mm": case "middlemouse": return mm;
      case  "rm": case "rightmouse" : return rm;
      
      case "key": return new Char(key);
      case "fps": case "framerate": return new Num(frameRate);
      case "fc": case "framecount": return new Num(frameCount);
      case "scroll": return new Num(scrolled);
      case "color": case "col": return new Fun() {
        public Value call(Value w) {
          return new Num(col(w));
        }
        public String repr() {return "P5.bg"; }
      };
      case "exit": return new Fun() {
        public Value call(Value w) {
          System.exit(w.asInt());
          return null;
        }
        public String repr() {return "P5.exit"; }
      };
      case "noise": return new Fun() {
        public Value call(Value w) {
          double[] da = w.asDoubleArr();
          double res = 0;
          if (da.length == 1) res = noise((float)da[0]);
          if (da.length == 2) res = noise((float)da[0], (float)da[1]);
          if (da.length == 3) res = noise((float)da[0], (float)da[1], (float)da[2]);
          return new Num(res);
        }
        public String repr() {return "P5.noise"; }
      };
      // files
      
      case "bytes": return new Fun() {
        public Value call(Value w) {
          return APL(loadBytes(w.asString()));
        }
        public String repr() {return "P5.bytes"; }
      };
      case "lines": return new Fun() {
        public Value call(Value w) {
          return APL(loadStrings(w.asString()));
        }
        public String repr() {return "P5.lines"; }
      };
      case "image": case "img": return new Fun() {
        public Value call(Value w) {
          if (w.rank == 2) {
            int[] pixels = new int[w.ia];
            double[] wv = w.asDoubleArr();
            for (int i = 0; i < w.ia; i++) pixels[i] = (int)(long)wv[i];
            PImage img = createImage((int)w.shape[1], (int)w.shape[0], ARGB);
            img.pixels = pixels;
            img.updatePixels();
            return new APLImg(img);
          } else {
            return new APLImg(loadImage(w.asString()));
          }
        }
        public String repr() {return "P5.img"; }
      };
      case "lerp": return new Mop() {
        float p;
        @Override public Value call(Obj f, Value a, Value w, DerivedMop derv) {
          p = (float) ((Value) f).asDouble();
          return new Fn().rec(DNF, a, w);
        }
        class Fn extends Builtin {
          Value rec(DNf f, Value a, Value w) {
            return numD(f, a, w);
          }
          public String repr(){return "";}
        }
        DNf DNF = new DNf();
        class DNf extends Fun.D_NNeN {
          public double on(double a, double w) {
            int ai = (int) (long) a;
            int wi = (int) (long) w;
            return lerpColor(ai, wi, p);
          }
        }
        public String repr() {return "P5.lerp"; }
      };
      case "pressed": return new Fun() {
        public Value call(Value w) {
          return pressedKeys.contains(w.asString())? Num.ONE : Num.ZERO;
        }
        public String repr() {return "P5.lines"; }
      };
      default: return NULL;
    }
  }
  int size() {
    throw new SyntaxError("Getting size of the P5 object");
  }
  String toString() { return "P5"; }
}


Num mx, my;
Num w, h;
Arr mpos;
void draw() {
  mx = new Num(mouseX);
  my = new Num(mouseY);
  mpos = arr(mouseX, mouseY);
  w = new Num(width);
  h = new Num(height);
  p5.lm.draw();
  p5.mm.draw();
  p5.rm.draw();
  call(draw, mpos);
  scrolled = 0;
}
int scrolled;
void mouseWheel(MouseEvent e) {
  int c = -e.getCount();
  scrolled+= c;
  Num n = new Num(c);
  call(scroll, n);
  if (c > 0) call(scrollU, n);
  if (c < 0) call(scrollD, n);
}

Arr CTRL  = Main.toAPL("ctrl" );
Arr SHIFT = Main.toAPL("shift");
Arr ALT   = Main.toAPL("alt"  );
Arr ALTGR = Main.toAPL("altgr");
Arr MENU  = Main.toAPL("menu" );

//void keyPr


void keyPressed(KeyEvent e) {// println("press");
  keyHandle(e, key, kp, mp, true);
  keyCode = key = 0; // bad processing and your tendency to close the sketch :|
}
void keyReleased(KeyEvent e) {// println("release", kr, mr);
  keyHandle(e, key, kr, mr, false);
}
HashSet<String> pressedKeys = new HashSet();
void keyHandle(KeyEvent e, char key, Fun kp, Fun mp, boolean press) {
  if (e.getNative() instanceof java.awt.event.KeyEvent) {
    java.awt.event.KeyEvent ne = (java.awt.event.KeyEvent) e.getNative();
    String skey = java.awt.event.KeyEvent.getKeyText(e.getKeyCode());
    //println(key, +key, keyCode, skey);
    switch (skey) {
      case "Ctrl":         call(mp, CTRL ); return;
      case "Shift":        call(mp, SHIFT); return;
      case "Alt Graph":    call(mp, ALTGR); return;
      case "Alt":          call(mp, ALT  ); return;
      default:
        boolean shift = ne.isShiftDown();
        boolean ctrl = ne.isControlDown();
        boolean alt = ne.isAltDown();
        boolean meta = ne.isMetaDown();
        boolean altgr = ne.isAltGraphDown();
        Value v;
        if (key == 65535 || key == 127) {
          v = Main.toAPL(skey);
        } else {
          if (key < 32) {
            v = Main.toAPL(shift || skey.length() != 1? skey : skey.toLowerCase());
          } else {
            v = new ChrArr(String.valueOf(key));
          }
        }
        call(kp, arr(ctrl, shift, alt, altgr, meta), v);
        if (press) pressedKeys.add(v.asString());
        else pressedKeys.remove(v.asString());
    }
  }
}
