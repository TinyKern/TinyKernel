ifneq (,$(findstring xterm,${TERM}))
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED			:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	LIGHT_PURPLE:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	BLUE		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	RESET		:= $(shell tput -Txterm sgr0)
else
	BLACK		:= ""
	RED			:= ""
	GREEN		:= ""
	YELLOW		:= ""
	LIGHT_PURPLE:= ""
	PURPLE		:= ""
	BLUE		:= ""
	WHITE		:= ""
	RESET		:= ""
endif
