#pragma once


#include <apl/types/Callable.hpp>
#include <apl/Config.hpp>

// #include <apl/types/Value.hpp>
class Value;

// abstract
struct Arr : Value {

    Arr(std::vector<int> shape)
        : Value(shape)
    {}

    Arr(std::vector<int> shape, int ia)
        : Value(shape, ia, shape.size())
    {}

    Arr(std::vector<int> shape, int ia, int rank)
        : Value(shape, ia, rank)
    {}

    std::optional<std::string> string(bool quote) const;

    std::string toString();

    std::string oneliner(std::vector<int> where) const {
        auto qs = string(true);
        if (qs) return *qs;

        std::string res = where.size() == 0 ? "{" : "[";
        if (rank == 0) {
            return first()->oneliner();
        } else if (where.size() == rank - 1) {
            std::vector<int> pos(rank);
            pos.insert(std::begin(pos), std::begin(where), std::end(where));
            // System.arraycopy(where, 0, pos, 0, where.size());

            for (int i = 0; i < shape[where.size()]; i++) {
                pos[rank-1] = i;
                if (i != 0) res.append(", ");
                res.append(simpleAt(pos)->oneliner());
            }
        } else {
            // std::vector<int> pos = new int[where.size()+1];
            // System.arraycopy(where, 0, pos, 0, where.size());

            std::vector<int> pos(where.size() + 1);
            pos.insert(std::begin(pos), std::begin(where), std::end(where));

            for (int i = 0; i < shape[where.size()]; i++) {
                pos[where.size()] = i;
                if (i != 0) res.append(", ");
                res.append(oneliner(pos));
            }
        }
        return res + (where.size() == 0 ? "}" : "]");
    }

    Arr* reverseOn(int dim) {
        if (rank == 0) {
            if (dim != 0) {
                //TODO
                // throw new DomainError("rotating a scalar with a non-⎕IO axis", this);
                throw "rotating a scalar with a non-⎕IO axis";
            }
            return this;
        }
        if (dim < 0) dim+= rank;
        // 2×3×4:
        // 0 - 3×4s for 2
        // 1 - 4s for 3
        // 2 - 1s for 4
        int chunkS = 1;
        int cPSec = shape[dim]; // chunks per section
        for (int i = rank-1; i > dim; i--) {
            chunkS*= shape[i];
        }
        int sec = chunkS * cPSec; // section length
        std::vector<Value const*> res(ia);
        int c = 0;
        while (c < ia) {
            for (int i = 0; i < cPSec; i++) {
                for (int j = 0; j < chunkS; j++) {
                    res[c + (cPSec-i-1)*chunkS + j] = get(c + i*chunkS + j);
                }
            }
            c+= sec;
        }
        return Arr::create(res, shape);
    }

    static Value const* createL(std::vector<Value const*> v, std::vector<int> sh) { // accepts ⊂Primitive; doesn't attempt individual item squeezing; TODO check more places where this should be used
        if (sh.size()==0 && instanceof<Primitive>(v[0]) && ! Config::enclosePrimitives) {
            return v[0];
        }
        return create(v, sh);
    }

    // static Arr create(std::vector<Value> v) {
    //     return create(v, new int[]{v.size()});
    // }

    // static Arr create(std::vector<Value> v, std::vector<int> sh) { // note, doesn't attempt individual item squeezing
    //     if (v.size() == 0) return new EmptyArr(sh, nullptr);

    //     if (v[0] instanceof Num) {
    //         double[] da = new double[v.size()];
    //         for (int i = 0; i < v.size(); i++) {
    //             if (v[i] instanceof Num) da[i] = ((Num)v[i]).num;
    //             else {
    //                 da = nullptr;
    //                 break;
    //             }
    //         }
    //         if (da != nullptr) return new DoubleArr(da, sh);
    //     }

    //     if (instanceof<Char>(v[0])) {
    //         std::string s;
    //         for (Value aV : v) {
    //             if (instanceof<Char>(aV)) {
    //                 s.append(((Char) aV).chr);
    //             } else {
    //                 s = nullptr;
    //                 break;
    //             }
    //         }
    //         if (s != nullptr) return new ChrArr(s.toString(), sh);
    //     }
    //     return new HArr(v, sh);
    // }

    static Arr* create(std::vector<Value const*> v) {
        // return create(v, new int[]{v.size()});

        std::vector<int> tmp;
        tmp.push_back(v.size());
        return create(v, tmp);
    }

    static Arr* create(std::vector<Value const*> v, std::vector<int> sh);

    //TODO
    // virtual bool equals(Obj o) const override {
    //     if (!(o instanceof Arr)) return false;
    //     Arr a = (Arr) o;
    //     if (!Arrays.equals(shape, a.shape)) return false;
    //     if (hash!=0 && a.hash!=0 && hash != a.hash) return false;
    //     std::vector<Value> mvs = values();
    //     std::vector<Value> ovs = a.values();
    //     for (int i = 0; i < mvs.size(); i++) {
    //       if (!mvs[i].equals(ovs[i])) return false;
    //     }
    //     return true;
    // }

    // virtual int hashCode() override {
    //     if (hash == 0) {
    //       for (Value v : this) hash = hash*31 + v.hashCode();
    //       hash = shapeHash(hash);
    //     }
    //     return hash;
    // }

    static int prod(std::vector<int> ia) {
        int r = 1;
        for (int i : ia) r*= i;
        return r;
    }

    static void eqShapes(Value a, Value w) {
        std::vector<int> as = a.shape;
        std::vector<int> ws = w.shape;
        if (as.size() != ws.size()) {
            //TODO
            // throw new RankError("ranks don't equal (shapes: " + Main.formatAPL(as) + " vs " + Main.formatAPL(ws) + ")", w);
            throw "ranks don't equal (shapes: ... vs ...)";
        }
        for (int i = 0; i < as.size(); i++) {
            if (as[i] != ws[i]) {
                //TODO
                // throw new LengthError("shapes don't match (" + Main.formatAPL(as) + " vs " + Main.formatAPL(ws) + ")", w);
                throw "shapes don't match (... vs ...)";
            }
        }
    }

    static void eqShapes(std::vector<int> a, std::vector<int> w, Callable blame) {
      if (a.size() != w.size()) {
          //TODO
          // throw new RankError("ranks don't equal (shapes: " + Main.formatAPL(a) + " vs " + Main.formatAPL(w) + ")", blame);
          throw "ranks don't equal (shapes: ... vs ...)";
      }
      for (int i = 0; i < a.size(); i++) {
          if (a[i] != w[i]) {
              //TODO
              // throw new LengthError("shapes don't match (" + Main.formatAPL(a) + " vs " + Main.formatAPL(w) + ")", blame);
              throw "shapes don't match (... vs ...)";
          }
      }
    }

protected:
    int shapeHash(int hash) {
        int h = 0;
        for (int i : shape) {
          h = h*31 + i;
        }
        int res = hash*113 + h;
        if (res == 0) return 100003;
        return res;
    }

    int hash;
};

#include <apl/types/Char.hpp>

std::optional<std::string> Arr::string(bool quote) const {
    if (rank == 1/* && shape[0] != 1*/) { // strings
        std::string all;
        for (Value const* v : *this) {

            // if (instanceof<Char>(v)) {

            Char const* vc = dynamic_cast<Char const*>(v);
            if (vc != nullptr) {
                char c = vc->chr;
                if (quote && c == '\"') {
                    all.append("\"\"");
                } else {
                    all.push_back(c);
                }
            } else {
                return std::nullopt;
            }
        }
        if (quote) {
            return "\"" + all + "\"";
        }
        return all;
    }
    return std::nullopt;
}

std::string Arr::toString() {
    if (ia == 0) {
      std::string mr = instanceof<Char>(safePrototype()) ? "''" : "⍬";
      if (rank == 1) return mr;
      else {
          std::string s = Main.formatAPL(shape);
          return s + "⍴" + mr;
      }
    }
    std::string qs = string(Config::quotestrings || Config::noBoxing);
    if (qs != nullptr) return qs;
    if (Config::noBoxing) {
        if (rank == 0) return "⊂" + oneliner();
        return oneliner();
    } else {
        if (rank == 0) return "⊂" + first()->toString().replace("\n", "\n ");
        if (ia==1) {
          Value c = get(0);
          if (instanceof<Primitive>(c) || rank > 2) {
            if (rank==1) return "⍮"+c;
            std::string pre = Main.formatAPL(shape);
            return pre + "⍴⊂" + c.toString().replace("\n", "\n" + Main.repeat(" ", pre.size()+2));
          }
      }

      if (rank == 1) { // simple vectors
        std::string res;
        auto simple = true;
        for (Value v : this) {
          if (res.size() > 0) res.append(" ");
          if (v == nullptr) {
            res.append("NULLPTR");
          } else {
            simple &= instanceof<Primitive>(v);
            res.append(v.toString());
          }
        }
        if (simple) return res.toString();
      }

      if (rank == 2) {
          bool charmat = true;
          if ( ! instanceof<ChrArr>(this)) {
              for (Value v : this) {
                  if ( ! instanceof<Char>(v)) {
                      charmat = false;
                      break;
                  }
              }
          }

          if (charmat) {
              std::string b;
              int i = 0;
              for (Value v : this) {
                  if (i++ % shape[1] == 0 && i!=1) b.append('\n');
                  b.append(((Char) v).chr);
              }
              return b;
          }
      }

      if (rank < 3) { // boxed arrays
          int w = rank==1? shape[0] : shape[1];
          int h = rank==1? 1 : shape[0];
          std::string[][][] stringified = new std::string[w][h][];
          int[][] itemWidths = new int[w][h];
          std::vector<int> widths = new int[w];
          std::vector<int> heights = new int[h];
          auto simple = true;
          int x=0, y=0;
          for (Value v : this) {
            if (v == nullptr) v = Main.toAPL("NULLPTR");
            simple &= instanceof<Primitive>(v);
            auto c = v.toString().split("\n");
            auto cw = 0;
            for (auto ln : c) {
              cw = Math.max(ln.size(), cw);
            }
            itemWidths[x][y] = cw;
            widths[x] = Math.max(widths[x], cw);
            heights[y] = Math.max(heights[y], c.size());
            stringified[x][y] = c;
            x++;
            if (x==w) {
              x = 0;
              y++;
            }
        }

        int borderSize = simple? 0 : 1;
        int rw = simple? -1 : 1,
        rh = borderSize ; // result w&h;
        for (x = 0; x < w; x++) rw+= widths[x]+1;
        for (y = 0; y < h; y++) rh+= heights[y]+borderSize;
        char[][] chars = new char[rh][rw];
        int rx = borderSize , ry; // x&y in chars
        for (x = 0; x < w; x++) {
          ry = borderSize;
          for (y = 0; y < h; y++) {
            std::string[] cobj = stringified[x][y];
            for (int cy = 0; cy < cobj.size(); cy++) {
              std::string s = cobj[cy];
              char[] line = s.toCharArray();
              int sx = instanceof<Num>(get(y*w + x)) ? rx+widths[x]-itemWidths[x][y] : rx;
              System.arraycopy(line, 0, chars[ry + cy], sx, line.size());
            }
            ry+= heights[y]+borderSize;
          }
          rx+= widths[x]+1;
        }

        if (!simple) { // draw borders
          rx = 0;
          for (x = 0; x < w; x++) {
            ry = 0;
            for (y = 0; y < h; y++) {
              chars[ry][rx] = '┼';
              for (int cx = 1; cx <=  widths[x]; cx++) chars[ry][rx+cx] = '─';
              for (int cy = 1; cy <= heights[y]; cy++) chars[ry+cy][rx] = '│';
              if (x == 0) {
                for (int cy = 1; cy <= heights[y]; cy++) chars[ry+cy][rw-1] = '│';
                chars[ry][rw-1] = y==0? '┐' : '┤';
                chars[ry][0] = '├';
              }
              ry+= heights[y]+borderSize;
            }
            chars[0][rx] = '┬';
            chars[rh-1][rx] = x==0?'└' : '┴';
            for (int cx = 1; cx <=  widths[x]; cx++) chars[rh-1][rx+cx] = '─';
            rx+= widths[x]+1;
          }
          chars[0][0] = '┌';
          chars[rh-1][rw-1] = '┘';
        }

        for (char[] ca : chars) {
          for (int i = 0; i < ca.size(); i++) {
            if (ca[i] == 0) ca[i] = ' ';
          }
        }

        std::string res;
        bool next = false;
        for (char[] ln : chars) {
            if (next) res.append('\n');
            res.append(ln);
            next = true;
        }
        return res;
      } else return oneliner();
    }
}

static Arr* Arr::create(std::vector<Value> v, std::vector<int> sh) { // note, doesn't attempt individual item squeezing
    if (v.size() == 0) return new EmptyArr(sh, nullptr);
    Value f = v.get(0);
    if (f instanceof Num) {
      double[] da = new double[v.size()];
      for (int i = 0; i < v.size(); i++) {
        if (v.get(i) instanceof Num) da[i] = ((Num) v.get(i)).num;
        else {
          da = nullptr;
          break;
        }
      }
      if (da != nullptr) return new DoubleArr(da, sh);
    }
    if (f instanceof Char) {
      std::string s;
      for (Value aV : v) {
        if (aV instanceof Char) s.append(((Char) aV).chr);
        else {
          s = nullptr;
          break;
        }
      }
      if (s != nullptr) return new ChrArr(s.toString(), sh);
    }
    return new HArr(v, sh);
}







// public abstract class Arr extends Value {
//   public Arr(int[] shape) {
//     super(shape);
//   }
//   public Arr(int[] shape, int ia) {
//     super(shape, ia, shape.length);
//   }
//   public Arr(int[] shape, int ia, int rank) {
//     super(shape, ia, rank);
//   }

//   public std::string string(bool quote) {
//     if (rank == 1/* && shape[0] != 1*/) { // strings
//       StringBuilder all = new StringBuilder();
//       for (Value v : this) {
//         if (v instanceof Char) {
//           char c = ((Char) v).chr;
//           if (quote && c == '\"') all.append("\"\"");
//           else all.append(c);
//         } else return null;
//       }
//       if (quote)
//         return "\"" + all + "\"";
//       else return all.toString();
//     }
//     return null;
//   }
//   public std::string toString() {
//     if (ia == 0) {
//       std::string mr = safePrototype() instanceof Char? "''" : "⍬";
//       if (rank == 1) return mr;
//       else {
//         std::string s = Main.formatAPL(shape);
//         return s + "⍴" + mr;
//       }
//     }
//     std::string qs = string(Config::quotestrings || Config::noBoxing);
//     if (qs != null) return qs;
//     if (Config::noBoxing) {
//       if (rank == 0) return "⊂" + oneliner();
//       return oneliner();
//     } else {
//       if (rank == 0) return "⊂"+first().toString().replace("\n", "\n ");
//       if (ia==1) {
//         Value c = get(0);
//         if (c instanceof Primitive || rank > 2) {
//           if (rank==1) return "⍮"+c;
//           std::string pre = Main.formatAPL(shape);
//           return pre + "⍴⊂" + c.toString().replace("\n", "\n" + Main.repeat(" ", pre.length()+2));
//         }
//       }
//       if (rank == 1) { // simple vectors
//         StringBuilder res = new StringBuilder();
//         auto simple = true;
//         for (Value v : this) {
//           if (res.length() > 0) res.append(" ");
//           if (v == null) {
//             res.append("NULLPTR");
//           } else {
//             simple &= v instanceof Primitive;
//             res.append(v.toString());
//           }
//         }
//         if (simple) return res.toString();
//       }

//       if (rank == 2) {
//         bool charmat = true;
//         if (!(this instanceof ChrArr)) {
//           for (Value v : this) {
//             if (!(v instanceof Char)) {
//               charmat = false;
//               break;
//             }
//           }
//         }

//         if (charmat) {
//           StringBuilder b = new StringBuilder();
//           int i = 0;
//           for (Value v : this) {
//             if (i++ % shape[1] == 0 && i!=1) b.append('\n');
//             b.append(((Char) v).chr);
//           }
//           return b.toString();
//         }
//       }

//       if (rank < 3) { // boxed arrays
//         int w = rank==1? shape[0] : shape[1];
//         int h = rank==1? 1 : shape[0];
//         std::string[][][] stringified = new std::string[w][h][];
//         int[][] itemWidths = new int[w][h];
//         int[] widths = new int[w];
//         int[] heights = new int[h];
//         auto simple = true;
//         int x=0, y=0;
//         for (Value v : this) {
//           if (v == null) v = Main.toAPL("NULLPTR");
//           simple &= v instanceof Primitive;
//           auto c = v.toString().split("\n");
//           auto cw = 0;
//           for (auto ln : c) {
//             cw = Math.max(ln.length(), cw);
//           }
//           itemWidths[x][y] = cw;
//           widths[x] = Math.max(widths[x], cw);
//           heights[y] = Math.max(heights[y], c.length);
//           stringified[x][y] = c;
//           x++;
//           if (x==w) {
//             x = 0;
//             y++;
//           }
//         }
//         int borderSize = simple? 0 : 1;
//         int rw = simple? -1 : 1,
//         rh = borderSize ; // result w&h;
//         for (x = 0; x < w; x++) rw+= widths[x]+1;
//         for (y = 0; y < h; y++) rh+= heights[y]+borderSize;
//         char[][] chars = new char[rh][rw];
//         int rx = borderSize , ry; // x&y in chars
//         for (x = 0; x < w; x++) {
//           ry = borderSize;
//           for (y = 0; y < h; y++) {
//             std::string[] cobj = stringified[x][y];
//             for (int cy = 0; cy < cobj.length; cy++) {
//               std::string s = cobj[cy];
//               char[] line = s.toCharArray();
//               int sx = get(y*w + x) instanceof Num? rx+widths[x]-itemWidths[x][y] : rx;
//               System.arraycopy(line, 0, chars[ry + cy], sx, line.length);
//             }
//             ry+= heights[y]+borderSize;
//           }
//           rx+= widths[x]+1;
//         }
//         if (!simple) { // draw borders
//           rx = 0;
//           for (x = 0; x < w; x++) {
//             ry = 0;
//             for (y = 0; y < h; y++) {
//               chars[ry][rx] = '┼';
//               for (int cx = 1; cx <=  widths[x]; cx++) chars[ry][rx+cx] = '─';
//               for (int cy = 1; cy <= heights[y]; cy++) chars[ry+cy][rx] = '│';
//               if (x == 0) {
//                 for (int cy = 1; cy <= heights[y]; cy++) chars[ry+cy][rw-1] = '│';
//                 chars[ry][rw-1] = y==0? '┐' : '┤';
//                 chars[ry][0] = '├';
//               }
//               ry+= heights[y]+borderSize;
//             }
//             chars[0][rx] = '┬';
//             chars[rh-1][rx] = x==0?'└' : '┴';
//             for (int cx = 1; cx <=  widths[x]; cx++) chars[rh-1][rx+cx] = '─';
//             rx+= widths[x]+1;
//           }
//           chars[0][0] = '┌';
//           chars[rh-1][rw-1] = '┘';
//         }
//         for (char[] ca : chars) {
//           for (int i = 0; i < ca.length; i++) {
//             if (ca[i] == 0) ca[i] = ' ';
//           }
//         }
//         StringBuilder res = new StringBuilder();
//         bool next = false;
//         for (char[] ln : chars) {
//           if (next) res.append('\n');
//           res.append(ln);
//           next = true;
//         }
//         return res.toString();
//       } else return oneliner();
//     }
//   }
//   public std::string oneliner(int[] where) {
//     auto qs = string(true);
//     if (qs != null) return qs;
//     StringBuilder res = new StringBuilder(where.length == 0 ? "{" : "[");
//     if (rank == 0) {
//       return first().oneliner();
//     } else if (where.length == rank-1) {
//       int[] pos = new int[rank];
//       System.arraycopy(where, 0, pos, 0, where.length);
//       for (int i = 0; i < shape[where.length]; i++) {
//         pos[rank-1] = i;
//         if (i != 0) res.append(", ");
//         res.append(simpleAt(pos).oneliner());
//       }
//     } else {
//       int[] pos = new int[where.length+1];
//       System.arraycopy(where, 0, pos, 0, where.length);
//       for (int i = 0; i < shape[where.length]; i++) {
//         pos[where.length] = i;
//         if (i != 0) res.append(", ");
//         res.append(oneliner(pos));
//       }
//     }
//     return res + (where.length==0?"}":"]");
//   }
//   public Arr reverseOn(int dim) {
//     if (rank == 0) {
//       if (dim != 0) throw new DomainError("rotating a scalar with a non-⎕IO axis", this);
//       return this;
//     }
//     if (dim < 0) dim+= rank;
//     // 2×3×4:
//     // 0 - 3×4s for 2
//     // 1 - 4s for 3
//     // 2 - 1s for 4
//     int chunkS = 1;
//     int cPSec = shape[dim]; // chunks per section
//     for (int i = rank-1; i > dim; i--) {
//       chunkS*= shape[i];
//     }
//     int sec = chunkS * cPSec; // section length
//     Value[] res = new Value[ia];
//     int c = 0;
//     while (c < ia) {
//       for (int i = 0; i < cPSec; i++) {
//         for (int j = 0; j < chunkS; j++) {
//           res[c + (cPSec-i-1)*chunkS + j] = get(c + i*chunkS + j);
//         }
//       }
//       c+= sec;
//     }
//     return Arr.create(res, shape);
//   }


//   public static Value createL(Value[] v, int[] sh) { // accepts ⊂Primitive; doesn't attempt individual item squeezing; TODO check more places where this should be used
//     if (sh.length==0 && v[0] instanceof Primitive && !Config::enclosePrimitives) return v[0];
//     return create(v, sh);
//   }

//   public static Arr create(Value[] v) {
//     return create(v, new int[]{v.length});
//   }
//   public static Arr create(Value[] v, int[] sh) { // note, doesn't attempt individual item squeezing
//     if (v.length == 0) return new EmptyArr(sh, null);
//     if (v[0] instanceof Num) {
//       double[] da = new double[v.length];
//       for (int i = 0; i < v.length; i++) {
//         if (v[i] instanceof Num) da[i] = ((Num)v[i]).num;
//         else {
//           da = null;
//           break;
//         }
//       }
//       if (da != null) return new DoubleArr(da, sh);
//     }
//     if (v[0] instanceof Char) {
//       StringBuilder s = new StringBuilder();
//       for (Value aV : v) {
//         if (aV instanceof Char) s.append(((Char) aV).chr);
//         else {
//           s = null;
//           break;
//         }
//       }
//       if (s != null) return new ChrArr(s.toString(), sh);
//     }
//     return new HArr(v, sh);
//   }

//   public static Arr create(std::vector<Value> v) {
//     return create(v, new int[]{v.size()});
//   }
//   public static Arr create(std::vector<Value> v, int[] sh) { // note, doesn't attempt individual item squeezing
//     if (v.size() == 0) return new EmptyArr(sh, null);
//     Value f = v.get(0);
//     if (f instanceof Num) {
//       double[] da = new double[v.size()];
//       for (int i = 0; i < v.size(); i++) {
//         if (v.get(i) instanceof Num) da[i] = ((Num) v.get(i)).num;
//         else {
//           da = null;
//           break;
//         }
//       }
//       if (da != null) return new DoubleArr(da, sh);
//     }
//     if (f instanceof Char) {
//       StringBuilder s = new StringBuilder();
//       for (Value aV : v) {
//         if (aV instanceof Char) s.append(((Char) aV).chr);
//         else {
//           s = null;
//           break;
//         }
//       }
//       if (s != null) return new ChrArr(s.toString(), sh);
//     }
//     return new HArr(v, sh);
//   }

//   @Override
//   public bool equals(Obj o) {
//     if (!(o instanceof Arr)) return false;
//     Arr a = (Arr) o;
//     if (!Arrays.equals(shape, a.shape)) return false;
//     if (hash!=0 && a.hash!=0 && hash != a.hash) return false;
//     Value[] mvs = values();
//     Value[] ovs = a.values();
//     for (int i = 0; i < mvs.length; i++) {
//       if (!mvs[i].equals(ovs[i])) return false;
//     }
//     return true;
//   }
//   protected int hash;
//   @Override
//   public int hashCode() {
//     if (hash == 0) {
//       for (Value v : this) hash = hash*31 + v.hashCode();
//       hash = shapeHash(hash);
//     }
//     return hash;
//   }

//   protected int shapeHash(int hash) {
//     int h = 0;
//     for (int i : shape) {
//       h = h*31 + i;
//     }
//     int res = hash*113 + h;
//     if (res == 0) return 100003;
//     return res;
//   }

//   public static int prod(int[] ia) {
//     int r = 1;
//     for (int i : ia) r*= i;
//     return r;
//   }

//   public static void eqShapes(Value a, Value w) {
//     int[] as = a.shape;
//     int[] ws = w.shape;
//     if (as.length != ws.length) throw new RankError("ranks don't equal (shapes: " + Main.formatAPL(as) + " vs " + Main.formatAPL(ws) + ")", w);
//     for (int i = 0; i < as.length; i++) {
//       if (as[i] != ws[i]) throw new LengthError("shapes don't match (" + Main.formatAPL(as) + " vs " + Main.formatAPL(ws) + ")", w);
//     }
//   }
//   public static void eqShapes(int[] a, int[] w, Callable blame) {
//     if (a.length != w.length) throw new RankError("ranks don't equal (shapes: " + Main.formatAPL(a) + " vs " + Main.formatAPL(w) + ")", blame);
//     for (int i = 0; i < a.length; i++) {
//       if (a[i] != w[i]) throw new LengthError("shapes don't match (" + Main.formatAPL(a) + " vs " + Main.formatAPL(w) + ")", blame);
//     }
//   }
// }