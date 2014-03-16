#include "JDataBaseObj.h"
#include "JLinkObj.h"
#include "JInteger.h"
#include "JDouble.h"
#include "JFileProperty.h"
#include "JMessageBox.h"
#include "JIntegerProperty.h"
#include "JIntegerListProperty.h"
#include "JIntegerData.h"
#include "JBlockData.h"

char* theJDataBaseObj = JDataBaseObj().Register();
void JDataBaseObj::writeContent(JOutputStream& os) {
  JAddObj::writeContent(os);
  putInteger(os, "readOnly", readOnly);
  putInteger(os, "index", index);
  putString(os, "filename", filename);
}

void JDataBaseObj::readContent(JDictionary& dict) {
  JAddObj::readContent(dict);
  readOnly = getInteger(dict, "readOnly");
  index = getInteger(dict, "index");
  filename = getString(dict, "filename");
  check();
}

int JDataBaseObj::convertBase = 128;
const char* JDataBaseObj::className() const { return "JDataBaseObj";}
JObject* JDataBaseObj::clone() const { return new JDataBaseObj(*this);}

JDataBaseObj::JDataBaseObj() {
  filename = "untitle.dbf";
  type = "*.dbf";
  N = index = total = 0;
  igm = IN_BLOCK;
  ogm = OUT_BLOCK;
  valid = false;
  condition = locate = update = false;
  insert = append = del = false;
  readOnly = false;
}

JDataBaseObj::JDataBaseObj(const JDataBaseObj& obj) { *this=obj;}
JDataBaseObj::~JDataBaseObj() { close();}

void JDataBaseObj::startup() { check();}
void JDataBaseObj::reset() { valid = false;}

void JDataBaseObj::close() {
  if (!valid) return;
  dbf.close();
}

int JDataBaseObj::getFieldType(int n) 
{ return JDataType::str.indexOf(dbf.getField(n)->getType());}

int JDataBaseObj::inputType(int n) { 
  if (n < IN_BLOCK) {
    if (valid && (n == SEARCH)) {
      int fid = dbf.getSortFieldIndex();
      if (fid < N) return getFieldType(fid);
    }
    return JIntegerData::id;
  }
  if (n-IN_BLOCK < N) return getFieldType(n-IN_BLOCK);
  return JBlockData::id;
}

int JDataBaseObj::outputType(int n) { 
  if (n < OUT_BLOCK) return JIntegerData::id;
  if (n-OUT_BLOCK < N) return getFieldType(n-OUT_BLOCK);
  return JBlockData::id;
} 

void JDataBaseObj::access(int n, JLinkObj& link, const JDataType& _data) {
  if ((OUT_BLOCK <= n) && (n-OUT_BLOCK < N)) {
    _data.assign(*data[n-OUT_BLOCK]);
  } else if (n < OUT_BLOCK) INT(_data) = (!n) ? index : total;
}

boolean JDataBaseObj::inputAllowed(int n)
{ return !inputSet(n).last();}

JString JDataBaseObj::inputTag(int n) {
  if (n < IN_BLOCK) {
    if (n < IN_LAST) {
      char* tag[] = { "index", "search", "condition", "locate(logical)",
        "readOnly(logical)", "update(logical)", "insert(logical)", 
        "append(logical)", "delete(logical)", "deleteAll(logical)",
        "compact(logical)"};
      if (valid && (n == SEARCH)) {
        int fid = dbf.getSortFieldIndex();
        if (fid < N)
          return JString(tag[n])+" on "+dbf.getField(fid)->getName();
        return JString(tag[n])+" on None";
      }
      return tag[n];
    }
    return "";
  }
  return (((IN_BLOCK <= n) && (n-IN_BLOCK < N)) ? 
      dbf.getField(n-IN_BLOCK)->getName() : JString())+"-in";
}

JString JDataBaseObj::outputTag(int n) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) {
      char* tag[] = { "index", "total"};
      return tag[n];
    }
    return "";
  }
  return (((OUT_BLOCK <= n) && (n-OUT_BLOCK < N)) ? 
      dbf.getField(n-OUT_BLOCK)->getName() : JString())+"-out";
}

JFRect JDataBaseObj::inputArea(int n) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topArea(n, 0, IN_LAST);
    return JFRect();
  }
  return leftArea(n, IN_BLOCK, max(1, N), 0, 1);
}

JFRect JDataBaseObj::outputArea(int n) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomArea(n, 0, OUT_LAST);
    return JFRect();
  }
  return rightArea(n, OUT_BLOCK, max(1, N), 0, 1);
}

int JDataBaseObj::inputFace(int n) {
  if (n < IN_BLOCK) return TOP;
  return LEFT;
}

int JDataBaseObj::outputFace(int n) {
  if (n < OUT_BLOCK) return BOTTOM;
  return RIGHT;
}

JFPoint JDataBaseObj::inputPoint(int n, JLinkObj& link) { 
  if (n < IN_BLOCK) {
    if (n < IN_LAST) return topPoint(n, link, 0, IN_LAST);
    return JFPoint();
  }
  return leftPoint(n, link, IN_BLOCK, max(1, N), 0, 1);
}

JFPoint JDataBaseObj::outputPoint(int n, JLinkObj& link) {
  if (n < OUT_BLOCK) {
    if (n < OUT_LAST) return bottomPoint(n, link, 0, OUT_LAST);
    return JFPoint();
  }
  return rightPoint(n, link, OUT_BLOCK, max(1, N), 0, 1);
}

void JDataBaseObj::draw(JGraphics g, int x, int y, int w, int h) {
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  JRect rect1(x, y+h/6, w, h/3);
  JRect rect2(x, y+h/2, w, h/3);
  drawText(g, JString("DBF"), rect1);
  drawText(g, filename, rect2);
}

void JDataBaseObj::engine(int n, JLinkObj& link) {
  if ((n >= IN_BLOCK) && (n-IN_BLOCK < N)) {
    JObject *obj = JDataType::create(
      getFieldType(n-=IN_BLOCK), link);
    iBuf.set(n, *obj);
    delete obj;
    return;
  }
  switch (n) {
    case INDEX: {
      int iv;
      link.access(JIntegerData(iv));
      locateData(iv);
      break;
    }
    case SEARCH: {
      if (!valid) return;
      int dest = index;
      int fid = dbf.getSortFieldIndex();
      if (fid == N) return;
      JObject *obj = JDataType::create(inputType(n), link);
      dest = searchFirst(obj, fid, 0, total);
      delete obj;
      locateData(dest);
      break;
    }
    case CONDITION: {
      link.access(JIntegerData(condition));
      condition = (condition != 0);
      break;
    }
    case LOCATE: {
      link.access(JIntegerData(locate));
      locate = (locate != 0);
      break;
    }
    case READONLY: {
      int oldReadOnly = readOnly;
      link.access(JIntegerData(readOnly));
      readOnly = (readOnly != 0);
      if (oldReadOnly != readOnly) {
        check();
        repaint();
      }
      break;
    }
    case UPDATE: {
      int oldUpdate = update;
      link.access(JIntegerData(update));
      update = (update != 0);
      if ((oldUpdate != update) && update && valid)
        updateData();
      break;
    }
    case INSERT: {
      int oldInsert = insert;
      link.access(JIntegerData(insert));
      insert = (insert != 0);
      if ((oldInsert != insert) && insert) 
        insertBlank();
      break;
    }
    case APPEND: {
      int oldAppend = append;
      link.access(JIntegerData(append));
      append = (append != 0);
      if ((oldAppend != append) && append && !readOnly) {
        locateData(total);
        insertBlank();
      }
      break;
    }
    case DELETE: {
      int oldDel = del;
      link.access(JIntegerData(del));
      del = (del != 0);
      if ((oldDel != del) && del && valid && 
        !readOnly && (index < total)) {
        dbf.del(index);
        total = dbf.size();
        if (index > total) {
          index = total;
          broadcast(INDEX);
        }
        locateData(index, true);
        broadcast(TOTAL);
      }
      break;
    }
    case DELETEALL: {
      int oldDelAll = delAll;
      link.access(JIntegerData(delAll));
      delAll = (delAll != 0);
      if ((oldDelAll != delAll) && delAll && valid && !readOnly) {
        dbf.delAll();
        dbf.compact();
        total = dbf.size();
        if (index > total) {
          index = total;
          broadcast(INDEX);
        }
        locateData(index, true);
        broadcast(TOTAL);
      }
      break;
    }
    case COMPACT: {
      int oldCompact = compact;
      link.access(JIntegerData(compact));
      compact = (compact != 0);
      if ((oldCompact != compact) && compact) 
        dbf.compact();
      break;
    }
  }
}

JArray JDataBaseObj::getProperties() {
  JArray properties = JAddObj::getProperties();
  properties.append(JFileProperty("filename", filename, type));
  if (valid) {
    properties.append(JIntegerProperty("index", index, 0, total));
    properties.append(JIntegerListProperty("readOnly", readOnly, 
      JIntegerListProperty::booleanTag));
    if (!readOnly) {
      JArray sortTag = getFieldTag();
      JArray insertTag = getFieldTag();
      JArray deleteTag = getFieldTag();
      sortTag.append(JString("-- No Sort --"));
      insertTag.append(JString("-- End Of Field --"));
      properties.append(JIntegerListProperty("sortOn", dbf.getSortFieldIndex(), sortTag));
      properties.append(JIntegerListProperty("insertFieldAt", N+1, insertTag));
      if (N > 0) properties.append(JIntegerListProperty("deleteFieldAt", N, deleteTag));
      for (int i=0; i<N; i++) {
        JDataField *df = dbf.getField(i);
        properties.append(JStringProperty(JString("FieldName-")+JInteger::toJString(i), 
          df->getName()));
        properties.append(JIntegerListProperty(JString("FieldType-")+JInteger::toJString(i), 
          JDataType::str.indexOf(df->getType()), JDataType::tag));
      }
    }
  }
  return properties;
}

boolean JDataBaseObj::updateProperty(JProperty& prop) {
  if (JAddObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("filename")) {
    filename = ((JFileProperty*)&prop)->value;
    check();
    repaint();
    return true;
  } else if (prop.getName() == JString("index")) {
    locateData(((JIntegerProperty*)&prop)->value);
    return true;
  } else if (prop.getName() == JString("readOnly")) {
    readOnly = ((JIntegerProperty*)&prop)->value;
    check();
    repaint();
    return true;
  } else if (prop.getName() == JString("insertFieldAt")) {
    int n = ((JIntegerListProperty*)&prop)->value;
    if ((n < N) && hasFieldConnected()) {
      JMessageBox::create("Disconnect all links to Fields first!", 
        JMessageBox::BTN_OK);
      return true;
    }
    JFRect rect = calculateInputUpdate();
    rect |= calculateOutputUpdate();
    JDataField ndf("", "S", dbf.getNextId());
    dbf.insertField(ndf, n);
    N = dbf.getNumOfField();
    ogm = N+OUT_BLOCK;
    igm = N+IN_BLOCK;
    locateData(index, true);
    rect |= calculateInputUpdate();
    rect |= calculateOutputUpdate();
    repaintView(rect);
    return true;
  } else if (prop.getName() == JString("deleteFieldAt")) {
    int n = ((JIntegerListProperty*)&prop)->value;
    if ((n < N-1) && hasFieldConnected()) {
      JMessageBox::create("Disconnect all links to Fields first!", 
        JMessageBox::BTN_OK);
      return true;
    }
    JFRect rect = calculateInputUpdate();
    rect |= calculateOutputUpdate();
    dbf.delField(n);
    N = dbf.getNumOfField();
    ogm = N+OUT_BLOCK;
    igm = N+IN_BLOCK;
    locateData(index, true);
    rect |= calculateInputUpdate();
    rect |= calculateOutputUpdate();
    repaintView(rect);
    return true;
  } else if (prop.getName() == JString("sortOn")) {
    int nid = ((JIntegerListProperty*)&prop)->value;
    JLinkObj *link = (JLinkObj*)inputSet(SEARCH).last();
    if (link) {
      int nType;
      if (nid < N) nType = getFieldType(nid);
      else nType = JIntegerData::id;
      if (link->from->outputType(link->fn) != nType) {
        JMessageBox::create("Disconnect all links to search_on first!", 
          JMessageBox::BTN_OK);
        return true;
      }
    }
    dbf.setSortFieldIndex(nid);
    sort(dbf.getSortFieldIndex());
    locateData(index, true);
    return true;
  } else {
    for (int i=0; i<N; i++) {
      JDataField *df = dbf.getField(i);
      if (prop.getName() == JString("FieldName-")+JInteger::toJString(i)) {
        JDataField ndf(((JStringProperty*)&prop)->value, df->getType(), df->getId());
        if (ndf.getName() == "") {
          JMessageBox::create("Please assign a valid filed name !", 
            JMessageBox::BTN_OK);
        } else if (dbf.hasField(ndf)) {
          JMessageBox::create("The field name already exist !", 
            JMessageBox::BTN_OK);
        } else dbf.setField(i, ndf);
        return true;
      } else if (prop.getName() == JString("FieldType-")+JInteger::toJString(i)) {
        if (hasFieldConnected(i)) {
          JMessageBox::create(JString("Disconnect all links to Field ")+
            df->getName()+" first!", JMessageBox::BTN_OK);
          return true;
        }
        int type = ((JIntegerListProperty*)&prop)->value;
        dbf.setField(i, JDataField(df->getName(), 
          JDataType::str(type, type+1),
          dbf.getNextId()));
        locateData(index, true);
        return true;
      }
    }
  }
  return false;
}

boolean JDataBaseObj::check() {
  close();
  dbf.open(filename, readOnly);
  if (dbf.isValid()) {
    valid = true;
    condition = locate = update = false;
    insert = append = del = false;
    N = dbf.getNumOfField();
    ogm = N+OUT_BLOCK;
    igm = N+IN_BLOCK;
    total = dbf.size();
    locateData(index, true);
  } else {
    valid = false;
    total = 0;
    index = 0;
    N = 0;
    close();
  }
  broadcast(TOTAL);
  broadcast(INDEX);
  return valid;
}

int JDataBaseObj::search(JObject *obj, int fid, int from, int to) {
  int mid, cmp;
  int lo = from;
  int hi = to-1;
  JArray buf;
  do {
    buf = fetchData(mid = (lo+hi)/2);
    if ((cmp = obj->compareTo(*buf[fid])) > 0) lo = mid+1;
    else if (cmp < 0) hi = mid-1;
    else break;
  } while (lo <= hi);
  while ((mid < to) && (obj->compareTo(*buf[fid]) >= 0))
    buf = fetchData(++mid);
  return mid;
}

int JDataBaseObj::searchFirst(JObject *obj, int fid, int from, int to) {
  int mid, cmp;
  int lo = from;
  int hi = to-1;
  JArray buf;
  do {
    buf = fetchData(mid = (lo+hi)/2);
    if ((cmp = obj->compareTo(*buf[fid])) > 0) lo = mid+1;
    else if (cmp < 0) hi = mid-1;
    else break;
  } while (lo <= hi);
  while ((mid > from) && (obj->compareTo(*buf[fid]) <= 0)) 
    buf = fetchData(--mid);
  if (obj->compareTo(*buf[fid]) > 0) ++mid;
  return mid;
}

void JDataBaseObj::sort(int fid) {
  if (!valid || readOnly) return;
  if (fid == N) return;
  JArray data;
  int dest;
  int sz = dbf.size();
  for (int i=1; i<sz; i++) {
    data = fetchData(i);
    dbf.del(i);
    dest = search(data[fid], fid, 0, i);
    dbf.insert(prepareData(data), dest);
  }
}

JArray JDataBaseObj::prepareData(JArray& data) {
  JArray buf(N);
  for (int i=0; i<N; i++) {
    buf.set(i, JDataType::toBlock(
      getFieldType(i), *data[i]));
  }
  return buf;
}

void JDataBaseObj::updateData() {
  if (!valid || readOnly) return;
  int fid = dbf.getSortFieldIndex();
  if ((fid < N) && (total > 1)) {
    int dest = index;
    int oldTotal = total;
    if (index < total) {
      dbf.del(index);
      index = search(iBuf[fid], fid, 0, total-1);
    } else index = search(iBuf[fid], fid, 0, total);
    dbf.insert(prepareData(iBuf), index);
    total = dbf.size();
    if (total != oldTotal) broadcast(TOTAL);
    if (index != dest) broadcast(INDEX);
  } else {
    if (index == total) {
      dbf.append(prepareData(iBuf));
      total = dbf.size();
      broadcast(TOTAL);
    } else dbf.set(index, prepareData(iBuf));
  }
  locateData(index, true);
}

JArray JDataBaseObj::fetchData(int index) {
  int i;
  JArray data(N);
  JArray buf = dbf.get(index);
  JObject *obj;
  for (i=0; i<N; i++) {
    obj = JDataType::create(
      getFieldType(i), *(JBlock*)buf[i]);
    data.set(i, *obj);
    delete obj;
  }
  return data;
}

boolean JDataBaseObj::locateData(int _index, boolean force) {
  int oindex = index;
  if (!valid) return false;
  index = max(0, min(total, _index));
  if (force || (index != oindex)) {
    iBuf = data = fetchData(index);
    iBuf.Dereference();
    for (int i=0; i<N; i++)
      broadcast(OUT_BLOCK+i);
    broadcast(INDEX);
    return true;
  }
  return false;
}

void JDataBaseObj::insertBlank() {
  if (!valid || readOnly) return;
  int fid = dbf.getSortFieldIndex();
  if ((fid < N) && (total > 0)) {
    int dest = index;
    data = fetchData(total);
    index = search(data[fid], fid, 0, total);
    if (index != dest) broadcast(INDEX);
  }
  dbf.insert(index);
  total = dbf.size();
  broadcast(TOTAL);
  locateData(index, true);
}

JArray JDataBaseObj::getFieldTag() {
  JArray tag;
  if (!valid) return tag;
  for (int i=0; i<N; i++)
    tag.append(dbf.getField(i)->getName());
  return tag;
}

boolean JDataBaseObj::hasFieldConnected(int index) {
  if (index < 0) {
    int i;
    for (i=igSize; --i>IN_BLOCK;) 
      if (inputSet(i).last()) return true;
    for (i=ogSize; --i>OUT_BLOCK;) 
      if (outputSet(i).last()) return true;
  } else {
    if (inputSet(IN_BLOCK+index).last()) return true;
    if (outputSet(OUT_BLOCK+index).last()) return true;
  }
  return false;
}
