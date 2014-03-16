#include "JTNG3XObj.h"
#include "JInteger.h"
#include "JIntegerProperty.h"
#include "JLinkObj.h"

char* theJTNG3XObj = JTNG3XObj().Register();

void JTNG3XObj::writeContent(JOutputStream& os) {
  JTNGObj::writeContent(os);
  putInteger(os, "separator0", separators[0]);
  putInteger(os, "separator1", separators[1]);
}

void JTNG3XObj::readContent(JDictionary& dict) {
  JTNGObj::readContent(dict);
  separators[0] = getInteger(dict, "separator0");
  separators[1] = getInteger(dict, "separator1");
}

const char* JTNG3XObj::className() const { return "JTNG3XObj";}
JObject* JTNG3XObj::clone() const { return new JTNG3XObj(*this);}

JTNG3XObj::JTNG3XObj() {
  factor = 10;
  channelCount = 9;
  channel = -1;
  byteCount = 17;
  oddbyte = 0;
  iByte = -1;
  StoreIt = 0;
  ClockIt = 1;
  ClockOff = 0;
  ogm = channelCount+offset;
  sepCount = 0;
  separators[0] = 170;
  separators[1] = 85;
}

void JTNG3XObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  drawText(g, JString("TNG3X"), rect);
}

void JTNG3XObj::processByte(int b) {
  iByte++;									// count this byte
  d = b & 0x00FF;

  if (v[0]) {				
    if ( iByte >= byteCount){				// v[0] has to be != 0; check byte count
      if (d != separators[sepCount]) {      // ibyte >= 17; is byte = separator?
    	v[0] = 0;						    // no: make v[0]=0 and return
	    broadcast(0);
	    return;
    } else {
        sepCount = (++sepCount)%2;			// yes: alternate separator and initialize
    	sequence++;							// for new packet
        channel = -1;
		iByte = -1;
		oddbyte = 0;
		a=0;
		ClockIt = 1;
		ClockOff= 0;
		return;
      }
    }

    if (sequence%factor) return;		   // return if the remainder of sequence/factor > 0

	if (oddbyte==1){					   // even or odd byte?
		oddbyte = 0;					   // odd; next byte even	
		d = d | a;			               // or together MSB and LSB
	    StoreIt = 1;					   // set storage flag
	
	} else {						       // even:
		d <<= 8;						   // get MSB and shift.
		a = d;			                   // save for combining
		oddbyte=1;						   // next byte odd
		channel++;                         // increment channel (0,1,..8)
		if (channel==8) StoreIt=1;	       // digital is only 8bits.
	}

	if ( ClockIt ) {
		if( ClockOff ){
			ClockIt  = 0;
			ClockOff = 0;
			v[1] = 0;
			broadcast(1);
		} else {
			ClockOff = 1;
	        v[1] = mask; 
            broadcast(1);
		}
    }
	

	if ( StoreIt ) {
      if (inv[channel])
	       v[channel+offset] = mask-d;
      else v[channel+offset] = d;
      broadcast(channel+offset);
	  StoreIt=0;
	  oddbyte=0;
	  a=0;
	  } 
	  
    sequence = 0;

  } else {									// v[0] is 0
    if (d == separators[sepCount]) {		// is byte a separator?
      sepCount = (++sepCount)%2;			// yes: alternate and initialize
      channel = -1;
	  iByte = -1;
	  oddbyte = 0;
	  StoreIt = 0;
	  ClockIt = 1;
	  ClockOff = 0;
	  a=0;
	  sequence = 0;
	  v[0] = mask;
      broadcast(0);
    }
  }
}

JArray JTNG3XObj::getProperties() {
  JArray properties = JTNGObj::getProperties();
  properties.append(JIntegerProperty("separator0", separators[0], 0, 255));
  properties.append(JIntegerProperty("separator1", separators[1], 0, 255));
  return properties;
}

boolean JTNG3XObj::updateProperty(JProperty& prop) {
  if (prop.getName() == JString("separator0")) {
    separators[0] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (prop.getName() == JString("separator1")) {
    separators[1] = ((JIntegerProperty*)&prop)->value;
    return true;
  } else if (JTNGObj::updateProperty(prop)) 
    return true;
  return false;
}

