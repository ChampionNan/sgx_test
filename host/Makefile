# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

include ../../config.mk

CFLAGS=$(shell pkg-config oehost-$(COMPILER) --cflags)
LDFLAGS=$(shell pkg-config oehost-$(COMPILER) --libs)
INCDIR=$(shell pkg-config oehost-$(COMPILER) --variable=includedir)

build:
	@ echo "Compilers used: $(CC), $(CXX)"
	oeedger8r ../sgx_test.edl --untrusted \
		--search-path $(INCDIR) \
		--search-path $(INCDIR)/openenclave/edl/sgx
	$(CXX) -g -c $(CFLAGS) host.cpp
	$(CC) -g -c $(CFLAGS) sgx_test_u.c
	$(CXX) -o sgx_test_host sgx_test_u.o host.o $(LDFLAGS)

clean:
	rm -f sgx_test_host host.o sgx_test_u.o sgx_test_u.c sgx_test_u.h sgx_test_args.h