DEFINES += SERVER_LIBRARY

include(../../athleticplugin.pri)

QT += network sql

SOURCES += \
	abstractresponder.cpp \
	base64decoder.cpp \
	base64decoder_private.cpp \
	blockingresponder.cpp \
	blockingresponder_private.cpp \
	cache.cpp \
	cachebackend.cpp \
	cacheentry.cpp \
	cacheentryprivate.cpp \
	cacheprivate.cpp \
	caches.cpp \
	clientiodevice.cpp \
	communicationinterface.cpp \
	communicationinterface_worker.cpp \
	database.cpp \
	databaseguard.cpp \
	enumhelpers.cpp \
	filecache.cpp \
	filedependentcache.cpp \
	manager.cpp \
	manager_private.cpp \
	mimemultipartstreamreader.cpp \
	mimemultipartstreamreader_private.cpp \
	mimepartiodevice.cpp \
	mimepartiodevice_private.cpp \
	postdatastreamreader.cpp \
	postdatastreamreaderbackend.cpp \
	prefixmapper.cpp \
	prefixmapper_private.cpp \
	prespawnedspawner.cpp \
	proxyclientiodevice.cpp \
	request.cpp \
	request_private.cpp \
	requestfactory.cpp \
	requestqueue.cpp \
	requestrunner.cpp \
	service.cpp \
	socketflusher.cpp \
	threadedresponder.cpp \
	threadedresponder_private.cpp \
	threadpool.cpp \
	threadpool_worker.cpp \
	urlencodedpostdatastreamreader.cpp  \
	serverplugin.cpp \
    iserviceprefix.cpp \
    uploadedfile.cpp

HEADERS += \
	abstractresponder.h \
	base64decoder.h \
	base64decoder_private.h \
	blockingresponder.h \
	blockingresponder_private.h \
	cache.h \
	cachebackend.h \
	cacheentry.h \
	cacheentryprivate.h \
	cacheprivate.h \
	caches.h \
	clientiodevice.h \
	communicationinterface.h \
	communicationinterface_worker.h \
	database.h \
	databaseguard.h \
	databaseprivate.h \
	enumhelpers.h \
	server_global.h \
	filecache.h \
	filedependentcache.h \
	manager.h \
	manager_private.h \
	memcpy_safe.h \
	mimemultipartstreamreader.h \
	mimemultipartstreamreader_private.h \
	mimepartiodevice.h \
	mimepartiodevice_private.h \
	postdatastreamreader.h \
	postdatastreamreader_private.h \
	postdatastreamreaderbackend.h \
	prefixmapper.h \
	prefixmapper_private.h \
	prespawnedspawner.h \
	proxyclientiodevice.h \
	request.h \
	request_private.h \
	requestfactory.h \
	requestqueue.h \
	requestrunner.h \
	scopedcaller.h \
	service.h \
	service_private.h \
	socketflusher.h \
	threadedresponder.h \
	threadedresponder_private.h \
	threadpool.h \
	threadpool_worker.h \
	urlencodedpostdatastreamreader.h \
	serverplugin.h \
    iserviceprefix.h \
    uploadedfile.h
# abstractmapper.h \
