#include "JKeyboardObj.h"
#include "JLinkObj.h"
#include "JCharacter.h"
#include "JInteger.h"
#include "JIntegerData.h"
#include "JIntegerListProperty.h"

int keyValue[] = {
  JEvent::JK_space,
  JEvent::JK_exclam, 
  JEvent::JK_quotedbl, 
  JEvent::JK_numbersign,
  JEvent::JK_dollar, 
  JEvent::JK_percent, 
  JEvent::JK_ampersand,
  JEvent::JK_quoteright, 
  JEvent::JK_parenleft, 
  JEvent::JK_parenright, 
  JEvent::JK_asterisk, 
  JEvent::JK_plus, 
  JEvent::JK_comma, 
  JEvent::JK_minus, 
  JEvent::JK_period, 
  JEvent::JK_slash, 
  JEvent::JK_0, 
  JEvent::JK_1, 
  JEvent::JK_2, 
  JEvent::JK_3, 
  JEvent::JK_4, 
  JEvent::JK_5, 
  JEvent::JK_6, 
  JEvent::JK_7, 
  JEvent::JK_8, 
  JEvent::JK_9,
  JEvent::JK_colon, 
  JEvent::JK_semicolon, 
  JEvent::JK_less, 
  JEvent::JK_equal, 
  JEvent::JK_greater,
  JEvent::JK_question, 
  JEvent::JK_at, 
  JEvent::JK_A, 
  JEvent::JK_B, 
  JEvent::JK_C, 
  JEvent::JK_D, 
  JEvent::JK_E, 
  JEvent::JK_F, 
  JEvent::JK_G, 
  JEvent::JK_H, 
  JEvent::JK_I,
  JEvent::JK_J, 
  JEvent::JK_K, 
  JEvent::JK_L, 
  JEvent::JK_M, 
  JEvent::JK_N, 
  JEvent::JK_O, 
  JEvent::JK_P, 
  JEvent::JK_Q, 
  JEvent::JK_R,
  JEvent::JK_S, 
  JEvent::JK_T, 
  JEvent::JK_U, 
  JEvent::JK_V, 
  JEvent::JK_W, 
  JEvent::JK_X, 
  JEvent::JK_Y, 
  JEvent::JK_Z,
  JEvent::JK_bracketleft, 
  JEvent::JK_backslash, 
  JEvent::JK_bracketright, 
  JEvent::JK_asciicircum,
  JEvent::JK_underscore, 
  JEvent::JK_quoteleft,
  JEvent::JK_a, 
  JEvent::JK_b, 
  JEvent::JK_c, 
  JEvent::JK_d, 
  JEvent::JK_e, 
  JEvent::JK_f, 
  JEvent::JK_g, 
  JEvent::JK_h, 
  JEvent::JK_i,
  JEvent::JK_j, 
  JEvent::JK_k, 
  JEvent::JK_l, 
  JEvent::JK_m, 
  JEvent::JK_n, 
  JEvent::JK_o, 
  JEvent::JK_p, 
  JEvent::JK_q, 
  JEvent::JK_r,
  JEvent::JK_s,
  JEvent::JK_t, 
  JEvent::JK_u, 
  JEvent::JK_v, 
  JEvent::JK_w, 
  JEvent::JK_x, 
  JEvent::JK_y, 
  JEvent::JK_z,
  JEvent::JK_braceleft, 
  JEvent::JK_bar, 
  JEvent::JK_braceright, 
  JEvent::JK_asciitilde,
  JEvent::JK_127,
  JEvent::JK_128,
  JEvent::JK_129,
  JEvent::JK_130,
  JEvent::JK_131,
  JEvent::JK_132,
  JEvent::JK_133,
  JEvent::JK_134,
  JEvent::JK_135,
  JEvent::JK_136,
  JEvent::JK_137,
  JEvent::JK_138,
  JEvent::JK_139,
  JEvent::JK_140,
  JEvent::JK_141,
  JEvent::JK_142,
  JEvent::JK_143,
  JEvent::JK_144,
  JEvent::JK_145,
  JEvent::JK_146,
  JEvent::JK_147,
  JEvent::JK_148,
  JEvent::JK_149,
  JEvent::JK_150,
  JEvent::JK_151,
  JEvent::JK_152,
  JEvent::JK_153,
  JEvent::JK_154,
  JEvent::JK_155,
  JEvent::JK_156,
  JEvent::JK_157,
  JEvent::JK_158,
  JEvent::JK_159,
  JEvent::JK_160,
  JEvent::JK_161,
  JEvent::JK_162,
  JEvent::JK_163,
  JEvent::JK_164,
  JEvent::JK_165,
  JEvent::JK_166,
  JEvent::JK_167,
  JEvent::JK_168,
  JEvent::JK_169,
  JEvent::JK_170,
  JEvent::JK_171,
  JEvent::JK_172,
  JEvent::JK_173,
  JEvent::JK_174,
  JEvent::JK_175,
  JEvent::JK_176,
  JEvent::JK_177,
  JEvent::JK_178,
  JEvent::JK_179,
  JEvent::JK_180,
  JEvent::JK_181,
  JEvent::JK_182,
  JEvent::JK_183,
  JEvent::JK_184,
  JEvent::JK_185,
  JEvent::JK_186,
  JEvent::JK_187,
  JEvent::JK_188,
  JEvent::JK_189,
  JEvent::JK_190,
  JEvent::JK_191,
  JEvent::JK_192,
  JEvent::JK_193,
  JEvent::JK_194,
  JEvent::JK_195,
  JEvent::JK_196,
  JEvent::JK_197,
  JEvent::JK_198,
  JEvent::JK_199,
  JEvent::JK_200,
  JEvent::JK_201,
  JEvent::JK_202,
  JEvent::JK_203,
  JEvent::JK_204,
  JEvent::JK_205,
  JEvent::JK_206,
  JEvent::JK_207,
  JEvent::JK_208,
  JEvent::JK_209,
  JEvent::JK_210,
  JEvent::JK_211,
  JEvent::JK_212,
  JEvent::JK_213,
  JEvent::JK_214,
  JEvent::JK_215,
  JEvent::JK_216,
  JEvent::JK_217,
  JEvent::JK_218,
  JEvent::JK_219,
  JEvent::JK_220,
  JEvent::JK_221,
  JEvent::JK_222,
  JEvent::JK_223,
  JEvent::JK_224,
  JEvent::JK_225,
  JEvent::JK_226,
  JEvent::JK_227,
  JEvent::JK_228,
  JEvent::JK_229,
  JEvent::JK_230,
  JEvent::JK_231,
  JEvent::JK_232,
  JEvent::JK_233,
  JEvent::JK_234,
  JEvent::JK_235,
  JEvent::JK_236,
  JEvent::JK_237,
  JEvent::JK_238,
  JEvent::JK_239,
  JEvent::JK_240,
  JEvent::JK_241,
  JEvent::JK_242,
  JEvent::JK_243,
  JEvent::JK_244,
  JEvent::JK_245,
  JEvent::JK_246,
  JEvent::JK_247,
  JEvent::JK_248,
  JEvent::JK_249,
  JEvent::JK_250,
  JEvent::JK_251,
  JEvent::JK_252,
  JEvent::JK_253,
  JEvent::JK_254,
  JEvent::JK_255,
  JEvent::JK_BackSpace,
  JEvent::JK_Tab,
  JEvent::JK_BackTab,
  JEvent::JK_Clear,
  JEvent::JK_Return,
  JEvent::JK_Pause,
  JEvent::JK_Scroll_Lock,
  JEvent::JK_Escape,
  JEvent::JK_Delete,
  JEvent::JK_Home,
  JEvent::JK_Left,
  JEvent::JK_Up,
  JEvent::JK_Right,
  JEvent::JK_Down, 
  JEvent::JK_Prior, 
  JEvent::JK_Next, 
  JEvent::JK_End,
  JEvent::JK_Select,
  JEvent::JK_Print,
  JEvent::JK_Execute,
  JEvent::JK_Insert,
  JEvent::JK_Cancel,
  JEvent::JK_Help,
  JEvent::JK_Num_Lock,
  JEvent::JK_KP_Enter,
  JEvent::JK_KP_Multiply,
  JEvent::JK_KP_Add,
  JEvent::JK_KP_Separator,
  JEvent::JK_KP_Subtract,
  JEvent::JK_KP_Decimal,
  JEvent::JK_KP_Divide,
  JEvent::JK_KP_0,
  JEvent::JK_KP_1, 
  JEvent::JK_KP_2, 
  JEvent::JK_KP_3,
  JEvent::JK_KP_4, 
  JEvent::JK_KP_5, 
  JEvent::JK_KP_6, 
  JEvent::JK_KP_7, 
  JEvent::JK_KP_8, 
  JEvent::JK_KP_9,
  JEvent::JK_F1,
  JEvent::JK_F2, 
  JEvent::JK_F3, 
  JEvent::JK_F4, 
  JEvent::JK_F5,
  JEvent::JK_F6, 
  JEvent::JK_F7, 
  JEvent::JK_F8, 
  JEvent::JK_F9, 
  JEvent::JK_F10,
  JEvent::JK_F11, 
  JEvent::JK_F12, 
  JEvent::JK_F13, 
  JEvent::JK_F14, 
  JEvent::JK_F15, 
  JEvent::JK_F16,
  JEvent::JK_Shift,
  JEvent::JK_ShiftR,
  JEvent::JK_Control,
  JEvent::JK_ControlR,
  JEvent::JK_Caps_Lock,
  JEvent::JK_Alt,
  JEvent::JK_AltR,
  null
};

char* keyTag[] = {
  "Spc",
  "!", 
  "\"", 
  "#",
  "$", 
  "%", 
  "&",
  "'", 
  "(", 
  ")", 
  "*", 
  "+", 
  ",", 
  "-", 
  ".", 
  "/", 
  "0", 
  "1", 
  "2", 
  "3", 
  "4", 
  "5", 
  "6", 
  "7", 
  "8", 
  "9",
  ":", 
  ";", 
  "<", 
  "=", 
  ">",
  "?", 
  "@", 
  "A", 
  "B", 
  "C", 
  "D", 
  "E", 
  "F", 
  "G", 
  "H", 
  "I",
  "J", 
  "K", 
  "L", 
  "M", 
  "N", 
  "O", 
  "P", 
  "Q", 
  "R",
  "S", 
  "T", 
  "U", 
  "V", 
  "W", 
  "X", 
  "Y", 
  "Z",
  "[", 
  "\\", 
  "]", 
  "^",
  "_", 
  "`",
  "a", 
  "b", 
  "c", 
  "d", 
  "e", 
  "f", 
  "g", 
  "h", 
  "i",
  "j", 
  "k", 
  "l", 
  "m", 
  "n", 
  "o", 
  "p", 
  "q", 
  "r",
  "s",
  "t", 
  "u", 
  "v", 
  "w", 
  "x", 
  "y", 
  "z",
  "{", 
  "|", 
  "}", 
  "~",
  "",
  "\200", "\201", "\202", "\203", "\204", "\205", "\206", "\207",
  "\210", "\211", "\212", "\213", "\214", "\215", "\216", "\217",
  "\220", "\221", "\222", "\223", "\224", "\225", "\226", "\227",
  "\230", "\231", "\232", "\233", "\234", "\235", "\236", "\237",
  "\240", "\241", "\242", "\243", "\244", "\245", "\246", "\247",
  "\250", "\251", "\252", "\253", "\254", "\255", "\256", "\257",
  "\260", "\261", "\262", "\263", "\264", "\265", "\266", "\267",
  "\270", "\271", "\272", "\273", "\274", "\275", "\276", "\277",
  "\300", "\301", "\302", "\303", "\304", "\305", "\306", "\307",
  "\310", "\311", "\312", "\313", "\314", "\315", "\316", "\317",
  "\320", "\321", "\322", "\323", "\324", "\325", "\326", "\327",
  "\330", "\331", "\332", "\333", "\334", "\335", "\336", "\337",
  "\340", "\341", "\342", "\343", "\344", "\345", "\346", "\347",
  "\350", "\351", "\352", "\353", "\354", "\355", "\356", "\357",
  "\360", "\361", "\362", "\363", "\364", "\365", "\366", "\367",
  "\370", "\371", "\372", "\373", "\374", "\375", "\376", "\377",
  "BSpc",
  "Tab",
  "BTab",
  "Clear",
  "Enter",
  "Pause",
  "sLock",
  "Esc",
  "Del",
  "Home",
  "Left",
  "Up",
  "Right",
  "Down", 
  "PgUp", 
  "PgDn", 
  "End",
  "Select",
  "Print",
  "Exe",
  "Ins",
  "Cancel",
  "Help",
  "nLock",
  "KEnter",
  "K*",
  "K+",
  "KSep",
  "K-",
  "K.",
  "K/",
  "K0",
  "K1", 
  "K2", 
  "K3",
  "K4", 
  "K5", 
  "K6", 
  "K7", 
  "K8", 
  "K9",
  "F1",
  "F2", 
  "F3", 
  "F4", 
  "F5",
  "F6", 
  "F7", 
  "F8", 
  "F9", 
  "F10",
  "F11", 
  "F12", 
  "F13", 
  "F14", 
  "F15", 
  "F16",
  "Shift",
  "ShiftR",
  "Ctrl",
  "CtrlR",
  "Caps",
  "Alt",
  "AltR",
  null
};

char* theJKeyboardObj = JKeyboardObj().Register();
void JKeyboardObj::writeContent(JOutputStream& os) {
  JNOTObj::writeContent(os);
  putInteger(os, "id", id);
}

void JKeyboardObj::readContent(JDictionary& dict) {
  JNOTObj::readContent(dict);
  id = getInteger(dict, "id", -1);
  if (id == -1) {
    jKey = getInteger(dict, "jKey");
    for (int i=0; keyValue[i]; i++) {
      if (keyValue[i] == jKey) {
        id = i;
        break;
      }
    }
  }
  jKey = keyValue[id];
  name = keyTag[id];
  vKey = JEvent::JKtoVK(jKey, needShift);
}

const char* JKeyboardObj::className() const { return "JKeyboardObj";}
JObject* JKeyboardObj::clone() const { return new JKeyboardObj(*this);}

JKeyboardObj::JKeyboardObj(int _id) { 
  eventMask = GLOBAL_KEYBOARD_MASK;
  igm = 2;
  id = _id;
  jKey = keyValue[id]; 
  name = keyTag[id];
  state = false; 
  vKey = JEvent::JKtoVK(jKey, needShift);
}

void JKeyboardObj::draw(JGraphics g, int x, int y, int w, int h) {
  JRect rect(x, y, w, h);
  if (name.length() == 1) {
    int factor = 30, sh, sw, delta;
    delta = rect.height*factor/100;
    sh = rect.height;
    JFont font("courier", JFont::BOLD, sh);
    g.setJFont(font);
    JFontMetrics fm(g);
    sw = fm.stringWidth(name);
    sh = fm.getHeight();
    g.drawJString(name, rect.x+(rect.width-sw)/2, 
      rect.y+(rect.height-sh)/2);
  } else drawText(g, name, rect);
}

boolean JKeyboardObj::inputAllowed(int n)
{ return true;}

JString JKeyboardObj::inputTag(int n) { 
  char* tag[] = { "stroke(logical)", "depress(logical)"};
  return tag[n];
}

boolean JKeyboardObj::globalKeyDown(JEvent& e, int key) {
  if (key == jKey) {
    value = mask;
    broadcast(0);
  }
  return true;
}

boolean JKeyboardObj::globalKeyUp(JEvent& e, int key) {
  if (key == jKey) {
    value = 0;
    broadcast(0);
  }
  return true;
}

#if defined(WIN32)
  #include <windows.h>
#endif

void vkeyDown(int vKey) {
#if defined(WIN32)
  keybd_event(vKey, MapVirtualKey(vKey, 0), null, null);
#endif
}

void vkeyUp(int vKey) {
#if defined(WIN32)
  keybd_event(vKey, MapVirtualKey(vKey, 0), KEYEVENTF_KEYUP, null);
#endif
}

void vkeyStroke(int vKey) {
#if defined(WIN32)
  keybd_event(vKey, MapVirtualKey(vKey, 0), null, null);
  keybd_event(vKey, MapVirtualKey(vKey, 0), KEYEVENTF_KEYUP, null);
#endif
}

void vkeySequence(int jKey) {
#if defined(WIN32)
  JString s = JInteger(jKey).toJString();
  int len = s.length();
  vkeyDown(VK_MENU);
  vkeyStroke(VK_NUMPAD0);
  for (int i=0; i<len; i++) 
    vkeyStroke(VK_NUMPAD0+(s[i]-'0'));
#endif
}

boolean isSequence(int jKey) {
  return (JEvent::JK_asciitilde < jKey) && (jKey < JEvent::JK_ASCIILast);
}

void JKeyboardObj::engine(int n, JLinkObj& link) {
  if (!n) {
    int click;
    link.access(JIntegerData(click));
    if (click && !state) {
#if defined(WIN32)
      if (isSequence(jKey)) {
        vkeySequence(jKey);
        vkeyUp(VK_MENU);
      } else {
        if (needShift) vkeyDown(VK_SHIFT);
        vkeyStroke(vKey);
        if (needShift) vkeyUp(VK_SHIFT);
      }
#endif
    }
  } else {
    int olds = state;
    link.access(JIntegerData(state));
    state = (state != 0);
    if (state != olds) {
#if defined(WIN32)
      if (state) {
        if (isSequence(jKey)) {
          vkeySequence(jKey);
        } else {
          if (needShift) vkeyDown(VK_SHIFT);
          vkeyDown(vKey);
        }
      } else { 
        if (isSequence(jKey)) {
          vkeyUp(VK_MENU);
        } else {
          vkeyUp(vKey);
          if (needShift) vkeyUp(VK_SHIFT);
        }
      }
#endif
    }
  }
}

void JKeyboardObj::addButton(JComponent* panel) { 
  for (int i=0; keyValue[i]; i++) {
    addModuleButton(panel, JKeyboardObj(i));
  }
}

JArray JKeyboardObj::getProperties() {
  JArray properties = JNOTObj::getProperties();
  properties.append(JIntegerListProperty("id", id, keyTag));
  return properties;
}

boolean JKeyboardObj::updateProperty(JProperty& prop) {
  if (JNOTObj::updateProperty(prop)) return true;
  if (prop.getName() == JString("id")) {
    id = ((JIntegerListProperty*)&prop)->value;
    jKey = keyValue[id];
    name = keyTag[id];
    vKey = JEvent::JKtoVK(jKey, needShift);
    repaint();
    return true;
  }
  return false;
}

