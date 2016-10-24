TEMPLATE = subdirs
SUBDIRS = \
	ramcache \

!win32 {
    SUBDIRS += memcache
}
