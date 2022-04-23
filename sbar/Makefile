PREFIX  := /usr/local

# FreeBSD (uncomment)
#LDFLAGS += -L/usr/local/lib -I/usr/local/include
# # OpenBSD (uncomment)
#LDFLAGS += -L/usr/X11R6/lib -I/usr/X11R6/include

all: scripts

scripts:
	mkdir -p ~/.sbar
	cp -f scripts/* ~/.sbar
	chmod +x ~/.sbar/*

install: 
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f sbar ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/sbar

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/sbar

.PHONY: all scripts install uninstall
