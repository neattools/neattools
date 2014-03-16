#if !defined( _JMixerObj_h )
#define _JMixerObj_h

#include "JANDObj.h"
#include "JArray.h"

class JMixerObj : public JANDObj {
  protected:
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public:
    enum { DST_SPEAKERS, DST_WAVEIN, DST_VOICEIN,
      SRC_CD, SRC_WAVE, SRC_MIDI, SRC_LINE, SRC_MIC,
      SRC_PHONE, SRC_AUX, SRC_ANALOG, SRC_MISC, SRC_LAST};
    enum { CTRL_VOLUME, CTRL_MUTE, 
      CTRL_SELECT, CTRL_SELECT_MIXER, CTRL_SELECT_SINGLE,
      CTRL_SELECT_MULTIPLE, CTRL_SWITCH};
    enum { MAX_CTRL_TYPE = SRC_LAST-SRC_CD};
    static int getNumDevs();
    static boolean isValidDev(int mid);
    static void openDevs(int handle);
    static void closeDevs();
    virtual const char* className() const;
    virtual JObject* clone() const;
    JMixerObj(int _mid = 0, int _lid = 0, 
  	  int _cid = 0, int _sid = 0);
    boolean check();
    boolean isValid();
    int type2src(int t);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    virtual boolean mixerLineNotify(JEvent& e, int mid, int lid);
    virtual boolean mixerControlNotify(JEvent& e, int mid, int cid);
    virtual void startup();
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    virtual boolean inputAllowed(int n);
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    virtual void engine(int n, JLinkObj& link);
    virtual void addButton(JComponent *panel);
    virtual JArray getDeviceTag();
    virtual JArray getProperties();
    virtual boolean updateProperty(JProperty& prop);
  protected:
    int mid, lid, cid, sid;
    long dwLineID, dwCtrlID;
    long cItems, cMultipleItems;
    long cChannels, nTotal;
    JString lname, tname, cname, dname;
    boolean valid, exclusive, simulate, reverse;
    int v[MAX_CTRL_TYPE];
    JArray mute;
};

#endif
