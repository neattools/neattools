#if !defined( _JRecorderObj_h )
#define _JRecorderObj_h

#include "JAddObj.h"
#include "JThread.h"
#include "JFileInputStream.h"
#include "JFileOutputStream.h"
#include "JBufferedInputStream.h"
#include "JBufferedOutputStream.h"
#include "JCriticalSection.h"

/* The Purpose of JRecorderObj is to Provide a 
   NeatTools Module that could record event of
   any data type
*/
class JRecorderObj : public JAddObj {
  protected: /* Object Persistency Methods */
    virtual void writeContent(class JOutputStream& os);
    virtual void readContent(class JDictionary& dict);
  public: 
    /* Enum for Input/Ouput Ports */
    enum { RECORD, PLAY, PAUSE, FILENAME, SEQUENCE, 
      POS, NTRACK, PLAYBACK_SCALE, WAVE_FEEDBACK, IN_LAST, IN_BLOCK = 10};
    enum { COUNT, TOTAL, OUT_LAST, OUT_BLOCK = 5};
    /* Override Methods from JObject */
    virtual const char* className() const;
    virtual JObject* clone() const;
    JRecorderObj();
    /* GCC 2.7.2 will crash if don't have this constructor
       defined. It is not needed in VC++ */ 
    JRecorderObj(const JRecorderObj& obj);
    ~JRecorderObj();
    /* NeatTools will inform the module that it could start */
    virtual void startup();
    /* NeatTools will inform the module that a reset occur */
    virtual void reset();
    /* Start to record events */
    virtual void record();
    /* Play back the events */
    virtual void play();
    /* Close the Record or Play action */
    virtual void close();
    /* Close the associated Handles */
    virtual void closeHandle();
    /* Basic Module Behavior for Input/Output Data Type */
    virtual int inputType(int n);
    virtual int outputType(int n);
    /* Basic Module Behavior for Data Exchange */
    virtual void access(int n, JLinkObj& link, const JDataType& data);
    /* Basic Module Behavior for access control */
    virtual boolean inputAllowed(int n);
    /* Basic Module Behavior for Input/Output Tag */
    virtual JString inputTag(int n);
    virtual JString outputTag(int n);
    /* Basic Module Behavior for Input/Output Area */
    virtual JFRect inputArea(int n);
    virtual JFRect outputArea(int n);
    /* Basic Module Behavior for Input/Output Attach Edge */
    virtual int inputFace(int n);
    virtual int outputFace(int n);
    /* Basic Module Behavior for Input/Output Attach Point */
    virtual JFPoint inputPoint(int n, JLinkObj& link);
    virtual JFPoint outputPoint(int n, JLinkObj& link);
    /* Basic Module Behavior for Display */
    virtual void paint(JGraphics g, double dx, double dy, JRegion& rgn, double scale);
    virtual void draw(JGraphics g, int x, int y, int w, int h);
    /* Basic Module Behavior for Input Events */
    virtual void engine(int n, JLinkObj& link);
    /* Thread Run Procedure */
    virtual void run();
    /* Get the Module's Property Set */
    virtual JArray getProperties();
    /* System will call this method to update Property */
    virtual boolean updateProperty(JProperty& prop);
    /* Check the Valid Status */
    virtual boolean check(boolean redraw);
    /* Update the number of input channels */
    virtual boolean updateN(int nN, boolean redraw);
    /* Composit the filename from prefix and sequence number */
    JString composit(JString prefix, int sequence);
    /* Parse filename into prefix and sequence number */
    int parseName(JString name, JString& prefix);
  protected:
    int sequence; // File Sequence Number
    int N;	  // Number of I/O Channel
    int pos;	  // Current Playback Start Position
    int count;	  // Current Event Count
    int total;	  // Total Event Count
    int startPos; // File Data Start Position
    int counter;  // Counter for Thread Delay Loop
    long timeBase;  // Record Time Base Point
    long pauseBase; // Pause Time Base Point
    boolean recording; // Recording State
    boolean playing;   // Playing State
    boolean repeat;    // Repeat State
    boolean feedback;  // Feedback State
    int recordEnabled; // Is Record Enabled ?
    int playEnabled;   // Is Play Enabled ?
    int pause;         // Is Pause ?
    int textOutput;    // Need Text Output File ?
    int waveFeedback;
    double playbackScale;
    JThread thread; // Thread for Play back
    JString prefix; // File Prefix
    JString filename;  // Data File Name
    JString type;   // Data File Extension Type
    JArray data;    // Array of event data
    JFileInputStream fis;
    JFileOutputStream fos;
    JFileOutputStream ftos;
    JBufferedInputStream bis;
    JBufferedOutputStream bos;
    JBufferedOutputStream btos;
    JCriticalSection cs;  // Mutex for concurency
};

#endif
