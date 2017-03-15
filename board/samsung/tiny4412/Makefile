#
#			2017
# 	Modified by AP0904225 <ap0904225@qq.com>  on the basis of odroid board
#
# Configuration settings for the FriendlyARM TINY4412 (EXYNOS4412) board.
#     FriendlyARM Tiny4412 SDK board hardware version:
#           core board   :  Tiny4412-1412
#          bottom board :  Tiny4412/Super4412SDK 1506
#
# SPDX-License-Identifier:	GPL-2.0+
#

ifdef CONFIG_SPL_BUILD
# necessary to create built-in.o
obj- := __dummy__.o

hostprogs-y := tools/mktiny4412spl
always := $(hostprogs-y)

# omit -O2 option to suppress
#   warning: dereferencing type-punned pointer will break strict-aliasing rules
#
# TODO:
# Fix the root cause in tools/mktiny4412spl.c and delete the following work-around
$(obj)/tools/mktiny4412spl: HOSTCFLAGS:=$(filter-out -O2,$(HOSTCFLAGS))
else
obj-y	+= tiny4412.o
endif
