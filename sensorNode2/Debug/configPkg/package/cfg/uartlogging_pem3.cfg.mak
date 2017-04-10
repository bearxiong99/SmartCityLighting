# invoke SourceDir generated makefile for uartlogging.pem3
uartlogging.pem3: .libraries,uartlogging.pem3
.libraries,uartlogging.pem3: package/cfg/uartlogging_pem3.xdl
	$(MAKE) -f /Users/robbiezuazua/tryNumber2/sensorNode/src/makefile.libs

clean::
	$(MAKE) -f /Users/robbiezuazua/tryNumber2/sensorNode/src/makefile.libs clean

