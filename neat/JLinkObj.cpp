#include "JLinkObj.h"
#include "JLineObj.h"
#include "JInteger.h"
#include "JPObject.h"
#include "JFocusSet.h"

char* theJLinkObj = JLinkObj().Register();
void JLinkObj::writeContent(JOutputStream& os) {
  JViewObj::writeContent(os);
  putInteger(os, "from", (int)from);
  putInteger(os, "to", (int)to);
  putInteger(os, "fn", fn);
  putInteger(os, "tn", tn);
  putDouble(os, "pos", pos);
}

void JLinkObj::readContent(JDictionary& dict) {
  JViewObj::readContent(dict);
  from = (JModuleObj*)getInteger(dict, "from");
  to = (JModuleObj*)getInteger(dict, "to");
  fn = getInteger(dict, "fn");
  tn = getInteger(dict, "tn");
  pos = getDouble(dict, "pos");
}

const char* JLinkObj::className() const { return "JLinkObj";}
JObject* JLinkObj::clone() const { return new JLinkObj(*this);}
int JLinkObj::compareTo(const JObject& s) const {
  if (className() != s.className())
    return JObject::compareTo(s);
  JLinkObj &obj = *(JLinkObj*)&s;
  int result = from-obj.from;
  if (!result) result = to-obj.to;
  if (!result) result = fn-obj.fn;
  if (!result) result = tn-obj.tn;
  return result;
}

JLinkObj::JLinkObj() { from = to = null;}

JLinkObj::JLinkObj(JModuleObj* _from, int _fn, JModuleObj* _to, int _tn, double _pos) {
  from = _from;
  to = _to;
  fn = _fn;
  tn = _tn;
  pos = _pos;
  calculateExtent();
}

JString JLinkObj::info() {
  return JString(className()+1)+":"+
    (from->className()+1)+
    "("+from->outputTagType(fn)+")-"+
    (to->className()+1)+
    "("+to->inputTagType(tn)+")";
}

JFPoint& JLinkObj::translate(double dx, double dy) { return *this;}

void JLinkObj::rescale(JFRect& info, double wscale, double hscale) {}

void JLinkObj::remove() {
  from->delOutput(fn, *this);
  to->delInput(tn, *this);
  JViewObj::remove();
}

void JLinkObj::addSelf() {
  from->addOutput(fn, *this);
  to->addInput(tn, *this);
  to->engine(tn, *this);
}

JFRect JLinkObj::calculateExtent() {
  double delta1 = min(from->height, from->width)/5;
  double delta2 = min(to->height, to->width)/5;
  int fromFace = from->outputFace(fn);
  int toFace = to->inputFace(tn);
  JFPoint p1 = from->outputPoint(fn, *this);
  JFPoint p2 = to->inputPoint(tn, *this);
  delAll();
  if ((fromFace == RIGHT) && (toFace == LEFT)) {
    if (p1.x < p2.x) {
      JFPoint mp((p1.x+p2.x)/2, p1.y);
      JFPoint np(mp.x, p2.y);
      JLineObj l1(p1, mp);
      JLineObj l2(mp, np);
      JLineObj l3(np, p2);
      add(l1);
      add(l2);
      add(l3); 
    } else {
      JFPoint k1, k2, k3, k4;
      if (*from && *to) {
        k1 = JFPoint(to->x+to->width+delta2, p1.y);
        if (p1.y < p2.y) 
	  k2 = JFPoint(k1.x, to->y+to->height+delta2);
        else k2 = JFPoint(k1.x, to->y-delta2);
      } else {
        k1 = JFPoint(p1.x+delta1, p1.y);
        if (p1.y < p2.y)
	  k2 = JFPoint(k1.x, (from->y+from->height+to->y)/2);
	else k2 = JFPoint(k1.x, (to->y+to->height+from->y)/2);
      }
      k3 = JFPoint(to->x-delta2, k2.y);
      k4 = JFPoint(k3.x, p2.y);
      JLineObj l1(p1, k1);
      JLineObj l2(k1, k2);
      JLineObj l3(k2, k3);
      JLineObj l4(k3, k4);
      JLineObj l5(k4, p2);
      add(l1);
      add(l2);
      add(l3);
      add(l4);
      add(l5);
    }
  } else if ((fromFace == RIGHT) && (toFace == TOP)) {
    if (p1.x < p2.x) {
      if (p1.y < p2.y) {
        JFPoint mp(p2.x, p1.y);
        JLineObj l1(p1, mp);
        JLineObj l2(mp, p2);
        add(l1);
        add(l2);
      } else if (*from && *to) {
	JFPoint k1, k2, k3;
        k1 = JFPoint(to->x+to->width+delta2, p1.y);
	k2 = JFPoint(k1.x, to->y-delta2);
	k3 = JFPoint(p2.x, k2.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
      } else if (p1.x < to->x) {
	JFPoint k1, k2, k3;
        k1 = JFPoint((p1.x+to->x)/2, p1.y);
	k2 = JFPoint(k1.x, to->y-delta2);
        k3 = JFPoint(p2.x, k2.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
      } else {
	JFPoint k1, k2, k3, k4, k5;
        k1 = JFPoint(p1.x+delta1, p1.y);
	k2 = JFPoint(k1.x, (to->y+to->height+from->y)/2);
        k3 = JFPoint(to->x-delta2, k2.y);
        k4 = JFPoint(k3.x, to->y-delta2);
        k5 = JFPoint(p2.x, k4.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, k4);
        JLineObj l5(k4, k5);
        JLineObj l6(k5, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
        add(l5);
        add(l6);
      }
    } else {
      JFPoint k1, k2, k3;
      k1 = JFPoint(p1.x+delta1, p1.y);
      if (p1.y < p2.y) 
	k2 = JFPoint(k1.x, (to->y+from->y+from->height)/2);
      else k2 = JFPoint(k1.x, to->y-delta2);
      k3 = JFPoint(p2.x, k2.y);
      JLineObj l1(p1, k1);
      JLineObj l2(k1, k2);
      JLineObj l3(k2, k3);
      JLineObj l4(k3, p2);
      add(l1);
      add(l2);
      add(l3);
      add(l4);
    }
  } else if ((fromFace == BOTTOM) && (toFace == TOP)) {
    if (p1.y < p2.y) {
      JFPoint mp(p1.x, (p1.y+p2.y)/2);
      JFPoint np(p2.x, mp.y);
      JLineObj l1(p1, mp);
      JLineObj l2(mp, np);
      JLineObj l3(np, p2);
      add(l1);
      add(l2);
      add(l3);
    } else {
      JFPoint k1, k2, k3, k4;
      k1 = JFPoint(p1.x, p1.y+delta1);
      if (*from && *to) {
        if (p1.x < p2.x) 
	  k2 = JFPoint(to->x+to->width+delta2, k1.y);
        else k2 = JFPoint(to->x-delta2, k1.y);
      } else {
        if (p1.x < p2.x)
	  k2 = JFPoint((from->x+from->width+to->x)/2, k1.y);
	else k2 = JFPoint((to->x+to->width+from->x)/2, k1.y);
      }
      k3 = JFPoint(k2.x, to->y-delta2);
      k4 = JFPoint(p2.x, k3.y);
      JLineObj l1(p1, k1);
      JLineObj l2(k1, k2);
      JLineObj l3(k2, k3);
      JLineObj l4(k3, k4);
      JLineObj l5(k4, p2);
      add(l1);
      add(l2);
      add(l3);
      add(l4);
      add(l5);
    }
  } else if ((fromFace == BOTTOM) && (toFace == LEFT)) {
    if (p1.y < p2.y) {
      if (p1.x < p2.x) {
        JFPoint mp(p1.x, p2.y);
        JLineObj l1(p1, mp);
        JLineObj l2(mp, p2);
        add(l1);
        add(l2);
      } else if (*from && *to) {
	JFPoint k1, k2, k3;
        k1 = JFPoint(p1.x, to->y+to->height+delta2);
	k2 = JFPoint(to->x-delta2, k1.y);
	k3 = JFPoint(k2.x, p2.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
      } else if (p1.y < to->y) {
	JFPoint k1, k2, k3;
        k1 = JFPoint(p1.x, (p1.y+to->y)/2);
	k2 = JFPoint(to->x-delta2, k1.y);
        k3 = JFPoint(k2.x, p2.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
      } else {
	JFPoint k1, k2, k3, k4, k5;
        k1 = JFPoint(p1.x, p1.y+delta1);
	k2 = JFPoint((to->x+to->width+from->x)/2, k1.y);
        k3 = JFPoint(k2.x, to->y-delta2);
        k4 = JFPoint(to->x-delta2, k3.y);
        k5 = JFPoint(k4.x, p2.y);
        JLineObj l1(p1, k1);
        JLineObj l2(k1, k2);
        JLineObj l3(k2, k3);
        JLineObj l4(k3, k4);
        JLineObj l5(k4, k5);
        JLineObj l6(k5, p2);
        add(l1);
        add(l2);
        add(l3);
        add(l4);
        add(l5);
        add(l6);
      }
    } else {
      JFPoint k1, k2, k3;
      k1 = JFPoint(p1.x, p1.y+delta1);
      if (p1.x < p2.x) 
	k2 = JFPoint((to->x+from->x+from->width)/2, k1.y);
      else k2 = JFPoint(to->x-delta2, k1.y);
      k3 = JFPoint(k2.x, p2.y);
      JLineObj l1(p1, k1);
      JLineObj l2(k1, k2);
      JLineObj l3(k2, k3);
      JLineObj l4(k3, p2);
      add(l1);
      add(l2);
      add(l3);
      add(l4);
    }
  }
  reshape(JViewSet::calculateExtent());
  return *this;
}

void JLinkObj::fixPointer(JDictionary& dict) {
  JObject *fobj = dict[JInteger((int)from)];
  JObject *tobj = dict[JInteger((int)to)];
  if (fobj && tobj) {
    from = (JModuleObj*)(JObject*)(*(JPObject*)fobj);
    to = (JModuleObj*)(JObject*)(*(JPObject*)tobj);
    addSelf();
  } else JViewObj::remove();
}

void JLinkObj::access(const JDataType& data) 
{ from->access(fn, *this, data);}
void JLinkObj::engine() { to->engine(tn, *this);}
boolean JLinkObj::cond() { return from->cond(fn, *this);}
