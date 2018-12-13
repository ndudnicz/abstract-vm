#ifndef REGEX_DEFINES_HPP
# define REGEX_DEFINES_HPP

# define REG_PUSH			"^push ([a-z0-9]+\\(\\-?.+\\))([\\s]{0,}?;.*?)?$"
# define REG_POP			"^pop([\\s]{0,}?;.*?)?$"
# define REG_DUMP			"^dump([\\s]{0,}?;.*?)?$"
# define REG_ASSERT		"^assert ([0-9a-z]+\\(\\-?.+\\))([\\s]{0,}?;.*?)?$"
# define REG_ADD			"^add([\\s]{0,}?;.*?)?$"
# define REG_SUB			"^sub([\\s]{0,}?;.*?)?$"
# define REG_MUL			"^mul([\\s]{0,}?;.*?)?$"
# define REG_DIV			"^div([\\s]{0,}?;.*?)?$"
# define REG_MOD			"^mod([\\s]{0,}?;.*?)?$"
# define REG_PRINT		"^print([\\s]{0,}?;.*?)?$"
# define REG_EXIT			"^exit([\\s]{0,}?;.*?)?$"
# define REG_COMMENT	"^;.*$"

# define REG_INT			"^int(8|16|32)\\((\\-?[0-9]+)\\)$"
# define REG_FLOAT		"^float\\((\\-?[0-9]+(.[0-9]{1,})?)\\)$"
# define REG_DOUBLE		"^double\\((\\-?[0-9]+(.[0-9]{1,})?)\\)$"

#endif
