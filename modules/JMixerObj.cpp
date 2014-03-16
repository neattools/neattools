#include "JMixerObj.h"
#include "JMath.h"
#include "JLinkObj.h"
#include "JIntegerData.h"
#include "JWindow.hpp"
//#include <stdio.h>

char* theJMixerObj = JMixerObj().Register();
void** JMixerObj::hMixer = null;

char* lineName[] = {
  "Master", "Record",
  "Mic", "Phone", "CD", "Line", "MIDI",
  "Misc", "Wave", "Aux", "Analog"
};
char* destName[] = { "Output", "Input", "Recog"};
char* ctrlName[] = { "Volume", "Mute", "Select"};

#if defined(WIN32)

  DWORD lineType[] = {
    MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
    MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
    MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
    MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE,
    MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
    MIXERLINE_COMPONENTTYPE_SRC_LINE,
    MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
    MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED,
    MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
    MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY,
    MIXERLINE_COMPONENTTYPE_SRC_ANALOG,
  };
  DWORD ctrlType[] = {
    MIXERCONTROL_CONTROLTYPE_VOLUME,
    MIXERCONTROL_CONTROLTYPE_MUTE,
    MIXERCONTROL_CONTROLTYPE_MUX,
    MIXERCONTROL_CONTROLTYPE_MIXER,
    MIXERCONTROL_CONTROLTYPE_SINGLESELECT,
    MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT,
  };
  char* idName[] = {
    "VOL", "REC",
    "MIC", "PHONE", "CD", "LINE", "SYN",
    "MISC", "WAVE", "AUX", "ANALOG"
  };
  char* idName2[] = {
    "VOL", "REC",
    "MIC", "PHONE", "CD", "LINE", "MIDI",
    "MISC", "WAVE", "AUX", "ANALOG"
  };

  int index[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	
  int JMixerObj::getNumDevs() 
  { return mixerGetNumDevs();}

  boolean JMixerObj::isValidDev(int mid) {
    if (hMixer) return (hMixer[mid] != 0);
    return false;
  }

  void JMixerObj::openDevs(int handle) {
    int numDevs = getNumDevs();
    if (numDevs) {
      MMRESULT rc;
      hMixer = new void*[numDevs];
      for (int i=0; i<numDevs; i++) {
	rc = mixerOpen((LPHMIXER)&hMixer[i], i, (DWORD)handle, 
	  (DWORD)null, CALLBACK_WINDOW);
	if (rc != MMSYSERR_NOERROR) hMixer[i] = null;
      }
    }
  }

  void JMixerObj::closeDevs() {
    int numDevs = getNumDevs();
    if (numDevs && hMixer) {
      for (int i=0; i<numDevs; i++)
	if (hMixer[i]) mixerClose((HMIXER)hMixer[i]);
      delete hMixer;
    }
  }

  boolean JMixerObj::check() {
    boolean result = false;
    MMRESULT rc;
    MIXERCAPS mxcaps;
    MIXERLINE mxl;
    mxcaps.cDestinations = 0;
    mixerGetDevCaps(mid, &mxcaps, sizeof(MIXERCAPS));
    igm = ogm = cChannels = cItems = nTotal = 1;
    dwLineID = dwCtrlID = null;
    simulate = false;
    if (hMixer && hMixer[mid] && mxcaps.cDestinations) {
      mxl.cbStruct = sizeof(mxl);
      mxl.dwLineID = 0;
      mxl.dwComponentType = lineType[lid];
      rc = mixerGetLineInfo((HMIXEROBJ)hMixer[mid],
        &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE);
      if (rc == MMSYSERR_NOERROR) {
	if (sid) {
	  DWORD dwDest = mxl.dwDestination;
	  DWORD cConnections = mxl.cConnections;
	  for (DWORD i=0; i<cConnections; i++) {
	    mxl.cbStruct = sizeof(mxl);
	    mxl.dwDestination = dwDest;
	    mxl.dwSource = i;
	    rc = mixerGetLineInfo((HMIXEROBJ)hMixer[mid], 
	      &mxl, MIXER_GETLINEINFOF_SOURCE);
            if (rc == MMSYSERR_NOERROR) {
	      JString sName = JString(mxl.szName).toUpperCase();
	      boolean match = 
		(sName.indexOf(idName[sid]) == 0) ||
	        (sName.indexOf(idName2[sid]) == 0);
	      if ((lineType[sid] == mxl.dwComponentType) || match) {
                dwLineID = mxl.dwLineID;
	        cChannels = mxl.cChannels;
		result = true;
		if (result) break;
	      }
	    }
          }
	} else {
          dwLineID = mxl.dwLineID;
	  cChannels = mxl.cChannels;
	  result = true;
	}
      }
    }
    lname = JString(lineName[(sid)?sid:lid]);
    tname = JString(destName[lid]);
    cname = JString(ctrlName[cid]);
    if (result) {
      JEvent e;
      MIXERLINECONTROLS mxlc;
      MIXERCONTROL mc;
      result = false;
      mxlc.cbStruct = sizeof(mxlc);
      mxlc.dwLineID = dwLineID;
      mxlc.dwControlType = ctrlType[cid];
      mxlc.cControls = 1;
      mxlc.cbmxctrl = sizeof(mc);
      mxlc.pamxctrl = &mc;
      rc = mixerGetLineControls((HMIXEROBJ)hMixer[mid], 
        &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
      if ((rc != MMSYSERR_NOERROR) && (cid == CTRL_SELECT)) {
	int i = 1;
	do {
          mxlc.dwControlType = ctrlType[cid+i];
          rc = mixerGetLineControls((HMIXEROBJ)hMixer[mid], 
            &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);
	  if (++i > 3) {
            simulate = true;
            mute.delAll();
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_CD));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_WAVE));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_MIDI));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_LINE));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_PHONE));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_MIC));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_AUX));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_ANALOG));
            mute.append(JMixerObj(mid, DST_WAVEIN, CTRL_SWITCH, SRC_MISC));
            exclusive = false;
            dwCtrlID = 0;
            cChannels = 1;
            ogm = igm = nTotal = cItems = cMultipleItems = MAX_CTRL_TYPE;
            return true;
          }
	} while (rc != MMSYSERR_NOERROR);
        
      }
      if (rc == MMSYSERR_NOERROR) {
	int gMax;
	exclusive = !(mxlc.dwControlType & MIXERCONTROL_CT_SC_LIST_MULTIPLE);
        dwCtrlID = mc.dwControlID;
	cMultipleItems = mc.cMultipleItems;
	cItems = 1;
	if (mc.fdwControl & MIXERCONTROL_CONTROLF_UNIFORM)
	  cChannels = 1;
	if (mc.fdwControl & MIXERCONTROL_CONTROLF_MULTIPLE)
	  cItems = cMultipleItems;
	gMax = nTotal = cItems*cChannels;
	if (cid == CTRL_SELECT) {
	  /*
	  char buf[256];
	  sprintf(buf, "cItems=%d, cChannels=%d, %d %d %d %d %d %d %d %d %d", cItems, cChannels,
	    index[0], index[1], index[2], index[3], index[4], index[5], index[6], index[7], index[8]);
	  MessageBox(0, "Message", buf, MB_ICONEXCLAMATION | MB_OK);
	  */
	  gMax = MAX_CTRL_TYPE;
	}
	ogm = igm = gMax;
	result = true;
      }
    }
    return result;
  }

  boolean JMixerObj::mixerLineNotify(JEvent& e, int _mid, int _lid) {
    if (!valid || (dwLineID != _lid)) return false;
    MIXERLINE mxl;
    mxl.cbStruct = sizeof(MIXERLINE);
    mxl.dwLineID = dwLineID;
    mixerGetLineInfo((HMIXEROBJ)hMixer[mid],
      &mxl, MIXER_GETLINEINFOF_LINEID);
    return true;
  }

  boolean JMixerObj::mixerControlNotify(JEvent& e, int _mid, int _cid) {
    if (valid && simulate) {
      JMixerObj *mo;
      for (int i=0; i<MAX_CTRL_TYPE; i++) {
        mo = (JMixerObj*)mute[i];
        mo->mixerControlNotify(e, _mid, _cid);
        v[i] = mo->v[0];
        broadcast(i);
      }
      return true;
    }
    if (!valid || (dwCtrlID != _cid)) return false;
    int i;
    MMRESULT rc;
    MIXERCONTROLDETAILS mxcd;
    MIXERCONTROLDETAILS_UNSIGNED *mxcdu
      = new MIXERCONTROLDETAILS_UNSIGNED[nTotal];
    mxcd.cbStruct = sizeof(mxcd);
    mxcd.dwControlID = dwCtrlID;
    mxcd.cChannels = cChannels;
    mxcd.cMultipleItems = cMultipleItems;
    mxcd.cbDetails = sizeof(*mxcdu);
    mxcd.paDetails = mxcdu;
    rc = mixerGetControlDetails((HMIXEROBJ)hMixer[mid],
      &mxcd, MIXER_GETCONTROLDETAILSF_VALUE);
    if (rc == MMSYSERR_NOERROR) {
      switch (cid) {
        case CTRL_MUTE:
          if (reverse) {
            for (i=0; i<ogm; i++)
              v[i] = (mxcdu[i].dwValue) ? 0 : limit;
          } else {
            for (i=0; i<ogm; i++)
	      v[i] = (mxcdu[i].dwValue) ? limit : 0;
          }
          break;
        case CTRL_VOLUME:
	  if ((ogm > 1) && !inputSet(ogm-1).last()) {
	    int vmax = mxcdu[0].dwValue;
            for (i=1; i<ogm; i++)
              vmax = max(vmax, (int)mxcdu[i].dwValue);
            for (i=0; i<ogm; i++)
              v[i] = vmax;
	  } else {
            for (i=0; i<ogm; i++)
              v[i] = (int)mxcdu[i].dwValue;
	  }
	  break;
        case CTRL_SELECT:
          for (i=0; i<ogm; i++) {
            if (index[i] > -1)
	      v[i] = (mxcdu[index[i]].dwValue) ? limit : 0;
            else v[i] = 0;
          }
	  break;
      }
      for (i=0; i<ogm; i++)
        broadcast(i);
    }
    delete mxcdu;
    return true;
  }

#else

  int JMixerObj::getNumDevs() 
  { return 1;}

  boolean JMixerObj::isValidDev(int id) {
    return false;
  }

  void JMixerObj::openDevs(int handle) {
  }

  void JMixerObj::closeDevs() {
  }

  boolean JMixerObj::check() {
    cChannels = cItems = 1;
    dwLineID = dwCtrlID = null;
    lname = JString(lineName[(sid)?sid:lid]);
    tname = JString(destName[lid]);
    cname = JString(ctrlName[cid]);
    return false;
  }

  boolean JMixerObj::mixerLineNotify(JEvent& e, int _mid, int _lid) {
    if (!valid || (dwLineID != _lid)) return false;
    return true;
  }

  boolean JMixerObj::mixerControlNotify(JEvent& e, int _mid, int _cid) {
    if (!valid || (dwCtrlID != _cid)) return false;
    return true;
  }

#endif

void JMixerObj::writeContent(JOutputStream& os) {
  JANDObj::writeContent(os);
  putInteger(os, "mid", mid);
  putInteger(os, "lid", lid);
  putInteger(os, "cid", cid);
  putInteger(os, "sid", sid);
  putInteger(os, "v0", v[0]);
  putInteger(os, "v1", v[1]);
  putInteger(os, "v2", v[2]);
  putInteger(os, "v3", v[3]);
  putInteger(os, "v4", v[4]);
}

void JMixerObj::readContent(JDictionary& dict) {
  JANDObj::readContent(dict);
  mid = getInteger(dict, "mid");
  lid = getInteger(dict, "lid");
  cid = getInteger(dict, "cid");
  sid = getInteger(dict, "sid");
  v[0] = getInteger(dict, "v0");
  v[1] = getInteger(dict, "v1");
  v[2] = getInteger(dict, "v2");
  v[3] = getInteger(dict, "v3");
  v[4] = getInteger(dict, "v4");
  valid = check();
  if (simulate) {
    for (int i=0; i<MAX_CTRL_TYPE; i++)
      ((JMixerObj*)mute[i])->v[0] = v[i];
  }
}

const char* JMixerObj::className() const { return "JMixerObj";}
JObject* JMixerObj::clone() const { return new JMixerObj(*this);}

JMixerObj::JMixerObj(int _mid, int _lid, 
  int _cid, int _sid) { 
  eventMask = MIXER_MASK;
  v[0] = v[1] = v[2] = v[3] = v[4] = 0;
  mid = _mid;
  lid = _lid;
  cid = _cid;
  sid = _sid;
  if (cid == CTRL_SWITCH) {
     reverse = true;
     cid = CTRL_MUTE;
  } else reverse = false;
  valid = check();
}

boolean JMixerObj::isValid() { return valid;}

void JMixerObj::draw(JGraphics g, int x, int y, int w, int h) {
  int dh = h/3;
  int dy = h/12;
  JRect rect1(x, y+dy, w, dh);
  JRect rect2(x, y+h/3, w, dh);
  JRect rect3(x, y+h*2/3-dy, w, dh);
  if (!valid) {
    if (g.getJColor() == JColor::black)
      g.setJColor(JColor::gray);
    else return;
  }
  drawText(g, lname, rect1);
  drawText(g, tname, rect2);
  drawText(g, cname, rect3);
}

void JMixerObj::startup() {
  JEvent ev;
  if (simulate) {
    JMixerObj *mo;
    for (int i=0; i<MAX_CTRL_TYPE; i++) {
      mo = (JMixerObj*)mute[i];
      mo->mixerControlNotify(ev, (int)hMixer[mid], mo->dwCtrlID);
      v[i] = mo->v[0];
      broadcast(i);
    }
  } else mixerControlNotify(ev, (int)hMixer[mid], dwCtrlID);
}

void JMixerObj::access(int n, JLinkObj& link, const JDataType& data) 
{ INT(data) = matchNB(v[n], 16);}

JString JMixerObj::inputTag(int n) { 
  switch (cid) {
    case CTRL_MUTE:
    case CTRL_VOLUME:
      if (ogm == 2) {
        char* tag[] = { "input-L/Mono", "input-R"};
        return JString(tag[n])+NBTag();
      }
      break;
#if defined(WIN32)
    case CTRL_SELECT:
      if (index[n] != -1) 
	return JString("input-")+lineName[n+SRC_MIC]+NBTag();
      return JString("input-")+lineName[n+SRC_MIC]+"(N.A.)";
#endif
  }
  return JString("input")+NBTag();
}

JString JMixerObj::outputTag(int n) { 
  switch (cid) {
    case CTRL_MUTE:
    case CTRL_VOLUME:
      if (ogm == 2) {
        char* tag[] = { "output-L/Mono", "output-R"};
        return JString(tag[n])+NBTag();
      }
      break;
#if defined(WIN32)
    case CTRL_SELECT:
      if (index[n] != -1) 
	return JString("output-")+lineName[n+SRC_MIC]+NBTag();
      return JString("output-")+lineName[n+SRC_MIC]+"(N.A.)";
#endif
  }
  return JString("output")+NBTag();
}

boolean JMixerObj::inputAllowed(int n) {
  switch (cid) {
    case CTRL_MUTE:
    case CTRL_VOLUME:
      if (ogm == 2)
        return (boolean)!inputSet(n).last();
      break;
#if defined(WIN32)
    case CTRL_SELECT:
      return (index[n] > -1) ? (boolean)!inputSet(n).last() : false;
#endif
  }
  return (boolean)((!n) ? !inputSet(n).last() : false);
}

JFRect JMixerObj::inputArea(int n) {
  switch (cid) {
    case CTRL_SELECT:
      if (igm > 0) return leftArea(n, 0, igm, 0, 1);
    default:
      if (!n) return leftArea(n, 0, 1);
      return topArea(n, 1, 1);
  }
}

JFRect JMixerObj::outputArea(int n) { 
  switch (cid) {
    case CTRL_SELECT:
      if (ogm > 0) return rightArea(n, 0, ogm, 0, 1);
    default:
      if (!n) return rightArea(n, 0, 1);
      return bottomArea(n, 1, 1);
  }
}

int JMixerObj::inputFace(int n) { 
  switch (cid) {
    case CTRL_SELECT:
      return LEFT;
    default:
      return (!n) ? LEFT : TOP;
  }
}

int JMixerObj::outputFace(int n) { 
  switch (cid) {
    case CTRL_SELECT:
      return RIGHT;
    default:
      return (!n) ? RIGHT : BOTTOM;
  }
}

JFPoint JMixerObj::inputPoint(int n, JLinkObj& link) { 
  switch (cid) {
    case CTRL_SELECT:
      if (igm > 0) return leftPoint(n, link, 0, igm, 0, 1);
    default:
      if (!n) return leftPoint(n, link, 0, 1);
      return topPoint(n, link, 1, 1);
  }
}

JFPoint JMixerObj::outputPoint(int n, JLinkObj& link) { 
  switch (cid) {
    case CTRL_SELECT:
      if (ogm > 0) 
        return rightPoint(n, link, 0, ogm, 0, 1);
    default:
      if (!n) return rightPoint(n, link, 0, 1);
      return bottomPoint(n, link, 1, 1);
  }
}

void JMixerObj::engine(int n, JLinkObj& link) {
  if (!valid) return;
  if (simulate) {
    ((JMixerObj*)mute[n])->engine(0, link);
    return;
  }
  int oldv = v[n];
  link.access(JIntegerData(v[n]));
  if ((cid == CTRL_MUTE) || (cid == CTRL_SELECT)) {
    oldv = (oldv) ? limit : 0;
    v[n] = (v[n]) ? limit : 0;
  } else v[n] = matchBack(v[n], 16);
  if (oldv != v[n]) {
#if defined(WIN32)
    MIXERCONTROLDETAILS mxcd;
    MIXERCONTROLDETAILS_UNSIGNED *mxcdu
      = new MIXERCONTROLDETAILS_UNSIGNED[nTotal];
    mxcd.cbStruct = sizeof(mxcd);
    mxcd.dwControlID = dwCtrlID;
    mxcd.cChannels = cChannels;
    mxcd.cMultipleItems = cMultipleItems;
    mxcd.cbDetails = sizeof(*mxcdu);
    mxcd.paDetails = mxcdu;
    switch (cid) {
      case CTRL_MUTE:
        if (reverse) {
          for (int i=0; i<ogm; i++)
            mxcdu[i].dwValue = ((limit-v[i]) != 0);
        } else {
          for (int i=0; i<ogm; i++)
            mxcdu[i].dwValue = (v[i] != 0);
        }
        mixerSetControlDetails((HMIXEROBJ)hMixer[mid],
          &mxcd, 0L);
        break;
      case CTRL_VOLUME:
	if (!n && (ogm > 1) &&
            !inputSet(ogm-1).last()) {
          for (int i=0; i<ogm; i++)
            mxcdu[i].dwValue = v[n];
        } else {
          for (int i=0; i<ogm; i++)
            mxcdu[i].dwValue = v[i];
	}
        mixerSetControlDetails((HMIXEROBJ)hMixer[mid],
          &mxcd, 0L);
	break;
      case CTRL_SELECT: {
        for (int i=0; i<cItems; i++)
          mxcdu[i].dwValue = 0;
	if (exclusive) {
	  if (index[n] == -1) {
	    v[n] = 0;
	    broadcast(n);
	    break;
	  }
	  if (v[n]) {
            for (int i=0; i<ogm; i++) {
	      if (i!=n) v[i] = 0;
	      if (index[i] > -1)
                mxcdu[index[i]].dwValue = (v[i] != 0);
	    }
            mixerSetControlDetails((HMIXEROBJ)hMixer[mid],
              &mxcd, 0L);
	  } else {
	    v[n] = limit;
	    broadcast(n);
	  }
	} else {
          for (int i=0; i<ogm; i++) {
	    if (index[i] > -1)
              mxcdu[index[i]].dwValue = v[i];
          }
          mixerSetControlDetails((HMIXEROBJ)hMixer[mid],
            &mxcd, 0L);
	}
        break;
      }
    }
    delete mxcdu;
#else
#endif
  }
}

void JMixerObj::addButton(JComponent* panel) {
  int numDevs = getNumDevs();
  for (int i=0; i<numDevs; i++) {
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_CD));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_CD));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_WAVE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_WAVE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_MIDI));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_MIDI));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_LINE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_LINE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_MIC));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_MIC));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_PHONE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_PHONE));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_AUX));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_AUX));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_ANALOG));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_ANALOG));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_VOLUME, SRC_MISC));
    addModuleButton(panel, JMixerObj(
      i, DST_SPEAKERS, CTRL_MUTE, SRC_MISC));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_MUTE));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_SELECT));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_CD));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_WAVE));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_MIDI));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_LINE));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_MIC));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_PHONE));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_AUX));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_ANALOG));
    addModuleButton(panel, JMixerObj(
      i, DST_WAVEIN, CTRL_VOLUME, SRC_MISC));
  }
}

