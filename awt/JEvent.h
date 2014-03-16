#if !defined( _JEvent_h )
#define _JEvent_h

#include "JObject.h"

class
#include "JAWT.hpp"
JEvent : public JObject {
  public:
    static int LBUTTON;
    static int RBUTTON;
    static int MBUTTON;
    static int BUTTONS;
    static int LBUTTON_MASK;
    static int RBUTTON_MASK;
    static int MBUTTON_MASK;
    static int SHIFT_MASK;
    static int CTRL_MASK;
    static int CAPS_MASK;
    static int NUM_MASK;
    static int SCROLL_MASK;
    static int META_MASK;
    static int ALT_MASK;
    static int DBCLK_MASK;

    enum {
      JK_space = 32, JK_exclam, JK_quotedbl, JK_numbersign,
      JK_dollar, JK_percent, JK_ampersand,
      JK_quoteright, JK_parenleft, JK_parenright, JK_asterisk, 
      JK_plus, JK_comma, JK_minus, JK_period, JK_slash, 
      JK_0, JK_1, JK_2, JK_3, JK_4, 
      JK_5, JK_6, JK_7, JK_8, JK_9,
      JK_colon, JK_semicolon, JK_less, JK_equal, JK_greater,
      JK_question, JK_at, 
      JK_A, JK_B, JK_C, JK_D, JK_E, JK_F, JK_G, JK_H, JK_I,
      JK_J, JK_K, JK_L, JK_M, JK_N, JK_O, JK_P, JK_Q, JK_R,
      JK_S, JK_T, JK_U, JK_V, JK_W, JK_X, JK_Y, JK_Z,
      JK_bracketleft, JK_backslash, JK_bracketright, JK_asciicircum,
      JK_underscore, JK_quoteleft,
      JK_a, JK_b, JK_c, JK_d, JK_e, JK_f, JK_g, JK_h, JK_i,
      JK_j, JK_k, JK_l, JK_m, JK_n, JK_o, JK_p, JK_q, JK_r,
      JK_s, JK_t, JK_u, JK_v, JK_w, JK_x, JK_y, JK_z,
      JK_braceleft, JK_bar, JK_braceright, JK_asciitilde,
      JK_127,
      JK_128,
      JK_129,
      JK_130,
      JK_131,
      JK_132,
      JK_133,
      JK_134,
      JK_135,
      JK_136,
      JK_137,
      JK_138,
      JK_139,
      JK_140,
      JK_141,
      JK_142,
      JK_143,
      JK_144,
      JK_145,
      JK_146,
      JK_147,
      JK_148,
      JK_149,
      JK_150,
      JK_151,
      JK_152,
      JK_153,
      JK_154,
      JK_155,
      JK_156,
      JK_157,
      JK_158,
      JK_159,
      JK_160,
      JK_161,
      JK_162,
      JK_163,
      JK_164,
      JK_165,
      JK_166,
      JK_167,
      JK_168,
      JK_169,
      JK_170,
      JK_171,
      JK_172,
      JK_173,
      JK_174,
      JK_175,
      JK_176,
      JK_177,
      JK_178,
      JK_179,
      JK_180,
      JK_181,
      JK_182,
      JK_183,
      JK_184,
      JK_185,
      JK_186,
      JK_187,
      JK_188,
      JK_189,
      JK_190,
      JK_191,
      JK_192,
      JK_193,
      JK_194,
      JK_195,
      JK_196,
      JK_197,
      JK_198,
      JK_199,
      JK_200,
      JK_201,
      JK_202,
      JK_203,
      JK_204,
      JK_205,
      JK_206,
      JK_207,
      JK_208,
      JK_209,
      JK_210,
      JK_211,
      JK_212,
      JK_213,
      JK_214,
      JK_215,
      JK_216,
      JK_217,
      JK_218,
      JK_219,
      JK_220,
      JK_221,
      JK_222,
      JK_223,
      JK_224,
      JK_225,
      JK_226,
      JK_227,
      JK_228,
      JK_229,
      JK_230,
      JK_231,
      JK_232,
      JK_233,
      JK_234,
      JK_235,
      JK_236,
      JK_237,
      JK_238,
      JK_239,
      JK_240,
      JK_241,
      JK_242,
      JK_243,
      JK_244,
      JK_245,
      JK_246,
      JK_247,
      JK_248,
      JK_249,
      JK_250,
      JK_251,
      JK_252,
      JK_253,
      JK_254,
      JK_255,
      JK_ASCIILast = 256,
      JK_WheelUp = 0xFF01,
      JK_WheelDown = 0xFF02,
      JK_BackSpace = 0xFF08,
      JK_Tab = 0xFF09,
      JK_BackTab = 0xFE20,
      JK_Clear = 0xFF9D,
      JK_Return = 0xFF0D,
      JK_Pause = 0xFF13,
      JK_Scroll_Lock = 0xFF14,
      JK_Escape = 0xFF1B,
      JK_Delete = 0xFFFF,
      JK_Home = 0xFF50, JK_Left, JK_Up, JK_Right,
      JK_Down, JK_Prior, JK_Next, JK_End,
      JK_Select = 0xFF60,
      JK_Print = 0xFF61,
      JK_Execute = 0xFF62,
      JK_Insert = 0xFF63,
      JK_Cancel = 0xFF69,
      JK_Help = 0xFF6A,
      JK_Num_Lock = 0xFF7F,
      JK_KP_Enter = 0xFF8D,
      JK_KP_Multiply = 0xFFAA,
      JK_KP_Add,
      JK_KP_Separator,
      JK_KP_Subtract,
      JK_KP_Decimal,
      JK_KP_Divide,
      JK_KP_0 = 0xFFB0, JK_KP_1, JK_KP_2, JK_KP_3,
      JK_KP_4, JK_KP_5, JK_KP_6, JK_KP_7, 
      JK_KP_8, JK_KP_9,
      JK_F1 = 0xFFBE, JK_F2, JK_F3, JK_F4, JK_F5,
      JK_F6, JK_F7, JK_F8, JK_F9, JK_F10,
      JK_F11, JK_F12, JK_F13, JK_F14, JK_F15, JK_F16,
      JK_Shift = 0xFFE1,
      JK_ShiftR = 0xFFE2,
      JK_Control = 0xFFE3,
      JK_ControlR = 0xFFE4,
      JK_Caps_Lock = 0xFFE5,
      JK_Alt = 0xFFE9,
      JK_AltR = 0xFFEA
    };

    enum {
      WINDOW_EVENT = 200,
      WINDOW_DESTROY,
      WINDOW_EXPOSE,
      WINDOW_ICONIFY,
      WINDOW_DEICONIFY,
      WINDOW_MOVED,
      WINDOW_CLOSE_QUERY,
      WINDOW_LAST,
      KEY_EVENT = 300,
      KEY_PRESS,
      KEY_RELEASE,
      KEY_ACTION,
      KEY_LAST,
      GLOBAL_KEY_EVENT = 400,
      GLOBAL_KEY_PRESS,
      GLOBAL_KEY_RELEASE,
      GLOBAL_KEY_ACTION,
      GLOBAL_KEY_LAST,
      MOUSE_EVENT = 500,
      MOUSE_DOWN,
      MOUSE_UP,
      MOUSE_MOVE,
      MOUSE_ENTER,
      MOUSE_EXIT,
      MOUSE_DRAG,
      MOUSE_ACTION,
      MOUSE_LAST,
      GLOBAL_MOUSE_EVENT = 600,
      GLOBAL_MOUSE_DOWN,
      GLOBAL_MOUSE_UP,
      GLOBAL_MOUSE_MOVE,
      GLOBAL_MOUSE_ACTION,
      GLOBAL_MOUSE_LAST,
      SCROLL_EVENT = 700,
      SCROLL_LINE_UP,
      SCROLL_LINE_DOWN,
      SCROLL_PAGE_UP,
      SCROLL_PAGE_DOWN,
      SCROLL_ABSOLUTE,
      SCROLL_LAST,
      LIST_EVENT = 800,
      LIST_SELECT,
      LIST_DESELECT,
      LIST_LAST,
      MIXER_EVENT = 900,
      MIXER_LINE_NOTIFY,
      MIXER_CONTROL_NOTIFY,
      MIXER_LAST,
      MISC_EVENT = 2000,
      ACTION_EVENT,
      LOAD_FILE,
      SAVE_FILE,
      GOT_FOCUS,
      LOST_FOCUS,
      CHILD_NOTIFY,
      PARENT_NOTIFY,
      PEER_NOTIFY,
      DATA_NOTIFY,
      AUX_NOTIFY,
      MISC_LAST
    };

    virtual const char* className() const;
    virtual JObject* clone() const;
    JEvent();
    JEvent(JObject* target, int id, JObject* arg = null);
    JEvent(JObject* target, int id, int x, int y,
      int key, int modifiers, int clickCount = 0, JObject* arg = null);
    void translate(int x, int y);
    boolean shiftDown();
    boolean controlDown();
    boolean metaDown();
    boolean altDown();
    boolean lButtonDown();
    boolean rButtonDown();
    boolean mButtonDown();
    static int VKtoJK(int vk, long info = null);
    static int JKtoVK(int key, boolean& needShift);
    static boolean isNumLock();
    static boolean isScrollLock();
    static boolean isKeyDown(int keycode);
#if !defined(WIN32)
    static void setKeyState(int keycode, boolean state);
    static char keyMap[];
#endif

    JObject *target;
    long when;
    int id;
    int x, y;
    int key;
    int modifiers;
    int clickCount;
    JObject *arg;
};

#endif
