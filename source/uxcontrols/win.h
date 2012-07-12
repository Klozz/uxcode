#if defined(_WIN32)
/* Keyboard keys */
typedef struct UXCONTROLS_KEYBOARD_KEYS {
	unsigned char keys[0xFF];                   //! Array of every key in the keyboard.
} UXCONTROLS_KEYBOARD_KEYS;

/* Keyboard definition */
typedef struct UXCONTROLS_KEYBOARD {
	struct UXCONTROLS_KEYBOARD_KEYS buffer;		//!< Key buffer.
	struct UXCONTROLS_KEYBOARD_KEYS	held;       //!< Keys currently held.
	struct UXCONTROLS_KEYBOARD_KEYS	pressed;    //!< Keys inmediately pressed.
	struct UXCONTROLS_KEYBOARD_KEYS	released;   //!< Keys inmediately released.
} UXCONTROLS_KEYBOARD;

/* Mouse buttons */
typedef struct UXCONTROLS_MOUSE_KEYS {
	struct {
		unsigned char left   : 1;				//!< Left button down
		unsigned char right  : 1;				//!< Center button down
		unsigned char center : 1;				//!< Right button down
		unsigned char res    : 5;               //!< 5-bit extra space.
	};
} UXCONTROLS_MOUSE_KEYS;

/* Mouse definition */
typedef struct UXCONTROLS_MOUSE {
	unsigned int x;                             //!< X mouse position
	unsigned int y;                             //!< Y mouse position
	
	struct UXCONTROLS_MOUSE_KEYS held;          //!< Keys currently held.
	struct UXCONTROLS_MOUSE_KEYS pressed;		//!< Keys inmediately pressed.
	struct UXCONTROLS_MOUSE_KEYS released;		//!< Keys inmediately released.
} UXCONTROLS_MOUSE;
#endif