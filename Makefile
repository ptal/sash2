# Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
# Permission is granted to use, distribute, or modify this source,
# provided that this copyright notice remains intact.
# 

#
# Makefile for sash
#
# The HAVE_GZIP definition adds the -gzip and -gunzip commands.
# The HAVE_LINUX_ATTR definition adds the -chattr and -lsattr commands.
# The HAVE_LINUX_MOUNT definition makes -mount and -umount work on Linux.
# The HAVE_BSD_MOUNT definition makes -mount and -umount work on BSD.
# The MOUNT_TYPE definition sets the default file system type for -mount.
#
HAVE_GZIP		= 0
HAVE_LINUX_ATTR		= 0
HAVE_LINUX_MOUNT	= 0
HAVE_BSD_MOUNT		= 0
MOUNT_TYPE		= '"ext3"'

CC=g++

CPPFLAGS = -g3 -Wall -Wextra -std=c++11 \
	-DHAVE_GZIP=$(HAVE_GZIP) \
	-DHAVE_LINUX_ATTR=$(HAVE_LINUX_ATTR) \
	-DHAVE_LINUX_MOUNT=$(HAVE_LINUX_MOUNT) \
	-DHAVE_BSD_MOUNT=$(HAVE_BSD_MOUNT) \
	-DMOUNT_TYPE=$(MOUNT_TYPE) \

# jsoncpp should be installed as explained on README-UPMC
LIBS = -lz -ljson

BINDIR = /bin
MANDIR = /usr/man/man1

OBJS = sash.o cmds.o cmd_dd.o cmd_ed.o cmd_grep.o cmd_ls.o cmd_tar.o \
	cmd_gzip.o cmd_find.o cmd_file.o cmd_chattr.o cmd_ar.o utils.o eval-upmc.o \
	arithmetic/evaluator.o arithmetic/parser.o \
        arithmetic/jsonast.o

sash:	$(OBJS)
	$(CC) $(CPPFLAGS) -o sash $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) sash

install: sash
	cp sash $(BINDIR)/sash
	cp sash.1 $(MANDIR)/sash.1

$(OBJS):	sash.h
