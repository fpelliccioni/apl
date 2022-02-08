class APLGraphics extends SimpleMap {
  PGraphics g;
  void setv(String k, Obj v) {
    String s = k.toLowerCase();
    if (g == null) throw new DomainError(this == mainGraphics? "Make P5.G calls in P5.setup/draw" : "object not yet initialized");
    switch (s) {
      
      case "fill":
        if (((Value) v).ia == 0) g.noFill();
        else g.fill(col(v));
      return;
      case "stroke":
        if (((Value) v).ia == 0) g.noStroke();
        else g.stroke(col(v));
      return;
      case "textsize": g.textSize(w.asInt()); return;
      default: throw new DomainError("setting non-existing key "+s+" for Graphics");
    }
  }
  Obj getv(String k) {
    String s = k.toLowerCase();
    if (g == null) throw new DomainError(this == mainGraphics? "Make P5.G calls in P5.setup/draw" : "object not yet initialized");
    switch (s) {
      case "background": case "bg": return new Fun() {
        public Value call(Value w) {
          g.background(col(w));
          return w;
        }
        public String repr() {return "P5.G.bg"; }
      };
      case "text": return new Fun() {
        public Value call(Value a, Value w) {
          XY p = new XY(a);
          g.text(w.asString(), (float)p.x, (float)p.y);
          return w;
        }
        public String repr() {return "P5.G.text"; }
      };
      case "textalign": case "ta": return new Fun() {
        public Value call(Value w) {
          String hs = w.asString();
          Integer h = hs.equals("center")? (Integer)CENTER : hs.equals("left")? (Integer)LEFT : hs.equals("right")? (Integer)RIGHT : null;
          if (h == null) throw new DomainError("textAlign with invalid horizontal align", w);
          g.textAlign(h);
          return w;
        }
        public Value call(Value a, Value w) {
          String hs = w.asString();
          Integer h = hs.equals("center")? (Integer)CENTER : hs.equals("left")? (Integer)LEFT : hs.equals("right")? (Integer)RIGHT : null;
          if (h == null) throw new DomainError("textAlign with invalid horizontal align "+hs, w);
          String vs = a.asString();
          Integer v = vs.equals("center")? (Integer)CENTER : vs.equals("top")? (Integer)TOP : vs.equals("bottom")? (Integer)BOTTOM : null;
          if (v == null) throw new DomainError("textAlign with invalid vertical align "+vs, w);
          g.textAlign(h, v);
          return w;
        }
        public String repr() { return "P5.G.ta"; }
      };
      case "rect": return new ForFA() {
        public void setup(Value a) {
          if (a == null) {  g.rectMode(CORNERS); return; }
          switch(a.asString().toLowerCase()) { default: throw new DomainError("⍺ for G.rect can't be "+a);
            case  "corner": g.rectMode(CORNER ); break;
            case "corners": g.rectMode(CORNERS); break;
            case  "radius": g.rectMode(RADIUS ); break;
            case  "center": g.rectMode(CENTER ); break;
          }
        }
        public void draw(double[] fa) {
          if (fa.length >= 5) {
            g.fill((int)(long)fa[4]);
            if (fa.length >= 6) g.stroke((int)(long)fa[5]);
          }
          g.rect((float)fa[0], (float)fa[1], (float)fa[2], (float)fa[3]);
        }
      };
      case "ellipse": return new ForFA() {
        public void setup(Value a) {
          if (a == null) {  g.ellipseMode(CORNERS); return; }
          switch(a.asString().toLowerCase()) { default: throw new DomainError("⍺ for G.ellipse can't be "+a);
            case  "corner": g.ellipseMode(CORNER ); break;
            case "corners": g.ellipseMode(CORNERS); break;
            case  "radius": g.ellipseMode(RADIUS ); break;
            case  "center": g.ellipseMode(CENTER ); break;
          }
        }
        public void draw(double[] fa) {
          g.ellipse((float)fa[0], (float)fa[1], (float)fa[2], (float)fa[3]);
        }
      };
      case "circle": return new ForFA() {
        public void setup(Value a) {
          if (a == null) {  g.ellipseMode(RADIUS ); return; }
          switch(a.asString().toLowerCase()) { default: throw new DomainError("⍺ for G.circle can't be "+a);
            case  "radius": g.ellipseMode(RADIUS ); break;
            case  "center": g.ellipseMode(CENTER ); break;
          }}
        public void draw(double[] fa) {
          g.ellipse((float)fa[0], (float)fa[1], (float)fa[2], (float)fa[2]);
        }
      };
      case "point": case "pt": return new ForFA() {
        public void draw(double[] fa) {
          if ((fa.length&2) == 1) throw new DomainError("G.point recieved odd length array", w);
          if (fa.length >= 2) {
            g.beginShape(POINTS);
            for (int i = 0; i < fa.length; i+= 2) g.vertex((float)fa[i]+.5, (float)fa[i+1]+.5);
            g.endShape();
          }
        }
      };
      case "line": case "ln": return new ForFA() {
        public void setup(Value a) {
          g.strokeWeight(a == null? 1 : a.asInt());
          g.noFill();
        }
        public void draw(double[] fa) {
          if ((fa.length&2) == 1) throw new DomainError("G.line recieved odd length array", w);
          if (fa.length >= 4) {
            g.beginShape();
            for (int i = 0; i < fa.length; i+= 2) g.vertex((float)fa[i], (float)fa[i+1]);
            g.endShape();
          }
        }
      };
      case "loop": return new ForFA() {
        public void setup(Value a) {
          g.strokeWeight(a == null? 1 : a.asInt());
        }
        public void draw(double[] fa) {
          if ((fa.length&2) == 1) throw new DomainError("G.loop recieved odd length array", w);
          if (fa.length > 2) {
            g.beginShape();
            for (int i = 0; i < fa.length; i+= 2) g.vertex((float)fa[i], (float)fa[i+1]);
            g.endShape(CLOSE);
          }
        }
      };
      case "img": case "image": return new Fun() {
        public Value call(Value a, Value w) {
          float[] fa = f1D(a);
          PImage img = ((APLImg) w).img;
          if (fa.length == 2) g.image(img, fa[0], fa[1]);
          else if (fa.length == 3) {
            g.imageMode(CORNER);
            g.image(img, fa[0], fa[1], fa[2]*img.width, fa[2]*img.height);
          }
          else if (fa.length == 4) {
            g.imageMode(CORNERS);
            g.image(img, fa[0], fa[1], fa[2], fa[3]);
          }
          return w;
        }
        public String repr() {return "P5.G.img"; }
      };
      default: return NULL;
    }
  }
  String toString() { return "G"; }
}
