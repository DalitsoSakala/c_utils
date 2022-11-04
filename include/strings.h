// ASCII value of small letter A (a)
#define SM_A (97)
#define TAB (9)
#define NL (10)
// ASCII value of space
#define SPACE (32)
// Gap between lower case letter and uppercase
#define CS_GAP (32)

// Hyphen character "-"
#define C_HYPHEN (45)

// Underscore char
#define C_UNDERSCORE (95)

enum	space_holder
{
	SPC_UNDERSCORE = 1,
	SPC_MINUS = 3
};

// Converts a C string to a string composed of
// uppercase letters starting each new word.
void	to_name(char *);

// Capitalize the first letter of a string.
void	to_cap(char *);

// Converts string seperated sequence to camel case.
void	to_camel(char *);

// Converts camel case string to a space seperated sequence.
void	from_camel(char *);

// Converts string from camel case replacing the with `spc_replacer`
void	from_camelrp(char *raw, char *spc_replacer);
