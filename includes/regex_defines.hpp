#ifndef REGEX_DEFINES_HPP
# define REGEX_DEFINES_HPP

# define REG_PUSH			"^push ([0-9.intdoublefa\\(\\)]+)$"
# define REG_POP			"^pop$"
# define REG_DUMP			"^dump$"
# define REG_ASSERT		"^assert ([0-9.intdoublefa\\(\\)]+)$"
# define REG_ADD			"^add$"
# define REG_SUB			"^sub$"
# define REG_MUL			"^mul$"
# define REG_DIV			"^div$"
# define REG_MOD			"^mod$"
# define REG_PRINT		"^print$"
# define REG_EXIT			"^exit$"
# define REG_COMMENT	"^;[;]?[^;]+?.*?$|^;$"

# define REG_INT			"^int(8|16|32)\\(([0-9]+)\\)$"
# define REG_DOUBLE		"^double\\(([0-9]+.[0-9])\\)$"

#endif
