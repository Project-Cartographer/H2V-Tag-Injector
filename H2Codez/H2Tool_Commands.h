#include "stdafx.h"

void _H2ToolAttachHooks();
void _H2ToolDetachHooks();

// Constant '\0' terminated ascii string
typedef const char* cstring;
// '\0\0' terminated unicode string
typedef wchar_t* wstring;
// Constant '\0\0' terminated unicode string
typedef const wchar_t* wcstring;
typedef void (_cdecl* _tool_command_proc)(wcstring arguments);
typedef char long_string[255 + 1];


#define CAST_PTR(type, ptr)		(reinterpret_cast<type>(ptr))
#define CAST_PTR_OP(type)		reinterpret_cast<type>
#define NUMBEROF_C(array) ( sizeof(array) / sizeof( (array)[0] ) )
#define NUMBEROF(array) _countof(array)
#define WIN32_FUNC(func) func
#define FLAG(bit)( 1<<(bit) )
#define BOOST_STATIC_ASSERT( ... ) static_assert(__VA_ARGS__, #__VA_ARGS__)


enum tool_command_argument_type : long {
	_tool_command_argument_type_0,
	_tool_command_argument_type_1,
	_tool_command_argument_type_data_directory,
	_tool_command_argument_type_3,
	_tool_command_argument_type_tag_name,
	_tool_command_argument_type_5,
	_tool_command_argument_type_data_file,
	_tool_command_argument_type_file,			// file system path, not limited to data or tags
	_tool_command_argument_type_real,
	_tool_command_argument_type_string,
	_tool_command_argument_type_10,
	_tool_command_argument_type_radio,			// definition holds choices, separated by '|'
	_tool_command_argument_type_boolean,
	_tool_command_argument_type,
};

struct s_tool_command_argument {
	signed long 	type;
	wcstring        name;
	const char*		definition;
	const char*		help;
};

struct s_tool_command {
	wcstring       					name;
	_tool_command_proc				import_proc;
	const s_tool_command_argument*	arguments;
	int							    argument_count;
	bool							dont_initialize_game;
	unsigned char : 8; unsigned short : 16;
};
struct s_file_reference
{
	unsigned long			signature;
	unsigned short      	flags;
	signed short     		location;
	long_string	            file_name;
	HANDLE		            handle;
	HRESULT		            api_result;
}; 
BOOST_STATIC_ASSERT(sizeof(s_file_reference) == 0x110);

class H2Tool_Extras
{
public:
	void Initialize();
	void AddExtraCommands();
	void Increase_structure_size_Check();

private:
};



