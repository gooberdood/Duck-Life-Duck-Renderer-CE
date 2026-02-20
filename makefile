# ----------------------------
# Makefile Options
# ----------------------------

NAME = DUCKLIFE
ICON = icon.png
DESCRIPTION = "A pack of Duck Life games, based on the flash games"
COMPRESSED = YES
COMPRESSED_MODE = zx7
ARCHIVED = YES
PREFER_OS_CRT = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
