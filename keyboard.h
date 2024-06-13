enum ButtonState {PRESSED, RELEASED};
enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};	

void KeyboardInit(void);
enum ButtonState ReadButton1(void);
enum KeyboardState eKeyboardRead(void);