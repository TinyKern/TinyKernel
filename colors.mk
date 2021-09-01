#* file Makefile
#* author Owen Boreham (owenkadeboreham@gmail.com)
#* version 0.1.8
#* date 2021-07-08
#* 
#* Copyright (c) 2021 TinyKernel
#* This file is part of TinyKernel which is released
#* under Apache License 2.0.  See file LICENSE or go
#* to https://www.apache.org/licenses/LICENSE-2.0 for
#* full license details.

ifneq (,$(findstring xterm,${TERM}))
	BLACK			= $(shell tput -Txterm setaf 0)
	RED				= $(shell tput -Txterm setaf 1)
	GREEN			= $(shell tput -Txterm setaf 2)
	YELLOW			= $(shell tput -Txterm setaf 3)
	LIGHT_PURPLE	= $(shell tput -Txterm setaf 4)
	PURPLE			= $(shell tput -Txterm setaf 5)
	BLUE			= $(shell tput -Txterm setaf 6)
	WHITE			= $(shell tput -Txterm setaf 7)
	RESET			= $(shell tput -Txterm sgr0)
else
	BLACK			= ""
	RED				= ""
	GREEN			= ""
	YELLOW			= ""
	LIGHT_PURPLE	= ""
	PURPLE			= ""
	BLUE			= ""
	WHITE			= ""
	RESET			= ""
endif
